// Fill out your copyright notice in the Description page of Project Settings.

#include "NonEntityTester.h"
#include "IBaseEntity/IBaseEntity.h"


// Called when the game starts or when spawned
void ANonEntityTester::BeginPlay()
{


	Msg("Beginning entity list report:");
	Super::BeginPlay();
	for (int i = 0; i < g_entList.Num(); i++) {
		MsgW(L"%s at address %p", WCStr(g_entList[i]->GetActor()->GetName()), g_entList[i]);
	}
}

// Called every frame
void ANonEntityTester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


