
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
	
	virtual void PreInit() override;

public:
	// Components
	UStaticMeshComponent * m_pPickupMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pickup)
	UStaticMesh* m_pMesh;

// set static mesh dynamically from within the editor
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
		FName PropertyName = (PropertyChangedEvent.Property != nullptr)
			? PropertyChangedEvent.Property->GetFName() : NAME_None;

		if (m_pPickupMeshComponent != nullptr) {
			m_pPickupMeshComponent->SetStaticMesh(m_pMesh);
		}
	
		Super::PostEditChangeProperty(PropertyChangedEvent);
	}
#endif

	// Functions
	void Pickup(ABaseController*);
	void Drop(ABaseController*);

	//Blueprint implementable events
	//UFUNCTION(BlueprintImplementableEvent)
	virtual void OnPickup(ABaseController*);
	//UFUNCTION(BlueprintImplementableEvent)
	virtual void OnDrop(ABaseController*);
};
