// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs

#ifndef IBASENTITY_H
#define IBASENTITY_H

#include "CoreMinimal.h"
#include "UnrealEngine.h"
#include "System/predefs.h"
#include "System/Globals.h"



//-------------------------------------------------------------------------------------
// The purpose of this struct is to declare a handler to an IBaseEntity. Acts as a "pointer"
//		to an IBaseEntity except that it is safe against entities which are removed
//		after the initial EHANDLE is created.
//-------------------------------------------------------------------------------------
struct EHANDLE {
private:
	eindex m_iEnt;

public:
	//construction and assignment
	EHANDLE(const IBaseEntity* pEnt);
	EHANDLE(eindex iEnt) : m_iEnt(iEnt) {}
	inline EHANDLE& operator=(const IBaseEntity* pEnt) { return (*this = EHANDLE(pEnt)); }

	inline IBaseEntity* Get() const { return g_ppEntityList[m_iEnt]; }

	inline eindex EntIndex() const { return m_iEnt; }
	inline operator IBaseEntity*() const { return Get(); }
	inline operator bool() const { return Get(); }

	inline IBaseEntity* operator->() const { return (Get()); }
};

/**********************************************************************
* IBaseEntity
* Declares functionality common to all "Base" types and defines some
*		of it.
* Derived types are, for example:
*	class CBaseEntity	 :	public AActor, public IBaseEntity {...};
*	class CBasePawn      :	public APawn, public IBaseEntity {...};
*	class CBaseCharacter :	public ACharacter, public IBaseEntity {...};
**********************************************************************/
abstract_class IBaseEntity {
public:
	//Default constructor performs defaults and adds self to global lists
	IBaseEntity();
	~IBaseEntity() {
		g_ppEntityList[EntIndex()] = NULL; //this fixes all EHANDLEs
	}
	ftime m_tConstructionTime;

	bool DestroyEntity(); //destroys this Actor
	//---------------------------------------------------------------
	// Entity indexing system
	//---------------------------------------------------------------
	inline eindex EntIndex() const { return m_iEntIndex; }
	EHANDLE GetEHandle() const { return EHANDLE(this); }
private:
	eindex m_iEntIndex;
	static void AddEntityToList(IBaseEntity* pEnt);

	etype  m_eBaseType; //denotes if we inherit from actor, pawn, or character

	//---------------------------------------------------------------
	// Linkage to vanilla Unreal4 Actor system
	// assumes that this in fact IS an actor. If not, you'll
	// get segmentation faults or something bad!
	//---------------------------------------------------------------
public:
	etype GetEntityType() const { return m_eBaseType; }
	static IBaseEntity* FromActor(AActor* pActor);
	inline IBaseEntity& GetRef() { return *this; }
	inline AActor* GetActor() const { return reinterpret_cast<AActor*>(const_cast<IBaseEntity*>(this)); }
	AActor* operator->() const { return GetActor(); }
	AActor& operator*() const { return *GetActor(); }
	operator AActor*() const { return GetActor(); }

	//---------------------------------------------------------------
	// Think system
	//	-DefaultThink() is always called
	//	-Think() is called if the entity has set one with SetThink(...)
	//---------------------------------------------------------------
public:
	typedef void (IBaseEntity::* BASEPTR)(void);
	virtual void	DefaultThink(); //this think function is always called
	inline void		Think()							{ if (m_pfnThink) this->(*m_pfnThink)(); }
	inline void		SetNextThink(ftime time)		{ m_tNextThink = time; }
	inline ftime	GetNextThink() const			{ return m_tNextThink; }
	inline void		SetThink(BASEPTR pProcedure)	{ m_pfnThink = pProcedure; }

private:
	BASEPTR		m_pfnThink = nullptr;
	ftime		m_tNextThink;

	//---------------------------------------------------------------
	// Respawn system
	//---------------------------------------------------------------
public:
	virtual void Respawn();
	
private:
	ftime m_tLastRespawn;
	ftime m_tNextRespawn;

	//---------------------------------------------------------------
	// Health System
	//---------------------------------------------------------------
public:
	int GetHealth() const { return m_iHealth; }
	int GetSpawnHealth() const { return m_iSpawnHealth; }
	void SetHealth(int health);

	virtual void TraceAttack(const CTakeDamageInfo& info);

private:
	void CheckDeath(int deltaHealth, const CTakeDamageInfo* pInfo);

protected:
	//for these functions with pointers, info is not guaranteed to be non-null
	virtual void OnHealed(const CTakeDamageInfo* info) {}
	virtual void OnTakeDamage(const CTakeDamageInfo* info) {}
	virtual void OnTakeDamage_Alive(const CTakeDamageInfo* info) {}
	virtual void OnKilled(const CTakeDamageInfo* info) {}
	virtual void OnKilled_Other(const CTakeDamageInfo& info) {}
	inline bool IsAlive() const { return m_iHealth > 0; }
	inline bool IsDead() const { return !IsAlive(); }

protected:
	int m_iSpawnHealth = 100;
	int m_iHealth;
	int m_iDestoryHealth = 0; //health at which this entity is destroyed

	//---------------------------------------------------------------
	// Flag system compactly stores up to 64 booleans
	// as a unsigned long has 64 bits
	//---------------------------------------------------------------
public:
	inline ulong	GetFlags()				const	{ return m_iFlags; }
	inline bool		HasFlags(ulong flags)	const	{ return m_iFlags & flags; }
	inline void		AddFlags(ulong flags)			{ m_iFlags |= flags; }
	inline void		RemoveFlags(ulong flags)		{ m_iFlags &= ~flags; }
	inline void		ToggleFlags(ulong flags)		{ m_iFlags ^= flags; }
	inline void		ResetFlags()					{ m_iFlags = m_iSpawnFlags; }
protected:
	ulong m_iSpawnFlags = 0;
	ulong m_iFlags;
};

#include "CTakeDamageInfo.h"

#define LOAD_HANDLE(referenceName) m_h##referenceName = m_a##referenceName

#endif //IBASEENTITY_H