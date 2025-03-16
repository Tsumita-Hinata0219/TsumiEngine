-- SphereEmitter
SphereEmitter = {
    translate = { x = 0.0, y = 0.0, z = 0.0, w = 0.0 },
    radius = { x = 2.0, y = 2.0, z = 2.0, w = 2.0 },
}

-- EmitterRange
EmitterRange = {
    scaleMin = { x = 0.5, y = 0.5, z = 0.5, w = 0.5 },
    scaleMax = { x = 0.5, y = 0.5, z = 0.5, w = 0.5 },

    rotateMin = { x = 0.0, y = 0.0, z = 0.0, w = 0.0 },
    rotateMax = { x = 0.0, y = 0.0, z = 0.0, w = 0.0 },

    colorMin = { x = 0.0, y = 0.0, z = 0.0, w = 1.0 },
    colorMax = { x = 1.0, y = 1.0, z = 1.0, w = 1.0 },

    velocityMin = { x = -0.3, y = 0.0, z = -0.3, w = 0.0 },
    velocityMax = { x = 0.3, y = 1.0, z = 0.3, w = 0.0 },

    baseLifeTime = 0.5 * 60.0,
    lifeTimeMin = 0.0,
    lifeTimeMax = 0.0,
}

-- EmitterConfig
EmitConfig = {
    spawnInterval = 0.1,
    elapsedTime = 0.1,
    spawnCount = 250,
    isEmitting = false,
}


-- ConstantField
ConstantField = {
    acceleration = { x = 0.0, y = 0.0, z = 0.0 },
    damping = 1.0,
    angularVelocity = { x = 0.0, y = 0.0, z = 0.0 },
    drag = 0.0,
    force = { x = 0.0, y = 0.0, z = 0.0 },
    mass = 0.0,
    isUse = false,
}






-- 円運動のパラメータ
local radius = 5.0      -- 半径
local speed = 1.0       -- 移動速度（角速度）
local cx, cz = 0, 0     -- 円の中心（x軸, z軸）

-- 移動を管理する変数
local angle = 0         -- 現在の角度（ラジアン）
local position = { x = cx + radius, z = cz }

-- 毎フレーム更新する関数
function UpdateMovement(deltaTime)
    -- 角度の更新（角速度 * 時間経過）
    angle = angle + speed * deltaTime

    -- 角度が2πを超えたらリセット
    if angle > math.pi * 2 then
        angle = angle - math.pi * 2
    end

    -- 新しい位置を計算（円運動の式）
    position.x = cx + radius * math.cos(angle)
    position.z = cz + radius * math.sin(angle)

    -- 結果を返す
    return position
end