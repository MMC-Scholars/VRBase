# `CGlobalVars` Class

`CGlobalVars` does not inherit from any other class, and acts as a wrapper for some global variables. It is a singleton named `g_pGlobals`; its most useful variables are `g_pGlobals->curtime`, which is a useful reference point for telling game time, and `g_pGlobals->frametime`, which keeps track of how much time has passed since the last frame. Time is displayed in seconds.