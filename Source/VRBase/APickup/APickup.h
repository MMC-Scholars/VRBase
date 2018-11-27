
#pragma once

#include "CoreMinimal.h"
#include "VRBase/ABaseEntity/ABaseEntity.h"

#include "Components/StaticMeshComponent.h"

#include "APickup.generated.h"

/**
 * 
 */
UCLASS()
class MMC_OFF_RECREATION_API APickup : public ABaseEntity
{
	GENERATED_BODY()
	
public:
	APickup();
	
	virtual void PreInit() override {};

public:
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	UStaticMeshComponent*	m_pPickupMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Static Mesh")
	UStaticMesh*			staticMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Materials")
	UMaterialInterface*		material0;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Mass")
	//float					m_fMass;

// set static mesh and material dynamically from within the editor
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {

		FName PropertyName = (PropertyChangedEvent.Property != nullptr)
			? PropertyChangedEvent.Property->GetFName() : NAME_None;

		if (m_pPickupMeshComponent	!= nullptr && 
			staticMesh				!= nullptr) {

			m_pPickupMeshComponent->SetStaticMesh(staticMesh);
			if (PropertyName == FName(STRINGIZE(staticMesh))) {
				material0 = staticMesh->GetMaterial(0);
			}
			m_pPickupMeshComponent->SetMaterial(0, material0);
		}
	
		Super::PostEditChangeProperty(PropertyChangedEvent);
	}
#endif

	// Functions
	void Pickup(ABaseController*);
	void Drop(ABaseController*);

	//Blueprint implementable events
	UFUNCTION(BlueprintNativeEvent)
		void OnPickup(ABaseController* controller);
	UFUNCTION(BlueprintNativeEvent)
		void OnDrop(ABaseController* controller);

};
