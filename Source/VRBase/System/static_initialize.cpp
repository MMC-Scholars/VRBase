#include "static_initialize.h"

CStaticInitializer::CStaticInitializer(EPriority priority) {
	switch (priority) {
	case EPriority::FIRST:
		s_pFirstInitializers.Add(this);
		break;
	case EPriority::SECOND:
		s_pSecondInitializers.Add(this);
		break;
	case EPriority::THIRD:
		s_pThirdInitializers.Add(this);
	}
}

void CStaticInitializer::InvokeAllInOrder() {
	for (uint16 i = 0; i < s_pFirstInitializers.Num(); i++)
		s_pFirstInitializers[i]->Invoke();
	for (uint16 i = 0; i < s_pSecondInitializers.Num(); i++)
		s_pSecondInitializers[i]->Invoke();
	for (uint16 i = 0; i < s_pThirdInitializers.Num(); i++)
		s_pThirdInitializers[i]->Invoke();
}

TArray<CStaticInitializer*> CStaticInitializer::s_pFirstInitializers;
TArray<CStaticInitializer*> CStaticInitializer::s_pSecondInitializers;
TArray<CStaticInitializer*> CStaticInitializer::s_pThirdInitializers;