// This software is under partial ownership by The Ohio State University, for it
// is a product of student employees. For official policy, see
// https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf or contact The
// Ohio State University's Office of Legal Affairs.

#pragma once

#include "ABaseEntity/ABaseEntity.h"
#include "CoreMinimal.h"

#include "AGameRules.generated.h"

/**
 *-------------------------------------------------------------------------------------
 * AGameRules
 * AGameRules handles default global variables (gpGlobals) and common game
 *logic. Override its game functions for whatever kind of game you want.
 *-------------------------------------------------------------------------------------
 */
UCLASS()
class VRBASE_API AGameRules : public ABaseEntity {
public:
    GENERATED_BODY()
    AGameRules();

    // UE4 Overrides create a new gamerules flow. AGameRules does not use
    // IBaseEntity::DefaultThink() nor IBaseEntity::Think() because if it
    // did, the game flow would end up calling itself.
    virtual void BeginPlay() override;
    virtual void Tick(float deltaTime) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    //-------------------------------------------------------------------------------------
    // Master game interface
    //-------------------------------------------------------------------------------------

public:
    virtual void RestartRound();
    inline void  SetNextRoundRestart(ftime next) { m_tNextRoundRestart = next; }
    inline ftime GetNextResetRound() const { return m_tNextRoundRestart; }

    bool GameReady() const { return m_bHasInitializedAllEntities; }

private:
    void InitializeAllEntities();

    bool  m_bHasInitializedAllEntities;
    bool  m_bHasRestartedRound;
    ftime m_tNextRoundRestart;
};

extern AGameRules* g_pGameRules;
