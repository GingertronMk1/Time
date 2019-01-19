data Expr = Val Int | App Op Expr Expr
            deriving Show
data Op = Add | Mul
          deriving Show

testExpr = App Mul (Val 2) (Val 3)

eval :: Expr -> Int
eval (Val n) = n
eval (App o e1 e2) = case o of Add -> (eval e1) + (eval e2)
                               Mul -> (eval e1) * (eval e2)

values :: Expr -> [Int]
values (Val n) = [n]
values (App o e1 e2) = values e1 ++ values e2

valuesAcc :: Expr -> [Int]
valuesAcc e = valuesAcc' e []

valuesAcc' :: Expr -> [Int] -> [Int]
valuesAcc' (Val n) is = n:is
valuesAcc' (App o e1 e2) is = valuesAcc' e1 (valuesAcc' e2 is)

delete :: Int -> [Int] -> [Int]
delete _ [] = []
delete n (i:is) = if i == n then is
                            else i:(delete n is)

split :: [Int] -> [([Int],[Int])]
split xs = [(take n xs, drop n xs) | n <- [1..(length xs - 1)]]

exprs :: [Int] -> [Expr]
exprs [n] = [Val n]
exprs xs = [App o l r | (ls, rs) <- split xs, l <- exprs ls, r <- exprs rs, o <- [Add, Mul]]

solve :: [Int] -> Int -> [Expr]
solve [] _ = []
solve xs n = [e | e <- exprs xs, eval e == n]

perms :: [Int] -> [[Int]]
perms [] = [[]]
perms is = [i:js | i <- is, js <- perms (delete i is)]
