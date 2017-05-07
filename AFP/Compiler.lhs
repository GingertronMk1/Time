G52AFP Coursework 2 - Monadic Compiler

Jack Ellis
psyje5@nottingham.ac.uk

--------------------------------------------------------------------------------

 import Data.List

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
MY CODE STARTS HERE:------------------------------------------------------------
--------------------------------------------------------------------------------

TEST CASES:---------------------------------------------------------------------

> testStack :: Stack
> testStack = [1,4,6,3]
> testMem :: Mem
> testMem = [('A',5),('B',3),('C',10),('D',0),('E',6)]
> mulTest :: Int -> Int -> Prog
> mulTest x y = Seqn [Assign 'A' (Val x),
>                     Assign 'B' (Val y),
>                     Assign 'A' (App Mul (Var 'A') (Var 'B'))]
> subTest :: Prog
> subTest = Seqn [Assign 'A' (Val 4),
>                 Assign 'B' (Val 1),
>                 Assign 'A' (App Sub (Var 'A') (Var 'B'))]
> labelTest :: Code
> labelTest = [LABEL 0, PUSH 1, LABEL 1]
> jumpTest :: Code
> jumpTest = [PUSH 1, POP 'A', JUMP 0, PUSH 2, POP 'A', LABEL 1, PUSH 10, POP 'B', JUMP 2, LABEL 0, JUMP 1, LABEL 2]
> labelTestProg :: Prog
> labelTestProg = Seqn [Assign 'A' (Val 1),
>                       Assign 'B' (Val 2),
>                       If (Var 'B') (fac 10) (fac 2)]

COMPILER CODE:------------------------------------------------------------------

'comp' goes from Prog to Code, where Code = [Inst]
Therefore it goes from Prog -> [Inst]

> comp :: Prog -> Code
> comp p = fst $ app (progCompST p) 0

Compiling expressions first; building blocks.

> exprComp :: Expr -> Code
> exprComp (Val i) = [PUSH i]   -- if it's just a value, PUSH that to the stack
> exprComp (Var n) = [PUSHV n]  -- if it's a variable, PUSHV that
> exprComp (App o e p) = exprComp e ++ exprComp p ++ [DO o] -- if it's an operation, do it recursively

Compiling programs statelessly, just to get my head around the syntax we need to build

progComp :: Prog -> Label -> (Code, Label)
progComp (Assign n e) l = (exprComp e ++ [POP n], l)
progComp (Seqn []) l = ([], l)
progComp (If e p1 p2) l = (exprComp e ++ [JUMPZ 0] ++ x1 ++ [JUMP 1] ++ [LABEL 0] ++ x2 ++ [LABEL 1], y2)
                          where (x1, y1) = progComp p1 (l+2)
                                (x2, y2) = progComp p2 y1
progComp (While e p) l = ([LABEL l] ++ exprComp e ++ [JUMPZ (l+1)] ++ x ++ [JUMP l] ++ [LABEL (l+1)], y)
                          where (x,y) = progComp p (l+2)

progComp (Seqn (p:ps)) l = (x ++ x2, y2)
                            where (x,y) = progComp p l
                                  (x2,y2) = progComp (Seqn ps) y

Starting on states
Stateful computation: State -> (a, State)

Generation of new labels done here

> fresh = S(\n -> (n, n+1))

And now, compiling programs using state

> progCompST :: Prog -> ST Code
> progCompST (Assign n e) = return $ exprComp e ++ [POP n]

For a While loop: reserve 2 fresh labels; one for the beginning and one for the  end of the loop (something to jump back to at the end 
of the loop and something to skip to once the predicate's fulfilled), and compile the sub-program to be run as the body of the loop, then 
`++` it all together

> progCompST (While e p) = do lab1 <- fresh
>                             lab2 <- fresh
>                             prog1 <- progCompST p
>                             return $ [LABEL lab1] ++ exprComp e ++ [JUMPZ lab2] ++ prog1 ++ [JUMP lab1] ++ [LABEL lab2]

For If/Else: similar to While in that two labels are reserved; this time one for the second branch (the Else sub-program) and one for the end
(for the If branch to skip to once that subprogram's finished), then recursively compile the two sub-programs, then `++` everything together.

> progCompST (If e p1 p2) = do lab1 <- fresh    -- reserve a label for one branch of the statement
>                              lab2 <- fresh    -- and one for the other
>                              prog1 <- progCompST p1   -- recursive call for the body of one branch
>                              prog2 <- progCompST p2   -- another for the other
>                              return $ exprComp e ++ [JUMPZ lab1] ++ prog1 ++ [JUMP lab2] ++ [LABEL lab1] ++ prog2 ++ [LABEL lab2]

Now onto Seqn. If it's an empty Seqn, return an empty list of code. Otherwise, compile the first program in the Seqn, then recursively compile
the rest as another Seqn, then `++` it all together.

> progCompST (Seqn []) = return []
> progCompST (Seqn (p:ps)) = do prog1 <- progCompST p               -- Compile the first bit (the first instruction)
>                               progRest <- progCompST (Seqn ps)    -- Compile the rest of it
>                               return $ prog1 ++ progRest          -- Concatenate the two together

EXECUTOR CODE:------------------------------------------------------------------

exec :: Code -> Mem

Machine state: (Code to be executed (including current instruction), Code already executed, Stack, Mem)

> type Machine = (Code, Code, Stack, Mem)   -- WELCOME MY SON

> instExec :: Machine -> Machine
> instExec ((PUSH n):is, is2, s, m)   = (is, (PUSH n):is2, n:s, m)
> instExec ((PUSHV n):is, is2, s, m)  = (is, (PUSHV n):is2, s', m)
>                                       where s' = instPushV n m s
> instExec ((POP n):is, is2, s, m)    = (is, (POP n):is2, s', m')
>                                       where (s', m') = instPop n s m
> instExec ((DO o):is, is2, s, m)     = (is, (DO o):is2, s', m)
>                                       where s' = instDo o s
> instExec ((LABEL l):is, is2, s, m)  = (is, (LABEL l):is2, s, m)
> instExec ((JUMP n):is, is2, s, m)   = (is', is2', s, m)
>                                       where (is', is2') = instJump n is (JUMP n:is2)
> instExec ((JUMPZ n):is, is2, s, m)  = (is', is2', s, m)
>                                       where (is', is2') = instJumpZ n is (JUMPZ n:is2) s

> instPushV :: Name -> Mem -> Stack -> Stack
> instPushV n m s = (instPushV' n m):s

> instPushV' :: Name -> Mem -> Int
> instPushV' n m = snd . head $ filter (\x -> fst x == n) m

> instPop :: Name -> Stack -> Mem -> (Stack, Mem)
> instPop n s m = (tail s, (n,head s):(filter (\x -> fst x /= n) m))

> instDo o s = case o of Add -> (y+x):newStack
>                        Sub -> (y-x):newStack
>                        Mul -> (y*x):newStack
>                        Div -> (div y x):newStack
>              where newStack = drop 2 s
>                    [x,y] = take 2 s

> instJump :: Label -> Code -> Code -> (Code, Code)
> instJump n is is2 = instJump' n $ (reverse is2 ++ is)

> instJump' :: Label -> Code -> (Code, Code)
> instJump' n c = (is, reverse is2)
>                  where is   = dropWhile (instJump'' n) c
>                        is2  = takeWhile (instJump'' n) c

> instJump'' :: Label -> Inst -> Bool
> instJump'' n (LABEL l) = not $ l == n
> instJump'' n _ = True

> instJumpZ :: Label -> Code -> Code -> Stack -> (Code, Code)
> instJumpZ n is is2 s = if (head s == 0) then instJump n is is2
>                                         else (is, is2)


> codeExec :: Machine -> Machine
> codeExec mac@(i:[], is2, s, m) = instExec mac
> codeExec mac@(i:is, is2, s, m) = codeExec (instExec mac)

> execBase :: Code -> Machine
> execBase c = codeExec (c, [], [], [])

> codeRes p = c2
>             where (c1, c2, s, m) = execBase $ comp p

> exec :: Code -> Mem
> exec c = m
>          where (c1, c2, s, m) = execBase c

> run :: Prog -> Mem
> run p = exec $ comp p

> ijptest n = instJump' n $ comp $ fac 10
