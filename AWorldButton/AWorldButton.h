/**
 * This software is under partial ownership by The Ohio State University,
 * for it is a product of student employees. For official policy, see
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf
 * or contact The Ohio State University's Office of Legal Affairs.
 */

#pragma once

#include "ABaseEntity/ABaseEntity.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "Sound/SoundCue.h"

#include "AWorldButton.generated.h"

UCLASS()
class VRBASE_API AWorldButton : public ABaseEntity {
    GENERATED_BODY()

public:
    AWorldButton();

    virtual void OnUsed(ABaseEntity*) override;

    UStaticMeshComponent* m_pMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button",
              DisplayName = "Static Mesh")
    UStaticMesh* m_pStaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button",
              DisplayName = "Material")
    UMaterialInterface* m_pOriginalMaterial;

#if WITH_EDITOR
    // set static mesh and original material from the editor
    virtual void
    PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {

        FName PropertyName = (PropertyChangedEvent.Property != nullptr)
                                 ? PropertyChangedEvent.Property->GetFName()
                                 : NAME_None;

        if (m_pMeshComponent != nullptr && m_pStaticMesh != nullptr) {
            m_pMeshComponent->SetStaticMesh(m_pStaticMesh);

            if (PropertyName == FName(STRINGIZE(m_pStaticMesh))) {
                m_pOriginalMaterial = m_pStaticMesh->GetMaterial(0);
            }

            m_pMeshComponent->SetMaterial(0, m_pOriginalMaterial);
        }

        Super::PostEditChangeProperty(PropertyChangedEvent);
    }
#endif

    //-------------------------------------------------------------------------------------
    // "Use" feedback response
    //-------------------------------------------------------------------------------------

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "On Pressed",
              DisplayName = "Sound")
    USoundCue* m_pOnPressCue;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "On Pressed",
              DisplayName = "Material")
    UMaterialInterface* m_pOnPressMaterial;

    // buttons required for press
    // UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Button)
    // FEntityInputRegistrationButtons m_requiredButtons;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                        bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION(BlueprintNativeEvent)
    void OnPressed(ABaseController* pController);
    virtual void OnPressed_Implementation(ABaseController* pController) {}

    UFUNCTION(BlueprintNativeEvent)
    void OffPressed(ABaseController* pController);
    virtual void OffPressed_Implementation(ABaseController* pController) {}

private:
    uint8 m_iOverlapped;
};
