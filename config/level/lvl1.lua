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
    table.insert(Level, Ennemy:new(nil, name, timeStamp, height))
end

function Level.spawnColumn(name, timeStamp, height)
    Level.addEnnemy(name, timeStamp, height)
    Level.addEnnemy(name, timeStamp + 0.2, height - 50)
    Level.addEnnemy(name, timeStamp + 0.4, height - 100)
    Level.addEnnemy(name, timeStamp + 0.6, height - 150)
    Level.addEnnemy(name, timeStamp + 0.8, height - 200)
    Level.addEnnemy(name, timeStamp + 1, height - 250)
    Level.addEnnemy(name, timeStamp + 1.2, height - 300)
    Level.addEnnemy(name, timeStamp + 1.4, height - 350)
    Level.addEnnemy(name, timeStamp + 1.6, height - 400)
    Level.addEnnemy(name, timeStamp + 1.8, height - 450)
    Level.addEnnemy(name, timeStamp + 2, height - 500)
end

function Level.spawnPack(name, timeStamp, height)
    Level.addEnnemy(name, timeStamp, height)
    Level.addEnnemy(name, timeStamp + 0.1, height - 20)
    Level.addEnnemy(name, timeStamp + 0.2, height + 30)
    Level.addEnnemy(name, timeStamp + 0.3, height)
end

Level.spawnPack("space_ship_2", 2, 200)
Level.spawnPack("space_ship_2", 3.5, 880)
Level.spawnPack("space_ship_2", 5, 1080 / 2)

Level.addEnnemy("space_ship_1", 6.5, 150)
Level.addEnnemy("space_ship_1", 6.5, 930)

Level.addEnnemy("space_ship_2", 6.2, 1080 / 2)

Level.addEnnemy("space_ship_3", 7.2, 1080 / 2)
Level.addEnnemy("space_ship_3", 7.4, 1080 / 2)
Level.addEnnemy("space_ship_3", 7.6, 1080 / 2)
Level.addEnnemy("space_ship_3", 7.8, 1080 / 2)
Level.addEnnemy("space_ship_3", 8, 1080 / 2)

Level.addEnnemy("item_shield", 10, 1080 / 5)

Level.spawnColumn("space_ship_1", 11, 1080 / 2)
Level.spawnColumn("space_ship_2", 12, 1030)

Level.addEnnemy("space_ship_3", 15.2, 1080)
Level.addEnnemy("space_ship_3", 15.4, 1080)
Level.addEnnemy("space_ship_3", 15.6, 1080)
Level.addEnnemy("space_ship_3", 15.8, 1080)
Level.addEnnemy("space_ship_3", 15, 1080)

Level.addEnnemy("space_ship_3", 15.2, 0)
Level.addEnnemy("space_ship_3", 15.4, 0)
Level.addEnnemy("space_ship_3", 15.6, 0)
Level.addEnnemy("space_ship_3", 15.8, 0)
Level.addEnnemy("space_ship_3", 15, 0)

Level.addEnnemy("item_weapon", 16, 1080 / 5)
Level.addEnnemy("item_weapon", 16, 1080 / 5 * 4)

Level.addEnnemy("space_ship_1", 17, 1080 / 5)
Level.addEnnemy("space_ship_1", 17, 1080 / 5 * 4)

Level.spawnPack("space_ship_2", 19, 200)
Level.spawnPack("space_ship_2", 20.5, 880)
Level.spawnPack("space_ship_2", 22, 1080 / 2)

Level.addEnnemy("space_ship_1", 23.5, 150)
Level.addEnnemy("space_ship_1", 23.5, 930)

Level.addEnnemy("space_ship_2", 23.2, 1080 / 2)

Level.addEnnemy("space_ship_3", 24.2, 1080 / 2)
Level.addEnnemy("space_ship_3", 24.4, 1080 / 2)
Level.addEnnemy("space_ship_3", 24.6, 1080 / 2)
Level.addEnnemy("space_ship_3", 24.8, 1080 / 2)
Level.addEnnemy("space_ship_3", 25, 1080 / 2)

Level.addEnnemy("item_shield", 27, 1080 / 5)

Level.spawnColumn("space_ship_1", 28, 1080 / 2)
Level.spawnColumn("space_ship_2", 29, 1030)

Level.addEnnemy("space_ship_3", 32, 1080)
Level.addEnnemy("space_ship_3", 32.2, 1080)
Level.addEnnemy("space_ship_3", 32.4, 1080)
Level.addEnnemy("space_ship_3", 32.6, 1080)
Level.addEnnemy("space_ship_3", 32.8, 1080)

Level.addEnnemy("space_ship_3", 32, 0)
Level.addEnnemy("space_ship_3", 32.2, 0)
Level.addEnnemy("space_ship_3", 32.4, 0)
Level.addEnnemy("space_ship_3", 32.6, 0)
Level.addEnnemy("space_ship_3", 32.8, 0)

Level.addEnnemy("item_weapon", 33, 1080 / 5)
Level.addEnnemy("item_weapon", 33, 1080 / 5 * 4)

Level.addEnnemy("space_ship_1", 34, 1080 / 5)
Level.addEnnemy("space_ship_1", 34, 1080 / 5 * 4)

Level.addEnnemy("boss", 40, 150)

function Level.update(dt)
    local time = tonumber(dt)
    for _, ennemy in ipairs(Level) do
        if ennemy.timeStamp >= time - 0.05 and ennemy.timeStamp <= time + 0.05
        then
            createEntity(ennemy.name, ennemy.height, 1920)
        end
    end
end
