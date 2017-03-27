G52AFP Coursework 2 - Monadic Compiler

Jack Ellis
psyje5@nottingham.ac.uk

--------------------------------------------------------------------------------

> import Data.List
> import Data.Maybe

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

> testStack :: Stack
> testStack = [1,4,6,3]
> testMem :: Mem
> testMem = [('A',5),('B',3),('C',10),('D',0),('E',6)]

> instPush :: Int -> Stack -> Stack
> instPush i is = i:is

 instPushV :: Name -> Mem -> Stack -> Stack
 instPushV n [] [] = []
 instPushV n m []  = do ind <- elemIndex n names
                        val <- vals !! ind
                        return [val]
                     where names = map fst m
                           vals  = map snd m

> instPop :: Name -> Stack -> Mem -> Mem
> instPop n [] m = m
> instPop n s m = if notElem n (map fst m) then (n,head s):m
>                                          else (n,head s):[x | x <- m, fst x /= n]

> memNames :: Mem -> [Name]
> memNames m = map fst m
> memVals :: Mem -> [Int]
> memVals m = map snd m
