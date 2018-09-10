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
#include "System/Globals.h"
#include "System/Input.h"
#include "System/static_initialize.h"
#include "IBaseEntity_flags.h"
#include "GameFramework/Actor.h"
#include "System/EHandle.h"
#include "UObject/ConstructorHelpers.h"



/**********************************************************************
* IBaseEntity
* Declares functionality common to all "Base" types and defines some
*		of it.
* Derived types are, for example:
*	class ABaseEntity	 :	public AActor, public IBaseEntity {...};
*	class ABasePawn      :	public APawn, public IBaseEntity {...};
*	class ABaseCharacter :	public ACharacter, public IBaseEntity {...};
**********************************************************************/
abstract_class IBaseEntity {
public:
	friend class CGlobalVars;
	//Default constructor performs defaults and adds self to global lists
							IBaseEntity();
	virtual					~IBaseEntity() {
		RemoveSelfFromLists();
		//Msg("Decrementing entity count");
		//s_iEntityCount--;
		//s_iReadyEntityCount--;
	}
	ftime m_tConstructionTime;

			void			RemoveSelfFromLists(); //invalidates EHANDLES, does NOT modify static counts, do that yourself
			bool			DestroyEntity(); //destroys this Actor
	inline	void			ReportReady() { Msg(L"Entity %s ready", WCStr(FString(GetActor()->GetName()))); }
	//---------------------------------------------------------------
	// Entity indexing system
	//---------------------------------------------------------------
	inline	eindex			EntIndex()			const { return m_iEntIndex; }
			EHANDLE			GetEHandle()		const { return EHANDLE(this); }
private:
	eindex m_iEntIndex;
protected:
			void			PostDuplicate(EDuplicateMode::Type mode);
	static	void			AddEntityToLists(IBaseEntity* pEnt);

	//---------------------------------------------------------------
	// Intiailization system
	//---------------------------------------------------------------
public:
	virtual void			PreInit() {}	//called before all the static intializers
	virtual void			PostInit();	//called after all the static initializers

	//---------------------------------------------------------------
	// Linkage to vanilla Unreal4 Actor system
	// assumes that this in fact IS an actor. If not, you'll
	// get segmentation faults or something bad!
	//---------------------------------------------------------------
public:
			bool			IsBaseEntity()		const	{ return GetActor()->ActorHasTag(TAG_BASEENTITY); }
			bool			IsBasePawn()		const 	{ return GetActor()->ActorHasTag(TAG_BASEPAWN); }
			bool			IsBaseCharacter()	const	{ return GetActor()->ActorHasTag(TAG_BASECHARACTER); }
	static	IBaseEntity*	FromActor(AActor* pActor);
	inline	IBaseEntity&	GetRef()					{ return *this; }
	inline	AActor*			GetActor()			const	{ return m_pSelfAsActor; }
protected:
	AActor* m_pSelfAsActor;

	//---------------------------------------------------------------
	// Think system
	//	-DefaultThink() is always called
	//	-Think() is called if the entity has set one with SetThink(...)
	//---------------------------------------------------------------
public:
	typedef void (IBaseEntity::* BASEPTR)(void);
	virtual void			DefaultThink(); //this think function is always called
	inline	void			Think()							{ if (m_pfnThink) (this->*m_pfnThink)(); }
	inline	void			SetNextThink(ftime time)		{ m_tNextThink = time; }
	inline	ftime			GetNextThink() const			{ return m_tNextThink; }
	inline	void			SetThink(BASEPTR pProcedure)	{ m_pfnThink = pProcedure; }

	static inline bool		AllEntitiesReady()				{ return s_iReadyEntityCount == s_iEntityCount; }
private:
	BASEPTR m_pfnThink		= nullptr;
	ftime m_tNextThink;

protected:
	static int	s_iReadyEntityCount;
	static int	s_iEntityCount;



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
			int				GetHealth()			const { return m_iHealth; }
			int				GetSpawnHealth()	const { return m_iSpawnHealth; }
			void			SetHealth(int health);

	virtual void			TraceAttack(const CTakeDamageInfo& info);

	inline	bool			IsInvincible()		const { return HasFlags(FL_INVINCIBLE); }
	inline	bool			IsNotDamageable()	const { return HasFlags(FL_NODAMAGE); }

private:
			void			CheckDamageEvents(int deltaHealth, const CTakeDamageInfo* pInfo);

protected:
	//for these functions with pointers, info is not guaranteed to be non-null
	virtual void			OnHealed(const CTakeDamageInfo* info)			{}
	virtual void			OnTakeDamage(const CTakeDamageInfo* info)		{}
	virtual void			OnTakeDamage_Alive(const CTakeDamageInfo* info) {}
	virtual void			OnKilled(const CTakeDamageInfo* info)			{}
	virtual void			OnKilled_Other(const CTakeDamageInfo& info)		{}
	inline	bool			IsAlive()	const								{ return m_iHealth > 0; }
	inline	bool			IsDead()	const								{ return !IsAlive(); }

protected:
	int m_iSpawnHealth = 100;
	int m_iHealth;
	int m_iDestoryHealth = 0; //health at which this entity is destroyed

	//---------------------------------------------------------------
	// Flag system compactly stores up to 64 booleans
	// as a unsigned long has 64 bits
	//---------------------------------------------------------------
public:
	inline	ulong			GetFlags()				const	{ return m_iFlags; }
	inline	bool			HasFlags(ulong flags)	const	{ return (m_iFlags & flags) != 0; }
	inline	bool			HasFlagsAll(ulong flags)const	{ return (m_iFlags & flags) == flags; }
	inline	void			AddFlags(ulong flags)			{ m_iFlags |= flags; }
	inline	void			RemoveFlags(ulong flags)		{ m_iFlags &= ~flags; }
	inline	void			ToggleFlags(ulong flags)		{ m_iFlags ^= flags; }
	inline	void			ResetFlags()					{ m_iFlags = m_iSpawnFlags; }
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "IBaseEntity")
	ulong m_iSpawnFlags = 0;
	ulong m_iFlags;

	//---------------------------------------------------------------
	//Generic "Use" System
	//---------------------------------------------------------------
public:
			bool			Use(ABaseEntity* pActivator);	//returns true on success, false if blocked
	virtual void			OnUsed(ABaseEntity* pActivator)				{}
	inline	bool			IsUseable()							const	{ return !HasFlags(FL_IGNORE_USE | FL_INGORE_INPUT); }
	inline	bool			IsInputEnabled()					const	{ return !HasFlags(FL_INGORE_INPUT); }
	UInputComponent*		GetInput();
	void					RegisterInputsToControllers();

	//These functions are overriden by functions declared in ABaseEntity
	virtual FEntityInputRegistrationParams*			GetLeftControllerInputRegistrationParams() { return NULL; }
	virtual FEntityInputRegistrationParams*			GetRightControllerInputRegistrationParams() { return NULL; }
	
};

//Finds a UStaticMesh by path
UStaticMesh* FindMesh(const wchar_t* path);

#include "CTakeDamageInfo.h"

#endif //IBASEENTITY_H