//
//  LucusMeshFormatFBX.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 22/02/2020.
//

#ifndef _LUCUS_ENGINE_MESH_FORMAT_FBX_H
#define _LUCUS_ENGINE_MESH_FORMAT_FBX_H

#include "LucusMeshFormat.h"
#include "LucusVertexTypes.h"
#include "LucusMesh.h"
#include <fbxsdk.h>
#include <vector>

namespace LucusEngine
{
    typedef std::unordered_map<TriangleIndex, u32> VertexIndexMap;

    class MeshFormatFBX : public MeshFormat
    {
        FbxManager* mSdkManager;
        FbxGeometryConverter* mConverter;
        FbxScene* mScene;
        std::vector<FbxNode*> mMeshNodes;
        VertexIndexMap mMap;
        
    public:
        MeshFormatFBX();
        virtual ~MeshFormatFBX();
        
        virtual void LoadMesh( Mesh* mesh, cc8* name ) override;
        
    protected:
        bool OpenFile( cc8* path );
        void ConvertScene();
        void TriangulateScene();
        void AddMeshNode( FbxNode* node );
        void LoadPositionNormalTexCoord( FbxMesh* data, Mesh* mesh );
        u32 GetVertexIndexFrom(const TriangleIndex& idx,
                                std::vector<SimpleVertex>& outvert,
                                const std::vector<FVector3>& positions,
                                const std::vector<FVector2>& texcoords,
                                const std::vector<FVector3>& normals);
    };
}

#endif /* _LUCUS_ENGINE_MESH_FORMAT_FBX_H */
