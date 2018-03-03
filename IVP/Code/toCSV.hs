import Data.List          ((\\), intersperse, sortBy, sort, group)
import Data.Ord           (comparing)
import Data.List.Split    (splitOn)

-- Variable declarations here ------------------------------------------------------------------------------------------

searchJSON :: FilePath
searchJSON = "Files/search.json"

csvLocation :: FilePath
csvLocation = "Files/data.csv"

-- Helper functions here -----------------------------------------------------------------------------------------------

flatten :: [[a]] -> [a]
flatten ass = [a | as <- ass, a <- as]

rmDups :: (Eq a, Ord a) => [a] -> [a]
rmDups = map head . group . sort

substitute :: Eq a => [a] -> [a] -> [a] -> [a]
substitute s1 s2 = flatten . intersperse s1 . splitOn s2

toTuple :: Eq a => [a] -> [a] -> ([a], [a])
toTuple s xs = let splitList = splitOn s xs in (head splitList, (flatten . tail) splitList)

-- Actual functions here -----------------------------------------------------------------------------------------------

-- First and foremost, getting the data out of the json file
sJSONShows :: IO [[(String, String)]]
sJSONShows = readFile searchJSON >>= return
                                     . filter (elem ("type","show"))                                                      -- I'm only interested in the shows
                                     . map (sortBy (comparing fst)                                                        -- Sorting the columns
                                            . filter (not . (\b -> null b || b==",") . snd)                               -- Getting rid of the empty values
                                            . map (toTuple ": " . substitute "/" "," . removeEndComma . filter (/='\"'))  -- Converting to tuples by way of some cleaning
                                            . filter (not . null . (\\"[]{}"))                                            -- Removing all brackets/braces
                                            . map (dropWhile (==' ')) . lines)                                            -- Clearing whitespace before data and splitting by line
                                     . splitOn "    }"                                                                    -- Splitting

-- Now we want to see all of the available column heading, so we can populate the first line of our csv file properly
allHeaders :: [[(String, String)]] -> IO [String]
allHeaders = return . rmDups . flatten . map (map fst)

-- Here we take each 'line' and ensure it contains all columns, populating empty ones with the string "NA"
compareHeaders :: [String] -> [(String, String)] -> [(String, String)]
compareHeaders [] _          = []
compareHeaders hs []         = map (\h -> (h,"NA")) hs
compareHeaders (h:hs) (s:ss) = if h == fst s
                               then s:(compareHeaders hs ss)
                               else (h,"NA"):(compareHeaders hs (s:ss))


-- For some reason a lot of the lines end on commas
removeEndComma :: String -> String
removeEndComma (s:[]) = if s == ',' then [] else s:[]
removeEndComma (s:ss) = s:(removeEndComma ss)

-- If I choose to compile this properly this is the function that will be called
main :: IO ()
main = do shows <- sJSONShows                       -- Take in the shows
          headerString <- allHeaders shows          -- Generate the column headers
          let showData = (flatten . intersperse "\n" . map (flatten . intersperse "," . map snd . compareHeaders headerString)) shows -- Convert the show data into the body of a csv
          let fullString = ((flatten . intersperse ",") headerString) ++ "\n" ++ showData -- And add it on to the headers
          writeFile csvLocation fullString          -- Write the csv
          putStrLn fullString                       -- Also write to the screen


-- Code used for debugging here ----------------------------------------------------------------------------------------

ppData :: IO ()
ppData = sJSONShows >>= putStrLn . flatten . intersperse "\n" . flatten . intersperse ["\n\n"] . map (map show)

headerTest = do shows <- sJSONShows
                headers <- allHeaders shows
                (return . map (map snd . compareHeaders headers)) shows
