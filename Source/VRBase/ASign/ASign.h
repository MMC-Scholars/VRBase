/*
 * This software is under partial ownership by The Ohio State University, 
 * for it is a product of student employees.For official policy, see 
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf 
 * or contact The Ohio State University Office of Legal Affairs.
 */

#pragma once

#include "System/NLogger.h"

#include "CoreMinimal.h"
#include "VRBase/ABaseEntity/ABaseEntity.h"
#include "Components/BoxComponent.h"
#include "ProceduralMeshComponent.h"
#include "ASign.generated.h"

UCLASS()
class VRBASEDEMO_API ASign : public ABaseEntity {
	GENERATED_BODY()

	public:
		ASign();
	
		virtual void PreInit() override {};

	private:
		UProceduralMeshComponent* m_pMesh;

	public:
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rendering", DisplayName = "Mesh Hidden In Game")
		bool m_bMeshHiddenInGame;
		
		// TODO
		// bool m_bAlwaysFacePlayer;
	
//-------------------------------------------------------------------------------------
// UProperty editor handling
//-------------------------------------------------------------------------------------

#if WITH_EDITOR
		virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {

			m_pMesh->bHiddenInGame = m_bMeshHiddenInGame;

			Super::PostEditChangeProperty(PropertyChangedEvent);
		}

//		virtual void PostEditMove(bool bFinished) {
//		}
#endif
};
