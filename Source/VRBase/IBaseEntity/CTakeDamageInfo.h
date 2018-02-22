// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs

//-------------------------------------------------------------------------------------
// The purpose of this file is to declare a class which contains damage information.
//		Does not contain much cool functionality yet, but provides an entity point
//		to add into later.
//-------------------------------------------------------------------------------------
#ifndef CTAKEDAMAGEINFO_H
#define CTAKEDAMAGEINFO_H

#include "System/predefs.h"



class CTakeDamageInfo {
private:
	ushort m_iBaseDamage;
	EHANDLE m_hReceiver; //entity who "receives" this attack
	EHANDLE m_hAttacker;
	//EHANDLE m_pWeapon;
	
public:
	CTakeDamageInfo(ushort damage, EHANDLE receiver, EHANDLE attacker)
		: m_iBaseDamage(damage), m_hReceiver(receiver), m_hAttacker(attacker) {}

	ushort GetBaseDamage() const { return m_iBaseDamage; }
	EHANDLE GetReceiver() const { return m_hReceiver; }
	EHANDLE GetAttacker() const { return m_hAttacker; }
};

#endif //CTAKEDAMAGEINFO_H
