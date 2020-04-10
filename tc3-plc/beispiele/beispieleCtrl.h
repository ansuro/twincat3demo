///////////////////////////////////////////////////////////////////////////////
// beispieleCtrl.h

#ifndef __BEISPIELECTRL_H__
#define __BEISPIELECTRL_H__

#include <atlbase.h>
#include <atlcom.h>


#include "resource.h"       // main symbols
#include "beispieleW32.h"
#include "TcBase.h"
#include "beispieleClassFactory.h"
#include "TcOCFCtrlImpl.h"

class CbeispieleCtrl 
	: public CComObjectRootEx<CComMultiThreadModel>
	, public CComCoClass<CbeispieleCtrl, &CLSID_beispieleCtrl>
	, public IbeispieleCtrl
	, public ITcOCFCtrlImpl<CbeispieleCtrl, CbeispieleClassFactory>
{
public:
	CbeispieleCtrl();
	virtual ~CbeispieleCtrl();

DECLARE_REGISTRY_RESOURCEID(IDR_BEISPIELECTRL)
DECLARE_NOT_AGGREGATABLE(CbeispieleCtrl)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CbeispieleCtrl)
	COM_INTERFACE_ENTRY(IbeispieleCtrl)
	COM_INTERFACE_ENTRY(ITcCtrl)
	COM_INTERFACE_ENTRY(ITcCtrl2)
END_COM_MAP()

};

#endif // #ifndef __BEISPIELECTRL_H__
