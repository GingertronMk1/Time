let
    const x: Integer = 9;
    var y: Integer;
    var z: Integer
in
    begin
        y := x;
        repeat
            y := y + 1
        until y > 42;
        putint(y);
        z := (y > 30 ? 1 : 0);
        putint(z);
        if z == 1 then
            y := 5
        elsif z == 2 then
            y := 10
        else
            y := 0
//      putint(y);
    end
