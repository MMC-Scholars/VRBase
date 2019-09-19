/**
 * This software is under partial ownership by The Ohio State University, 
 * for it is a product of student employees. For official policy, see
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf 
 * or contact The Ohio State University's Office of Legal Affairs.
 */

// CTakeDamageInfo.h declares a class which contains damage information.

#ifndef CTAKEDAMAGEINFO_H
#define CTAKEDAMAGEINFO_H

#include "System/predefs.h"

class CTakeDamageInfo {
	private:
		ushort m_iBaseDamage;
		EHANDLE m_hReceiver; //entity who "receives" this attack
		EHANDLE m_hAttacker;

	public:
		CTakeDamageInfo(ushort damage, EHANDLE receiver, EHANDLE attacker)
			: m_iBaseDamage(damage), m_hReceiver(receiver), m_hAttacker(attacker) {}

		ushort GetBaseDamage() const { return m_iBaseDamage; }
		EHANDLE GetReceiver() const { return m_hReceiver; }
		EHANDLE GetAttacker() const { return m_hAttacker; }
};

#endif // CTAKEDAMAGEINFO_H
