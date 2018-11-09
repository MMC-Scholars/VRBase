// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VRBase/ABaseEntity/ABaseEntity.h"
#include "AWorldButton.generated.h"

/**
 * 
 */
UCLASS()
class MMC_OFF_RECREATION_API AWorldButton : public ABaseEntity
{
	GENERATED_BODY()

public:

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
};
