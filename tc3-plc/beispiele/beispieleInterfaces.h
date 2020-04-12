///////////////////////////////////////////////////////////////////////////////
// beispieleInterfaces.h

#pragma once

#include "TcInterfaces.h"
#include "TcIoInterfaces.h"
#include "TcRtInterfaces.h"
#include "beispieleServices.h"

///<AutoGeneratedContent id="Interfaces">
#if !defined(_TC_TYPE_4400D997_C606_47B2_8486_FA74A26F4E2F_INCLUDED_)
#define _TC_TYPE_4400D997_C606_47B2_8486_FA74A26F4E2F_INCLUDED_
struct __declspec(novtable) IFancyService : public ITcUnknown
{
	virtual HRESULT TCOMAPI GetFancyData(FancyData* pData)=0;
};
_TCOM_SMARTPTR_TYPEDEF(IFancyService, IID_IFancyService);
#endif // !defined(_TC_TYPE_4400D997_C606_47B2_8486_FA74A26F4E2F_INCLUDED_)

///</AutoGeneratedContent>
