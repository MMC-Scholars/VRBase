// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABaseEntity/ABaseEntity.h"
#include "AGameRules.generated.h"

//------------------------------------------------------
//AGameRules is an interface for global game logic.
//	Also handles default global variables (gpGlobals) and
//		common game logic
//	Override its game functions for whatever kind of game
//		you want. Call the base functions too unless specified
//		otherwise.
//------------------------------------------------------
UCLASS()
class VRBASE_API AGameRules : public ABaseEntity
{
public:
	DECLARE_CLASS_SIMPLE(AGameRules, ABaseEntity);
	GENERATED_BODY()


	AGameRules();

	virtual void BeginPlay() override;

	//-------------------------------------------------------
	// UE4 Overrides create a new gamerules flow
	// CGameRules does not use IBaseEntity::DefaultThink() nor
	//		IBaseEntity::Think() because if it did, the game flow
	//		would end up calling itself.
	//-------------------------------------------------------
	virtual void Tick(float deltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	//-------------------------------------------------------
	// New master game interface
	//-------------------------------------------------------
public:
	virtual void	RestartRound();
	inline	void	SetNextRoundRestart(ftime next) { m_tNextRoundRestart = next; }
	inline	ftime	GetNextResetRound() const { return m_tNextRoundRestart; }

	bool	GameReady() const { return m_bHasInitializedAllEntities; }
private:
	void	InitializeAllEntities();

	bool	m_bHasInitializedAllEntities;
	bool	m_bHasRestartedRound;
	ftime	m_tNextRoundRestart;
};
extern AGameRules* g_pGameRules;
