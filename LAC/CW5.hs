import Data.List
import Data.Maybe

data SAT = Var Int
         | Not SAT
         | And SAT SAT
         | Or SAT SAT
         deriving Show

type Assignment = [Bool]

baseSAT :: SAT
baseSAT = Not (Var 0)

testSAT :: SAT
testSAT = And (Or (Var 0) (Not (Var 1))) (Not (Var 0))

testAss :: Assignment
testAss = [False, False]

testSAT2 :: SAT
testSAT2 = And (And (And (Var 0) (Var 1)) (And (Var 2) (Var 3))) (And (Var 4) (Not (Var 5)))

testSAT3 :: SAT
testSAT3 = And (Not (Var 0)) (Var 0)

testSATs :: [SAT]
testSATs = [testSAT,testSAT2,testSAT3]

evaluate :: SAT -> Assignment -> Bool
evaluate (Var n) a = a !! n
evaluate (Not s) a = not $ evaluate s a
evaluate (And s1 s2) a = (evaluate s1 a) && (evaluate s2 a)
evaluate (Or s1 s2) a = (evaluate s1 a) || (evaluate s2 a)

varNum :: SAT -> Int
varNum s = maximum $ varNum' s []

varNum' :: SAT -> [Int] -> [Int]
varNum' (Var n) is = n:is
varNum' (Not s) is = varNum' s is
varNum' (And s1 s2) is = (varNum' s1 is) ++ (varNum' s2 is)
varNum' (Or s1 s2) is = (varNum' s1 is) ++ (varNum' s2 is)

allAssign :: Int -> [Assignment]
allAssign n = sequence $ replicate (n+1) [True, False]

allAssignSAT :: SAT -> [Assignment]
allAssignSAT s = allAssign $ varNum s

satisfiable :: SAT -> Bool
satisfiable s = or $ map (evaluate s) (allAssignSAT s)

solution :: SAT -> Maybe Assignment
solution s = do i <- elemIndex True $ map (evaluate s) allAss
                return $ allAss !! i
                where allAss = allAssignSAT s

solutions :: [SAT] -> [Maybe Assignment]
solutions ss = map solution ss
