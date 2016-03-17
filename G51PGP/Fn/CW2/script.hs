import Data.List (sort)
type Party = String
type Ballot = [Party]

count :: Eq a => a -> [a] -> Int
count p xs = length[ x | x <- xs, p x]
