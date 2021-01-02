
print("[LUA] Lua loaded!")

print("[LUA] default libs loaded: "..math.sin(1))

-- if World then
--     local rootComp = nil
--     if SceneComponent then
--         rootComp = SceneComponent()
--         print("[LUA] rootComp = " .. tostring(rootComp))
--         rootComp:SetLocation(0, 0, 3)
--     end
--     local meshComp = nil
--     if MeshComponent then
--         meshComp = MeshComponent()
--         print("[LUA] meshComp = " .. tostring(meshComp))
--         meshComp:SetMesh("Assets/meshes/cube.fbx")
--         meshComp:SetImage("Assets/textures/test-image.tga")
--         if rootComp then
--             rootComp:AddChild(meshComp)
--         end
--     end
--     local actor = nil
--     if Actor then
--         actor = Actor()
--         print("[LUA] actor = " .. tostring(actor))
--         actor:SetRootComponent(rootComp)
--     end
--     World:AddActor(actor)
-- end

function GetImage( name )
    return "Assets/textures/" .. name
end

function GetMesh( name )
    return "Assets/meshes/"..name..".fbx"
end

function SpawnCamera( Location )
    local root = SpringArmComponent()
    local camera = CameraComponent()
    camera:SetLocation( table.unpack(Location))
    root:AddChild(camera)
    local actor = Actor()
    actor:SetRootComponent(root)
    World:AddActor(actor)
end

function SpawnActor( Component, Mesh, Image, Location )
    local Create = Component or MeshComponent
    local mesh = Create()
    mesh:SetMesh(GetMesh(Mesh))
    mesh:SetImage(GetImage(Image))
    local Loc = Location or { 0, 0, 0 }
    mesh:SetLocation( table.unpack(Loc) )
    local actor = Actor()
    actor:SetRootComponent(mesh)
    World:AddActor(actor)
end

SpawnCamera({0, 0, -3})
SpawnActor(nil, "cube", "test-image.tga")
SpawnActor(RotatedMeshComponent, "cube", "checker.png", { 1, 0, 0 })
SpawnActor(nil, "cube", "checker-map.png", { -1, 0, 0 })
