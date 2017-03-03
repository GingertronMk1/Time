G52AFP Coursework 1 - Connect Four

Jack Ellis
psyje5@nottingham.ac.uk

----------------------------------------------------------------------

Gonna need some stuff from Data.List, as well as Data.Char (`isDigit` mostly), System.Random, and Data.Tree

> import Data.List
> import Data.Char
> import System.Random
> import Data.Maybe
> import System.IO.Unsafe

For flexibility, we define constants for the row and column size of the
board, length of a winning sequence, and search depth for the game tree:

> rows :: Int
> rows = 6    -- Standard: 6
>
> cols :: Int
> cols = 7    -- Standard: 7
>
> win :: Int
> win = 4     -- Standard: 4
>
> depth :: Int
> depth = 3   -- Standard: 6

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

Testing boards for various situations

> test2 :: Board
> test2 = [[B,B,B,O,B,B,B],
>          [B,B,B,X,B,B,B],
>          [B,B,B,O,B,B,B],
>          [B,B,O,X,X,B,B],
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

> xNearWin :: Board
> xNearWin = [[B,B,B,B,B,B,B],
>             [B,B,B,B,B,B,B],
>             [B,B,B,B,B,B,B],
>             [O,X,B,B,B,B,B],
>             [O,X,B,B,B,B,B],
>             [O,X,B,B,B,B,B]]

> fullBoard :: Board
> fullBoard = [[X,O,X,O,X,O,X],
>              [X,O,X,O,X,O,X],
>              [O,X,O,X,O,X,O],
>              [O,X,O,X,O,X,O],
>              [X,O,X,O,X,O,X],
>              [X,O,X,O,X,O,X]]

> notQuiteFullBoard :: Board
> notQuiteFullBoard = [[X,X,B,O,O,O,X],
>                      [X,O,X,O,X,O,X],
>                      [O,X,O,X,O,X,O],
>                      [O,X,O,X,O,X,O],
>                      [X,O,X,O,X,O,X],
>                      [X,O,X,O,X,O,X]]

> cgBoard :: Board
> cgBoard = [[B,B,B,B,B,B,O],
>            [B,B,B,B,B,B,O],
>            [B,B,X,B,B,B,X],
>            [X,B,O,B,B,X,O],
>            [X,O,O,O,X,X,X],
>            [X,O,O,O,X,X,O]]

......O
......O
..X...X
X.O..XO
X.OOXXX
XOOOXXO

Generate an empty board of the correct number of rows and cols
DEFAULT IS 6 ROWS, 7 COLUMNS

> empty :: Board
> empty = boardGen rows cols

----------------------------------------------------------------------
BOARD MANIPULATION HERE:----------------------------------------------
----------------------------------------------------------------------


Generate a board of `rows` rows and `cols` columns

> boardGen :: Int -> Int -> Board
> boardGen c r = replicate c (replicate r B)

Now for a function that turns columns into rows:

> colsToRows :: Board -> [Row]
> colsToRows = transpose

From this, colsToRows . colsToRows = id

Furthermore, just to make things a bit easier, a function that returns a specific column

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

----------------------------------------------------------------------
MOVEMENT CODE HERE:---------------------------------------------------
----------------------------------------------------------------------

Removing blanks from the beginning of a column

> removeColBlanks :: Board -> Int -> Row
> removeColBlanks board a = removeBlanks (getCol board a)

Helper for the above, gets rid of blank list items

> removeBlanks :: Row -> Row
> removeBlanks = dropWhile (==B)

Fill the row back up with blanks.

> fillCol :: Row -> Row
> fillCol col = if (length col < rows) then fillCol (B:col) else col

Add a piece to the front of a row

> addPiece :: Row -> Player -> Row
> addPiece col piece = piece:col

Fill the rest of a row with blanks

> putPiece :: Board -> Int -> Player -> Row
> putPiece board n piece = fillCol (addPiece (removeColBlanks board n) piece)

[Columns before the modified one] ++ [modified one] ++ [all columns after modified one] = board

> makeMove :: Board -> Int -> Player -> Board
> makeMove board n piece = colsToRows ((take n (colsToRows board))
>                                     ++ [(putPiece board n piece)]
>                                     ++ (drop (n+1) (colsToRows board)))

Counting the number of pieces in play

> numPieces :: Board -> Int
> numPieces = length . filter (/= B) . concat

Using this to determine whose go it is. X goes first in my book.

> whoseGo :: Board -> Player
> whoseGo board = if mod (numPieces board) 2 == 0 then X else O

Actually making the move now, suing just the board to determine whose go it is

> move :: Board -> Int -> Board
> move board n = makeMove board n $ whoseGo board

Returns a list of all non-full columns on the board

> emptyCols :: Board -> [Int]
> emptyCols board = filter (not . isColFull board) [0..cols-1]

Checking if a column is full, to help with the above

> isColFull :: Board -> Int -> Bool
> isColFull board n = (getCol board n) !! 0 /= B

Check if a move is valid

> isValid :: Board -> Int -> Bool
> isValid board n
>             | not (elem n [0..cols-1]) = False
>             | isColFull board n = False
>             | otherwise = True

Check if the board is full

> isFull :: Board -> Bool
> isFull board = if (numPieces board == rows*cols) then True else False

----------------------------------------------------------------------
HAS WON LOGIC GOES HERE:----------------------------------------------
----------------------------------------------------------------------

Determines if either player has won a row. Uses the `win` value defined
at the start to generate a list of, say 4 X's and one of 4 O's, if the
value of `win` is 4

> hasXWon :: Row -> Bool
> hasXWon = elem (replicate win X) . group

> hasOWon :: Row -> Bool
> hasOWon = elem (replicate win O) . group

Determines *which* player won the row

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
> hasWonCols board = map hasWonRow $ colsToRows board

Win states of every diagonal

> hasWonDiags :: Board -> [Player]
> hasWonDiags board = map hasWonRow $ allDiagonals board

Win states of all three combined into one list

> hasWon :: Board -> [Player]
> hasWon board = hasWonRows board ++ hasWonCols board ++ hasWonDiags board

Who won?

> whoWon :: Board -> Player
> whoWon board
>           | elem X (hasWon board) = X
>           | elem O (hasWon board) = O
>           | otherwise = B

And using that, is there a winner? (Yes this seems backwards, but it works)

> isAWinner :: Board -> Bool
> isAWinner board = whoWon board /= B

----------------------------------------------------------------------
GENERAL HELPERS HERE:-------------------------------------------------
----------------------------------------------------------------------

Need a little helper to let us get which column wants a piece putting in

> getNat :: String -> IO Int
> getNat prompt = do putStr prompt
>                    xs <- getLine
>                    if xs /= [] && all isDigit xs then return (read xs)
>                    else do putStrLn "ERROR: Invalid number"
>                            getNat prompt

Good to have one little function that tells us if the board is done

> isFinished :: Board -> Bool
> isFinished board = isAWinner board || isFull board

> getPlayerNo :: String -> IO Int
> getPlayerNo prompt = do p <- getNat prompt
>                         if elem p [0..2] then return p
>                         else getPlayerNo "Please enter 0, 1, or 2 "

----------------------------------------------------------------------
GAME TREE STUFF HERE:-------------------------------------------------
----------------------------------------------------------------------

First, what is a tree? It's a Node with a value attached, whose children can be
expressed as a list of further trees

> data Tree a = Node a [Tree a] deriving Show

Now, a function to generate a full game tree from a board. It's important that it
stops on a board that would be the end of the game. The node consists of the
current board and a list of nodes of the same format where the boards are the 
result of every possible move

> gameTree :: Board -> Tree Board
> gameTree board = if isFinished board then Node board []
>                                      else Node board [gameTree (move board n) | n <- emptyCols board]

Limiting is needed to keep us at a reasonable height; this does that

> limitTree :: Int -> Tree a -> Tree a
> limitTree 0 (Node x _) = Node x []
> limitTree n (Node x ts) = Node x [limitTree (n-1) t | t <- ts]

And now a function to generate a limited tree

> treeOfHeight :: Int -> Board -> Tree Board
> treeOfHeight h b = limitTree h $ gameTree b

Generating a new tree containing (board, winner) tuples.
A childless node implies the board is either full or someone's won, per the gameTree function.
If the node being converted has children, the new node contains the board, and the maximum or minimum of
its children

> tupleGen :: Tree Board -> Tree (Board, Player)
> tupleGen (Node b []) = Node (b, whoWon b) []
> tupleGen (Node b bs) = Node (b, minOrMax (whoseGo b) (map (getPlayerTuple . tupleGen) bs)) (map tupleGen bs)

> minOrMax :: Player -> ([Player] -> Player)
> minOrMax X = maximum
> minOrMax O = minimum

Getting the player part of the tuple

> getPlayerTuple :: Tree (a, b) -> b
> getPlayerTuple (Node t _) = snd t

Generating a tuple tree of height n: apply tupleGen to treeOfHeight in one function

> tupleTreeHeight :: Board -> Int -> Tree (Board, Player)
> tupleTreeHeight board n = tupleGen $ treeOfHeight n board

Getting the next move to take by seeing if the winning move has propagated up the tree

> getChildIndex :: Tree (Board, Player) -> Maybe Int
> getChildIndex (Node (board, player) tuples) = elemIndex (whoseGo board) $ map getPlayerTuple tuples

Wrapping the above so we can get it from just a board

> returnIndex :: Board -> Maybe Int
> returnIndex board = getChildIndex $ tupleTreeHeight board depth

Finally, if a value has been returned by the above, strip away the `Just` part and give us the value
Else, if the above has returned Nothing, choose a random value from all empty columns

> pickAWinner :: Board -> Int
> pickAWinner board = case (returnIndex board) of
>                         Just x -> x
>                         Nothing -> randomEmptyCol board

Generating a random number in a way that doesn't then wrap it in IO, cos that'll propagate through and be a pain to
deal with.

> randomNum :: Int -> Int
> randomNum n = unsafePerformIO(randomRIO(0,n-1))

Selecting a random member of the list of empty columns

> randomEmptyCol :: Board -> Int
> randomEmptyCol board = (emptyCols board) !! randomNum (length (emptyCols board))

----------------------------------------------------------------------
GAME LOOP HERE:-------------------------------------------------------
----------------------------------------------------------------------

PvE Connect-4: show the board. If it's full, the game is tied, so end. If there's a winner, print the winner and end.
Otherwise, the game's still on. If it's X to play, get a human input, make sure it's valid, if it is play it. If it's
not, try again. If it's O to play, the computer does it.

> play :: Board -> IO()
> play board = do showBoard board
>                 if isFull board then putStrLn "Board Full: DRAW!!"
>                 else if isAWinner board then putStrLn ("Winner: " ++ show (whoWon board))
>                 else do
>                   if (whoseGo board) == X then do
>                     c <- getNat "Your turn: "
>                     putChar '\n'
>                     if isValid board (c-1) then
>                       play (move board (c-1))
>                     else
>                       putStrLn ("Move invalid: either column is full or out of range. Your move: " ++ [intToDigit c])
>                   else
>                     play $ move board $ pickAWinner board

EvE Connect-4: See above, but without the human bits.

> playAI :: Board -> IO()
> playAI board = do showBoard board
>                   if isFull board then putStrLn "Board Full: DRAW!!"
>                   else if isAWinner board then putStrLn ("Winner: " ++ show (whoWon board))
>                   else do let c = pickAWinner board
>                           putStrLn (show (whoseGo board) ++ " chooses " ++ [intToDigit c] ++ " from " ++ (map intToDigit (emptyCols board)))
>                           playAI $ move board c

PvP Connect-4: as PvE, but without the computer bits.

> playPVP :: Board -> IO()
> playPVP board = do showBoard board
>                    if isFull board then putStrLn "Board Full: DRAW!!"
>                    else if isAWinner board then putStrLn ("Winner: " ++ show (whoWon board))
>                    else do
>                      putStrLn (show (whoseGo board) ++ " to play")
>                      c <- getNat "Choose a column: "
>                      putChar '\n'
>                      if isValid board (c-1) then playPVP $ move board (c-1)
>                      else putStrLn ("Move invalid: either column is full or out of range. Your move: " ++ [intToDigit c])


And finally, main, in which the human gets to decide how many humans are playing.

> main :: IO()
> main = do p <- getPlayerNo "How many human players? (0, 1, or 2) "
>           if p == 0 then playAI empty
>           else if p == 1 then play empty
>           else if p == 2 then playPVP empty
>           else putStrLn "Something's gone very wrong..."

----------------------------------------------------------------------

TODO: Tidy up

----------------------------------------------------------------------
