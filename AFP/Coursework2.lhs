G52AFP Coursework 2 - Monadic Compiler

Jack Ellis
psyje5@nottingham.ac.uk

--------------------------------------------------------------------------------

> import Data.List

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

COMPILER CODE:------------------------------------------------------------------

'comp' goes from Prog to Code, where Code = [Inst]
Therefore it goes from Prog -> [Inst]

> comp :: Prog -> Code
> --comp p = fst $ progComp p 0   -- Stateless compilation
> comp p = fst $ app (progCompST p) 0

Compiling expressions first; building blocks.

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

> fresh = S(\n -> (n, n+1))

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
> progCompST (Seqn (p:ps)) = do prog1 <- progCompST p               -- Compile the first bit (the first instruction)
>                               progRest <- progCompST (Seqn ps)    -- Compile the rest of it
>                               return $ prog1 ++ progRest          -- Concatenate the two together

EXECUTOR CODE:------------------------------------------------------------------

exec :: Code -> Mem

> type PC = Int    -- A program counter to keep track of where I am in the code

The 'Machine': the program counter, Stack, Memory, a copy of all the code, and a list of `Int`s representing
where all the labels are (this function comes later)

> type Machine = (PC, Stack, Mem, Code, [Int])   -- WELCOME MY SON

> run :: Prog -> Mem
> run p = exec $ comp p

> exec :: Code -> Mem
> exec c = m
>          where (p,s,m,c',ls) = codeExec (0,[],[],c,firstPass c)

Push takes an int and puts it at the beginning of the stack

> instPush :: Int -> Stack -> Stack
> instPush i s = i:s

PushV takes a name, looks it up in memory, and PUSHes the associated value to the stack

> instPushV :: Name -> Mem -> Stack -> (Stack, Mem)
> instPushV n m s = (instPush (memSearch n m) s, m)

To search the memory without going through `Maybe`s (I imagine this is a language like C where it just expects you to know what you're doing)
construct a copy of memory where the `Name` section corresponds to the name given, return the first list item and take the second part of that.

> memSearch :: Name -> Mem -> Int
> memSearch n m = snd $ head [x | x <- m, fst x == n]

Pop takes the head of the stack (an int), as well as a name, and puts it into memory as a tuple
If the stack is empty, return the memory as-is

> instPop :: Name -> Stack -> Mem -> (Stack,Mem)
> instPop n [] m = ([],m)
> instPop n s m = (s, (n,head s):[x | x <- m, fst x /= n])

`Do`ing a mathematical operation means taking the top two stack items, performing the operation
and returning the result to the head of the stack

> instDo :: Op -> Stack -> Stack
> instDo Add s = (y+x):(drop 2 s)
>                where [x,y] = take 2 s
> instDo Sub s = (y-x):(drop 2 s)
>                where [x,y] = take 2 s
> instDo Mul s = (y*x):(drop 2 s)
>                where [x,y] = take 2 s
> instDo Div s = (quot y x):(drop 2 s)    -- quot: integer division that rounds down
>                where [x,y] = take 2 s

Executing individual instructions, which change the state of the machine.

> instExec :: Inst -> Machine -> Machine
> instExec (PUSH i) (p,s,m,c,ls) = (p+1,s',m,c,ls)                -- PUSH updates the stack
>                               where s' = instPush i s
> instExec (PUSHV n) (p,s,m,c,ls) = (p+1,s', m',c,ls)             -- PUSHV updates both memory and stack
>                                where (s',m') = instPushV n m s
> instExec (POP n) (p,s,m,c,ls) = (p+1,s', m',c,ls)               -- As does POP
>                              where (s',m') = instPop n s m
> instExec (DO o) (p,s,m,c,ls) = (p+1,s',m,c,ls)                  -- DO updates the stack
>                             where s' = instDo o s
> instExec (LABEL l) (p,s,m,c,ls) = skip (p,s,m,c,ls)             -- LABEL instructions get skipped; this function comes later
> instExec (JUMP n) (p,s,m,c,ls) = (ls!!n,s,m,c,ls)               -- JUMP changes the program counter, which changes out position in the code
> instExec (JUMPZ n) (p,s,m,c,ls) = if (head s) == 0 then instExec (JUMP n) (p,s,m,c,ls)    -- JUMPZ is just JUMP with a predicate: if the predicate is fulfilled, JUMP
>                                                    else skip (p,s,m,c,ls)                 -- Else, skip

Little skip function for LABEL and JUMPZ if the predicate doesn't happen. It just updates the program counter

> skip :: Machine -> Machine
> skip (p,s,m,c,ls) = (p+1,s,m,c,ls)

To execute the code: if you're not at the last thing, do the next instruction, using the machine state from performing the
current instruction. If you are at the last thing, just do this one.

The intuition on that last part is that you're never going to get a JUMP as the last instruction, as any given loop or IF
will put a label at the end as a place to JUMP to, and a straight-through program won't have JUMPs at all.

> codeExec :: Machine -> Machine
> codeExec (p,s,m,c,ls) = if p < (length c)-1 then codeExec (p',s',m',c',ls')
>                         else instExec (c!!p) (p,s,m,c,ls)
>                         where (p',s',m',c',ls') = instExec (c!!p) (p,s,m,c,ls)

Generating a list of labels' positions in the code is the first pass of the executor. First, we make a function that looks at individual instructions
and updates a list of positions based on that instructions' position in the code (passed in as an argument). If the Inst passed in is a LABEL, take its
index and add it to the list of positions, else return the list of positions unchanged.

> labelPos' :: Inst -> Int -> [Int] -> [Int]
> labelPos' (LABEL l) i xs = xs ++ [i]
> labelPos' _ i xs = xs

Applying this function over some Code, if you are at the end of the code, return the result of applying the helper to the last Inst. Otherwise, recursively
apply yourself to the remainder of the code, passing in the list of positions that results from applying the helper to the current Inst.

> labelPos :: Code -> Int -> [Int] -> [Int]
> labelPos (i:[]) n s = labelPos' i n s
> labelPos (i:is) n s = labelPos is (n+1) $ labelPos' i n s

As the above two functions take an index and a list of positions as arguments, as well as the Code to scan through, we need to create a function that will take
just code. This is trivially labelPos, with the Code to scan passed in as well as initial values of 0 for the index and the empty list for the list.

> firstPass :: Code -> [Int]
> firstPass c = labelPos c 0 []
