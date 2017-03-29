G52AFP Coursework 2 - Monadic Compiler

Jack Ellis
psyje5@nottingham.ac.uk

--------------------------------------------------------------------------------


Imperative language:

> data Prog = Assign Name Expr
>           | If Expr Prog Prog
>           | While Expr Prog
>           | Seqn [Prog]
>             deriving Show
>
> data Expr = Val Int | Var Name | App Op Expr Expr
>             deriving Show
>
> type Name = Char
>
> data Op   = Add | Sub | Mul | Div
>             deriving Show

Factorial example:

> fac :: Int -> Prog
> fac n = Seqn [Assign 'A' (Val 1),
>               Assign 'B' (Val n),
>               While (Var 'B') (Seqn
>                  [Assign 'A' (App Mul (Var 'A') (Var 'B')),
>                   Assign 'B' (App Sub (Var 'B') (Val (1)))])]

Virtual machine:

> type Stack = [Int]
>
> type Mem   = [(Name,Int)]
>
> type Code  = [Inst]
> 
> data Inst  = PUSH Int         -- Pushes an Int to the top of the stack
>            | PUSHV Name       -- Takes a variable name, looks it up in memory, PUSHes the relevant value
>            | POP Name         -- Takes the value from the top of the stack, stores in memory with the name 'Name'
>            | DO Op            -- Does a mathematical operation on the top two values, PUSHes the result
>            | JUMP Label       -- Jump to label 'Label' in the code
>            | JUMPZ Label      -- Jump if the value at the top of the stack == 0
>            | LABEL Label      -- Put a label at this point
>              deriving Show
> 
> type Label = Int

State monad:

> type State = Label
>
> newtype ST a = S (State -> (a, State))
>
> app :: ST a -> State -> (a,State)
> app (S st) x  =  st x
>
> instance Functor ST where
>    -- fmap :: (a -> b) -> ST a -> ST b
>    fmap g st = S (\s -> let (x,s') = app st s in (g x, s'))
>
> instance Applicative ST where
>    -- pure :: a -> ST a
>    pure x = S (\s -> (x,s))
>
>    -- (<*>) :: ST (a -> b) -> ST a -> ST b
>    stf <*> stx = S (\s ->
>       let (f,s')  = app stf s
>           (x,s'') = app stx s' in (f x, s''))
>
> instance Monad ST where
>    -- return :: a -> ST a
>    return x = S (\s -> (x,s))
>
>    -- (>>=) :: ST a -> (a -> ST b) -> ST b
>    st >>= f = S (\s -> let (x,s') = app st s in app (f x) s')

--------------------------------------------------------------------------------


'comp' goes from Prog to Code, where Code = [Inst]
Therefore it goes from Prog -> [Inst]

> comp :: Prog -> Code
> --comp p = fst $ progComp p 0
> comp p = fst $ app (progCompST p) 0

Compiling expressions first; building blocks

> exprComp :: Expr -> Code
> exprComp (Val i) = [PUSH i]   -- if it's just a value, PUSH that to the stack
> exprComp (Var n) = [PUSHV n]  -- if it's a variable, PUSHV that
> exprComp (App o e p) = exprComp e ++ exprComp p ++ [DO o] -- if it's an operation, do it recursively

Compiling programs statelessly, just to get my head around the syntax we need to build

> progComp :: Prog -> Label -> (Code, Label)
> progComp (Assign n e) l = (exprComp e ++ [POP n], l)
> progComp (Seqn []) l = ([], l)
> progComp (If e p1 p2) l = (exprComp e ++ [JUMPZ 0] ++ x1 ++ [JUMP 1] ++ [LABEL 0] ++ x2 ++ [LABEL 1], y2)
>                           where (x1, y1) = progComp p1 (l+2)
>                                 (x2, y2) = progComp p2 y1
> progComp (While e p) l = ([LABEL l] ++ exprComp e ++ [JUMPZ (l+1)] ++ x ++ [JUMP l] ++ [LABEL (l+1)], y)
>                           where (x,y) = progComp p (l+2)
> progComp (Seqn (p:ps)) l = (x ++ x2, y2)
>                             where (x,y) = progComp p l
>                                   (x2,y2) = progComp (Seqn ps) y

Starting on states
Stateful computation: State -> (a, State)

Generation of new labels done here

> fresh = S (\n -> (n, n+1))

And now, compiling programs using state

> progCompST :: Prog -> ST Code
> progCompST (Assign n e) = return $ exprComp e ++ [POP n]
> progCompST (While e p) = do lab1 <- fresh     -- reserve a fresh label for the beginning of the loop
>                             lab2 <- fresh     -- and one for the end of the loop
>                             prog1 <- progCompST p   -- recursive call for the body of the loop
>                             return $ [LABEL lab1] ++ exprComp e ++ [JUMPZ lab2] ++ prog1 ++ [JUMP lab1] ++ [LABEL lab2]
> progCompST (If e p1 p2) = do lab1 <- fresh    -- reserve a label for one branch of the statement
>                              lab2 <- fresh    -- and one for the other
>                              prog1 <- progCompST p1   -- recursive call for the body of one branch
>                              prog2 <- progCompST p2   -- another for the other
>                              return $ exprComp e ++ [JUMPZ lab1] ++ prog1 ++ [JUMP lab2] ++ [LABEL lab1] ++ prog2 ++ [LABEL lab2]
> progCompST (Seqn []) = return []
> progCompST (Seqn (p:ps)) = do prog1 <- progCompST p
>                               progRest <- progCompST (Seqn ps)
>                               return $ prog1 ++ progRest

--------------------------------------------------------------------------------

exec :: Code -> Mem

> exec :: Code -> Mem
> exec [] = []
> exec c = snd $ codeExec c [] []

Creating a couple of test cases; stack and memory, as well as some basic addition code

> testStack :: Stack
> testStack = [1,4,6,3]
> testMem :: Mem
> testMem = [('A',5),('B',3),('C',10),('D',0),('E',6)]
> mulTest :: Int -> Int -> Prog
> mulTest x y = Seqn [Assign 'A' (Val x),
>                     Assign 'B' (Val y),
>                     Assign 'A' (App Mul (Var 'A') (Var 'B'))]

Push takes an int and puts it at the beginning of the stack

> instPush :: Int -> Stack -> Mem -> (Stack,Mem)
> instPush i s m = (i:s,m)

PushV takes a name, looks it up in memory, and PUSHes the associated value to the stack

> instPushV :: Name -> Mem -> Stack -> (Stack, Mem)
> instPushV n m s = ((memSearch n m):s, m)

To search the memory without going through `Maybe`s (I imagine this is a language like C where it just expects you to know what you're doing)
construct a copy of memory where the `Name` section corresponds to the name given, return the first list item and take the second part of that

> memSearch :: Name -> Mem -> Int
> memSearch n m = snd $ [x | x <- m, fst x == n] !! 0

Pop takes the head of the stack (an int), as well as a name, and puts it into memory as a tuple
If the stack is empty, return the memory as-is

> instPop :: Name -> Stack -> Mem -> (Stack,Mem)
> instPop n [] m = ([],m)
> instPop n s m = (s, (n,head s):[x | x <- m, fst x /= n])

`Do`ing a mathematical operation means taking the top two stack items, performing the operation
and returning the result to the head of the stack

> instDo :: Op -> Stack -> Mem -> (Stack,Mem)
> instDo Add s m = ((x+y):(drop 2 s), m)
>                where [x,y] = take 2 s
> instDo Sub s m = ((x-y):(drop 2 s), m)
>                where [x,y] = take 2 s
> instDo Mul s m = ((x*y):(drop 2 s), m)
>                where [x,y] = take 2 s
> instDo Div s m = ((quot x y):(drop 2 s), m)   -- quot: integer division that rounds down
>                where [x,y] = take 2 s

Executing individual instances, bar JUMP, JUMPZ, and LABEL, as I've not figured out how to do program flow yet

> instExec :: Inst -> Stack -> Mem -> (Stack, Mem)
> instExec (PUSH i) s m = instPush i s m
> instExec (PUSHV n) s m = instPushV n m s
> instExec (POP n) s m = instPop n s m
> instExec (DO o) s m = instDo o s m

> codeExec :: Code -> Stack -> Mem -> (Stack, Mem)
> codeExec (i:[]) s m = instExec i s m
> codeExec (i:is) s m = codeExec is s' m'
>                       where (s',m') = instExec i s m

> compExec :: Code -> (Stack,Mem)
> compExec c = codeExec c [] []

To store labels, a list of (Label name, Index) tuples is generated in the first pass over the code

> labelPos :: Code -> Int -> [(Int, Int)] -> [(Int, Int)]
> labelPos (i:[]) n s = snd $ labelPosHelp i (n,s)
> labelPos (i:is) n s = labelPos is n' s'
>                       where (n',s') = labelPosHelp i (n,s)

> labelPosFin :: Code -> [(Int, Int)]
> labelPosFin c = labelPos c 0 []

> labelPosHelp :: Inst -> (Int,[(Int, Int)]) -> (Int,[(Int, Int)])
> labelPosHelp (LABEL l) (x, xs) = (x+1, xs ++ [(l, x)])
> labelPosHelp _ (x, xs) = (x+1, xs)

TODO: Labels, program flow. To my understanding, a compiler/executor does two passes; the first goes through the labels and makes a note of where they are
The second goes through the code using that information to jump as necessary. I've to figure out how to LABEL the code so that the JUMPs can happen.

Idea: first pass of the 'executor' makes a list of (Int, Int) tuples that stores which label appears at which index in the code
