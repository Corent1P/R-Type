local LIMIT_TOP = 200
local LIMIT_BOTTOM = 850

Ennemy = {
    name = "",
    timeStamp = 0.0,
    height = 0
}

function Ennemy:new(o, name, timeStamp, height)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    o.name = name
    o.timeStamp = timeStamp
    o.height = height
    return o
end

Level = {}

function Level.addEnnemy(name, timeStamp, height)
    if name == "fly" or name == "octopus" or name == "space_ship_1" then
        height = math.max(LIMIT_TOP, math.min(height, LIMIT_BOTTOM))
    end
    table.insert(Level, Ennemy:new(nil, name, timeStamp, height))
end

function Level.spawnColumn(name, timeStamp, height, spacing, count)
    spacing = spacing or 50
    count = count or 10
    for i = 0, count - 1 do
        Level.addEnnemy(name, timeStamp + (i * 0.2), height - (i * spacing))
    end
end

function Level.spawnPack(name, timeStamp, height)
    Level.addEnnemy(name, timeStamp, height)
    Level.addEnnemy(name, timeStamp + 0.2, height - 40)
    Level.addEnnemy(name, timeStamp + 0.4, height + 60)
    Level.addEnnemy(name, timeStamp + 0.6, height)
end

function Level.spawnMixedWave(name1, name2, timeStamp, height, spacing, count)
    spacing = spacing or 60
    count = count or 5
    local timeSpacing = 0.25

    for i = 0, count - 1 do
        local name = i % 2 == 0 and name1 or name2
        Level.addEnnemy(name, timeStamp + (i * timeSpacing), height + (i * spacing))
    end
end

function Level.spawnVFormation(name, timeStamp, height, spread)
    spread = spread or 30
    Level.addEnnemy(name, timeStamp, height)
    Level.addEnnemy(name, timeStamp + 0.1, height + spread)
    Level.addEnnemy(name, timeStamp + 0.2, height - spread)
    Level.addEnnemy(name, timeStamp + 0.3, height + (spread * 2))
    Level.addEnnemy(name, timeStamp + 0.4, height - (spread * 2))
end

function Level.spawnHorizontalLine(name, timeStamp, height, spacing, count)
    spacing = spacing or 80
    count = count or 6
    for i = 0, count - 1 do
        Level.addEnnemy(name, timeStamp + (i * 0.15), height)
    end
end

function Level.spawnVerticalLine(name, timeStamp, height, spacing, count)
    spacing = spacing or 80
    count = count or 6
    for i = 0, count - 1 do
        Level.addEnnemy(name, timeStamp + (i * 0.15), height + (i * spacing))
    end
end

function Level.spawnCircle(name, timeStamp, centerY, radius, count)
    count = count or 8
    local angleStep = (2 * math.pi) / count
    for i = 0, count - 1 do
        local angle = i * angleStep
        local height = math.max(LIMIT_TOP, math.min(centerY + math.sin(angle) * radius, LIMIT_BOTTOM))
        Level.addEnnemy(name, timeStamp + (i * 0.1), height)
    end
end

function Level.spawnZigzag(name, timeStamp, startHeight, amplitude, count, timeStep)
    amplitude = amplitude or 100
    count = count or 10
    timeStep = timeStep or 0.2
    for i = 0, count - 1 do
        local height = startHeight + (i % 2 == 0 and amplitude or -amplitude)
        height = math.max(LIMIT_TOP, math.min(height, LIMIT_BOTTOM))
        Level.addEnnemy(name, timeStamp + (i * timeStep), height)
    end
end

Level.addEnnemy("item_heal", 5, 1080 / 4)
Level.addEnnemy("item_heal", 5, 1080 / 2)
Level.addEnnemy("item_heal", 5, 1080 / 4 * 3)


Level.addEnnemy("item_forcepod", 8, 1080 / 2)

Level.spawnVerticalLine("space_ship_1", 10, 250, 70, 4)
Level.spawnVerticalLine("fly", 10, 200, 80, 5)

Level.spawnPack("fly", 13, 600)
Level.spawnVerticalLine("space_ship_1", 14, 300, 90, 4)
Level.spawnHorizontalLine("fly", 15, 700, 70, 5)
Level.spawnCircle("space_ship_1", 16, 500, 120, 6)

Level.addEnnemy("space_ship_1", 17, 200)
Level.addEnnemy("fly", 18, 400)
Level.addEnnemy("fly", 18.3, 500)
Level.addEnnemy("fly", 18.6, 600)
Level.addEnnemy("fly", 18.9, 700)

Level.addEnnemy("item_heal", 19.5, 1080 / 2)

Level.spawnMixedWave("fly", "octopus", 20, 450, 50, 6)

Level.spawnZigzag("space_ship_1", 21, 300, 200, 5, 0.4)
Level.spawnCircle("fly", 22, 750, 200, 10)

Level.addEnnemy("item_shield", 24, 540)

Level.spawnVFormation("space_ship_1", 25, 600, 50)

Level.spawnColumn("fly", 28, 800, 40, 5)
Level.spawnMixedWave("fly", "space_ship_1", 30, 600, 70, 8)

Level.addEnnemy("item_heal", 32, 1080 / 2)

Level.addEnnemy("octopus", 32.5, 500)
Level.addEnnemy("octopus", 33, 650)

Level.spawnHorizontalLine("space_ship_2", 35, 850, 90, 4)
Level.spawnZigzag("octopus", 37, 400, 200, 10, 0.2)

Level.spawnVFormation("space_ship_3", 40, 700, 60)
Level.spawnPack("space_ship_1", 42, 400)

Level.spawnCircle("fly", 44, 800, 250, 12)

Level.addEnnemy("item_weapon", 47, 900)


Level.addEnnemy("item_heal", 48, 1080 / 5 * 2)
Level.addEnnemy("item_heal", 48, 1080 / 5 * 3)


Level.addEnnemy("space_ship_boss", 42 + 10, 0)

function Level.update(dt)
    local time = tonumber(dt)
    for _, ennemy in ipairs(Level) do
        if ennemy.timeStamp >= time - 0.05 and ennemy.timeStamp <= time + 0.05 then
            createEntity(ennemy.name, math.floor(ennemy.height), 1920)
        end
    end
end
