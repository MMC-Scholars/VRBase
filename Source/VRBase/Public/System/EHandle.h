// This software is under partial ownership by The Ohio State University, for it is a product of student employees. For official policy, see https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf or contact The Ohio State University's Office of Legal Affairs.

#pragma once
#include "System/predefs.h"

/**
 *-------------------------------------------------------------------------------------
 * EHandle
 * An EHandle provides a handler to an IBaseEntity acting as a pointer. An EHandle
 * is safe against entities which are removed after the initial EHandle is
 * created. What this means is that a BaseEntity that is overwritten after game start
 * will not return an arbitrary garbage value or entity, but instead, NULL.
 *
 * EHandles act as wrappers for BaseEntities, e.g.
 * APickup* pPickup = (APickup*) GetWorld()->SpawnActor(APickup::StaticClass(), &loc);
 * EHANDLE m_pMyPickup = EHANDLE(pPickup);
 *-------------------------------------------------------------------------------------
 */

struct EHANDLE {
	private:
		eindex m_iEnt = 0;

	public:
		EHANDLE(const IBaseEntity* pEnt); // defined later in IBaseEntity
		EHANDLE(eindex iEnt) : m_iEnt(iEnt) {}

		inline EHANDLE& operator=(const IBaseEntity* pEnt) { return (*this = EHANDLE(pEnt)); }

		inline IBaseEntity* Get() const { return g_ppEntityList[m_iEnt]; }

		inline eindex EntIndex() const { return m_iEnt; }
		inline operator IBaseEntity*() const { return Get(); }
		inline operator bool() const { return Get() != NULL; }

		inline IBaseEntity* operator->() const { return (Get()); }
};