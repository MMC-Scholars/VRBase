// This software is under partial ownership by The Ohio State University, for it is a product of student employees. For official policy, see https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf or contact The Ohio State University Office of Legal Affairs.

#pragma once

#include "System/NLogger.h"

#include "CoreMinimal.h"
#include "VRBase/ABaseEntity/ABaseEntity.h"
#include "ProceduralMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "ASign.generated.h"

UCLASS()
class VRBASE_API ASign : public ABaseEntity {
	GENERATED_BODY()

	public:
		ASign();

		virtual void PreInit() override;
		virtual void DefaultThink() override;

	private:
		UProceduralMeshComponent* m_pMesh;
		UTextRenderComponent* m_pTextRender;

	public:		
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text", DisplayName = "Text", meta=(MultiLine=true))
		FString m_string;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text", DisplayName = "Font Size")
		float m_fFontSize;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rendering", DisplayName = "Mesh Hidden In Game")
		bool m_bMeshHiddenInGame;
		
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rendering", DisplayName = "Always Face Player?")
		bool m_bAlwaysFacePlayer;

	private:
		void TextWrap(FString);

	public:

//-------------------------------------------------------------------------------------
// UProperty editor handling
//-------------------------------------------------------------------------------------

#if WITH_EDITOR
		virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
			if (m_pMesh && m_pTextRender) {
				m_pMesh->bHiddenInGame = m_bMeshHiddenInGame;

				m_pTextRender->SetXScale(m_fFontSize);
				m_pTextRender->SetYScale(m_fFontSize);

				TextWrap(m_string);
			}

			Super::PostEditChangeProperty(PropertyChangedEvent);
		}
		
		void PostEditMove(bool bFinished) {
			Super::PostEditMove(bFinished);
			
			if (m_pMesh && m_pTextRender) {
				TextWrap(m_string);
			}
		}
		
#endif

};
