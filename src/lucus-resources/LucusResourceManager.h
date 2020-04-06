//
//  LucusResourceManager.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 06/04/2020.
//

#ifndef _LUCUS_ENGINE_RESOURCE_MANAGER_H
#define _LUCUS_ENGINE_RESOURCE_MANAGER_H

#include "LucusTypes.h"

namespace LucusEngine
{
    class ResourceManager
    {
    public:
        ResourceManager();
        ~ResourceManager();

        void LoadXMLFile( cc8* name );
    };
}

#endif /* _LUCUS_ENGINE_RESOURCE_MANAGER_H */
