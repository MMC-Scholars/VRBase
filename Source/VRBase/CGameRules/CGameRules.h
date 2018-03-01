#ifndef CGAMERULES_H
#define CGAMERULES_H

#include "CBaseEntity\CBaseEntity.h"

//------------------------------------------------------
//CGameRules is an interface for global game logic.
//	Also handles default global variables (gpGlobals) and
//		common game logic
//	Override its game functions for whatever kind of game
//		you want. Call the base functions too unless specified
//		otherwise.
//------------------------------------------------------
class CGameRules; extern CGameRules* g_pGameRules;
class CGameRules : public CBaseEntity {
public:
	DECLARE_CLASS_SIMPLE(CGameRules, CBaseEntity);

	CGameRules();

	virtual void BeginPlay() override;

	//-------------------------------------------------------
	// UE4 Overrides create a new gamerules flow
	// CGameRules does not use IBaseEntity::DefaultThink() nor
	//		IBaseEntity::Think() because if it did, the game flow
	//		would end up calling itself.
	//-------------------------------------------------------
	virtual void Tick(float deltaTime) override {

	}
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	//-------------------------------------------------------
	// New master game interface
	//-------------------------------------------------------
public:
	virtual void	RestartRound();
	inline	void	SetNextRoundRestart(ftime next) { m_tNextRoundRestart = next; }
	inline	ftime	GetNextResetRound() const { return m_tNextRoundRestart; }

private:
	bool	m_bHasRestartRound;
	ftime	m_tNextRoundRestart;
};

#endif //CGAMERULES_H
