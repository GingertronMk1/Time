-- Monad Examples
data Expr = Val Int | Div Expr Expr

eval :: Expr -> Int
eval (Val n) = n
eval (Div e1 e2) = div (eval e1) (eval e2)

safediv :: Int -> Int -> Maybe Int
safediv _ 0 = Nothing
safediv n m = Just (div n m)

evalMaybe :: Expr -> Maybe Int
evalMaybe (Val n) = Just n
evalMaybe (Div e1 e2) = case evalMaybe e1 of
                             Nothing -> Nothing
                             Just n -> case evalMaybe e2 of
                                            Nothing -> Nothing
                                            Just m -> safediv n m

-- Not type correct
-- evalMaybeApp :: Expr -> Maybe Int
-- evalMaybeApp (Val n) = Just n
-- evalMaybeApp (Div e1 e2) = pure safediv <*> evalMaybeApp e1 <*> evalMaybeApp e2

-- (>>=) :: Maybe a -> (a -> Maybe b) -> Maybe b
-- mx >>= f = case mx of Nothing -> Nothing
--                       Just x  -> f x

evalCompact :: Expr -> Maybe Int
evalCompact (Val n) = Just n
evalCompact (Div e1 e2) = evalCompact e1 >>= \n ->
                          evalCompact e2 >>= \m ->
                          safediv n m

evalDo :: Expr -> Maybe Int
evalDo (Val n) = Just n
evalDo (Div e1 e2) = do
                     n <- evalDo e1
                     m <- evalDo e2
                     safediv n m

pairs :: [a] -> [b] -> [(a,b)]
pairs xs ys = do x <- xs
                 y <- ys
                 return (x,y)

type State = Int

--type ST = State -> State

newtype ST a = S (State -> (a, State))

app :: ST a -> State -> (a, State)
app (S st) x = st x

instance Functor ST where
  -- fmap :: (a -> b) -> ST a -> ST b
  fmap g st = S (\s -> let (x,s') = app st s in (g x, s'))

data Tree a = Leaf a | Node (Tree a) (Tree a)
              deriving Show

tree :: Tree Char
tree = Node (Node (Leaf 'a') (Leaf 'b')) (Leaf 'c')


-- what an utter ballache of a function, I mean look at it
rlabel :: Tree a -> Int -> (Tree Int, Int)
rlabel (Leaf _) n = (Leaf n, n+1)
rlabel (Node l r) n = (Node l' r', n'')
                      where (l', n') = rlabel l n
                            (r', n'') = rlabel r n'

instance Applicative ST where
  pure x = S (\s -> (x, s))
  stf <*> stx = S (\s ->
                let (f, s') = app stf s
                    (x, s'') = app stx s' in (f x , s''))

fresh :: ST Int
fresh = S (\n -> (n, n+1))

alabel :: Tree a -> ST (Tree Int)
alabel (Leaf _) = Leaf <$> fresh
alabel (Node l r) = Node <$> alabel l <*> alabel r

-- mlabel :: Tree a -> ST (Tree Int)
-- mlabel (Leaf _) = do n <- fresh
                     -- return (Leaf n)
-- mlabel (Node l r) = do l' <- mlabel l
                       -- r' <- mlabel r
                       -- return (Node l' r')



