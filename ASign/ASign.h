#pragma once

#include "Components/TextRenderComponent.h"
#include "ProceduralMeshComponent.h"
#include "ABaseEntity/ABaseEntity.h"

#include "ASign.generated.h"

UCLASS()
class VRBASE_API ASign : public ABaseEntity {
    GENERATED_BODY()

public:
    ASign();

    // set text display since uproperties seem to reset to default values on
    // editor start
    virtual void OnConstruction(const FTransform& Transform) override {
        TextReload();
    };

    virtual void PreInit() override;
    virtual void DefaultThink() override;

private:
    UProceduralMeshComponent* m_pMesh;
    UTextRenderComponent*     m_pTextRender;

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text",
              DisplayName = "Text", meta = (MultiLine = true))
    FString m_string;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text",
              DisplayName = "Font Size")
    float m_fFontSize;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text",
              DisplayName = "Horizontal Align")
    TEnumAsByte<EHorizTextAligment> m_eAlignX;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text",
              DisplayName = "Vertical Align")
    TEnumAsByte<EVerticalTextAligment> m_eAlignY;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text",
              DisplayName = "Text Color")
    FColor m_sColor;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rendering",
              DisplayName = "Mesh Material")
    UMaterialInterface* m_pMeshMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rendering",
              DisplayName = "Mesh Hidden In Game")
    bool m_bMeshHiddenInGame;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rendering",
              DisplayName = "Always Face Player?")
    bool m_bAlwaysFacePlayer;

private:
    void TextReload();
    void TextWrap(FString);

public:
    //-------------------------------------------------------------------------------------
    // UProperty editor handling
    //-------------------------------------------------------------------------------------

#if WITH_EDITOR
    virtual void
    PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
        if (m_pMesh && m_pTextRender) {
            // text
            TextReload();
            // rendering
            m_pMesh->SetMaterial(0, m_pMeshMaterial);
            m_pMesh->bHiddenInGame = m_bMeshHiddenInGame;
        }

        Super::PostEditChangeProperty(PropertyChangedEvent);
    }

    void PostEditMove(bool bFinished) {
        Super::PostEditMove(bFinished);
        if (m_pMesh && m_pTextRender) { TextWrap(m_string); }
    }

#endif
};
