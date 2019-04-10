#pragma once


#include "CoreMinimal.h"
#include "Engine.h"
#include "EngineMinimal.h"
#include "Components/TextRenderComponent.h"
#include "FPawnInstruction.generated.h"

USTRUCT(BlueprintType)
struct FPawnInstruction {
	GENERATED_BODY()

	UTextRenderComponent* m_pTextRender;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Instruction Text")
		FString m_pInstruction;

};