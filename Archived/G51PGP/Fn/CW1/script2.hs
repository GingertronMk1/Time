-- CW-2 Types and Classes Coursework

e1 :: [Bool]
e1 = [True,False,True]

e2 :: [[Int]]
e2 = [[1,2],[3,4]]

e3 :: (Char,Bool)
e3 = ('a', True)

e4 :: [(String,Int)]
e4 = [("Hello", 0), ("World", 1)]

e5 :: Int -> Int
e5 n = n*2

e6 :: Int -> Int -> Int
e6 x y = x+y

e7 :: (char,char) -> (char,char)
e7 (x,y) = (y,x)

e8 :: a -> (a,a)
e8 x = (x,x)
