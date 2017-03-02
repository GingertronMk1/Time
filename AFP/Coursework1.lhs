G52AFP Coursework 1 - Connect Four

Jack Ellis
psyje5@nottingham.ac.uk

----------------------------------------------------------------------

Gonna need some stuff from Data.List, as well as Data.Char (`isDigit` mostly), System.Random, and Data.Tree

> import Data.List
> import Data.Char
> import System.Random
> import Data.Maybe
> --import Data.Tree

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

----------------------------------------------------------------------
MY CODE STARTS HERE:--------------------------------------------------
----------------------------------------------------------------------

> test2 :: Board
> test2 = [[B,B,B,B,B,B,B],
>          [B,B,B,B,B,B,B],
>          [B,B,B,B,B,B,B],
>          [B,B,B,X,X,B,B],
>          [B,B,O,O,X,B,O],
>          [B,O,O,X,X,X,O]]

> test3 :: Board
> test3 = [[B,B,B,B,B,B,B],
>          [B,B,B,B,B,B,B],
>          [B,B,B,B,B,B,B],
>          [O,B,B,B,B,B,B],
>          [O,X,B,B,B,B,B],
>          [O,X,B,B,B,X,X]]

> testWon1 :: Board
> testWon1 = [[B,B,B,B,B,B,B],
>             [B,B,B,B,B,B,B],
>             [B,B,B,B,X,B,B],
>             [B,B,B,X,X,B,B],
>             [B,B,O,O,X,B,B],
>             [B,O,O,X,X,X,O]]

> testWon2 :: Board
> testWon2 = [[B,B,B,B,B,B,B],
>             [B,B,B,B,B,B,B],
>             [B,B,B,B,B,B,B],
>             [B,B,B,X,X,B,B],
>             [O,O,O,O,X,B,B],
>             [X,O,O,X,X,X,O]]

> testWon3 :: Board
> testWon3 = [[X,B,B,B,B,B,B],
>             [B,X,B,B,B,B,B],
>             [B,B,X,B,B,B,B],
>             [B,B,B,X,B,B,B],
>             [B,B,B,B,B,B,B],
>             [B,B,B,B,B,B,B]]

> testWon4 :: Board
> testWon4 = [[B,B,B,B,B,B,B],
>             [B,B,B,B,X,B,B],
>             [B,B,B,X,B,B,B],
>             [B,B,X,B,B,B,B],
>             [B,X,B,B,B,B,B],
>             [B,B,B,B,B,B,B]]

> oNearWin :: Board
> oNearWin = [[B,B,B,B,B,B,B],
>             [B,B,B,B,B,B,B],
>             [B,B,B,B,B,B,B],
>             [O,X,B,B,B,B,B],
>             [O,X,B,B,B,B,B],
>             [O,X,X,B,B,B,B]]

> fullBoard :: Board
> fullBoard = [[X,O,X,O,X,O,X],
>              [X,O,X,O,X,O,X],
>              [O,X,O,X,O,X,O],
>              [O,X,O,X,O,X,O],
>              [X,O,X,O,X,O,X],
>              [X,O,X,O,X,O,X]]

> notQuiteFullBoard :: Board
> notQuiteFullBoard = [[B,B,B,B,B,B,B],
>                      [X,O,X,O,X,O,X],
>                      [O,X,O,X,O,X,O],
>                      [O,X,O,X,O,X,O],
>                      [X,O,X,O,X,O,X],
>                      [X,O,X,O,X,O,X]]

> empty :: Board
> empty = boardGen rows cols

----------------------------------------------------------------------
BOARD MANIPULATION HERE:----------------------------------------------
----------------------------------------------------------------------


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

----------------------------------------------------------------------
MOVEMENT CODE HERE:---------------------------------------------------
----------------------------------------------------------------------

Removing blanks from the beginning of a column

> removeColBlanks :: Board -> Int -> Row
> removeColBlanks board a = removeBlanks (getCol board a)

> removeBlanks :: Row -> Row
> removeBlanks = dropWhile (==B)

Fill the row back up with blanks

> fillCol :: Row -> Row
> fillCol col = if (length col < rows) then fillCol (B:col) else col

Add a piece to the front of a row

> addPiece :: Row -> Player -> Row
> addPiece col piece = piece:col

Fill the rest of a row with blanks

> putPiece :: Board -> Int -> Player -> Row
> putPiece board n piece = fillCol (addPiece (removeColBlanks board n) piece)

[Columns before the modified one] ++ [modified one] ++ [all columns after modified one]

> makeMove :: Board -> Int -> Player -> Board
> makeMove board n piece = colsToRows ((take n (colsToRows board))
>                                     ++ [(putPiece board n piece)]
>                                     ++ (drop (n+1) (colsToRows board)))

Counting the number of pieces in play, for use in determining whose go it is

> numPieces :: Board -> Int
> numPieces = length . filter (/= B) . concat

> whoseGo :: Board -> Player
> whoseGo board = if mod (numPieces board) 2 == 0 then X else O

There wasn't any error checking in this one, however the beginnings of the AI code require it
The else case won't ever be invoked in the main game loop as the conditional's already there

> move :: Board -> Int -> Board
> move board n = makeMove board n (whoseGo board)

if isColFull board n || isAWinner board then []
                else if isValid board n then makeMove board n (whoseGo board)
                else board

> emptyCols :: Board -> [Int]
> emptyCols board = filter (not . isColFull board) [0..cols-1]

Check if a move is valid

> isValid :: Board -> Int -> Bool
> isValid board n
>             | not (elem n [0..cols-1]) = False
>             | (getCol board n) !! 0 /= B = False
>             | otherwise = True

> isColFull :: Board -> Int -> Bool
> isColFull board n = (getCol board n) !! 0 /= B

Check if the board is full

> isFull :: Board -> Bool
> isFull board = if (numPieces board == rows*cols) then True else False

----------------------------------------------------------------------
HAS WON LOGIC GOES HERE:----------------------------------------------
----------------------------------------------------------------------

Determines if either player has won a row

> hasXWon :: Row -> Bool
> hasXWon = elem (replicate win X) . group

> hasOWon :: Row -> Bool
> hasOWon = elem (replicate win O) . group

Determines `which` player won the row

> hasWonRow :: Row -> Player
> hasWonRow row
>           | hasXWon row = X
>           | hasOWon row = O
>           | otherwise   = B

Build a list with the win state of every row

> hasWonRows :: Board -> [Player]
> hasWonRows = map hasWonRow

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
>           | otherwise = B

> isAWinner :: Board -> Bool
> isAWinner board = whoWon board /= B

----------------------------------------------------------------------
COLUMN SELECTION HERE:------------------------------------------------
----------------------------------------------------------------------

Need a little helper to let us get which column wants a piece putting in

> getNat :: String -> IO Int
> getNat prompt = do putStr prompt
>                    xs <- getLine
>                    if xs /= [] && all isDigit xs then return (read xs)
>                    else do putStrLn "ERROR: Invalid number"
>                            getNat prompt

Beginnings of AI: choosing a random column within a range

Getting the right person (or computer)'s choice

> getChoice :: Board -> Int
> getChoice board = if (whoseGo board) == X then getNat "Which Column? " else pickAWinner board

----------------------------------------------------------------------
GAME TREE STUFF HERE:-------------------------------------------------
----------------------------------------------------------------------

First, what is a tree?

> data Tree a = Node a [Tree a] deriving Show

Now, a function to generate a full game tree from a board. It's important that it stops on a full board.

> gameTree :: Board -> Tree Board
> gameTree board = if isAWinner board then Node board []
>                                     else Node board [gameTree (move board n) | n <- emptyCols board]

Pruning is needed to keep us at a reasonable height

> limitTree :: Int -> Tree a -> Tree a
> limitTree 0 (Node x _) = Node x []
> limitTree n (Node x ts) = Node x [limitTree (n-1) t | t <- ts]

And now a function to generate a limited tree

> treeOfHeight :: Int -> Board -> Tree Board
> treeOfHeight h b = limitTree h (gameTree b)

`interpret`, or rather, just get the board from a node

> interpretNode :: Tree Board -> Board
> interpretNode (Node b _) = b

Possible boards from the current one

> possibleBoardsT :: Board -> Tree Board
> possibleBoardsT board = treeOfHeight 1 board

Generating a new tree containing (board, winner) tuples

> tupleGen :: Tree Board -> Tree (Board, Player)
> tupleGen (Node b []) = Node (b, whoWon b) []
> tupleGen (Node b bs) = Node (b, minOrMax (whoseGo b) (map (getPlayerTuple . tupleGen) bs)) (map tupleGen bs)

Getting the player part of the tuple

> getPlayerTuple :: Tree (a, b) -> b
> getPlayerTuple (Node t _) = snd t

> tupleTreeHeight :: Board -> Int -> Tree (Board, Player)
> tupleTreeHeight board n = tupleGen $ treeOfHeight n board

> getChildIndex :: Tree (Board, Player) -> Maybe Int
> getChildIndex (Node (board, player) tuples) = elemIndex (whoseGo board) $ map getPlayerTuple tuples

> minOrMax :: Player -> ([Player] -> Player)
> minOrMax X = maximum
> minOrMax O = minimum

> returnIndex board = getChildIndex (tupleTreeHeight board depth)

> pickAWinner :: Board -> Maybe Int
> pickAWinner board = case (returnIndex board) of
>                         Just x -> x+1
>                         Nothing -> 0


----------------------------------------------------------------------
GAME LOOP HERE:-------------------------------------------------------
----------------------------------------------------------------------

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
> play board =  do showBoard board                                    -- show the current board
>                  if isFull board then putStrLn "Board full: DRAW!"  -- If it's full, the game is a draw
>                  else do                                            -- If it isn't...
>                  n <- getChoice board                               -- get the new column
>                  putChar '\n'                                       -- put a new line in for tidyness
>                  if isValid board (n-1) then                        -- if the move is valid:
>                    do let newBoard = move board (n-1)                 -- do it
>                       if whoWon (newBoard) /= B then                  -- if someone's won:
>                        do showBoard newBoard                            -- show the board
>                           putStrLn ("Winner: " ++ show (whoWon newBoard)) -- and show who's won
>                       else                                            -- if neither of the above:
>                         play newBoard                                 -- ANOTHER ROUND
>                  else                                               -- else say the move's invalid, try again
>                    do putStrLn ("Move invalid (either the column's full or doesn't exist). Your move: " ++ show n)
>                       play board

And finally...

> main :: IO()
> main = play empty

----------------------------------------------------------------------

TODO: AI

Get the index of the child with the correct whoWon part of tuple from the getTuples function, use for AI
----------------------------------------------------------------------
