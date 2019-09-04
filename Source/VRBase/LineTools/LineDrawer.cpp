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
	//UTIL_DrawLine(start, t.Location, FColor::Red, 3.f, 1.f);

	g_iDrawnLines++;
}
