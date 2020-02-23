//
//  LucusMesh.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 22/02/2020.
//

#include "LucusCore.h"
#include "LucusMesh.h"
#include "LucusMeshFormat.h"

using namespace LucusEngine;

Mesh::Mesh()
{
    //
}

Mesh::~Mesh()
{
    //
}

void Mesh::Load( cc8* name )
{
    std::string formatName = Core::GetFileSystem()->GetFileFormat( name );
    MeshFormat* meshFormat = Core::GetMeshFormatMgr()->FindFormat( formatName.c_str() );
    if (nullptr != meshFormat)
    {
        meshFormat->LoadMesh(this, name);
    }
}
