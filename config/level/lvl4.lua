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


Level.spawnColumn("space_ship_1", 1, 300, 60, 3)
Level.spawnPack("fly", 2.5, 450)
Level.spawnMixedWave("space_ship_4", "fly", 4, 600, 80, 3)

Level.spawnHorizontalLine("fly", 5.5, 750, 70, 5)
Level.spawnCircle("space_ship_1", 6, 500, 150, 4)

Level.addEnnemy("space_ship_4", 7.5, 400)
Level.spawnMixedWave("space_ship_1", "space_ship_4", 8, 300, 80, 4)
Level.spawnPack("octopus", 9, 500)

Level.addEnnemy("item_weapon", 10.5, 500)

Level.spawnZigzag("fly", 11, 350, 150, 6, 0.25)
Level.spawnCircle("space_ship_4", 12.5, 600, 250, 5)

Level.addEnnemy("item_shield", 14, 600)

Level.spawnMixedWave("fly", "space_ship_4", 15, 700, 50, 5)
Level.spawnColumn("space_ship_2", 17, 850, 80, 3)

Level.addEnnemy("octopus", 19, 550)
Level.addEnnemy("octopus", 19.5, 650)

Level.spawnHorizontalLine("space_ship_2", 20.5, 850, 90, 4)
Level.spawnVFormation("fly", 22, 450, 50)

Level.spawnPack("space_ship_3", 23.5, 700)
Level.spawnCircle("fly", 24.5, 600, 250, 6)

Level.addEnnemy("item_weapon", 26, 500)

Level.spawnMixedWave("octopus", "space_ship_4", 28, 450, 100, 5)

Level.spawnMixedWave("fly", "space_ship_4", 30, 700, 50, 5)
Level.spawnColumn("space_ship_2", 32, 850, 80, 3)

Level.spawnMixedWave("fly", "space_ship_4", 36, 700, 50, 5)

-- Level.addEnnemy("item_heal", 38, 1080 / 4)
-- Level.addEnnemy("item_heal", 38, 1080 / 2)
-- Level.addEnnemy("item_heal", 38, 1080 / 4 * 3)
-- Level.addEnnemy("item_heal", 38, 1080 / 5 * 2)
-- Level.addEnnemy("item_heal", 38, 1080 / 5 * 3)


Level.addEnnemy("bomber_boss", 42, 500)

function Level.update(dt)
    local time = tonumber(dt)
    for _, ennemy in ipairs(Level) do
        if ennemy.timeStamp >= time - 0.05 and ennemy.timeStamp <= time + 0.05 then
            createEntity(ennemy.name, math.floor(ennemy.height), 1920)
        end
    end
end
