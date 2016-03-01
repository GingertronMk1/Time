--FP-CW3
--Name:     Jack Ellis
--Username: psyje5
--ID:       4262333

second1 :: [a] -> a
second1 a = head(tail a)

second2 :: [a] -> a
second2 a = a !! 1

second3 :: [a] -> a
second3 (x1:x2:xs) = x2

xor1             :: Bool -> Bool -> Bool
True `xor1` False  = True
False `xor1` True  = True
True `xor1` True   = False
False `xor1` False = False

xor2 :: Bool -> Bool -> Bool
xor2 a b =  if a == True then not b
                else b

xor3 :: Bool -> Bool -> Bool
xor3 = (/=)

sumsqr :: Int -> Int
sumsqr a = sum [x^2 | x <- [1..a]]

grid :: Int -> [(Int,Int)]
grid a = [(x,y) | x <- [0..a], y <- [0..a], x /= y]

euclid :: Int -> Int -> Int
euclid a b =    if a == b then a
                    else if a > b then euclid (a-b) b
                    else euclid a (b-a)

fastrev :: [a] -> [a]
fastrev xs = rev xs []

rev :: [a] -> [a] -> [a]
rev [] ys = [] ++ reverse ys
rev (x:xs) ys = (rev xs ys) ++ [x]
