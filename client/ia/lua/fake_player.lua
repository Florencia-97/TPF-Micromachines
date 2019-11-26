----------------------------------------------------
---------- SCRIPT: Pretends to be a player----------
----------------------------------------------------

-- Driver is turning left or right
local KEY_RIGHT = 1
local KEY_LEFT = 3

-- Driver stopped turning left or right
local KEY_UP_RIGHT = 2
local KEY_UP_LEFT = 4

--  v = matrix with every tile in the game
--  x = x position of car
--  y =  y position of car
--  rot = rotation of car
--  last_mov = last move made by the car

function decide_move(v, x, y, rot, last_mov)
    local i = math.floor(x)
    local j = math.floor(y)
    local r = math.floor(math.abs(rot) % 360)
    if j > #v or j<1 then return "" end
    if i > #v[j] or i<1 then return "" end
    local next_tile = get_tile_ahead(v,i,j,r)
    if next_tile == -1 then return "" end

    local map_right_bot = get_corner_right_bottom(v)
    local map_left_bot = get_corner_left_bottom(v)
    local map_left_up = get_corner_left_up(v)
    local map_right_up = get_corner_right_up(v)

    if i == map_right_bot.ci and j == map_right_bot.cj and last_mov ~= KEY_RIGHT then
        return "key-RIGHT"
    elseif i == map_right_bot.ci - 1 and j== map_right_bot.cj + 1 and last_mov == KEY_RIGHT and r > 70 then
        return "key_up-RIGHT"
    elseif i == map_left_up.ci and j == map_left_up.cj and last_mov ~= KEY_RIGHT then
        return "key-RIGHT"
    elseif i == map_left_up.ci + 1 and j == map_left_up.cj - 1 and last_mov == KEY_RIGHT and r > 255 then
        return "key_up-RIGHT"
    elseif i== map_left_bot.ci and j== map_left_bot.cj and last_mov ~= KEY_RIGHT then
        return "key-RIGHT"
    elseif i== map_left_bot.ci - 1 and j== map_left_bot.cj - 1 and last_mov == KEY_RIGHT and r > 165 then
        return "key_up-RIGHT"
    elseif i==map_right_up.ci and j==map_right_up.cj and last_mov ~= KEY_RIGHT then
        return "key-RIGHT"
    elseif i == map_right_up.ci + 1 and ((j == map_right_up.cj) or (j==map_right_up.cj+1)) and last_mov == KEY_RIGHT and r > 340 then
        return "key_up-RIGHT"
    end
    return ""
end

function get_corner_right_bottom(v)
    local des = {}
    for j=1,#v do
        for i=1,#v[1] do
            if v[j][i] == 3 then
                des.ci = i
                des.cj = j - 1
            end
        end
    end
    return des
end

function get_corner_right_up(v)
    local des = {}
    for j=1,#v do
        for i=1,#v[1] do
            if v[j][i] == 6 then
                des.ci = i - 1
                des.cj = j
                return des
            end
        end
    end
end

function get_corner_left_bottom(v)
    local des = {}
    for j=1,#v do
        for i=1,#v[1] do
            if v[j][i] == 4 then
                des.ci =i + 1
                des.cj =j
            end
        end
    end
    return des
end

function get_corner_left_up(v)
    local des = {}
    for j=1,#v do
        for i=1,#v[1] do
            if v[j][i] == 7 then
                des.ci = i
                des.cj = j + 1
                return des
            end
        end
    end
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
    else
        x = i +1
        y = j
    end
    if y > #v or y<1 then return -1 end
    if x > #v[y] or x<1 then return -1 end
    return math.floor(v[y][x])
end
