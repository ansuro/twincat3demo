///////////////////////////////////////////////////////////////////////////////
// beispieleDriver.cpp
#include "TcPch.h"
#pragma hdrstop

#include "beispieleDriver.h"
#include "beispieleClassFactory.h"

DECLARE_GENERIC_DEVICE(BEISPIELEDRV)

IOSTATUS CbeispieleDriver::OnLoad( )
{
	TRACE(_T("CObjClassFactory::OnLoad()\n") );
	m_pObjClassFactory = new CbeispieleClassFactory();

	return IOSTATUS_SUCCESS;
}

VOID CbeispieleDriver::OnUnLoad( )
{
	delete m_pObjClassFactory;
}

unsigned long _cdecl CbeispieleDriver::BEISPIELEDRV_GetVersion( )
{
	return( (BEISPIELEDRV_Major << 8) | BEISPIELEDRV_Minor );
}

