import Data.List (sort)

type Party = String
type Ballot = [Party]

votes :: [Party]
votes = ["Orange","Orange","Red","Blue","Green","Blue","Blue","Red"]

ballots ::  [Ballot]
ballots =   [["Red","Green"],
            ["Blue"],
            ["Green","Red","Blue"],
            ["Blue","Green","Red"],
            ["Green"]]

count :: Eq a => a -> [a] -> Int
count p = length.filter (== p)

rmdups :: Eq a => [a] -> [a]
rmdups [] = []
rmdups (x:xs)   | x `elem` xs   = rmdups xs
                | otherwise     = x : rmdups xs

frequency :: Eq a => [a] -> [(Int, a)]
frequency xs = [(count c xs, c) | c <- rmdups xs]

results :: [Party] -> [(Int,Party)]
results = sort.frequency

winner :: [Party] -> Party
winner = snd.last.results

rmempty :: Eq a => [[a]] -> [[a]]
rmempty xs = filter (not.null) xs

remove :: Eq a => a -> [[a]] -> [[a]]
remove y = map(filter(/=y))

rank :: [Ballot] -> [Party]
rank = map snd.results.map head

election :: [Ballot] -> Party
election bs = case rank (rmempty bs) of
                [p]    -> p
                (p:ps) -> election (remove p bs)
