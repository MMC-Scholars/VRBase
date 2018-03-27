#pragma once
#include "System/predefs.h"
//-------------------------------------------------------------------------------------
// The purpose of this struct is to declare a handler to an IBaseEntity. Acts as a "pointer"
//		to an IBaseEntity except that it is safe against entities which are removed
//		after the initial EHANDLE is created.
//-------------------------------------------------------------------------------------
struct EHANDLE {
private:
	eindex m_iEnt = 0;

public:
	//construction and assignment
	EHANDLE(const IBaseEntity* pEnt);
	EHANDLE(eindex iEnt) : m_iEnt(iEnt) {}
	inline EHANDLE& operator=(const IBaseEntity* pEnt) { return (*this = EHANDLE(pEnt)); }

	inline IBaseEntity* Get() const { return g_ppEntityList[m_iEnt]; }

	inline eindex EntIndex() const { return m_iEnt; }
	inline operator IBaseEntity*() const { return Get(); }
	inline operator bool() const { return Get() != NULL; }

	inline IBaseEntity* operator->() const { return (Get()); }
};