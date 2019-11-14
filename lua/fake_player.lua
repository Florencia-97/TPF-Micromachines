----------------------------------------------------
---------- SCRIPT: Pretends to be a player----------
----------------------------------------------------


function decide_move(v, x, y)
    print(x)
    print(y)
    for i, v1 in pairs(v) do
        for j, v2 in pairs(v1) do
            local tile = math.floor(v2)
            if (tile == 1) then
                print("Grass")
            elseif (1 < tile and tile <= 9) then
                print("Road")
            elseif ( 9 < tile and tile < 15) then
                print("Extras")
            elseif (tile == 15) then
                print("Mud")
            end
        end
    end
    return "move left bro"
end