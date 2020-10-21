# VRBase Library 2.0.0
VRBase is a simple C++ Unreal Engine 4 library designed to simplify virtual reality development in the Unreal Editor. It includes a variety of different classes, each of which perform specific functionality designed to improve overall ease of development.

VRBase implements all essential virtual reality classes in C++. This mitigates the need to program a camera or controllers, allowing greater flexibility in game development.

## Table of Contents
1. [Installation](#install)
2. [Code Formatting](#codeFormatting)
3. [VRBase Projects](#projects)
4. [Documentation](#doc)

## Installation <a name="install"></a>
VRBase must be added to an _existing_ Unreal project.

1. Clone VRBase into an existing Unreal project under the directory `Source/PROJECTNAME/VRBase`.
2. Right-click the Unreal `uproject` file in the main root directory and select _Generate Visual Studio Project Files_ to regenerate a clean Visual Studio `sln` file.
3. Update the `PROJECTNAME.Build.cs` file to include VRBase. This file is located in the `Source/PROJECTNAME/` directory. The snippet below can be copied and pasted into the file. **Be sure to change the project name**:
```cs
using System.IO;
using UnrealBuildTool;

public class YOURPROJECTNAME : ModuleRules {
    public YOURPROJECTNAME(ReadOnlyTargetRules Target) : base(Target) {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Slate", "SlateCore", "ProceduralMeshComponent" });
        PrivateDependencyModuleNames.AddRange(new string[] { "HeadMountedDisplay", "SteamVR" });

        PublicIncludePaths.AddRange(
            new string[]
            {
                Path.GetFullPath(Path.Combine(ModuleDirectory, "VRBase")),
                Path.GetFullPath(ModuleDirectory)
            }
        );
    }
}
```
4. After opening the Unreal project in the editor, VRBase **requires** an instance of [AGameRules](Doc/AGameRules.md) to be included in the level UMap for VRBase to function properly. VRBase classes will not function properly otherwise.

## Code Formatting <a name="codeFormatting"></a>
Code formatting, also known as linting, is the process of running a program to check and format source code files  according to a certain project or language specification. Without linting, each developer adds their own code style to the codebase, causing inconsistent formatting and making source code harder to read. Linting fixes these issues by formatting code for developers, allowing developers to focus more on the content of the code rather than indentation and spacing.

In VRBase, we use `clang-format` to maintain our codebase. To add this to your editor/IDE:

**Visual Studio:**

Typing `ctrl-k ctrl-d` will automatically format the focused document.

However, Visual Studio does not offer any method of auto-formatting code on save, so
each edited file will need to be formatted manually.

**Visual Studio Code:**

Download the `clang` libraries found on the [LLVM download page](https://releases.llvm.org/download.html),
using the [LLVM 11.0.0 Windows 64-bit pre-built binary](https://github.com/llvm/llvm-project/releases/download/llvmorg-11.0.0/LLVM-11.0.0-win64.exe). 
**Be sure to add LLVM to the system path for all users if prompted.** Once installed, you will need to restart your computer for your system path to be updated.

Next, install the [`clang-format`](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format) 
extension for VS Code. Once installed, you can enable `Format On Save` in VS Code settings to automatically format your code on save.

Alternatively, you can edit the json settings as follows:
```json
"[cpp]": {
    "editor.defaultFormatter": "xaver.clang-format",
    "editor.formatOnSave": true
},
```

## VRBase Projects <a name="projects"></a>
Below is a cumulative list of projects in which VRBase has been used:

- [Archery](https://github.com/bossley9/Archery)
- [Crime Solver](https://github.com/MMC-Scholars/CrimeSolver)
- [The Great Balloon Race](https://github.com/MMC-Scholars/TheGreatBalloonRace)
- [Office Recreation](https://github.com/MMC-Scholars/OfficeRecreation)

## Documentation <a name="doc"></a>
See the [documentation page](Doc/Doc.md) for more information.
