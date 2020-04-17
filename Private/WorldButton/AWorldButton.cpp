#include "WorldButton/AWorldButton.h"
#include "BaseController/ABaseController.h"
#include "System/NLogger.h"
#include "Kismet/GameplayStatics.h"

AWorldButton::AWorldButton() {
	m_pMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Button Mesh");
	RootComponent = m_pMeshComponent;
	m_pMeshComponent->SetStaticMesh(m_pStaticMesh);
	m_pMeshComponent->SetMaterial(0, m_pOriginalMaterial);

	m_pMeshComponent->bGenerateOverlapEvents = true;
	m_pMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AWorldButton::OnOverlapBegin);
	m_pMeshComponent->OnComponentEndOverlap.AddDynamic(this, &AWorldButton::OnOverlapEnd);
}

void AWorldButton::OnUsed(ABaseEntity* pActivator) {
	ABaseController* pController = dynamic_cast<ABaseController*>(pActivator);
	if (pController && m_iOverlapped) {
		OnPressed(pController);
	}
}

void AWorldButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor && dynamic_cast<ABaseController*>(OtherActor)) {
		m_iOverlapped++;

		// switch material
		m_pMeshComponent->SetMaterial(0, m_pOnPressMaterial);

		// play sound
		UGameplayStatics::PlaySoundAtLocation(this, m_pOnPressCue, GetActorLocation());

		// fire event
		OnUsed(Cast<ABaseEntity>(OtherActor));
	}
}

void AWorldButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	ABaseController* pController = dynamic_cast<ABaseController*>(OtherActor);
	if (pController) {
		m_iOverlapped--;
		
		// revert material
		m_pMeshComponent->SetMaterial(0, m_pOriginalMaterial);

		OffPressed(pController);
	}
}
