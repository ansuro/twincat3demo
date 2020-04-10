///////////////////////////////////////////////////////////////////////////////
// beispieleDriver.h

#ifndef __BEISPIELEDRIVER_H__
#define __BEISPIELEDRIVER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TcBase.h"

#define BEISPIELEDRV_NAME        "BEISPIELE"
#define BEISPIELEDRV_Major       1
#define BEISPIELEDRV_Minor       0

#define DEVICE_CLASS CbeispieleDriver

#include "ObjDriver.h"

class CbeispieleDriver : public CObjDriver
{
public:
	virtual IOSTATUS	OnLoad();
	virtual VOID		OnUnLoad();

	//////////////////////////////////////////////////////
	// VxD-Services exported by this driver
	static unsigned long	_cdecl BEISPIELEDRV_GetVersion();
	//////////////////////////////////////////////////////
	
};

Begin_VxD_Service_Table(BEISPIELEDRV)
	VxD_Service( BEISPIELEDRV_GetVersion )
End_VxD_Service_Table


#endif // ifndef __BEISPIELEDRIVER_H__