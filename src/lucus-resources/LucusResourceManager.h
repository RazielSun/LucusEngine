//
//  LucusResourceManager.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 06/04/2020.
//

#ifndef _LUCUS_ENGINE_RESOURCE_MANAGER_H
#define _LUCUS_ENGINE_RESOURCE_MANAGER_H

#include "LucusTypes.h"

namespace tinyxml2
{
    class XMLDocument;
}

namespace LucusEngine
{
    class ResourceManager
    {
    public:
        ResourceManager();
        ~ResourceManager();

        u32 LoadXMLFile( cc8* name, tinyxml2::XMLDocument& document );
    };
}

#endif /* _LUCUS_ENGINE_RESOURCE_MANAGER_H */
