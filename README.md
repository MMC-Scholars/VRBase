# VRBase Plugin v3.0.0

VRBase is a C++ Unreal Engine plugin designed to simplify virtual reality development in Unreal. It includes a variety of different classes, each of which perform specific functionality designed to improve overall ease of development.
It implements all basic virtual reality actors (such as a player pawn) in C++. You will not need to program the camera or controllers, allowing greater flexibility in game development.

## Table of Contents
1. [Installation](#install)
2. [VRBase Projects](#projects)
3. [Documentation](#doc)

## Installation <a name="install"></a>

1. Clone VRBase into an existing Unreal project in the directory `Plugins/VRBase`.
2. Right-click the Unreal `uproject` file in the main root directory and select _Generate Visual Studio Project Files_ to regenerate a clean Visual Studio `sln` file.
3. Open the Visual Studio `sln` and compile all VRBase classes with `CTRL+SHIFT+b`. If prompted, do not disable the VRBase plugin.
4. After opening the Unreal project in the editor, make sure `View Options > Show Plugin Content` is enabled in the bottom right corner of the Content Browser, or VRBase classes will not display otherwise.
5. VRBase requires a single instance of [GameRules](Source/VRBase/Doc/AGameRules.md) to be included in the world for VRBase to function properly. VRBase classes will not work properly otherwise.

## VRBase Projects <a name="projects"></a>

Below is a list of projects in which VRBase has been used:

- [Archery](https://github.com/bossley9/Archery)
- [The Great Balloon Race](https://github.com/MMC-Scholars/TheGreatBalloonRace)
- [Office Recreation](https://github.com/MMC-Scholars/OfficeRecreation)

## Documentation <a name="doc"></a>

See the [documentation page](Source/VRBase/Doc/Doc.md) for more information.
