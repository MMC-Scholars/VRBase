// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ABaseEntity/ABaseEntity.h"
#include "AWorldButton.generated.h"

/**
 * 
 */
UCLASS()
class MMC_OFF_RECREATION_API AWorldButton : public ABaseEntity
{
	GENERATED_BODY()

public:
	AWorldButton();

	//On Use, do some extra things according to our settings.
	//I.e. change material, play a sound, etc.
	virtual void OnUsed(ABaseEntity*) override {}
	
	//Visual component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Button)
	UStaticMeshComponent* m_pMeshComponent;

	//---------------------------------------------------------------
	//"Use" Feedback response
	//---------------------------------------------------------------

	//Sound to play on press
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Button)
	//USoundCue* m_pOnPress;

	//Switch to this material for the duration of the press
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Button)
	UMaterial* m_pOnPressMaterial;
private:
	UMaterial* m_pOriginalMaterial;
public:

	//Buttons require for press
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Button)
	FEntityInputRegistrationButtons m_requiredButtons;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Button)
	bool m_bOverlapRequired;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); 
	UFUNCTION(BlueprintImplementableEvent)
		void OnPressed(ABaseController* pController);
private:
	bool CheckPress(ABaseController* pController);
};
