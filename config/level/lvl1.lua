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
    if name == "octopus" then
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

Level.spawnPack("octopus", 1, 800)
Level.spawnPack("space_ship_2", 3.5, 880)

Level.addEnnemy("octopus", 4.5, 150)
Level.addEnnemy("octopus", 4.5, 930)

Level.spawnMixedWave("space_ship_2", "octopus", 5, 300, 60, 8)

Level.spawnColumn("octopus", 8, 1080 / 2, 40, 12)
Level.spawnColumn("space_ship_2", 10, 950, 45, 10)

Level.addEnnemy("item_weapon", 10.4, 950)

Level.spawnVFormation("space_ship_3", 12.5, 540, 50)

Level.addEnnemy("octopus", 15, 1080 / 2)
Level.addEnnemy("octopus", 15.5, 1080 / 2 + 80)
Level.addEnnemy("octopus", 16, 1080 / 2 - 80)


Level.spawnPack("space_ship_2", 19.5, 880)

-- Level.addEnnemy("item_heal", 20, 1080 / 2)

Level.addEnnemy("octopus", 21.5, 150)
Level.addEnnemy("octopus", 21.5, 930)

Level.spawnVFormation("space_ship_3", 22, 600, 40)

Level.spawnColumn("octopus", 27, 1080 / 2, 30, 12)
Level.spawnColumn("space_ship_2", 28, 950, 40, 10)

Level.addEnnemy("space_ship_3", 30, 950)
Level.addEnnemy("space_ship_3", 30.2, 950)
Level.addEnnemy("space_ship_3", 30.4, 950)

Level.addEnnemy("space_ship_3", 30, 0)
Level.addEnnemy("space_ship_3", 30.2, 0)
Level.addEnnemy("space_ship_3", 30.4, 0)

Level.addEnnemy("octopus", 33.5, 1080 / 5)
Level.addEnnemy("octopus", 33.5, 1080 / 5 * 4)

Level.spawnMixedWave("octopus", "space_ship_2", 36, 880, 50, 10)

-- Level.addEnnemy("item_heal", 38, 1080 / 2)
-- Level.addEnnemy("item_heal", 38.5, 1080 / 4)
-- Level.addEnnemy("item_heal", 38.5, 1080 / 4 * 3)
-- Level.addEnnemy("item_heal", 39, 1080 / 2)

Level.addEnnemy("octopus_boss", 42, 400)

function Level.update(dt)
    local time = tonumber(dt)
    for _, ennemy in ipairs(Level) do
        if ennemy.timeStamp >= time - 0.05 and ennemy.timeStamp <= time + 0.05
        then
            createEntity(ennemy.name, ennemy.height, 1920)
        end
    end
end
