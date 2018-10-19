import Data.List


import Sheet
import SBRAL

--hamming :: [Int]
--hamming = let ones = [n | n <- [1..], mod n 2 == 0 || mod n 3 == 0 || mod n 5 == 0]
--              twos = map (2*) ones
--              threes = map (3*) ones
--              fives = map (5*) ones
--          in 1 : merge (merge ones twos) (merge threes fives)

hamming' xs = let twos = map (*2) xs
                  threes = map (*3) xs
                  fives = map (*5) xs
               in merge (merge xs twos) (merge threes fives)

merge                       :: (Ord a) => [a] -> [a] -> [a]
merge xxs []                = xxs
merge [] yys                = yys
merge xxs@(x:xs) yys@(y:ys) | x == y = x:(merge xs ys)
                            | x < y = x:(merge xs yys)
                            | x > y = y:(merge xxs ys)




data Ivl = Ivl Double Double deriving Show
instance Num Ivl where
  (+) (Ivl l1 u1) (Ivl l2 u2) = Ivl (l1+l2) (u1+u2)
  (-) (Ivl l1 u1) (Ivl l2 u2) = Ivl (l1-u2) (u1-l2)
  (*) (Ivl l1 u1) (Ivl l2 u2) = Ivl (l1*l2) (u1*u2)
  abs (Ivl l u) = let al = abs l
                      au = abs u
                  in if al < au then Ivl al au
                     else Ivl au al
  signum (Ivl l u) = if l > 0 && u > 0 then 1
                     else if l < 0 && u < 0 then -1
                     else 0
  fromInteger n = let fin = fromInteger n in Ivl fin fin

instance Fractional Ivl where
  (/) (Ivl l1 u1) (Ivl l2 u2) = Ivl (l1/l2) (u1/u2)
  recip (Ivl l u) = Ivl (recip u) (recip l)
  fromRational n = let frn = fromRational n in Ivl frn frn

(+/-) :: Double -> Double -> Ivl
(+/-) n i = Ivl (n-i) (n+i)

test = 10 +/- 5.2
