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

// #include "LucusCore.h"
// #include "LucusFileSystem.h"
#include "LucusMeshFormatManager.h"
#include "LucusMeshFormat.h"

// #include "LucusCore.h"
// #include "LucusFileSystem.h"
#include "LucusImageFormatManager.h"
#include "LucusImageFormat.h"

#include "LucusUtils.h"

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

MeshPtr ResourceManager::GetMesh(cc8* name) 
{
	u32 hashKey = Utils::HashString(name);
	MeshMapIt it = mMeshes.find(hashKey);
	if (it != mMeshes.end())
	{
		return it->second;
	}
	if (LoadMesh(name))
	{
		it = mMeshes.find(hashKey);
		if (it != mMeshes.end())
		{
			return it->second;
		}
	}
	return MeshPtr();
}

ImagePtr ResourceManager::GetImage(cc8* name) 
{
	u32 hashKey = Utils::HashString(name);
	ImageMapIt it = mImages.find(hashKey);
	if (it != mImages.end())
	{
		return it->second;
	}
	if (LoadImage(name))
	{
		it = mImages.find(hashKey);
		if (it != mImages.end())
		{
			return it->second;
		}
	}
	return ImagePtr();
}

bool ResourceManager::LoadMesh(cc8* name) 
{
	std::string formatName = Core::GetFileSystem()->GetFileFormat( name );
    MeshFormat* meshFormat = Core::GetMeshFormatMgr()->FindFormat( formatName.c_str() );
    if (nullptr != meshFormat)
    {
    	Mesh* mesh = new Mesh();
        meshFormat->LoadMesh(mesh, Core::GetFileSystem()->GetAssetPath(name).c_str());
        mMeshes.emplace(Utils::HashString(name), mesh);
        return true;
    }
    return false;
}

bool ResourceManager::LoadImage(cc8* name) 
{
	std::string formatName = Core::GetFileSystem()->GetFileFormat( name );
    ImageFormat* imageFormat = Core::GetImageFormatMgr()->FindFormat( formatName.c_str() );
    if (nullptr != imageFormat)
    {
    	Image* image = new Image();
        imageFormat->LoadImage(image, Core::GetFileSystem()->GetAssetPath(name).c_str());
        mImages.emplace(Utils::HashString(name), image);
        return true;
    }
    return false;
}
