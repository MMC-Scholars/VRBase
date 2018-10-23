#include "stdio.h"

#define FILENAME_APP_NEXT "vr_app_next.tmp"

namespace VRAppController {
	void markNextProgramName(const char* pszName) {
		FILE* pFile = fopen(FILENAME_APP_NEXT, "w");
		if (pFile) {
			fprintf(pFile, pszName);
			fclose(pFile);
		}
	}

	void exit() {

	}
}