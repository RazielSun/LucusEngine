//
//  modules.h
//  LucusGame
//
//  Created by Alexander Kardakov on 22/02/2020.
//

#ifndef _LUCUS_ENGINE_MODULES_H
#define _LUCUS_ENGINE_MODULES_H

#include "host.h"
#include "LucusCore.h"

#ifndef AKU_MESH_FBX
    #define AKU_MESH_FBX 1
#endif

#ifndef AKU_IMAGE_TGA
    #define AKU_IMAGE_TGA 1
#endif

#ifndef AKU_IMAGE_PNG
    #define AKU_IMAGE_PNG 1
#endif

#if AKU_MESH_FBX
    #include "LucusMeshFormatFBX.h"
#endif

#if AKU_IMAGE_TGA
    #include "LucusImageFormatTGA.h"
#endif

#if AKU_IMAGE_PNG
    #include "LucusImageFormatPNG.h"
#endif

void AKUModulesCreate()
{
#if AKU_MESH_FBX
    LucusEngine::Core::GetMeshFormatMgr()->RegisterFormat<LucusEngine::MeshFormatFBX>( "fbx" );
#endif

#if AKU_IMAGE_TGA
    LucusEngine::Core::GetImageFormatMgr()->RegisterFormat<LucusEngine::ImageFormatTGA>( "tga" );
#endif

#if AKU_IMAGE_PNG
    LucusEngine::Core::GetImageFormatMgr()->RegisterFormat<LucusEngine::ImageFormatPNG>( "png" );
#endif
}


#endif /* _LUCUS_ENGINE_MODULES_H */
