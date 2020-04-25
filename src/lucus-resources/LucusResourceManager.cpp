//
//  LucusResourceManager.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 06/04/2020.
//

#include "tinyxml2.h"

#include "LucusResourceManager.h"
#include "LucusFileSystem.h"
#include "LucusCore.h"

using namespace tinyxml2;

using namespace LucusEngine;

ResourceManager::ResourceManager()
{
    //
}

ResourceManager::~ResourceManager()
{
    //
}

u32 ResourceManager::LoadXMLFile( cc8* name, XMLDocument& document )
{
    document.LoadFile( Core::GetFileSystem()->GetAssetPath(name).c_str() );
    return (u32)document.ErrorID();
}
