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

#if AKU_MESH_FBX
    #include "LucusMeshFormatFBX.h"
#endif

void AKUModulesCreate()
{
#if AKU_MESH_FBX
    LucusEngine::Core::GetMeshFormatMgr()->RegisterFormat<LucusEngine::FBXMeshFormat>( "fbx" );
#endif
}


#endif /* _LUCUS_ENGINE_MODULES_H */
