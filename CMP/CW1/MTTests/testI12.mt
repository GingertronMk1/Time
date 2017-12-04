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
        z := y > 30 ? x == 9 ? 2 : 1 : 0;
        putint(z)
    end
