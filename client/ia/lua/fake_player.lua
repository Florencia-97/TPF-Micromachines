----------------------------------------------------
---------- SCRIPT: Pretends to be a player----------
----------------------------------------------------

local KEY_RIGHT = 1
local KEY_UP_RIGHT = 2
local KEY_LEFT = 3
local KEY_UP_LEFT = 4


function decide_move(v, x, y, rot, last_mov)
    print("----")
    print(x)
    print(y)
    print(rot)
    local i = math.floor(x)
    local j = math.floor(y)
    local r = math.floor(math.abs(rot) % 360)
    if j > #v or j<1 then return "" end
    if i > #v[j] or i<1 then return "" end
    print (r)
    local next_tile = get_tile_ahead(v,i,j,r)
    if next_tile == -1 then return "" end
    print(v[j][i])
    print(next_tile)
    print("----")
    if i==9 and j==9 and last_mov ~= KEY_RIGHT then
        return "key-RIGHT"
    elseif i == 8 and j== 10 and last_mov == KEY_RIGHT and r > 70 then
        return "key_up-RIGHT"
    elseif i==2 and j==3 and last_mov ~= KEY_RIGHT then
        return "key-RIGHT"
    elseif i==3 and j==2 and last_mov == KEY_RIGHT and r > 255 then
        return "key_up-RIGHT"
    elseif i==3 and j==10 and last_mov ~= KEY_RIGHT then
        return "key-RIGHT"
    elseif i==2 and j==9 and last_mov == KEY_RIGHT and r > 165 then
        return "key_up-RIGHT"
    elseif i==8 and j==2 and last_mov ~= KEY_RIGHT then
        return "key-RIGHT"
    elseif i == 9 and (j== 2 or j==3) and last_mov == KEY_RIGHT and r > 340 then
        return "key_up-RIGHT"
    end
    return ""
end

function get_tile_ahead(v,i,j,r)
    local x = 0;
    local y = 0;
    if (r < 45 or r > 310) then
        x = i
        y = j+1
    elseif (r > 45 and r < 115) then
        x = i -1
        y = j
    elseif (r > 115 and r < 205) then
        x = i
        y = j-1
    -- elseif (r > 205 and r < 310) then
    else
        x = i +1
        y = j
    end
    if y > #v or y<1 then return -1 end
    if x > #v[y] or x<1 then return -1 end
    return math.floor(v[y][x])
end
