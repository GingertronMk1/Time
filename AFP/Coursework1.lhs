G52AFP Coursework 1 - Connect Four

Jack Ellis
psyje5@nottingham.ac.uk

----------------------------------------------------------------------

Gonna need some stuff from Data.List

> import Data.List

For flexibility, we define constants for the row and column size of the
board, length of a winning sequence, and search depth for the game tree:

> rows :: Int
> rows = 6
>
> cols :: Int
> cols = 7
>
> win :: Int
> win = 4
>
> depth :: Int
> depth = 6

The board itself is represented as a list of rows, where each row is
a list of player values, subject to the above row and column sizes:

> type Board = [Row]
>
> type Row = [Player]

In turn, a player value is either a nought, a blank, or a cross, with
a blank representing a position on the board that is not yet occupied:

> data Player = O | B | X
>               deriving (Ord, Eq, Show)

The following code displays a board on the screen:

> showBoard :: Board -> IO ()
> showBoard b = putStrLn (unlines (map showRow b ++ [line] ++ [nums]))
>               where
>                  showRow = map showPlayer
>                  line    = replicate cols '-'
>                  nums    = take cols ['0'..]
>
> showPlayer :: Player -> Char
> showPlayer O = 'O'
> showPlayer B = '.'
> showPlayer X = 'X'

The following is a test board:

> test :: Board
> test = [[B,B,B,B,B,B,B],
>         [B,B,B,B,B,B,B],
>         [B,B,B,B,B,B,B],
>         [B,B,B,X,X,B,B],
>         [B,B,O,O,X,B,B],
>         [B,O,O,X,X,X,O]]

Now for a function that turns columns into rows:

> colsToRows :: Board -> [Row]
> colsToRows =  transpose   -- from this, colsToRows . colsToRows = id



----------------------------------------------------------------------
