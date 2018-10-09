
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
	
};
