// Fill out your copyright notice in the Description page of Project Settings.

#include "AWorldButton.h"

#include "System/NLogger.h"



AWorldButton::AWorldButton() {
	m_pMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Button Mesh");
	m_pMeshComponent->bGenerateOverlapEvents = true;
	m_pMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AWorldButton::OnOverlapBegin);
}

void AWorldButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if ((OtherActor) && (OtherActor != this) && (OtherComp)) {
		OnPressed(OverlappedComp, OtherActor, OtherComp);
	}
}
