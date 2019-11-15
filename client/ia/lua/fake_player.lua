----------------------------------------------------
---------- SCRIPT: Pretends to be a player----------
----------------------------------------------------


function decide_move(v, x, y)
--    for i, v1 in pairs(v) do
--        for j, v2 in pairs(v1) do
--            local tile = math.floor(v2)
--            if (tile == 0) then
--                return "LEFT"
--            else
--                return "UP"
--            end
--        end
--    end
    local i = math.floor(x)
    local j = math.floor(y)
    local tile = math.floor(v[i][j])
    print(tile)
    if tile == 0 then
        return "LEFT"
    else
        return "UP"
    end
    return "UP"
end