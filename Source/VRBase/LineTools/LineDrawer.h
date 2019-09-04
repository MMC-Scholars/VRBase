/**
 * This software is under partial ownership by The Ohio State University, 
 * for it is a product of student employees. For official policy, see
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf 
 * or contact The Ohio State University's Office of Legal Affairs.
 */

#pragma once

#include "CoreMinimal.h"
#include "ABaseEntity/ABaseEntity.h"
#include "LineDrawer.generated.h"

/**
 * An entity which handles and dispatches line drawing jobs
 */
UCLASS()
class VRBASE_API ALineDrawer : public ABaseEntity
{
	GENERATED_BODY()

	void PreInit() override {}
	void DefaultThink() override;

	void OnUsed(ABaseEntity*) override { Msg("IT WORKS!"); }
	
};
