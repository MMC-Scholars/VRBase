# VRBase

VRBase is a C++ Unreal Engine library designed to improve virtual reality programming in Unreal. It includes a variety of different classes, each of which perform different functions and improve overall user experience.

## Table of Contents
1. [Guidelines](#guide)
2. [Initialization Order](#order)
3. [Setup](#setup)
4. [Class Specification](#spec)

## Guidelines <a name="guide"></a>
- Generally, functions which exist in Blueprint also exist in C++, although they may not be as easy to find or use.
- Types which exist in Blueprint are also used in C++; however, they may go by different names. For example, the Unreal class for Vector is FVector; the class for an Array is TArray<T>.
- Be able to differentiate between what is standard C++ and what is Unreal-specific code.
- Understand the capabilities and limits of the Unreal Header Tool.
- Use the Unreal Header Tool to expose your variables and functions to blueprints.

## Initialization Order <a name="order"></a>

The default object initialization order in Unreal is as follows: 

1. All objects are built via their constructors. These are called whenever the game starts, even when in editor. They are also called in the editor when dragging an object into the world.
2. `AActor::BeginPlay()` is called on all actors, in no particular order.
3. `AActor::Tick()` begins to be called for each actor and will continue to be called every frame.


**VRBase has its own default initialization order. Use the following initialization order instead:**

1. All objects are built via their constructors.
2. `AActor::BeginPlay()` is called on all actors, in no particular order.
3. `IBaseEntity::PreInit()` is called on all IBaseEntity-derived actors.
4. All global Static Initializer Priority 1 functions are called. Between files, order is not guaranteed, but within a file, order is in definition order.
5. All global Static Initializer Priority 2 functions are called; see above.
6. All global Static Initializer Priority 3 functions are called; see above.
7. `IBaseEntity::PreInit()` is called on all IBaseEntity-derived actors.
8. `IBaseEntity::DefaultThink()` and `IBaseEntity::Think()` both begin to be called for each actor and each continue to be called every frame. `IBaseEntity::DefaultThink()` will always be called before `IBaseEntity::Think()` on each frame.
9. `AActor::Tick()` is also called on every frame of the game. On any given frame it may happen before, during, or after `IBaseEntity::DefaultThink()` and `IBaseEntity::Think()`.

## Setup <a name="setup"></a>

There is no need to start virtual reality from scratch; we have already done so.

The VRBase Library implements the Blueprint VR Template in C++. You will not need to program the camera or controllers; this lets you focus on programming your game.

Since this is only a library, VRBase should be added to an existing project via a repository link.

- After cloning VRBase, you will need to right-click the Unreal project and select _Generate Visual Studio Project Files_ in order for the library to appear in the Visual Studio Project.
- You will need to update the _Build.cs_ file with the following dependencies:
  ```cs
  PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Slate", "SlateCore" });
		PrivateDependencyModuleNames.AddRange(new string[] { "HeadMountedDisplay", "SteamVR" });

  // PublicIncludePaths.Add("C:/Users/Public/Public Projects/MMC_Office_Recreation/Source/MMC_Off_Recreation/VRBase");
  PublicIncludePaths.Add("C:/Users/Public/Public Projects/MMC-Office-Recreation/Source/MMC_Off_Recreation/VRBase");
  ```
- To start using VRBase classes, an instance of AGameRules **must** be included in the level. The VRBase classes will not work otherwise.

**Do not directly edit the VRBase library**. If you find a bug or wish to add a feature, consult someone with the authority to edit the library.

## Class Specification <a name="spec"></a>

![VRBase Class Diagram](./Doc/ClassDiagram.png "VRBase Class Diagram")

[ABaseCharacter](Doc/ABaseCharacter.md)  
[ABaseController](Doc/ABaseController.md)  
[ABaseEntity](Doc/ABaseEntity.md)  
[ABaseMoving](Doc/ABaseMoving.md)  
[ABasePawn](Doc/ABasePawn.md)  
[AGameRules](Doc/AGameRules.md)  
[AHMDTeleportationTarget](Doc/AHMDTeleportationTarget.md)  
[AMoveLinear](Doc/AMoveLinear.md)  
[APickup](Doc/APickup.md)  
[AWorldButton](Doc/AWorldButton.md)  
[FMovingVector](Doc/FMovingVector.md)  
[IBaseEntity](Doc/IBaseEntity.md)  
[IGameRulesSystem](Doc/IGameRulesSystem.md)  
[LineTools](Doc/LineTools.md)  
[System](Doc/System.md)  
[CGlobalVars](Doc/CGlobalVars.md)  