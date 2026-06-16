function init()
    ger.log("Lua init")
end

function update(dt)
    if ger.input_is_key_down("space") then
        ger.log("space down")
    end
end
