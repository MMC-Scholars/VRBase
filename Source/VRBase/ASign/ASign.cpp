#include "ASign.h"
#include "Components/TextRenderComponent.h"

#define DEFAULT_WIDTH 200
#define DEFAULT_HEIGHT 100

FVector2D ConvertTo2D(FVector v) {
	int x = static_cast<int>(v.Y) ? 1 : 0;
	int y = static_cast<int>(v.Z) ? 1 : 0;
	return FVector2D(x, y);
}

ASign::ASign() {

//-------------------------------------------------------------------------------------
// UProperties
//-------------------------------------------------------------------------------------

	m_bMeshHiddenInGame = true;

//-------------------------------------------------------------------------------------
// Procedural mesh
//-------------------------------------------------------------------------------------

	FVector cornerTL = FVector(0, DEFAULT_WIDTH / -2, DEFAULT_HEIGHT / -2);
	FVector cornerTR = FVector(0, DEFAULT_WIDTH / 2, DEFAULT_HEIGHT / -2);
	FVector cornerBR = FVector(0, DEFAULT_WIDTH / 2, DEFAULT_HEIGHT / 2);
	FVector cornerBL = FVector(0, DEFAULT_WIDTH / -2, DEFAULT_HEIGHT / 2);

	TArray<FVector> vertices;
	vertices.Add(cornerTL); // 0
	vertices.Add(cornerTR); // 1
	vertices.Add(cornerBR); // 2
	vertices.Add(cornerBL); // 3

	TArray<int32> Triangles;
	// front
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(2);

	Triangles.Add(2);
	Triangles.Add(3);
	Triangles.Add(0);

	// back
	Triangles.Add(2);
	Triangles.Add(1);
	Triangles.Add(0);

	Triangles.Add(0);
	Triangles.Add(3);
	Triangles.Add(2);

	TArray<FVector2D> UV0;
	UV0.Add(ConvertTo2D(cornerTL));
	UV0.Add(ConvertTo2D(cornerTR));
	UV0.Add(ConvertTo2D(cornerBR));
	UV0.Add(ConvertTo2D(cornerBL));

	TArray<FVector> normals;
	TArray<FProcMeshTangent> tangents;
	TArray<FLinearColor> vertexColors;

	m_pMesh = CreateDefaultSubobject<UProceduralMeshComponent>("mesh");
	m_pMesh->bUseAsyncCooking = true;
	m_pMesh->bGenerateOverlapEvents = false;
	m_pMesh->bHiddenInGame = m_bMeshHiddenInGame;

	m_pMesh->CreateMeshSection_LinearColor(0, vertices, Triangles, normals, UV0, vertexColors, tangents, true);

	RootComponent = m_pMesh;

//-------------------------------------------------------------------------------------
// Text render
//-------------------------------------------------------------------------------------

	UTextRenderComponent* m_pLTextInstr = CreateDefaultSubobject<UTextRenderComponent>("Text");
	m_pLTextInstr->SetupAttachment(RootComponent);
	m_pLTextInstr->SetXScale(1);
	m_pLTextInstr->SetYScale(1);
	m_pLTextInstr->SetHorizontalAlignment(EHTA_Center);
	m_pLTextInstr->SetVerticalAlignment(EVRTA_TextBottom);
	m_pLTextInstr->SetWorldRotation(FRotator(0, 180, 0));
	m_pLTextInstr->AddRelativeLocation(FVector(0, 0, 2));

	m_pLTextInstr->SetText(FText::FromString("Hello this is a test of text"));

}
