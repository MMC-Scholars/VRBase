// Fill out your copyright notice in the Description page of Project Settings.

#include "AWorldButton.h"

#include "System/NLogger.h"



AWorldButton::AWorldButton() {
	m_pMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Button Mesh");
	m_pMeshComponent->bGenerateOverlapEvents = true;
	//m_pMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AWorldButton::OnOverlapBegin);
	//m_pMeshComponent->OnComponentEndOverlap.AddDynamic(this, &AWorldButton::OnOverlapEnd);
}

void AWorldButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	//CheckPress(dynamic_cast<ABaseController*>(OtherActor));
}

void AWorldButton::OnOverlapEnd(class UPrimitiveComponent *, class AActor *, class UPrimitiveComponent *, int, bool, struct FHitResult const &) {

}


bool AWorldButton::CheckPress(ABaseController* pController) {
	bool result = false;
	if (pController && IsUseableBy(pController)) {

	}

	return result;
}