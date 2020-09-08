// This software is under partial ownership by The Ohio State University, for it
// is a product of student employees. For official policy, see
// https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf or contact The
// Ohio State University's Office of Legal Affairs.

#ifndef GLOBALS_ASSETS_H
#define GLOBALS_ASSETS_H

#include "NLogger.h"
#include "predefs.h"
#include <chrono>

using namespace std::chrono;


class GPAssetsVar{

public:

    //A function which returns a static mesh, given a path reference to the mesh

    UStaticMesh* FindMesh(const char* path);
    UStaticMesh* FindMesh(const wchar_t* path);

    //TODO: Add functions for finding material, animation, etc.
    




};






#endif // GLOBALS_ASSETS_H