local player = nil
local player_x = 100
local player_y = 100
local speed = 120
local accumulator = 0

function init()
    ger.log("Lua game init")
    ger.log("Creating player sprite")

    player = ger.sprite_create()
    ger.sprite_set_pos(player, player_x, player_y)
    ger.sprite_set_color(player, 255, 255, 255, 255)
end

function update(dt)
    accumulator = accumulator + dt

    local moving = false

    if ger.input_is_key_down("w") or ger.input_is_key_down("up") then
        player_y = player_y - speed * dt
        moving = true
    end

    if ger.input_is_key_down("s") or ger.input_is_key_down("down") then
        player_y = player_y + speed * dt
        moving = true
    end

    if ger.input_is_key_down("a") or ger.input_is_key_down("left") then
        player_x = player_x - speed * dt
        moving = true
    end

    if ger.input_is_key_down("d") or ger.input_is_key_down("right") then
        player_x = player_x + speed * dt
        moving = true
    end

    if moving then
        ger.sprite_set_pos(player, player_x, player_y)
    end

    if ger.input_is_key_down("space") then
        ger.log("space down")
    end

    if accumulator >= 1 then
        accumulator = 0
        ger.log("player:", math.floor(player_x), math.floor(player_y))
    end
end
