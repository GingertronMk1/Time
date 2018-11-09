import Control.Concurrent
import Control.Concurrent.STM
import System.Random

type Spoon = TMVar Int
type Philosopher = String

maxDelay :: Int
maxDelay = 5

makePairs :: [a] -> [(a,a)]
makePairs (x:[])    = []
makePairs (x:y:[])  = (x,y):[]
makePairs (x:y:xs)  = (x,y):(makePairs (y:xs))

newSpoon :: Int -> IO Spoon
newSpoon n = newTMVarIO n

getSpoon :: Spoon -> STM Int
getSpoon f = takeTMVar f

retSpoon :: Spoon -> Int -> STM()
retSpoon f i = putTMVar f i

philNames :: [Philosopher]
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
