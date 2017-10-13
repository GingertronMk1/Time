let
    var x: Integer;
    var y: Integer;
    var z: Integer
in
    begin
        x := 3;
        y := 5;
        z := (x > y ? x : y);
        putint(z)
    end
