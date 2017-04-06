IMPORTS:-------------------------------------------

> import Data.List
> import Data.Maybe

WHAT WAS GIVEN:------------------------------------

> data SAT = Var Int
>          | Not SAT
>          | And SAT SAT
>          | Or SAT SAT
>          deriving Show

> type Assignment = [Bool]

MY CODE:-------------------------------------------

TEST CASES:------------------------------------

> baseSAT :: SAT
> baseSAT = Not (Var 0)

> testSAT :: SAT
> testSAT = And (Or (Var 0) (Not (Var 1))) (Not (Var 0))

> testAss :: Assignment
> testAss = [False, False]

> testSAT2 :: SAT
> testSAT2 = And (And (And (Var 0) (Var 1)) (And (Var 2) (Var 3))) (And (Var 4) (Not (Var 5)))

FUNCTIONS:-------------------------------------

Evaluate takes a SAT, compares it to the Assignment, and returns
whether or not it is True

> evaluate :: SAT -> Assignment -> Bool
> evaluate (Var n) a = a !! n
> evaluate (Not s) a = not $ evaluate s a
> evaluate (And s1 s2) a = (evaluate s1 a) && (evaluate s2 a)
> evaluate (Or s1 s2) a = (evaluate s1 a) || (evaluate s2 a)

varNum needs a helper function so it can accumulate the values of
the variables. This returns a list of Ints, which we use the standard 
prelude function `maximum` to obtain the largest of.

> varNum :: SAT -> Int
> varNum s = maximum $ varNum' s []

> varNum' :: SAT -> [Int] -> [Int]
> varNum' (Var n) is = n:is
> varNum' (Not s) is = varNum' s is
> varNum' (And s1 s2) is = (varNum' s1 is) ++ (varNum' s2 is)
> varNum' (Or s1 s2) is = (varNum' s1 is) ++ (varNum' s2 is)

allAssign: `sequence`, when applied to lists, returns the cartesian product
of the lists. Applying this to a list of lists containing `n` [True, False]
combinations gives us all possible combinations of `n` Trues and Falses.

> allAssign :: Int -> [Assignment]
> allAssign n = sequence $ replicate n [True, False]

> allAssignSAT :: SAT -> [Assignment]
> allAssignSAT s = allAssign $ (varNum s) + 1

satisfiable: first create a helper function that returns the result of all
applications of combinations of Assignments on the SAT. If any of them
return True, the solution is Satisfiable, so `or` the list.

> satisfiable :: SAT -> Bool
> satisfiable s = or $ satisfiable' s

> satisfiable' :: SAT -> [Bool]
> satisfiable' s = map (evaluate s) (allAssignSAT s)

solution: apply the function to each element of allAssign, to return a list
of Bools. Use elemIndex (defined in Data.Maybe) to find the Maybe Int corresponding
to a success, then via a helper function, return the value of that index in the
list of Assignments

> solution s = solution' (elemIndex True $ map (evaluate s) allAss) allAss
>              where allAss = allAssignSAT s

> solution' :: Maybe Int -> [a] -> Maybe a
> solution' (Just n) as = Just (as !! n)
> solution' Nothing _ = Nothing
