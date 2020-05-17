//
//  LucusResourceManager.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 06/04/2020.
//

#ifndef _LUCUS_ENGINE_RESOURCE_MANAGER_H
#define _LUCUS_ENGINE_RESOURCE_MANAGER_H

#include "LucusTypes.h"
#include "LucusMesh.h"
#include "LucusImage.h"

namespace tinyxml2
{
    class XMLDocument;
}

namespace LucusEngine
{
	typedef std::map<u32, MeshPtr> MeshMap;
	typedef MeshMap::iterator MeshMapIt;

	typedef std::map<u32, ImagePtr> ImageMap;
	typedef ImageMap::iterator ImageMapIt;

    class ResourceManager
    {
    	MeshMap mMeshes;
    	ImageMap mImages;

    public:
        ResourceManager();
        ~ResourceManager();

        MeshPtr GetMesh( cc8* name );
        ImagePtr GetImage( cc8* name );

        u32 LoadXMLFile( cc8* name, tinyxml2::XMLDocument& document );

    protected:

    	bool LoadMesh( cc8* name );
    	bool LoadImage( cc8* name );

    };
}

#endif /* _LUCUS_ENGINE_RESOURCE_MANAGER_H */
