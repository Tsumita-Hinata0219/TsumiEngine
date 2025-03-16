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