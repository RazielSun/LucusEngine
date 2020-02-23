//
//  LucusMeshFormatFBX.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 22/02/2020.
//

#ifndef _LUCUS_ENGINE_MESH_FORMAT_FBX_H
#define _LUCUS_ENGINE_MESH_FORMAT_FBX_H

#include "LucusMeshFormat.h"
#include <fbxsdk.h>
#include <vector>

namespace LucusEngine
{
    class FBXMeshFormat: public MeshFormat
    {
        FbxManager* mSdkManager;
        FbxScene* mScene;
        std::vector<FbxNode*> mMeshNodes;
        
    public:
        FBXMeshFormat();
        virtual ~FBXMeshFormat();
        
        virtual void LoadMesh( Mesh* mesh, cc8* name ) override;
        
    protected:
        bool OpenFile( cc8* path );
        void ConvertScene();
        void TriangulateScene();
        void AddMeshNode( FbxNode* node );
        void LoadPositionNormalTexCoord( FbxMesh* data, Mesh* mesh );
    };
}

#endif /* _LUCUS_ENGINE_MESH_FORMAT_FBX_H */