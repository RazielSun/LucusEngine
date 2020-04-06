//
//  LucusResourceManager.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 06/04/2020.
//

#include "LucusResourceManager.h"
#include "LucusCore.h"

// TEST
#include "tinyxml2.h"
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

void ResourceManager::LoadXMLFile( cc8* name )
{
    XMLDocument doc;
    // "Assets/levels/test_level.xml"
    doc.LoadFile( Core::GetFileSystem()->GetAssetPath(name).c_str() );
    int errorId = doc.ErrorID(); // Error ID File not found
}
