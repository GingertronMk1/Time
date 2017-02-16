G52AFP Coursework 1 - Connect Four

Jack Ellis
psyje5@nottingham.ac.uk

----------------------------------------------------------------------

Gonna need some stuff from Data.List, as well as Data.Char (`isDigit` mostly)

> import Data.List
> import Data.Char

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

deriving Eq means that the 'Player' data type supports equality
Ord means it supports ordering; O < B < X
Show prints things converted to strings

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

> testWonVert :: Board
> testWonVert = [[B,B,B,B,B,B,B],
>                [B,B,B,B,B,B,B],
>                [B,B,B,B,X,B,B],
>                [B,B,B,X,X,B,B],
>                [B,B,O,O,X,B,B],
>                [B,O,O,X,X,X,O]]

> testWonHor :: Board
> testWonHor = [[B,B,B,B,B,B,B],
>               [B,B,B,B,B,B,B],
>               [B,B,B,B,B,B,B],
>               [B,B,B,X,X,B,B],
>               [O,O,O,O,X,B,B],
>               [X,O,O,X,X,X,O]]

> testWonDiag :: Board
> testWonDiag = [[B,B,B,B,B,B,B],
>                [B,B,B,B,B,B,B],
>                [B,B,X,B,B,B,B],
>                [B,B,O,X,X,B,B],
>                [B,O,O,O,X,B,B],
>                [B,O,O,X,X,X,O]]

> blank :: Board
> blank = [[B,B,B,B,B,B,B],
>          [B,B,B,B,B,B,B],
>          [B,B,B,B,B,B,B],
>          [B,B,B,B,B,B,B],
>          [B,B,B,B,B,B,B],
>          [B,B,B,B,B,B,B]]


MY CODE STARTS HERE:-------------------------------------------------

Now for a function that turns columns into rows:

> colsToRows :: Board -> [Row]
> colsToRows = transpose

From this, colsToRows . colsToRows = id
Furthermore, just to make things a bit easier:

> getCol :: Board -> Int -> Row
> getCol board a = (colsToRows board) !! a

A few more helper functions:

turn :: Board -> Player
hasRow :: Player -> Row -> Bool
hasWon :: Player -> Board -> Bool
isValid :: Int -> Bool

No real need of these two functions; they're more to help me remember how to do stuff with lists within lists

> printRow :: Board -> Int -> IO()
> printRow board a = print (board !! a)

> printCol :: Board -> Int -> IO()
> printCol board a = print (getCol board a)


Removing blanks from the beginning of a column

> removeColBlanks :: Board -> Int -> Row
> removeColBlanks board a = removeBlanks (getCol board a)

> removeBlanks :: Row -> Row
> removeBlanks row = dropWhile (==B) row

Fill the row back up with blanks

> fillCol :: Row -> Row
> fillCol col = if (length col < rows) then fillCol (B:col)
>               else col

Add a piece to the front of a row

> addPiece :: Row -> Player -> Row
> addPiece col piece = piece:col

Fill the rest of a row with blanks

> putPiece :: Board -> Int -> Player -> Row
> putPiece board n piece = fillCol (addPiece (removeColBlanks board n) piece)

So now, to construct a board with the piece added, we add the piece to the relevant row, then reconstruct the board from the other rows

> move :: Board -> Int -> Board
> move board n = colsToRows ((take n (colsToRows board)) 
>                             ++ [(putPiece board n (whoseGo board))]
>                             ++ (drop (n+1) (colsToRows board)))

> showMove :: Board -> Int -> IO()
> showMove board n = showBoard (move board n)

Counting the number of pieces in play, for use in determining whose go it is

> numPieces :: Board -> Int
> numPieces = length . filter (/= B) . concat

> whoseGo :: Board -> Player
> whoseGo board = if mod (numPieces board) 2 == 0 then O
>                 else X

> hasXWon :: Row -> Bool
> hasXWon row = elem [X,X,X,X] (group row)

> hasOWon :: Row -> Bool
> hasOWon row = elem [O,O,O,O] (group row)

> hasWonRow :: Row -> Bool
> hasWonRow row = or [hasXWon row, hasOWon row]

> hasWon :: Board -> Bool
> hasWon board = or [or (map (hasWonRow) board), or (map (hasWonRow) (colsToRows board))]

> getDigit :: String -> IO Int
> getDigit prompt = do putStrLn prompt
>                      n <- getChar
>                      if isDigit n then
>                        return (ord n - ord '0')
>                      else
>                        do putStrLn "ERROR: INVALID DIGIT"
>                           getDigit prompt

> play :: Board -> IO()
> play board = do showBoard board
>                 n <- getDigit "Which Column?"
>                 putChar '\n'
>                 if hasWon (move board n) then
>                   do showBoard (move board n)
>                      putStrLn "Winner!"
>                 else
>                   play (move board n)

----------------------------------------------------------------------
