G52AFP Coursework 1 - Connect Four

Jack Ellis
psyje5@nottingham.ac.uk

----------------------------------------------------------------------

Gonna need some stuff from Data.List, as well as Data.Char (`isDigit` mostly)

> import Data.List
> import Data.Char
> import System.Random

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
>                  nums    = take cols ['1'..]
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

MY CODE STARTS HERE:-------------------------------------------------

> testWonCol :: Board
> testWonCol = [[B,B,B,B,B,B,B],
>                [B,B,B,B,B,B,B],
>                [B,B,B,B,X,B,B],
>                [B,B,B,X,X,B,B],
>                [B,B,O,O,X,B,B],
>                [B,O,O,X,X,X,O]]

> testWonRow :: Board
> testWonRow = [[B,B,B,B,B,B,B],
>               [B,B,B,B,B,B,B],
>               [B,B,B,B,B,B,B],
>               [B,B,B,X,X,B,B],
>               [O,O,O,O,X,B,B],
>               [X,O,O,X,X,X,O]]

> testWonDiag1 :: Board
> testWonDiag1 = [[X,B,B,B,B,B,B],
>                 [B,X,B,B,B,B,B],
>                 [B,B,X,B,B,B,B],
>                 [B,B,B,X,B,B,B],
>                 [B,B,B,B,B,B,B],
>                 [B,B,B,B,B,B,B]]

> testWonDiag2 :: Board
> testWonDiag2 = [[B,B,B,B,B,B,B],
>                 [B,B,B,B,X,B,B],
>                 [B,B,B,X,B,B,B],
>                 [B,B,X,B,B,B,B],
>                 [B,X,B,B,B,B,B],
>                 [B,B,B,B,B,B,B]]

Generate a board of `rows` rows and `cols` columns
Standard is c = 7, r = 6

> boardGen :: Int -> Int -> Board
> boardGen c r = replicate c (replicate r B)

Now for a function that turns columns into rows:

> colsToRows :: Board -> [Row]
> colsToRows = transpose

From this, colsToRows . colsToRows = id
Furthermore, just to make things a bit easier:

> getCol :: Board -> Int -> Row
> getCol board a = (colsToRows board) !! a

Taking Diagonals: diagonals of an empty list is an empty list
Diagonals of an empty list followed by some other list is that list

> diagonals :: Board -> [Row]
> diagonals []       = []
> diagonals ([]:xss) = xss
> diagonals xss      = zipWith (++) (map ((:[]) . head) xss ++ repeat []) ([]:(diagonals (map tail xss)))

The above takes diagonals that go from top-left to bottom-right. So to get the opposite, we flip the board about the middle vertical

> allDiagonals :: Board -> [Row]
> allDiagonals board = (diagonals board) ++ (diagonals (map reverse board))

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
From right to left: we make the columns rows again, doing this on a concatenation of all the columns before the one we wanted
to play on, the modified version of the one we wanted to play on (encased in [] otherwise this wouldn't work), and all the columns
after the one we wanted

> move :: Board -> Int -> Board
> move board n = colsToRows ((take n (colsToRows board))
>                ++ [(putPiece board n (whoseGo board))]
>                ++ (drop (n+1) (colsToRows board)))

Counting the number of pieces in play, for use in determining whose go it is

> numPieces :: Board -> Int
> numPieces = length . filter (/= B) . concat

> whoseGo :: Board -> Player
> whoseGo board = if mod (numPieces board) 2 == 0 then O
>                 else X

Check if a move is valid

> isValid :: Board -> Int -> Bool
> isValid board n
>             | not (elem n [0..cols-1]) = False
>             | (getCol board n) !! 0 /= B = False
>             | otherwise = True

HAS WON LOGIC GOES HERE

Determines if either player has won a row

> hasXWon :: Row -> Bool
> hasXWon row = elem (replicate win X) (group row)

> hasOWon :: Row -> Bool
> hasOWon row = elem (replicate win O) (group row)

Determines `which` player won the row

> hasWonRow :: Row -> Player
> hasWonRow row
>           | hasXWon row = X
>           | hasOWon row = O
>           | otherwise   = B

Build a list with the win state of every row

> hasWonRows :: Board -> [Player]
> hasWonRows board = map hasWonRow board

Win states of every column

> hasWonCols :: Board -> [Player]
> hasWonCols board = map hasWonRow (colsToRows board)

Win states of every diagonal

> hasWonDiags :: Board -> [Player]
> hasWonDiags board = map hasWonRow (allDiagonals board)

Win states of all three combined

> hasWon :: Board -> [Player]
> hasWon board = hasWonRows board ++ hasWonCols board ++ hasWonDiags board

Who won?

> whoWon :: Board -> Player
> whoWon board
>           | elem X (hasWon board) = X
>           | elem O (hasWon board) = O
>           | elem B (hasWon board) = B

Need a little helper to let us get just single digits from input

> getDigit :: String -> IO Int
> getDigit prompt = do putStrLn prompt
>                      n <- getLine
>                      return (toDigits n)

> toDigits :: String -> Int
> toDigits (x:[]) = digitToInt x
> toDigits (x:xs) = 10*(digitToInt x) + toDigits xs

Beginnings of AI:

> pickCol :: IO Int
> pickCol = getStdRandom (randomR (0, cols))

And now for the actual game loop!

Starting at the top:
  1) Show the board as it is
  2) Get the digit pertaining to the column to be played
    2.5) This is going to be decremented by one because of a mix of zero-indexing and format changing
  3) Put a new line in for tidyness
  4) If the move is valid, let the new board be the old board with the new move
    4.1) If someone's won, show the final board and let us know who won, and end the game
    4.2) Else, if the board's full, end the game with nobody having won
    4.3) If neither of those are the case, begin the loop again with the new board as the input
  5) If the move isn't valid, tell us so and start the loop again with the same input as last time

> play :: Board -> IO()
> play board = do showBoard board
>                 n <- getDigit "Which Column?"
>                 putChar '\n'
>                 if isValid board (n-1) then
>                   do let newBoard = move board (n-1)
>                      if whoWon (newBoard) /= B then
>                        do showBoard newBoard
>                           putStr "Winner: "
>                           print (whoWon newBoard)
>                      else if numPieces board == rows*cols then
>                        do showBoard newBoard
>                           putStrLn "Board full, nobody wins..."
>                      else
>                        play (newBoard)
>                 else
>                   do putStr "Move invalid (either the column's full or doesn't exist). Your move: "
>                      print n
>                      play board

And finally...

> main :: IO()
> main = play (boardGen rows cols)

----------------------------------------------------------------------

TODO: AI

So currently the making moves functions are a bit inextensible. Need to do something about that.
Change `move` to take `piece` as an arg, putting more on `whoseGo` so we can shove something in there about picking a number

----------------------------------------------------------------------
