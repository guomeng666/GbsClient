#include "frmvaluationedit.h"
#include "frmvaluationlist.h"
#include "serialize.h"
#include "ui_frmvaluationedit.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

FrmValuationEdit::FrmValuationEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmValuationEdit),
    m_number(0)
{
    ui->setupUi(this);
    initForm();
    m_editStatus = "add";
}

FrmValuationEdit::~FrmValuationEdit()
{
    delete ui;
}

void FrmValuationEdit::initForm()
{
    m_waterRule       = new FrmValuationList(this);
    m_waterRule->setTitleText("水分扣重规则");
    m_weightRule      = new FrmValuationList(this);
    m_weightRule->setTitleText("容重扣重规则");
    m_impurityRule    = new FrmValuationList(this);
    m_impurityRule->setTitleText("杂质扣重规则");
    m_sideImpurityRule= new FrmValuationList(this);
    m_sideImpurityRule->setTitleText("并肩杂扣重规则");
    m_mildewRule      = new FrmValuationList(this);
    m_mildewRule->setTitleText("霉变扣重规则");
    m_brokenRule      = new FrmValuationList(this);
    m_brokenRule->setTitleText("破碎扣重规则");
    m_heatHarmRule    = new FrmValuationList(this);
    m_heatHarmRule->setTitleText("热损扣重规则");
    m_listWidget<<m_waterRule<<m_weightRule<<m_impurityRule<<m_sideImpurityRule\
              <<m_mildewRule<<m_brokenRule<<m_heatHarmRule;

    ui->panelWidger->setWidget(m_listWidget,4);
}


void FrmValuationEdit::setEditType(const QString type)
{
    if(type == "add"){
        ui->labTitle->setText("计价方式添加");
        ui->btnEdit->setText("保存");
        m_editStatus = "add";
    }else if(type == "alter"){
        ui->labTitle->setText("计价方式修改");
        ui->btnEdit->setText("修改");
        m_editStatus = "alter";
    }
}

void FrmValuationEdit::setDetailData(const QStringList &detail)
{
    m_detailData = detail;
}

void FrmValuationEdit::deleteRowData(const QStringList &detail)
{
    m_number = detail.at(0).toInt();
    editRoleData("delete");
}

void FrmValuationEdit::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QTimer::singleShot(10,this,&FrmValuationEdit::onEventShowDetail);
}

void FrmValuationEdit::onEventShowDetail()
{
    if(m_editStatus == "alter"){
        //Q_ASSERT(m_detailData.size() == 10);
        qDebug()<<m_detailData.size();
        m_number = m_detailData.at(0).toInt();
        ui->editName->setText(m_detailData.at(1));
        ui->doubleSpinBox->setValue(m_detailData.at(2).toDouble());
        ui->checkBox->setChecked(m_detailData.at(3).toInt());
        ui->lineEdit_2->setText(m_detailData.at(5));
        QByteArray jsonData = m_detailData.at(4).toLatin1();
        showDetailRules(jsonData);
    }
}

bool FrmValuationEdit::checkFrmEditData()
{
    if(ui->editName->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","计价名字不能为空","确定");
        return false;
    }
    if(ui->doubleSpinBox->value() <= 0){
        QMessageBox::warning(NULL,"系统提示","单价不能为0.0","确定");
        return false;
    }
    for(int i = 0; i < m_listWidget.count(); ++i){
        FrmValuationList *frm = (FrmValuationList *)m_listWidget.at(i);
        if(frm->getRuleCount() == 0){
            QMessageBox::warning(NULL,"系统提示",frm->getTitleText()+"至少需要一条收购规则!","确定");
            return false;
        }
    }
    return true;
}

void FrmValuationEdit::editRoleData(QString editStatus)
{
    if(editStatus != "delete"){
        if(!checkFrmEditData()){
            return;
        }
    }
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdEditValuation);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number",QString::number(m_number));
    session.addRequestData("Name",ui->editName->text());
    session.addRequestData("Price",QString::number(ui->doubleSpinBox->value()));
    session.addRequestData("Default",QString::number(ui->checkBox->isChecked()));
    session.addRequestData("Marks",ui->lineEdit_2->text());
    session.addRequestData("Detail",m_jsonData);
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        this->done(0);
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

/**
 * 测试代码
    foreach (QByteArray rule, listRules) {
        Serialize in(&rule);
        QString a,b,c,d,e,f;
        in>>a>>b>>c>>d>>e>>f;
        qDebug()<<a<<b<<c<<d<<e<<f;
    }
*/

void FrmValuationEdit::on_btnEdit_clicked()
{
    QJsonDocument doc;
    QJsonObject root;
    QJsonObject tempJson;
    QList<QByteArray> listRules;
    QStringList ruleNames;
    if(!checkFrmEditData()) return;
    ruleNames<<"Water"<<"Cubage"<<"Impurity"<<"SideImpurity"\
              <<"MildewRule"<<"Broken"<<"HeatHarm";
    for(int i = 0; i < ruleNames.count(); ++i){
        FrmValuationList *frm = (FrmValuationList *)m_listWidget.at(i);
        listRules = frm->getListItemData();
        tempJson = generateJsonObject(listRules);
        root.insert(ruleNames.at(i),QJsonValue(tempJson));
    }
    doc.setObject(root);
    m_jsonData = doc.toJson(QJsonDocument::Compact);
    qDebug()<<m_jsonData;
    editRoleData(m_editStatus);
}

QJsonObject FrmValuationEdit::generateJsonObject(QList<QByteArray> &listRules)
{
    QJsonObject ruleObj;
    QJsonArray rejectJsonArray;
    QJsonArray ruleJsonArray;
    int rejectCnt = 0;
    int ruleCnt = 0;
    foreach (QByteArray rule, listRules) {
        Serialize in(&rule);
        QString type;
        //获取规则类型
        in >> type;
        if(type == "rule"){
            QJsonObject detailValue;
            QString symbol, min , symbol2, max, ration;
            in >> symbol >> min >> symbol2 >> max >> ration;
            detailValue.insert("GreateSymbol",QJsonValue(symbol));
            detailValue.insert("Min",QJsonValue(min));
            detailValue.insert("LessSymbol",QJsonValue(symbol2));
            detailValue.insert("Max",QJsonValue(max));
            detailValue.insert("Ratio",QJsonValue(ration));
            ruleJsonArray.append(QJsonValue(detailValue));
            ruleCnt++;
        }else if(type == "reject"){
            QString value;
            in >> value;
            rejectJsonArray.append(QJsonValue(value));
            rejectCnt++;
        }
    }
    ruleObj.insert("ReJectCount",QJsonValue(rejectCnt));
    ruleObj.insert("RuleCount",QJsonValue(ruleCnt));
    ruleObj.insert("Rejects",QJsonValue(rejectJsonArray));
    ruleObj.insert("Rules",QJsonValue(ruleJsonArray));
    return ruleObj;
}

void FrmValuationEdit::showDetailRules(QByteArray &json)
{
    qDebug()<<json;
    QJsonDocument doc;
    QJsonObject root;
    doc = QJsonDocument::fromJson(json);
    root = doc.object();
    QStringList ruleNames;
    ruleNames<<"Water"<<"Cubage"<<"Impurity"<<"SideImpurity"\
              <<"MildewRule"<<"Broken"<<"HeatHarm";
    for(int i = 0; i < ruleNames.count(); ++i){
        QJsonObject temp = root.value(ruleNames.at(i)).toObject();
        int rejectCount = temp.value("ReJectCount").toInt();
        int ruleCount = temp.value("RuleCount").toInt();
        qDebug()<<"rejectCount:"<<rejectCount<<"ruleCount:"<<ruleCount;
        QJsonArray rejectArray = temp.value("Rejects").toArray();
        QJsonArray ruleArray = temp.value("Rules").toArray();
        FrmValuationList *frm = (FrmValuationList *)m_listWidget.at(i);
        for(int i = 0; i < rejectCount; ++i){
            QByteArray itemData;
            Serialize out(&itemData);
            out <<"reject"<<rejectArray.at(i).toString();
            frm->setRuleItem(itemData);
        }
        for(int i = 0; i < ruleCount; ++i){
            QByteArray itemData;
            Serialize out(&itemData);
            QJsonObject rule = ruleArray.at(i).toObject();
            out <<"rule"<< rule.value("GreateSymbol").toString()<<rule.value("Min").toString()\
                <<rule.value("LessSymbol").toString()<<rule.value("Max").toString()\
                <<rule.value("Ratio").toString();
            frm->setRuleItem(itemData);
        }
    }
}


void FrmValuationEdit::on_btnReturn_clicked()
{
    reject();
}
