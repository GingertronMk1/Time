import Control.Concurrent
import Control.Concurrent.STM
import System.Random

type Spoon = TMVar Int
type Philosopher = String

maxDelay :: Int                   -- The maximum amount of time for which a
maxDelay = 5                      -- Philosopher should be eating

makePairs :: [a] -> [(a,a)]       -- A function to take a list of things and return
makePairs (x:[])    = []          -- A list of tuples, the pairs of which are adjacent
makePairs (x:y:[])  = (x,y):[]    -- List items
makePairs (x:y:xs)  = (x,y):(makePairs (y:xs))

newSpoon :: Int -> IO Spoon     -- Creating new spoons
newSpoon n = newTMVarIO n

getSpoon :: Spoon -> STM Int    -- When a philosopher wants to eat
getSpoon f = takeTMVar f        -- They try to get a spoon

retSpoon :: Spoon -> Int -> STM() -- When a philosopher wants to think
retSpoon f i = putTMVar f i       -- They return the spoon

philNames :: [Philosopher]      -- Our list of philosophers
philNames = ["Graham Hutton",
             "Steve Bagley",
             "Henrik Nilsson",
             "Thorsten Altenkirch",
             "John Garibaldi"]

runPhil :: Philosopher -> (Spoon, Spoon) -> IO()
runPhil p (l, r) = do putStrLn (p ++ " is hungry")
                      (ln, rn) <- atomically $ do leftNum <- getSpoon l
                                                  rightNum <- getSpoon r
                                                  return (leftNum, rightNum)
                      putStrLn (p ++ " has both spoons and is eating")
                      delay <- randomRIO (1,maxDelay)
                      threadDelay (delay*1000000)
                      putStrLn (p ++ " is done eating and is thinking again")
                      atomically $ do retSpoon l ln
                                      retSpoon r rn
                      delay <- randomRIO (1,maxDelay)
                      threadDelay (delay*1000000)
                      runPhil p (l, r)

main :: IO()
main = do spoons <- mapM newSpoon [1..length philNames]
          (putStrLn . show) philNames
          let namedPhils = map runPhil philNames
              spoonPairs = makePairs ((last spoons):spoons)
              philosophersWithSpoons = zipWith ($) namedPhils spoonPairs
          putStrLn "Press enter to stop"
          mapM_ forkIO philosophersWithSpoons
          getLine
