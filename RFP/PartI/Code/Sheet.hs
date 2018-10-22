module Sheet where

import Data.Array

type CellRef = (Char, Int)

type Sheet a = Array CellRef a

data BinOp = Add | Sub | Mul | Div

data Exp = Lit Double
         | Ref CellRef
         | App BinOp Exp Exp
         | Sum CellRef CellRef
         | Avg CellRef CellRef


mean    :: [Double] -> Double
mean xs = (sum xs)/((fromIntegral . length) xs) 

evalCell :: Sheet Double -> Exp -> Double
evalCell _ (Lit v)        = v
evalCell s (Ref r)        = s ! r
evalCell s (App op e1 e2) = (evalOp op) (evalCell s e1) (evalCell s e2)
evalCell s (Sum (r1,c1) (r2,c2))
  = sum [evalCell s (Ref (r,c)) 
         | r <- range (r1, r2), c <- range (c1,c2)]
evalCell s (Avg (r1,c1) (r2,c2))
  = mean [evalCell s (Ref (r,c)) 
          | r <- range (r1, r2), c <- range (c1,c2)]


evalOp :: BinOp -> (Double -> Double -> Double)
evalOp Add = (+)
evalOp Sub = (-)
evalOp Mul = (*)
evalOp Div = (/)


evalSheet :: Sheet Exp -> Sheet Double
evalSheet s = s'
    where
        s' = array (bounds s) [ (r, evalCell s' (s ! r)) | r <- indices s ]

testSheet :: Sheet Exp
testSheet = array (('a', 1), ('c', 3))
                  [ (('a', 1), Lit 1.0),
                    (('a', 2), Ref ('b', 1)),
                    (('a', 3), Lit 3.0),
                    (('b', 1), App Add (Ref ('c', 2)) (Ref ('b', 2))),
                    (('b', 2), Lit 2.0),
                    (('b', 3), App Mul (Ref ('a', 1)) (Ref ('a', 2))),
                    (('c', 1), App Add (Ref ('a',1)) (Ref ('b',3))),
                    (('c', 2), Lit 3.0),
                    (('c', 3), Lit 7.0)
                  ]

testSheet2 :: Sheet Exp
testSheet2 = array (('a', 1), ('d', 3))
                   [ (('a', 1), Lit 1.0),
                     (('a', 2), Ref ('b', 1)),
                     (('a', 3), Lit 3.0),
                     (('b', 1), App Add (Ref ('c', 2)) (Ref ('b', 2))),
                     (('b', 2), Lit 2.0),
                     (('b', 3), App Mul (Ref ('a', 1)) (Ref ('a', 2))),
                     (('c', 1), App Add (Ref ('a',1)) (Ref ('b',3))),
                     (('c', 2), Lit 3.0),
                     (('c', 3), Lit 7.0),
                     (('d', 1), Sum ('a', 1) ('c', 3)),
                     (('d', 2), Avg ('a', 1) ('c', 3)),
                     (('d', 3), Lit 0.0)
                   ]
