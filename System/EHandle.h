/**
 * This software is under partial ownership by The Ohio State University, 
 * for it is a product of student employees. For official policy, see
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf 
 * or contact The Ohio State University's Office of Legal Affairs.
 */

#pragma once
#include "predefs.h"

/**
 *****************************************************************************
 * EHandle
 * Provides a handler to an IBaseEntity which acts as a pointer. An EHandle
 * is safe against entities which are removed after the initial EHandle is 
 * created.
 *****************************************************************************
 */

struct EHANDLE {
	private:
		eindex m_iEnt = 0;

	public:
		EHANDLE(const IBaseEntity* pEnt);
		EHANDLE(eindex iEnt) : m_iEnt(iEnt) {}

		inline EHANDLE& operator=(const IBaseEntity* pEnt) { return (*this = EHANDLE(pEnt)); }

		inline IBaseEntity* Get() const { return g_ppEntityList[m_iEnt]; }

		inline eindex EntIndex() const { return m_iEnt; }
		inline operator IBaseEntity*() const { return Get(); }
		inline operator bool() const { return Get() != NULL; }

		inline IBaseEntity* operator->() const { return (Get()); }
};