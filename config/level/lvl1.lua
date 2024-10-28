Ennemy = {
    id = 0,
    timeStamp = 0,
    height = 0
}

function Ennemy:new(o, id, timeStamp, height)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    o.id = id
    o.timeStamp = timeStamp
    o.height = height
    return o
end

Level = {}

function Level.addEnnemy(id, timeStamp, height)
    table.insert(Level, Ennemy:new(nil, id, timeStamp, height))
end

for i = 1, 1000, 1 do
    Level.addEnnemy(4, i, (i * 100) % 1000)
    Level.addEnnemy(16, i, (i * 100 - 33) % 1000)
    Level.addEnnemy(17, i, (i * 100 - 66) % 1000)
    Level.addEnnemy(18, i, (i * 100 - 99) % 1000)
    Level.addEnnemy(23, i, (i * 100 - 122) % 1000)
    if i % 2 == 0 then
        Level.addEnnemy(5, i, (i * 100 - 33) % 1000)
        Level.addEnnemy(6, i, (i * 100 - 66) % 1000)
    end
end

function Level.update(dt)
    for _, ennemy in ipairs(Level) do
        if ennemy.timeStamp == dt
        then
            createEntity(ennemy.id, ennemy.height, 1920)
        end
    end
end
