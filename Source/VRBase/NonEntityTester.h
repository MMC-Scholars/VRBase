// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IBaseEntity/IBaseEntity.h"
#include "NonEntityTester.generated.h"


UCLASS()
class VRBASE_API ANonEntityTester : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANonEntityTester() {
		Msg(__FUNCTION__);
		// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;

		UWorld* world = GetWorld(); //GEngine->GetWorldFromContextObject(this);
		if (!world)
			Msg("Failed to find world");
		else {
			Msg("World type is %i", world->WorldType);
		}

		
	}
	~ANonEntityTester() {
		Msg("Destroying ANonEntityTester");
	}
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& transform) override {
		AActor::OnConstruction(transform);
		Msg("Calling On Construction!");
	}
	
	
	
};
