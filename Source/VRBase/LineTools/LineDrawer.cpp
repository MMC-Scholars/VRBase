// Fill out your copyright notice in the Description page of Project Settings.

#include "LineDrawer.h"
#include "linetools.h"

int g_iDrawnLines = 0;

void ALineDrawer::DefaultThink() {

	//if (g_iDrawnLines > 1)
		//return;

	FVector start = GetActorLocation();
	FVector direction = FVector(cosf(g_pGlobals->curtime), sinf(g_pGlobals->curtime), 0);

	SLineDrawParams rendered{ FColor::Red, 5.f, (ftime)0.2f };

	FHitResult t;
	//UTIL_TraceLine(t, start, direction);
	UTIL_TraceSpline(t, start, direction, FVector(0, 0, -0.1f), 128, &rendered);
	UTIL_DrawCircle(t.Location, 50.f, &rendered);
	
	// Michael, I commented out the line below because it was giving errors about how the function doesn't take 5 arguments.
	// I don't know what arguments it needs so I just commented it out.

	//UTIL_DrawLine(start, t.Location, FColor::Red, 3.f, 1.f);
	//Msg(t.Location);

	g_iDrawnLines++;


	//UTIL_DrawLine(start, t.TraceEnd, FColor::Red, 1.0f, 0.1f);
	//UTIL_DrawSpline(start, t.TraceEnd, FVector(0,0,50) * sinf(g_pGlobals->curtime), FColor::Red, 1.0f, 0.1f);
}

