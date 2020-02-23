//
//  LucusMeshFormatFBX.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 22/02/2020.
//

#include "LucusMeshFormatFBX.h"
#include "LucusMesh.h"
#include "LucusMath.h"

using namespace LucusEngine;

FBXMeshFormat::FBXMeshFormat()
{
    // Prepare the FBX SDK.
    mSdkManager = FbxManager::Create();
    
    if( !mSdkManager )
    {
        FBXSDK_printf("Error: Unable to create FBX Manager!\n");
    }
    else FBXSDK_printf("Autodesk FBX SDK version %s\n", mSdkManager->GetVersion());
    
    //Create an IOSettings object. This object holds all import/export settings.
    FbxIOSettings* ios = FbxIOSettings::Create(mSdkManager, IOSROOT);
    // Set the import states. By default, the import states are always set to
    // true. The code below shows how to change these states.
    ios->SetBoolProp(IMP_FBX_MATERIAL,        true);
    ios->SetBoolProp(IMP_FBX_TEXTURE,         true);
    ios->SetBoolProp(IMP_FBX_LINK,            true);
    ios->SetBoolProp(IMP_FBX_SHAPE,           true);
    ios->SetBoolProp(IMP_FBX_GOBO,            true);
    ios->SetBoolProp(IMP_FBX_ANIMATION,       true);
    ios->SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
    
    mSdkManager->SetIOSettings(ios);
}

FBXMeshFormat::~FBXMeshFormat()
{
    //
}

void FBXMeshFormat::LoadMesh( Mesh* mesh, cc8* name )
{
    if (!OpenFile( name ))
    {
        return;
    }
    
    ConvertScene();
    
    TriangulateScene();
    
    mMeshNodes.clear();
    AddMeshNode(mScene->GetRootNode());
    
    for (int i = 0; i < mMeshNodes.size(); i++)
    {
        FbxNode* node = mMeshNodes.at(i);
        LoadPositionNormalTexCoord(node->GetMesh(), mesh);
    }
}

bool FBXMeshFormat::OpenFile( cc8* path )
{
    // Create an importer.
    FbxImporter* mImporter = FbxImporter::Create(mSdkManager,"");
    
    // Load the scene.
    int lFileMajor, lFileMinor, lFileRevision;
    int lSDKMajor,  lSDKMinor,  lSDKRevision;
    
    // Get the file version number generate by the FBX SDK.
    FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);
    
    // Initialize the importer by providing a filename.
    const bool lImportStatus = mImporter->Initialize(path, -1, mSdkManager->GetIOSettings());
    mImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);
    
    if( !lImportStatus )
    {
        FbxString error = mImporter->GetStatus().GetErrorString();
        FBXSDK_printf("Call to FbxImporter::Initialize() failed.\n");
        FBXSDK_printf("Error returned: %s\n\n", error.Buffer());

        if (mImporter->GetStatus().GetCode() == FbxStatus::eInvalidFileVersion)
        {
            FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
            FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", path, lFileMajor, lFileMinor, lFileRevision);
        }

        return false;
    }
    
    FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
    
    if (mImporter->IsFBX())
    {
        FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", path, lFileMajor, lFileMinor, lFileRevision);

        // From this point, it is possible to access animation stack information without
        // the expense of loading the entire file.

        FBXSDK_printf("Animation Stack Information\n");

        int lAnimStackCount = mImporter->GetAnimStackCount();

        FBXSDK_printf("    Number of Animation Stacks: %d\n", lAnimStackCount);
        FBXSDK_printf("    Current Animation Stack: \"%s\"\n", mImporter->GetActiveAnimStackName().Buffer());
        FBXSDK_printf("\n");

        for(int i = 0; i < lAnimStackCount; i++)
        {
            FbxTakeInfo* lTakeInfo = mImporter->GetTakeInfo(i);

            FBXSDK_printf("    Animation Stack %d\n", i);
            FBXSDK_printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
            FBXSDK_printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

            // Change the value of the import name if the animation stack should be imported
            // under a different name.
            FBXSDK_printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

            // Set the value of the import state to false if the animation stack should be not
            // be imported.
            FBXSDK_printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
            FBXSDK_printf("\n");
        }
    }
    
    mScene = FbxScene::Create(mSdkManager, "ImportScene");
    
    bool lResult = mImporter->Import(mScene);
    
    u32 animStackCount = mScene->GetSrcObjectCount<FbxAnimStack>();
    int i, j, l, a;
    FBXSDK_printf("Animation Stack Information (LOADED SCENE)\n");
    for ( a = 0; a < animStackCount; a++ )
    {
        FbxAnimStack* animStack = mScene->GetSrcObject<FbxAnimStack>(a);
        
        FBXSDK_printf("     Name: %s\n", animStack->GetName());
        
        const int layerCount = animStack->GetMemberCount<FbxAnimLayer>();
        FBXSDK_printf("     Layers: %d\n", layerCount);
        
        for (i = 0; i < layerCount; i++)
        {
            FbxAnimLayer* layer = animStack->GetMember<FbxAnimLayer>(i);
            FBXSDK_printf("         Layer %d: %s\n", i, layer->GetName());
            
            const int curveNodeCount = layer->GetSrcObjectCount<FbxAnimCurveNode>();
            FBXSDK_printf("         Layer %d: curve nodes %d\n", i, curveNodeCount);
            
            for (j = 0; j < curveNodeCount; j++)
            {
                FbxAnimCurveNode* curveNode = layer->GetSrcObject<FbxAnimCurveNode>(j);
                FBXSDK_printf("             CNode %d: %s\n", j, curveNode->GetName());
                
                const int propCount = curveNode->GetDstPropertyCount();
                FBXSDK_printf("             CNode %d: properties %d\n", j, propCount);
                
                const int curveCount = curveNode->GetCurveCount(0);
                FBXSDK_printf("             CNode %d: curves %d\n", j, curveCount);
                
                for (l = 0; l < curveCount; l++)
                {
                    FbxAnimCurve* curve = curveNode->GetCurve(0,l);
                    FBXSDK_printf("                     Curve %d: %s\n", l, curve->GetName());
                }
            }
        }
        FBXSDK_printf("\n");
    }
    
    mImporter->Destroy();
    
    return lResult;
}

void FBXMeshFormat::ConvertScene()
{
    // Setup X, Y, Z axis
    
    // Setup cm or m system
}

void FBXMeshFormat::TriangulateScene()
{
    // Triangulate before use
    FbxGeometryConverter converter(mSdkManager);
    converter.Triangulate(mScene, true);
}

void FBXMeshFormat::AddMeshNode(FbxNode* node)
{
    FbxNodeAttribute* nodeAttribute = node->GetNodeAttribute();
    if ( nodeAttribute )
    {
        FbxNodeAttribute::EType nodeType = nodeAttribute->GetAttributeType();
        if (nodeType == FbxNodeAttribute::eMesh)
        {
            mMeshNodes.push_back(node);
        }
    }
    
    for (int i = 0; i < node->GetChildCount(); i++)
    {
        AddMeshNode(node->GetChild(i));
    }
}

void FBXMeshFormat::LoadPositionNormalTexCoord(FbxMesh* data, Mesh* mesh)
{
    std::vector<FVector3> vertices;
    std::vector<FVector2> texcoords;
    std::vector<FVector3> normals;
    std::vector<FMeshFaceData> faces;
    
    int verticesCount = data->GetControlPointsCount(); // for cube - 8
    int indicesCount = data->GetPolygonVertexCount(); // for cube - 24 & 36 (total indices = poly * tri :: 12 * 3 = 36) 6 * 4 = 24
    int polyCount = data->GetPolygonCount(); // for cube - 6 (face) 12 (triangles)
    FBXSDK_printf("    Mesh Data\n");
    FBXSDK_printf("         Vertices: \"%d\"\n", verticesCount);
    FBXSDK_printf("         Indices: \"%d\"\n", indicesCount);
    FBXSDK_printf("         Poly: \"%d\"\n", polyCount);
    FBXSDK_printf("\n");
    
//    int uvCount = data->GetUVLayerCount();
//    int texUvCount = data->GetTextureUVCount();
//    int elemUvCount = data->GetElementUVCount();
//    FBXSDK_printf("   - UV count %d tex %d element %d\n", uvCount, texUvCount, elemUvCount);
    
    for (int vid = 0; vid < verticesCount; vid++)
    {
        FbxVector4 vertex = data->GetControlPointAt(vid);

        vertices.push_back( (FVector3){(float)vertex[0], (float)vertex[1], (float)vertex[2]} );
        
//        FBXSDK_printf("    %d vertex: %f %f %f\n", vid, (float)vertex[0], (float)vertex[1], (float)vertex[2]);
    }
    
    int layers = data->GetLayerCount();
    if (layers > 0)
    {
        FbxLayer* layer = data->GetLayer(0);
        
        FbxLayerElementUV* elemUV = layer->GetUVs();
        
        // index 20 direct 24
//        FBXSDK_printf("   - Layer0 uv: %s  index: %d direct: %d\n", elemUV->GetName(), elemUV->GetIndexArray().GetCount(), elemUV->GetDirectArray().GetCount());
        int uvCount = elemUV->GetDirectArray().GetCount();
        for (int i = 0; i < uvCount; i++)
        {
            FbxVector2 uv = elemUV->GetDirectArray()[i];
            texcoords.push_back( (FVector2){(float)uv[0], (float)uv[1]} );
//            FBXSDK_printf("   - Layer0 uv: i %i  %f %f\n", i, (float)uv[0], (float)uv[1]);
        }
        
        FBXSDK_printf("    UV Data\n");
        FBXSDK_printf("         Count: \"%d\"\n", uvCount);
        FBXSDK_printf("\n");
        
//        FbxLayerElementNormal* elemNormal = layer->GetNormals();
        
        // index 0 direct 24
//        FBXSDK_printf("   - Layer0 normal: %s index: %d direct: %d\n", elemNormal->GetName(), elemNormal->GetIndexArray().GetCount(), elemNormal->GetDirectArray().GetCount());
        
//        int normalCount = elemNormal->GetDirectArray().GetCount();
//        for (int i = 0; i < normalCount; i++)
//        {
//            FbxVector4 normal = elemNormal->GetDirectArray()[i];
//
//            normals.push_back( (FVector3){(float)normal[0], (float)normal[1], (float)normal[2]} );
//            FBXSDK_printf("   - Layer0 normal: i %i  %f %f %f\n", i, (float)normal[0], (float)normal[1], (float)normal[2]);
//        }
        
        FbxArray<FbxVector4> mNormals;
        data->GetPolygonVertexNormals(mNormals);
        
        FBXSDK_printf("    Normal Data\n");
        FBXSDK_printf("         Count: \"%d\"\n", mNormals.GetCount());
        FBXSDK_printf("\n");
        
        for (int i = 0; i < mNormals.GetCount(); i++)
        {
            FbxVector4 normal = mNormals[i];
            normals.push_back( (FVector3){(float)normal[0], (float)normal[1], (float)normal[2]} );
        }
    }
    
    for (int p = 0; p < polyCount; p++)
    {
        FMeshFaceData face;
        
//        int startPolyIndex = data->GetPolygonVertexIndex(p);
//        int* indices = data->GetPolygonVertices() + startPolyIndex;
        int polySize = data->GetPolygonSize(p);
        
        face.count = polySize;
        
        for (int v = 0; v < polySize; v++)
        {
            face.tris[v].x = data->GetPolygonVertex(p, v);
            face.tris[v].y = data->GetTextureUVIndex(p, v);
            face.tris[v].z = p * polySize + v; // normals indices same as face counter
            
//            FbxVector4 pNormal;
//            data->GetPolygonVertexNormal(p, v, pNormal); // Good
            
//            FVector3 tNormal = normals[data->GetPolygonVertex(p, v)]; // Wrong Normals
            
//            FBXSDK_printf("         %d.poly %d.vertex : %f %f %f :: %f %f %f \n", p, v, pNormal[0], pNormal[1], pNormal[2], tNormal.x, tNormal.y, tNormal.z);
            
//            FBXSDK_printf("         %d.poly %d.vertex : %d \n", p, v, idx);
        }
        
//        u32 idx1 = static_cast<u32>(indices[0]);
//        face.points[0].x = idx1;
        
//        if (polySize == 3)
//        {
////            mesh->AddFace(idx1, idx2, idx3);
//            FBXSDK_printf("    %d.poly : start %d :: (3) - %d %d %d \n", p, startPolyIndex, idx1, idx2, idx3);
//        }
//        else if (polySize == 4)
//        {
//            u32 idx4 = static_cast<u32>(indices[3]);
//
//            face.points[3].x = idx4;
//
////            mesh->AddFace(idx1, idx2, idx3, idx4);
//            FBXSDK_printf("    %d.poly : start %d :: (4) - %d %d %d %d \n", p, startPolyIndex, idx1, idx2, idx3, idx4);
//        }
        
//        if (layers > 0)
//        {
//            FbxLayer* layer = data->GetLayer(0);
//
//            FbxLayerElementUV* elemUV = layer->GetUVs();
//            int uvIndexCount = elemUV->GetIndexArray().GetCount();
//            if (uvIndexCount > 0)
//            {
//                face.points[0].y = data->GetTextureUVIndex(p, 0);
//                face.points[1].y = data->GetTextureUVIndex(p, 1);
//                face.points[2].y = data->GetTextureUVIndex(p, 2);
//                if (polySize == 4)
//                {
//                    face.points[3].y = data->GetTextureUVIndex(p, 3);
//                }
//            }
//            else
//            {
//                //
//            }
//
//            FbxLayerElementNormal* elemNormal = layer->GetNormals();
//            int normalIndexCount = elemNormal->GetIndexArray().GetCount();
//            if (normalIndexCount > 0)
//            {
//                //
//            }
//            else
//            {
//                int id1 = data->GetPolygonVertex(p, 0);
//                int id2 = data->GetPolygonVertex(p, 1);
//                int id3 = data->GetPolygonVertex(p, 2);
//                face.points[0].z = idx1;
//                face.points[1].z = idx2;
//                face.points[2].z = idx3;
//                FBXSDK_printf("    %d.poly : start %d :: normal %d %d %d :: %d %d %d\n", p, startPolyIndex, idx1, idx2, idx3, id1, id2, id3);
//                if (polySize == 4)
//                {
//                    u32 idx4 = static_cast<u32>(indices[3]);
//                    face.points[3].z = idx4;
//                }
//            }
//        }
        
        faces.push_back(face);
    }
    
//    mesh->Load(vertices, texcoords, normals, faces);
    
    FBXSDK_printf("    Done\n");
}
