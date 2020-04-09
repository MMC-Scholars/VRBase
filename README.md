# VRBase Library v2

VRBase is a C++ Unreal Engine library designed to simplify virtual reality development in Unreal. It includes a variety of different classes, each of which perform specific functionality designed to improve overall ease of development.

VRBase implements all basic virtual reality actors (such as the player pawn) C++. You will not need to program the camera or controllers, allowing greater flexibility in game development.

## Table of Contents
1. [Installation](#install)
2. [VRBase Projects](#projects)
3. [Documentation](#doc)

## Installation <a name="install"></a>

VRBase is only a library and therefore can only be added to an existing Unreal project.

1. Clone VRBase into an Unreal project under the directory `Source/PROJECTNAME/VRBase`.
2. Right-click the Unreal `uproject` file in the main root directory and select _Generate Visual Studio Project Files_ to regenerate a clean Visual Studio `sln` file.
3. Update the `PROJECTNAME.Build.cs` file to include VRBase. This file is located in the `Source/PROJECTNAME/` directory. The snippet below can be copied and pasted into the file. **Be sure to change the project name**:
```cs
using System.IO;
using UnrealBuildTool;

public class YOURPROJECTNAME : ModuleRules {
	public YOURPROJECTNAME(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Slate", "SlateCore", "ProceduralMeshComponent" });
        PrivateDependencyModuleNames.AddRange(new string[] { "HeadMountedDisplay", "SteamVR" });
        
        PublicIncludePaths.Add(Path.GetFullPath(Path.Combine(ModuleDirectory, "VRBase")));
    }
}
```
4. After opening the Unreal project in the editor, VRBase **requires** an instance of [AGameRules](Doc/AGameRules.md) to be included in the level UMap for VRBase to function properly. VRBase classes may not work otherwise.

## VRBase Projects <a name="projects"></a>

Below is a list of projects in which VRBase has been used:

- [Archery](https://github.com/bossley9/Archery)
- [The Great Balloon Race](https://github.com/MMC-Scholars/TheGreatBalloonRace)
- [Office Recreation](https://github.com/MMC-Scholars/OfficeRecreation)

## Documentation <a name="doc"></a>

See the [documentation page](Doc/Doc.md) for more information.
