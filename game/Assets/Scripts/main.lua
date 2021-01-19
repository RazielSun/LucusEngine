
print("[LUA] Lua loaded!")

application = {
    width = 1280,
    height = 720,
    title = "Lucus Test Game"
}

lucus = {}
updater = {}

function create_world()
    local world = lucus.World()
    lucus.core.world = world
    return world
end

function create_camera( location )
    local root = lucus.SceneComponent()
    local camera = lucus.CameraComponent()
    camera:SetLocation( table.unpack(location or {0,0,0}) )
    root:AddChild(camera)
    local actor = lucus.Actor()
    actor:SetRootComponent(root)
    local function create_rotator()
        local speed = 30.0
        local yaw = 0.0
        return function(dt)
            local newyaw = yaw + speed * dt
            if newyaw > 360.0 then newyaw = newyaw - 360 end
            if newyaw < -360.0 then newyaw = newyaw + 360 end
            root:SetRotation(0, 0, newyaw)
            yaw = newyaw
        end
    end
    table.insert(updater, create_rotator())
    return actor
end

function create_mesh_actor( mesh, image, location )
    local meshComp = lucus.MeshComponent()
    meshComp:SetMesh(mesh)
    meshComp:SetImage(image)
    meshComp:SetLocation( table.unpack(location or { 0, 0, 0 }) )
    local actor = lucus.Actor()
    actor:SetRootComponent(meshComp)
    return actor, meshComp
end

lucus.init = function()
    print("[LUA] lucus init called")
    local world = create_world()

    local camera = create_camera({0, 0, -3}); world:AddActor(camera);
    local actor1 = create_mesh_actor("cube.fbx", "test-image.tga"); world:AddActor(actor1);
    local actor2 = create_mesh_actor("cube.fbx", "checker.png", { 1, 0, 0 }); world:AddActor(actor2);
    local actor3 = create_mesh_actor("cube.fbx", "checker-map.png", { -1, 0, 0 }); world:AddActor(actor3);
end

lucus.tick = function(dt)
    -- print("[LUA] lucus tick "..dt)
    for _, func in ipairs(updater) do
        func(dt)
    end
end
