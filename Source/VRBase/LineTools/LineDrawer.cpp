// Fill out your copyright notice in the Description page of Project Settings.

#include "LineDrawer.h"
#include "linetools.h"

int g_iDrawnLines = 0;

void ALineDrawer::DefaultThink() {

	//if (g_iDrawnLines > 1)
		//return;

	FVector start = GetActorLocation();
	FVector direction = FVector(cosf(g_pGlobals->curtime), sinf(g_pGlobals->curtime), 0);

	FHitResult t;
	//UTIL_TraceLine(t, start, direction);
	UTIL_TraceSpline(t, start, direction, FVector(0, 0, -0.1f), 10);
	UTIL_DrawLine(start, t.TraceEnd, FColor::Red, 3.f, 1.f);
	Msg("%s", WCStr(t.TraceEnd.ToString()));

	g_iDrawnLines++;


	//UTIL_DrawLine(start, t.TraceEnd, FColor::Red, 1.0f, 0.1f);
	//UTIL_DrawSpline(start, t.TraceEnd, FVector(0,0,50) * sinf(g_pGlobals->curtime), FColor::Red, 1.0f, 0.1f);
}