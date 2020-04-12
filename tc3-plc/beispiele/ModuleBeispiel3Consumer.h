///////////////////////////////////////////////////////////////////////////////
// ModuleBeispiel3Consumer.h
#pragma once

#include "beispieleInterfaces.h"

class CModuleBeispiel3Consumer 
	: public ITComObject
	, public ITcADI
	, public ITcWatchSource
///<AutoGeneratedContent id="InheritanceList">
	, public ITcCyclic
///</AutoGeneratedContent>
{
public:
	DECLARE_IUNKNOWN()
	DECLARE_IPERSIST(CID_beispieleCModuleBeispiel3Consumer)
	DECLARE_ITCOMOBJECT_LOCKOP()
	DECLARE_ITCADI()
	DECLARE_ITCWATCHSOURCE()
	DECLARE_OBJPARAWATCH_MAP()
	DECLARE_OBJDATAAREA_MAP()

	CModuleBeispiel3Consumer();
	virtual	~CModuleBeispiel3Consumer();


///<AutoGeneratedContent id="InterfaceMembers">
	// ITcCyclic
	virtual HRESULT TCOMAPI CycleUpdate(ITcTask* ipTask, ITcUnknown* ipCaller, ULONG_PTR context);

///</AutoGeneratedContent>

protected:
	DECLARE_ITCOMOBJECT_SETSTATE();

	HRESULT AddModuleToCaller();
	VOID RemoveModuleFromCaller();

	// Tracing
	CTcTrace m_Trace;

///<AutoGeneratedContent id="Members">
	TcTraceLevel m_TraceLevelMax;
	ModuleBeispiel3ConsumerData m_Data;
	ITcCyclicCallerInfoPtr m_spCyclicCaller;
	IFancyServicePtr m_spIPFancyService;
///</AutoGeneratedContent>

	ULONGLONG m_Counter;
};
