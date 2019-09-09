# `IBaseEntity` Interface

The `IBaseEntity` class is the most important part of the library. It defines a common interface shared by all Actor-derived classes in the libraries. Its features include: a more detailed initialization system, null-safe referencing, dynamically timed thinking, respawning, optional health system, bitfield flags, and a generic VR-controller-compatible “Use” system.

	<!-- //	-DefaultThink() is always called
	//	-Think() is called if the entity has set one with SetThink(...) -->
