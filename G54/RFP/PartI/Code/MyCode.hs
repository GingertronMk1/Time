import Test.QuickCheck

merge                       :: (Ord a) => [a] -> [a] -> [a]
merge xxs []                = xxs
merge [] yys                = yys
merge xxs@(x:xs) yys@(y:ys) | x == y = x:(merge xs ys)
                            | x < y = x:(merge xs yys)
                            | x > y = y:(merge xxs ys)

hamming = let twos   = fmap (2*) hamming
              threes = fmap (3*) hamming
              fives  = fmap (5*) hamming
          in 1 : twos `merge` threes `merge` fives

data Ivl = Ivl Double Double deriving Show

isWellDef :: Ivl -> Bool
isWellDef (Ivl l u) = l <= u

wellDef1 :: Ivl -> Ivl -> Ivl
wellDef1 i i' = if isWellDef i
                then i'
                else error "Poorly defined argument"

wellDef2 :: Ivl -> Ivl -> Ivl -> Ivl
wellDef2 i1 i2 i' | isWellDef i1 && isWellDef i2 = i'
                  | not (isWellDef i1) && isWellDef i2
                    = error "First argument is not well-defined."
                  | isWellDef i1 && not (isWellDef i2)
                    = error "Second argument is not well-defined."
                  | otherwise
                    = error "Neither argument is well-defined."

makeWellDef :: Ivl -> Ivl
makeWellDef i@(Ivl l u) | isWellDef i = i
                        | otherwise   = Ivl u l

instance Num Ivl where
  (+) i1@(Ivl l1 u1) i2@(Ivl l2 u2)
    = wellDef2 i1 i2 $ makeWellDef (Ivl (l1+l2) (u1+u2))
  (-) i1@(Ivl l1 u1) i2@(Ivl l2 u2)
    = wellDef2 i1 i2 $ makeWellDef (Ivl (l1-u2) (u1-l2))
  (*) i1@(Ivl l1 u1) i2@(Ivl l2 u2)
    = wellDef2 i1 i2 $ makeWellDef (Ivl (l1*l2) (u1*u2))
  abs i@(Ivl l u)
    = let abl = abs l
          abu = abs u
      in wellDef1 i (if l < 0 && 0 < u
                     then if abl > abu
                          then Ivl 0.0 abl
                          else Ivl 0.0 abu
                     else makeWellDef (Ivl abl abu))
  signum i@(Ivl l u)
    = wellDef1 i (Ivl (signum l) (signum u))
  fromInteger n
    = let fin = fromInteger n
      in Ivl fin fin

instance Fractional Ivl where
  (/) i1@(Ivl l1 u1) i2@(Ivl l2 u2)
    = if u2 /= 0 && l2 /= 0
      then wellDef2 i1 i2 (Ivl (l1/u2) (u1/l2))
      else error "Arguments result in attempt to divide by 0"
  recip i@(Ivl l u)
    = wellDef1 i $ makeWellDef (Ivl (recip l) (recip u))
  fromRational n
    = let frn = fromRational n
      in makeWellDef (Ivl frn frn)

(+/-) :: Double -> Double -> Ivl
(+/-) n i = makeWellDef (Ivl (n-i) (n+i))

instance Arbitrary Ivl where
  arbitrary = do i1 <- arbitrary
                 i2 <- arbitrary
                 return $ if i1 <= i2 then Ivl i1 i2
                                      else Ivl i2 i1

prop_wellFormedResult1 ::(Ivl -> Ivl) -> Ivl -> Bool
prop_wellFormedResult1 f i = let Ivl l u = f i in l <= u

prop_wellFormedResult2 ::(Ivl -> Ivl -> Ivl) -> Ivl -> Ivl -> Bool
prop_wellFormedResult2 f i1 i2 = let Ivl l u = f i1 i2 in l <= u

functions1 :: [(Ivl -> Ivl)]
functions1 = [abs, signum, recip]

functions2 :: [(Ivl -> Ivl -> Ivl)]
functions2 = [(+),(-),(*),(/)]

check1 = sequence $ map (quickCheck . prop_wellFormedResult1) functions1
check2 = sequence $ map (quickCheck . prop_wellFormedResult2) functions2
