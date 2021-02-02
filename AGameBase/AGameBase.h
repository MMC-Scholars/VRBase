#pragma once

#include "ABaseEntity/ABaseEntity.h"

#include "AGameBase.generated.h"

/**
 *-------------------------------------------------------------------------------------
 * AGameBase
 * AGameBase handles default global variables (gpGlobals) and common game
 *logic. Override its game functions for whatever kind of game you want.
 *-------------------------------------------------------------------------------------
 */
UCLASS()
class VRBASE_API AGameBase : public ABaseEntity {
public:
    GENERATED_BODY()
    AGameBase();

    // UE4 Overrides create a new game flow. This does not use
    // IBaseEntity::DefaultThink() nor IBaseEntity::Think() because if it
    // did, the game flow would end up calling itself.
    // virtual void BeginPlay() override;
    virtual void Tick(float deltaTime) override;

private:
    void InitializeBaseEntities();
};

extern AGameBase* g_pGameBase;