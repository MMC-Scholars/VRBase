// This software is under partial ownership by The Ohio State University, for it
// is a product of student employees. For official policy, see
// https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf or contact The
// Ohio State University's Office of Legal Affairs.

#include "Globals.h"
#include "AGameRules/AGameRules.h"
#include "NLogger.h"


UStaticMesh* GPAssetsVar::FindMesh(const char* path){

    size_t pathLen = strlen(path) + 1;
    wchar_t* wcharPath = new wchar_t[pathLen];
    size_t outputSize;
    mbstowcs_s(&outputSize, wcharPath, pathLen, path, pathLen - 1);

    return FindMesh(wcharPath);


}

UStaticMesh# GPAssetsVar::FindMesh(const wchar_t* path){
    
    //Todo: Check meshFinder documentation
    ConstructionHelpers::FObjectFinder<UStaticMesh> meshFinder(path);

    return meshFinder.Object;
}

//Todo: Implement other potential features such as find Animation, Material, etc. 