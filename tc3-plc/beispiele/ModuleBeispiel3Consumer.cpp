///////////////////////////////////////////////////////////////////////////////
// ModuleBeispiel3Consumer.cpp
#include "TcPch.h"
#pragma hdrstop

#include "ModuleBeispiel3Consumer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
DEFINE_THIS_FILE()

///////////////////////////////////////////////////////////////////////////////
// CModuleBeispiel3Consumer
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Collection of interfaces implemented by module CModuleBeispiel3Consumer
BEGIN_INTERFACE_MAP(CModuleBeispiel3Consumer)
	INTERFACE_ENTRY_ITCOMOBJECT()
	INTERFACE_ENTRY(IID_ITcADI, ITcADI)
	INTERFACE_ENTRY(IID_ITcWatchSource, ITcWatchSource)
///<AutoGeneratedContent id="InterfaceMap">
	INTERFACE_ENTRY(IID_ITcCyclic, ITcCyclic)
///</AutoGeneratedContent>
END_INTERFACE_MAP()


IMPLEMENT_ITCOMOBJECT(CModuleBeispiel3Consumer)
IMPLEMENT_ITCOMOBJECT_SETSTATE_LOCKOP2(CModuleBeispiel3Consumer)
IMPLEMENT_ITCADI(CModuleBeispiel3Consumer)
IMPLEMENT_ITCWATCHSOURCE(CModuleBeispiel3Consumer)

///////////////////////////////////////////////////////////////////////////////
// Set parameters of CModuleBeispiel3Consumer 
BEGIN_SETOBJPARA_MAP(CModuleBeispiel3Consumer)
	SETOBJPARA_DATAAREA_MAP()
///<AutoGeneratedContent id="SetObjectParameterMap">
	SETOBJPARA_VALUE(PID_TcTraceLevel, m_TraceLevelMax)
	SETOBJPARA_ITFPTR(PID_Ctx_TaskOid, m_spCyclicCaller)
	SETOBJPARA_ITFPTR(PID_ModuleBeispiel3ConsumerIPFancyService, m_spIPFancyService)
///</AutoGeneratedContent>
END_SETOBJPARA_MAP()

///////////////////////////////////////////////////////////////////////////////
// Get parameters of CModuleBeispiel3Consumer 
BEGIN_GETOBJPARA_MAP(CModuleBeispiel3Consumer)
	GETOBJPARA_DATAAREA_MAP()
///<AutoGeneratedContent id="GetObjectParameterMap">
	GETOBJPARA_VALUE(PID_TcTraceLevel, m_TraceLevelMax)
	GETOBJPARA_ITFPTR(PID_Ctx_TaskOid, m_spCyclicCaller)
	GETOBJPARA_ITFPTR(PID_ModuleBeispiel3ConsumerIPFancyService, m_spIPFancyService)
///</AutoGeneratedContent>
END_GETOBJPARA_MAP()

///////////////////////////////////////////////////////////////////////////////
// Get watch entries of CModuleBeispiel3Consumer
BEGIN_OBJPARAWATCH_MAP(CModuleBeispiel3Consumer)
	OBJPARAWATCH_DATAAREA_MAP()
///<AutoGeneratedContent id="ObjectParameterWatchMap">
///</AutoGeneratedContent>
END_OBJPARAWATCH_MAP()

///////////////////////////////////////////////////////////////////////////////
// Get data area members of CModuleBeispiel3Consumer
BEGIN_OBJDATAAREA_MAP(CModuleBeispiel3Consumer)
///<AutoGeneratedContent id="ObjectDataAreaMap">
	OBJDATAAREA_VALUE(ADI_ModuleBeispiel3ConsumerData, m_Data)
///</AutoGeneratedContent>
END_OBJDATAAREA_MAP()


///////////////////////////////////////////////////////////////////////////////
CModuleBeispiel3Consumer::CModuleBeispiel3Consumer()
	: m_Trace(m_TraceLevelMax, m_spSrv)
	, m_Counter(0)
{
///<AutoGeneratedContent id="MemberInitialization">
	m_TraceLevelMax = tlAlways;
	memset(&m_Data, 0, sizeof(m_Data));
///</AutoGeneratedContent>
}

///////////////////////////////////////////////////////////////////////////////
CModuleBeispiel3Consumer::~CModuleBeispiel3Consumer() 
{
}


///////////////////////////////////////////////////////////////////////////////
// State Transitions 
///////////////////////////////////////////////////////////////////////////////
IMPLEMENT_ITCOMOBJECT_SETOBJSTATE_IP_PI(CModuleBeispiel3Consumer)

///////////////////////////////////////////////////////////////////////////////
// State transition from PREOP to SAFEOP
//
// Initialize input parameters 
// Allocate memory
HRESULT CModuleBeispiel3Consumer::SetObjStatePS(PTComInitDataHdr pInitData)
{
	m_Trace.Log(tlVerbose, FENTERA);

	HRESULT hr = S_OK;
	IMPLEMENT_ITCOMOBJECT_EVALUATE_INITDATA(pInitData);

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// State transition from SAFEOP to OP
//
// Register with other TwinCAT objects
HRESULT CModuleBeispiel3Consumer::SetObjStateSO()
{
	m_Trace.Log(tlVerbose, FENTERA);
	HRESULT hr = S_OK;

	// Muss manuell eingefügt werden
	hr = FAILED(hr) ? hr : m_spSrv->TcQuerySmartObjectInterface(m_spIPFancyService);

	// If following call is successful the CycleUpdate method will be called, 
	// possibly even before this method has been left.
	hr = FAILED(hr) ? hr : AddModuleToCaller(); 

	// Cleanup if transition failed at some stage
	if ( FAILED(hr) )
	{
		RemoveModuleFromCaller(); 
	}
	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// State transition from OP to SAFEOP
HRESULT CModuleBeispiel3Consumer::SetObjStateOS()
{
	m_Trace.Log(tlVerbose, FENTERA);
	HRESULT hr = S_OK;

	RemoveModuleFromCaller(); 

	// interface pointer referenz muss entfernt werden
	m_spIPFancyService = NULL;

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// State transition from SAFEOP to PREOP
HRESULT CModuleBeispiel3Consumer::SetObjStateSP()
{
	m_Trace.Log(tlVerbose, FENTERA);
	HRESULT hr = S_OK;

	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///<AutoGeneratedContent id="ImplementationOf_ITcCyclic">
HRESULT CModuleBeispiel3Consumer::CycleUpdate(ITcTask* ipTask, ITcUnknown* ipCaller, ULONG_PTR context)
{
	HRESULT hr = S_OK;

	m_Counter++;
	if ((m_Counter % 100) == 0)
	{
		m_spIPFancyService->GetFancyData(&m_Data.FancyData);
		m_Trace.Log(tlAlways, FLEAVEA "FancyData Id=%d Value=%d", m_Data.FancyData.Id, m_Data.FancyData.Value);
	}

	return hr;
}
///</AutoGeneratedContent>

///////////////////////////////////////////////////////////////////////////////
HRESULT CModuleBeispiel3Consumer::AddModuleToCaller()
{
	m_Trace.Log(tlVerbose, FENTERA);
	HRESULT hr = S_OK;
	if ( m_spCyclicCaller.HasOID() )
	{
		if ( SUCCEEDED_DBG(hr = m_spSrv->TcQuerySmartObjectInterface(m_spCyclicCaller)) )
		{
			if ( FAILED(hr = m_spCyclicCaller->AddModule(m_spCyclicCaller, THIS_CAST(ITcCyclic))) )
			{
				m_spCyclicCaller = NULL;
			}
		}
	}
	else
	{
		hr = ADS_E_INVALIDOBJID; 
		SUCCEEDED_DBGT(hr, "Invalid OID specified for caller task");
	}
	m_Trace.Log(tlVerbose, FLEAVEA "hr=0x%08x", hr);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
VOID CModuleBeispiel3Consumer::RemoveModuleFromCaller()
{
	m_Trace.Log(tlVerbose, FENTERA);
	if ( m_spCyclicCaller )
	{
		m_spCyclicCaller->RemoveModule(m_spCyclicCaller);
	}
	m_spCyclicCaller	= NULL;
	m_Trace.Log(tlVerbose, FLEAVEA);
}

