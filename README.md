# LucusEngine
Custom game engine for own education
## References
IsettaEngine, MOAI SDK, Unreal Engine, OGRE3D

## Engine structure
### 3rdparty
fbx-sdk-osx: 2018.1 - DOWNLOAD FROM
fbx-sdk-uwp: 2019.5 - DOWNLOAD FROM

libpng osx:- static libs (need to compile from source)[https://github.com/glennrp/libpng]
zlib osx: - static libs (need to compile from source)[https://github.com/madler/zlib]

### game
Assets - folder with assets, for xcode/vs2017 projects need to copy from Assets to:
    1) in xcode project to Resource folder
    2) in vs2017 project to LucusGame folder

### src
lucus-core
lucus-render
lucus-sim
lucus-shaders
lucus-mesh-fbx

### templates
MetalTemplate - basic xcode metal game template. (Objective-C)
DirectX12Template - basic UWP visual studio 2017 directx12 app template. (C++)

### xcode
LucusGame - ios/osx test project for the engine.

### vs2017
LucusGame - win10 test project for the engine.

## Roadmap