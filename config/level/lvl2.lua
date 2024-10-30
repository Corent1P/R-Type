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
    if name == "fly" or name == "octopus" then
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
Level.addEnnemy("item_heal", 5, 1080 / 5 * 2)
Level.addEnnemy("item_heal", 5, 1080 / 5 * 3)

Level.addEnnemy("item_forcepod", 8, 1080 / 2)

Level.spawnPack("fly", 10, 600)
Level.spawnHorizontalLine("fly", 12, 700, 70, 5)
Level.spawnHorizontalLine("fly", 12.5, 300, 80, 4)
Level.spawnZigzag("octopus", 13, 400, 100, 6, 0.3)
Level.spawnCircle("fly", 14, 600, 150, 8)

Level.spawnColumn("fly", 15, 350, 40, 4)
Level.addEnnemy("fly", 16, 400)
Level.addEnnemy("fly", 16.3, 500)
Level.addEnnemy("fly", 16.6, 600)
Level.addEnnemy("fly", 16.9, 700)
Level.spawnPack("fly", 17, 250)

Level.addEnnemy("item_heal", 17.5, 1080 / 4)
Level.addEnnemy("item_heal", 17.5, 1080 / 2)
Level.addEnnemy("item_heal", 17.5, 1080 / 4 * 3)

Level.spawnMixedWave("fly", "octopus", 18, 450, 50, 6)
Level.spawnCircle("fly", 19, 400, 120, 6)
Level.spawnZigzag("fly", 20, 500, 180, 8, 0.3)
Level.spawnVFormation("space_ship_3", 21, 300, 40)
Level.spawnCircle("fly", 22, 750, 200, 10)
Level.spawnHorizontalLine("octopus", 23, 450, 100, 5)

Level.spawnVFormation("fly", 25, 600, 50)
Level.spawnPack("space_ship_2", 26, 500)

Level.spawnColumn("fly", 28, 800, 40, 5)
Level.spawnCircle("fly", 28, 450, 150, 8)
Level.spawnColumn("space_ship_2", 29, 350, 45, 5)

Level.spawnMixedWave("fly", "space_ship_2", 30, 600, 70, 8)

Level.addEnnemy("item_weapon", 31.5, 540)

Level.addEnnemy("octopus", 32.5, 500)
Level.addEnnemy("octopus", 33, 650)

Level.addEnnemy("item_heal", 34, 1080 / 4)
Level.addEnnemy("item_heal", 34, 1080 / 2)
Level.addEnnemy("item_heal", 34, 1080 / 4 * 3)

Level.spawnHorizontalLine("space_ship_2", 35, 850, 90, 4)
Level.spawnZigzag("octopus", 37, 400, 200, 10, 0.2)

Level.spawnVFormation("space_ship_3", 40, 700, 60)
Level.spawnPack("fly", 42, 600)

Level.spawnCircle("fly", 44, 800, 250, 12)


Level.addEnnemy("item_heal", 48, 1080 / 4)
Level.addEnnemy("item_heal", 48, 1080 / 2)
Level.addEnnemy("item_heal", 48, 1080 / 4 * 3)
Level.addEnnemy("item_heal", 48, 1080 / 5 * 2)
Level.addEnnemy("item_heal", 48, 1080 / 5 * 3)

Level.addEnnemy("fly_boss", 42 + 10, 400)

function Level.update(dt)
    local time = tonumber(dt)
    for _, ennemy in ipairs(Level) do
        if ennemy.timeStamp >= time - 0.05 and ennemy.timeStamp <= time + 0.05 then
            createEntity(ennemy.name, math.floor(ennemy.height), 1920)
        end
    end
end
