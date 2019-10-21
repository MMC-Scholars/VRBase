// This software is under partial ownership by The Ohio State University, for it is a product of student employees. For official policy, see https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf or contact The Ohio State University Office of Legal Affairs.

#include "ASign.h"
#include "ABasePawn/ABasePawn.h"

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

	m_string = FString("Hello world!");
	m_fFontSize = 1.0f;

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

	m_pTextRender = CreateDefaultSubobject<UTextRenderComponent>("text render");
	m_pTextRender->SetupAttachment(RootComponent);

	m_pTextRender->SetRelativeLocation(FVector(-0.1f, DEFAULT_WIDTH / -2, DEFAULT_HEIGHT / 2));

	m_pTextRender->SetXScale(m_fFontSize);
	m_pTextRender->SetYScale(m_fFontSize);
	m_pTextRender->SetHorizontalAlignment(EHTA_Left);
	m_pTextRender->SetVerticalAlignment(EVRTA_TextTop);
	m_pTextRender->SetWorldRotation(FRotator(0, 180, 0));
	m_pTextRender->AddRelativeLocation(FVector(0, 0, 2));

	m_pTextRender->SetText(FText::FromString(m_string));
}

void ASign::DefaultThink() {
	if (m_bAlwaysFacePlayer) {
		FVector vLocCurrent = GetActorLocation();
		FVector vLocPlayer = g_pBasePawn->GetActorLocation();

		FVector forward = vLocCurrent- vLocPlayer;
		FRotator rot = forward.ToOrientationRotator();

		SetActorRotation(rot);
	}
}