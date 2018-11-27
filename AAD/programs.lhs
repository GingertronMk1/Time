> import Data.List (splitAt)
> type AdjList = [[Int]]
> type AdjMatrix = [[Bool]]

> testAdjList :: AdjList
> testAdjList = [[1,4],[0,5],[5,3],[2,4,5],[0,3],[1,2,3]]
> falseMatrix :: Int -> AdjMatrix
> falseMatrix l = (replicate l (replicate l False))

>-- listToMatrix :: AdjList -> AdjMatrix
>-- listToMatrix as = listToMatrix' as 0 (falseMatrix (length as))
>-- listToMatrix' :: AdjList -> Int -> AdjMatrix -> AdjMatrix
>-- listToMatrix' [] _ _     = []
>-- listToMatrix' (a:as) n m = (adjListToMatrixRow a (m!!n)) ++ (listToMatrix' (as) (n+1) m)

>-- adjToMatrixRow :: [Bool] -> [Int] -> [Bool]
> adjToMatrixRow r ns = ({-zipWith (\x y -> x || y) .-} map (intToMatrixRow r)) ns
> intToMatrixRow :: [Bool] -> Int -> [Bool]
> intToMatrixRow r n = let (before, after) = splitAt n r in init before ++ [True] ++ after
