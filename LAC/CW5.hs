import Data.Maybe

data SAT = Var Int
         | Not SAT
         | And SAT SAT
         | Or SAT SAT
         deriving Show

type Assignment = [Bool]

baseSAT :: SAT
baseSAT = Not (Var 0)

testAss :: Assignment
testAss = [False, False]

testSATs :: [SAT]
testSATs = [And (Or (Var 0) (Not (Var 1))) (Not (Var 0)),
            And (And (And (Var 0) (Var 1)) (And (Var 2) (Var 3))) (And (Var 4) (Not (Var 5))),
            And (Not (Var 0)) (Var 0)]

evaluate :: SAT -> Assignment -> Bool
evaluate (Var n) a = a !! n
evaluate (Not s) a = not $ evaluate s a
evaluate (And s1 s2) a = (evaluate s1 a) && (evaluate s2 a)
evaluate (Or s1 s2) a = (evaluate s1 a) || (evaluate s2 a)

varNum :: SAT -> Int
varNum = maximum . varNum'

varNum' :: SAT -> [Int]
varNum' (Var n) = [n]
varNum' (Not s) = varNum' s
varNum' (And s1 s2) = varNum' s1 ++ varNum' s2
varNum' (Or s1 s2) = varNum' s1 ++ varNum' s2

allAssign :: Int -> [Assignment]
allAssign n = sequence (replicate (n+1) [True, False])

allAssignSAT :: SAT -> [Assignment]
allAssignSAT = allAssign . varNum

satisfiable :: SAT -> Bool
satisfiable s = or (map (evaluate s) (allAssignSAT s))

solution :: SAT -> Maybe Assignment
solution s = if trueSols /= [] then Just $ fst $ head trueSols
                               else Nothing
             where trueSols = filter snd (map (\x -> (x, evaluate s x)) (allAssignSAT s))

solutions :: [SAT] -> [Maybe Assignment]
solutions = map solution

soltest :: [Maybe Assignment]
soltest = solutions testSATs
