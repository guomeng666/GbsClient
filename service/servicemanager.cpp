#include "servicemanager.h"
#include "queryroletable.h"
#include "querypermission.h"
#include "querydepartment.h"
#include "queryuser.h"
#include "editpersission.h"
#include "editdeparment.h"
#include "editrole.h"
#include "edituser.h"
#include "editvehicletype.h"
#include "queryvehicletype.h"
#include "queryvehicle.h"
#include "editvehicle.h"
#include "querywarehouse.h"
#include "editwarehouse.h"
#include "querybanktype.h"
#include "editbanktype.h"
#include "editseller.h"
#include "queryseller.h"
#include "querysupplier.h"
#include "editsupplier.h"
#include "edittransport.h"
#include "querytransport.h"
#include "querypaymenttype.h"
#include "editpaymenttype.h"
#include "querypacktype.h"
#include "editpacktype.h"
#include "querygraintype.h"
#include "editgraintype.h"
#include "querysampleclass.h"
#include "editsampleclass.h"
#include "querycontracttype.h"
#include "editcontracttype.h"
#include "queryprocedurenode.h"
#include "editprocedurenode.h"
#include "editpurchase.h"
#include "querypurchase.h"
#include "editvaluation.h"
#include "queryvaluation.h"
#include "editcontract.h"
#include "querycontract.h"
#include "queryregister.h"
#include "editregister.h"
#include "querysellerbyidentityid.h"
#include "querypicture.h"

ServiceManager::ServiceManager(QObject *parent) : QObject(parent)
{
    m_servicesMap[CmdQueryVehicleType] = new QueryVehicleType;
    m_servicesMap[CmdEditVehicleType] = new EditVehicleType;
    m_servicesMap[CmdQuerPermission] = new QueryPermission;
    m_servicesMap[CmdEditPermission] = new EditPersission;
    m_servicesMap[CmdQueryRoel] = new QueryRoleTable;
    m_servicesMap[CmdEditRole] = new EditRole;
    m_servicesMap[CmdQueryDepartment] = new QueryDepartment;
    m_servicesMap[CmdEditDepartment] = new EditDeparment;
    m_servicesMap[CmdQueryUser] = new QueryUser;
    m_servicesMap[CmdEditUser] = new EditUser;
    m_servicesMap[CmdQueryVehicle] = new QueryVehicle;
    m_servicesMap[CmdEditVehicle] = new EditVehicle;
    m_servicesMap[CmdQueryWarehouse] = new QueryWarehouse;
    m_servicesMap[CmdEditWarehouse] = new EditWarehouse;
    m_servicesMap[CmdQueryBankType] = new QueryBankType;
    m_servicesMap[CmdEditBankType] = new EditBankType;
    m_servicesMap[CmdQuerySeller] = new QuerySeller;
    m_servicesMap[CmdEditSeller] = new EditSeller;
    m_servicesMap[CmdQuerySupplier] = new QuerySupplier;
    m_servicesMap[CmdEditSupplier] = new EditSupplier;
    m_servicesMap[CmdQueryTransport] = new QueryTransport;
    m_servicesMap[CmdEditTransport] = new EditTransport;
    m_servicesMap[CmdQueryPaymenttype] = new QueryPaymenttype;
    m_servicesMap[CmdEditPaymenttype] = new EditPaymenttype;
    m_servicesMap[CmdQueryPackType] = new QueryPackType;
    m_servicesMap[CmdEditPackType] = new EditPackType;
    m_servicesMap[CmdQueryGrainType] = new QueryGrainType;
    m_servicesMap[CmdEditGrainType] = new EditGrainType;
    m_servicesMap[CmdQuerySampleClass] = new QuerySampleClass;
    m_servicesMap[CmdEditSampleClass] = new EditSampleClass;
    m_servicesMap[CmdQueryContractType] = new QueryContractType;
    m_servicesMap[CmdEditContractType] = new EditContractType;
    m_servicesMap[CmdQueryProcedureNode] = new QueryProcedureNode;
    m_servicesMap[CmdEditProcedureNode] = new EditProcedureNode;
    m_servicesMap[CmdQueryPurchase] = new QueryPurchase;
    m_servicesMap[CmdEditPurchase] = new EditPurchase;
    m_servicesMap[CmdQueryValuation] = new QueryValuation;
    m_servicesMap[CmdEditValuation] = new EditValuation;
    m_servicesMap[CmdQueryContract] = new QueryContract;
    m_servicesMap[CmdEditContract] = new EditContract;
    m_servicesMap[CmdQueryRegister] = new QueryRegister;
    m_servicesMap[CmdEditRegister] = new EditRegister;
    m_servicesMap[CmdQuerySellerByIdentityID] = new QuerySellerByIdentityID;
    m_servicesMap[CmdQueryPicture] = new QueryPicture;
}

ServiceManager::~ServiceManager()
{

}

bool ServiceManager::doAction(GbsSession &session)
{
    //通过服务管理器选择正确的服务,然后处理回话
    QString cmd = session.getCmd();
    if (m_servicesMap.find(cmd) != m_servicesMap.end()){
        m_servicesMap[cmd]->Execute(session);
        return true;
    }
    return false;
}
