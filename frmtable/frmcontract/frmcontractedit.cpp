#include "frmcontractedit.h"
#include "gbstoolfunctions.h"
#include "ui_frmcontractedit.h"
#include <QCompleter>
#include <QDateTime>

FrmContractEdit::FrmContractEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmContractEdit),
    m_number(0)
{
    ui->setupUi(this);
    m_editStatus = "add";
    initForm();
}

FrmContractEdit::~FrmContractEdit()
{
    delete ui;
}

void FrmContractEdit::initForm()
{
    ui->editContractNumber->setPlaceholderText("必须填写");
    ui->dateEditEnd->setDate(QDate::currentDate());
    ui->dateEditStart->setDate(QDate::currentDate());
}

void FrmContractEdit::setEditType(const QString type)
{
    if(type == "add"){
        ui->labTitle->setText("仓库添加");
        ui->btnEdit->setText("保存");
        m_editStatus = "add";
    }else if(type == "alter"){
        ui->labTitle->setText("仓库修改");
        ui->btnEdit->setText("修改");
        m_editStatus = "alter";
    }
}

void FrmContractEdit::setDetailData(const QStringList &detail)
{
    m_detailData = detail;
}

void FrmContractEdit::deleteRowData(const QStringList &detail)
{
    m_number = detail.at(0).toInt();
    editRoleData("delete");
}

void FrmContractEdit::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    QTimer::singleShot(10,this,&FrmContractEdit::onEventShowDetail);
}

void FrmContractEdit::onEventShowDetail()
{
    setGrainTypeCombox();
    setContractTypeCombox();
    setSupplierCombox();
    setTransportCompanyCombox();
    setPayTypeCombox();
    setValuationCombox();
    setBankTypeCombox();
    if(m_editStatus == "alter"){
//        Q_ASSERT(m_detailData.size() == 6);
        m_number = m_detailData.at(0).toInt();
        ui->editContractNumber->setText(m_detailData.at(1));
        ui->cbxContractType->setCurrentText(m_detailData.at(2));
        ui->cbxGrainType->setCurrentText(m_detailData.at(3));
        ui->dateEditStart->setDateTime(QDateTime::fromString(m_detailData.at(4), "yyyy-MM-dd hh:mm:ss"));
        ui->dateEditEnd->setDateTime(QDateTime::fromString(m_detailData.at(5), "yyyy-MM-dd hh:mm:ss"));
        ui->editOrder->setText(m_detailData.at(6));
        ui->cbxSupplier->setCurrentText(m_detailData.at(7));
        ui->cbxTransport->setCurrentText(m_detailData.at(8));
        ui->editSource->setText(m_detailData.at(9));
        ui->dbSpinBoxTotal->setValue(m_detailData.at(10).toDouble());
        ui->dbSpinBoxConmpleted->setValue(m_detailData.at(11).toDouble());
        ui->cbxIsComplete->setChecked(m_detailData.at(12).toInt());
        ui->editTransportID->setText(m_detailData.at(13));
        ui->editWagonID->setText(m_detailData.at(14));
        ui->cbxPayType->setCurrentText(m_detailData.at(15));
        ui->cbxBankType->setCurrentText(m_detailData.at(16));
        ui->editBankID->setText(m_detailData.at(17));
        ui->cbxValuation->setCurrentText(m_detailData.at(18));
        ui->editContacts->setText(m_detailData.at(19));
        ui->editPhone->setText(m_detailData.at(20));
        ui->editMark->setText(m_detailData.at(21));
        qDebug()<<"银行类型:"<<ui->cbxBankType->currentData().toString();
    }
}

bool FrmContractEdit::checkFrmEditData()
{
    if(ui->editContractNumber->text().isEmpty()){
        QMessageBox::warning(NULL,"系统提示","合同号码不能为空","确定");
        return false;
    }
    return true;
}

void FrmContractEdit::editRoleData(QString editStatus)
{
    if(editStatus != "delete"){
        if(!checkFrmEditData()){
            return;
        }
    }
    //创建回话
    GbsSession session;
    session.addRequestData("Cmd",CmdEditContract);
    session.addRequestData("Sender","Admin");
    session.addRequestData("Operation",editStatus);
    session.addRequestData("Number",QString::number(m_number));
    session.addRequestData("ContractNum",ui->editContractNumber->text());
    session.addRequestData("ContractType",ui->cbxContractType->currentData().toString());
    session.addRequestData("GrainType",ui->cbxGrainType->currentData().toString());
    session.addRequestData("Start",ui->dateEditStart->text());
    session.addRequestData("End",ui->dateEditEnd->text());
    session.addRequestData("OrderID",ui->editOrder->text());
    session.addRequestData("Supplier",ui->cbxSupplier->currentData().toString());
    session.addRequestData("TransCompany",ui->cbxTransport->currentData().toString());
    session.addRequestData("Source",ui->editSource->text());
    session.addRequestData("Total",QString::number(ui->dbSpinBoxTotal->value()));
    session.addRequestData("Complete",QString::number(ui->dbSpinBoxTotal->value()));
    session.addRequestData("TransportNum",ui->editTransportID->text());
    session.addRequestData("WagaonNum",ui->editWagonID->text());
    session.addRequestData("PayType",ui->cbxPayType->currentData().toString());
    session.addRequestData("BankType",ui->cbxBankType->currentData().toString());
    session.addRequestData("BankNum",ui->editBankID->text());
    session.addRequestData("Contact",ui->editContacts->text());
    session.addRequestData("ContactPhone",ui->editPhone->text());
    session.addRequestData("IsComplete",QString::number(ui->cbxIsComplete->isChecked()));
    session.addRequestData("Remark",ui->editMark->text());
    session.addRequestData("Valuation",ui->cbxValuation->currentData().toString());
    //把回话传递给服务管理器,服务管理器内部会根据回话内容选择一个合适的服务接口与服务器通讯
    Singleton<ServiceManager>::Instance().doAction(session);
    //调用返回,判断回话的应答标志
    if(session.getErrNo() == 0){
        this->done(0);
    }else{
        QMessageBox::warning(NULL,"系统提示",session.getLastErrString(),"确定");
    }
}

void FrmContractEdit::setGrainTypeCombox()
{
    GbsToolFunctions::setComboxItem(CmdQueryGrainType,ui->cbxGrainType);
}

void FrmContractEdit::setContractTypeCombox()
{
    GbsToolFunctions::setComboxItem(CmdQueryContractType,ui->cbxContractType);
}

void FrmContractEdit::setSupplierCombox()
{
    GbsToolFunctions::setComboxItem(CmdQuerySupplier,ui->cbxSupplier);
}

void FrmContractEdit::setTransportCompanyCombox()
{
    GbsToolFunctions::setComboxItem(CmdQueryTransport,ui->cbxTransport);
}

void FrmContractEdit::setPayTypeCombox()
{
    GbsToolFunctions::setComboxItem(CmdQueryPaymenttype,ui->cbxPayType);
}

void FrmContractEdit::setValuationCombox()
{
    GbsToolFunctions::setComboxItem(CmdQueryValuation,ui->cbxValuation);
}

void FrmContractEdit::setBankTypeCombox()
{
    GbsToolFunctions::setComboxItem(CmdQueryBankType,ui->cbxBankType);
}

void FrmContractEdit::on_btnEdit_clicked()
{
    editRoleData(m_editStatus);
}


void FrmContractEdit::on_btnEdit_2_clicked()
{
    reject();
}
