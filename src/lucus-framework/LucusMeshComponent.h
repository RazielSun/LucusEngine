//
//  LucusMeshComponent.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 5/03/2020.
//

#ifndef _LUCUS_ENGINE_MESH_COMPONENT_H
#define _LUCUS_ENGINE_MESH_COMPONENT_H

#include "LucusSceneComponent.h"
#include "LucusMesh.h"
#include "LucusImage.h"

namespace LucusEngine
{
    class MeshComponent : public SceneComponent
    {
    public:
        MeshComponent();
        MeshComponent(cc8* meshName);
        MeshComponent(cc8* meshName, cc8* imageName);
        virtual ~MeshComponent();
        
        DECL_LUA_OBJECT(MeshComponent)
        
        void SetMesh(cc8* meshName);
        void SetImage(cc8* imageName);
        
        Mesh* GetMesh();
        Image* GetImage();

    protected:
    	MeshPtr mMesh;
        ImagePtr mImage;
    
    public:
        virtual void BindLuaFunctions(lua_State* lua) override;
        
    public:
        static int _setMesh(lua_State* L);
        static int _setImage(lua_State* L);
    };
}

#endif /* _LUCUS_ENGINE_MESH_COMPONENT_H */
