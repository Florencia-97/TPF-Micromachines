----------------------------------------------------
---------- SCRIPT: Pretends to be a player----------
----------------------------------------------------

function decide_move(v, x, y)
    print(x)
    print(y)
    for i, v1 in pairs(v) do
        for j, v2 in pairs(v1) do
            print(v2);
        end
    end
    return "move left bro"
end