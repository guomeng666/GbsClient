#include "frmselledit.h"
#include "ui_frmselledit.h"

FrmSellEdit::FrmSellEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmSellEdit),
    m_number(0)
{
    ui->setupUi(this);
    m_editStatus = "add";
}

FrmSellEdit::~FrmSellEdit()
{
    delete ui;
}

void FrmSellEdit::setEditType(const QString type)
{
    if(type == "alter"){
        ui->labTitle->setText("售粮信息修改");
        ui->btnEdit->setText("修改");
        m_editStatus = "alter";
    }
}

void FrmSellEdit::setDetailData(const QStringList &detail)
{
    m_detailData = detail;
}

void FrmSellEdit::deleteRowData(const QStringList &detail)
{
    m_number = detail.at(0).toInt();
    editData("delete");
}

void FrmSellEdit::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QTimer::singleShot(10,this,&FrmSellEdit::onEventShowDetail);
}

void FrmSellEdit::onEventShowDetail()
{
    if(m_editStatus == "alter"){
        m_number = m_detailData.at(0).toInt();
        ui->editLicense->setText(m_detailData.at(1));
        ui->comboBox->setCurrentText(m_detailData.at(2));
    }
}

bool FrmSellEdit::checkFrmEditData()
{
    return true;
}

void FrmSellEdit::editData(QString editStatus)
{
    if(editStatus != "delete"){
        if(!checkFrmEditData()){
            return;
        }
    }
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdSellGrain);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number",QString::number(m_number));
    session.addRequestData("ProcedureNum","");
    session.addRequestData("Sell",QString::number(ui->comboBox->currentIndex()));
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        this->done(0);
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

void FrmSellEdit::on_btnEdit_clicked()
{
    editData(m_editStatus);
}
