// Fill out your copyright notice in the Description page of Project Settings.

#include "AWorldButton.h"
#include "ABaseController/ABaseController.h"
#include "System/NLogger.h"



AWorldButton::AWorldButton() {
	m_pMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Button Mesh");
	m_pMeshComponent->bGenerateOverlapEvents = true;
	m_pMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AWorldButton::OnOverlapBegin);
	m_pMeshComponent->OnComponentEndOverlap.AddDynamic(this, &AWorldButton::OnOverlapEnd);
	m_iOverlapped--;
}

void AWorldButton::OnUsed(ABaseEntity* pActivator) {
	ABaseController* pController = dynamic_cast<ABaseController*>(pActivator);
	if (pController && (m_iOverlapped || !m_bOverlapRequired)) {
		Msg(L"Used by %s", WCStr(pActivator->GetName()));
		OnPressed(pController);
	}
}

void AWorldButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor && dynamic_cast<ABaseController*>(OtherActor)) {
		m_iOverlapped++;
	}
}

void AWorldButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor && dynamic_cast<ABaseController*>(OtherActor)) {
		m_iOverlapped--;
	}
}

