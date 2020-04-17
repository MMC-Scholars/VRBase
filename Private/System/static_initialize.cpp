#include "System/static_initialize.h"
#include "System/NLogger.h"

TArray<CStaticInitializer*> CStaticInitializer::s_pInitializers[(unsigned long long)EPriority::NUM];

CStaticInitializer::CStaticInitializer(EPriority priority) {
	s_pInitializers[(unsigned long long)priority].Add(this);
}

void CStaticInitializer::InvokeAllInOrder() {
	for (uint8 i = 0; i < (uint8)(EPriority::NUM); i++) {
		for (uint16 j = 0; j < s_pInitializers[i].Num(); j++) {
			s_pInitializers[i][j]->Invoke();
		}
	}
}

STATIC_INTIALIZE(log_priority_first, FIRST) {
	Msg("Static Initializer Priority 1");
}

STATIC_INTIALIZE(log_priority_second, SECOND) {
	Msg("Static Initializer Priority 2");
}

STATIC_INTIALIZE(log_priority_third, THIRD) {
	Msg("Static Initializer Priority 3");
}