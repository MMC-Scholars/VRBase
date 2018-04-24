// Fill out your copyright notice in the Description page of Project Settings.

#include "LineDrawer.h"
#include "linetools.h"



void ALineDrawer::DefaultThink() {
	FVector start = GetActorLocation();

	FVector dest = start + 100 * sinf(g_pGlobals->curtime) * FVector(cosf(g_pGlobals->curtime), sinf(g_pGlobals->curtime), 0);
	
	


	UTIL_DrawLine(start, dest, FColor::Red, 1.0f, 0.1f);
	UTIL_DrawSpline(start, dest, FVector(0,0,50) * sinf(g_pGlobals->curtime), FColor::Red, 1.0f, 0.1f);
}