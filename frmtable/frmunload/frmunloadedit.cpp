#include "frmunloadedit.h"
#include "gbstoolfunctions.h"
#include "ui_frmunloadedit.h"

FrmUnloadEdit::FrmUnloadEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmUnloadEdit),
    m_number(0)
{
    ui->setupUi(this);
    m_editStatus = "add";
}

FrmUnloadEdit::~FrmUnloadEdit()
{
    delete ui;
}

void FrmUnloadEdit::setEditType(const QString type)
{
    if(type == "alter"){
        ui->labTitle->setText("卸粮信息修改");
        ui->btnEdit->setText("修改");
        m_editStatus = "alter";
    }
}

void FrmUnloadEdit::setDetailData(const QStringList &detail)
{
    m_detailData = detail;
}

void FrmUnloadEdit::deleteRowData(const QStringList &detail)
{
    m_number = detail.at(0).toInt();
    editData("delete");
}

void FrmUnloadEdit::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QTimer::singleShot(10,this,&FrmUnloadEdit::onEventShowDetail);
}

void FrmUnloadEdit::onEventShowDetail()
{
    GbsToolFunctions::setComboxItem(CmdQueryWarehouse,ui->cbxWareHouse);
    if(m_editStatus == "alter"){
        m_number = m_detailData.at(0).toInt();
        ui->editLicense->setText(m_detailData.at(1));
        ui->cbxWareHouse->setCurrentText(m_detailData.at(2));
        ui->doubleSpinBox->setValue(m_detailData.at(3).toDouble());
        ui->textEdit->append(m_detailData.at(4));
    }
}

bool FrmUnloadEdit::checkFrmEditData()
{
    return true;
}

void FrmUnloadEdit::editData(QString editStatus)
{
    if(editStatus != "delete"){
        if(!checkFrmEditData()){
            return;
        }
    }
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdEditUnload);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number",QString::number(m_number));
    session.addRequestData("WareHouseID",ui->cbxWareHouse->currentData().toString()); // 查询时获得的登记编号
    session.addRequestData("TakeCount",QString::number(ui->doubleSpinBox->value()));
    session.addRequestData("Remarks",ui->textEdit->toPlainText());
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        this->done(0);
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

void FrmUnloadEdit::on_btnEdit_clicked()
{
    editData(m_editStatus);
}
