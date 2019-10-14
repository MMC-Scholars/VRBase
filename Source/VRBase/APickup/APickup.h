/**
 * This software is under partial ownership by The Ohio State University, 
 * for it is a product of student employees. For official policy, see
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf 
 * or contact The Ohio State University's Office of Legal Affairs.
 */

#pragma once

#include "CoreMinimal.h"
#include "VRBase/ABaseEntity/ABaseEntity.h"
#include "Components/StaticMeshComponent.h"
#include "APickup.generated.h"

UCLASS()
class VRBASE_API APickup : public ABaseEntity {
	GENERATED_BODY()
	
	public:
		APickup();

		TArray<AActor*> 							m_aParentActors;
		UStaticMeshComponent*					m_pPickupMeshComponent;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Mesh", DisplayName = "Static Mesh")
		UStaticMesh*									staticMesh;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Mesh", DisplayName = "Material")
		UMaterialInterface*						material0;

		// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup Mass")
		// float											m_fMass;

#if WITH_EDITOR
		// set static mesh and material dynamically from within the editor
		virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {

			FName PropertyName = 
				(PropertyChangedEvent.Property != nullptr)
				? PropertyChangedEvent.Property->GetFName() 
				: NAME_None;

			if (m_pPickupMeshComponent != nullptr && staticMesh != nullptr) {

				m_pPickupMeshComponent->SetStaticMesh(staticMesh);
				
				if (PropertyName == FName(STRINGIZE(staticMesh))) {
					material0 = staticMesh->GetMaterial(0);
				}

				m_pPickupMeshComponent->SetMaterial(0, material0);
			}
		
			Super::PostEditChangeProperty(PropertyChangedEvent);
		}
#endif

		virtual void Pickup(ABaseController*);
		virtual void Drop(ABaseController*);

		UFUNCTION(BlueprintNativeEvent)
		void OnPickup(ABaseController* controller);
		UFUNCTION(BlueprintNativeEvent)
		void OnDrop(ABaseController* controller);
};
