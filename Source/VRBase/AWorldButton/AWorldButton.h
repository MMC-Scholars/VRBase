// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ABaseEntity/ABaseEntity.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "AWorldButton.generated.h"

/**
 * 
 */
UCLASS()
class VRBASE_API AWorldButton : public ABaseEntity
{
	GENERATED_BODY()

public:
	AWorldButton();

	//On Use, do some extra things according to our settings.
	//I.e. change material, play a sound, etc.
	virtual void OnUsed(ABaseEntity*) override;
	
	//Visual component
	UStaticMeshComponent* m_pMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Button)
	UStaticMesh* m_pStaticMesh;
	

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {

		FName PropertyName = (PropertyChangedEvent.Property != nullptr)
			? PropertyChangedEvent.Property->GetFName() : NAME_None;
		// set static mesh and original material from the editor
		if (m_pMeshComponent != nullptr &&
			m_pStaticMesh != nullptr) {

			m_pMeshComponent->SetStaticMesh(m_pStaticMesh);
			if (PropertyName == FName(STRINGIZE(m_pStaticMesh))) {
				m_pOriginalMaterial = m_pStaticMesh->GetMaterial(0);
			}
			m_pMeshComponent->SetMaterial(0, m_pOriginalMaterial);

		}

		Super::PostEditChangeProperty(PropertyChangedEvent);
	}
#endif

	//---------------------------------------------------------------
	//"Use" Feedback response
	//---------------------------------------------------------------

	//Sound to play on press
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Button)
	USoundCue* m_pOnPressCue;

	//Switch to this material for the duration of the press
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Button)
	UMaterialInterface* m_pOnPressMaterial;
private:
	UPROPERTY(EditAnywhere, Category = Button)
	UMaterialInterface* m_pOriginalMaterial;
public:

	//Buttons require for press
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Button)
	//FEntityInputRegistrationButtons m_requiredButtons;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Button)
	bool m_bOverlapRequired;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex); 
	UFUNCTION(BlueprintNativeEvent)
		void OnPressed(ABaseController* pController);
	virtual void OnPressed_Implementation(ABaseController* pController) {}
private:
	uint8 m_iOverlapped;
};
