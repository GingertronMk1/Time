import Data.List          ((\\), intersperse, sortBy, sort, group)
import Data.Ord           (comparing)
import Data.List.Split    (splitOn)

------------------------------------------------------------------------------------------------------------------------
-- GENERATING THE CSV WITH ALL THE SHOWS DATA --------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------

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

dropColumn :: Int -> [[a]] -> [[a]]
dropColumn n = map (\ss -> (take (n-1) ss)++(drop n ss))

-- Actual functions here -----------------------------------------------------------------------------------------------

-- First and foremost, getting the data out of the json file
jsonToTuples :: String -> [[(String, String)]]
jsonToTuples =  map (filter (\(a,_) -> a/="content" && a/="excerpt")) -- And the excerpt and content aren't going to give me anything useful
                . filter (elem ("type","show"))                       -- I'm only interested in the shows
                . map (sortBy (comparing fst)                         -- Sorting the columns
                  . filter (not . (\b -> null b || b==",") . snd)     -- Getting rid of the empty values
                  . map (toTuple ": "                                 -- The tuple conversion
                          . substitute "-" "&ndash;"                  -- Some fun with HTML I suppose
                          . substitute "/" ", "                       -- Subbing out commas
                          . removeEndComma                            -- Getting rid of end comma
                          . filter (/='\"'))                          -- Removing quote marks
                  . filter (not . null . (\\"[]{}"))                  -- Removing all brackets/braces
                  . map (dropWhile (==' ')) . lines)                  -- Clearing whitespace before data and splitting by line
                . splitOn "    }"                                     -- Splitting

sJSONShows :: IO [[(String, String)]]
sJSONShows = readFile searchJSON >>= return . jsonToTuples

test = do fileData <- readFile searchJSON
          let shows = jsonToTuples fileData
          let headers = allHeaders shows
          (return . map (compareHeaders headers)) shows

-- Now we want to see all of the available column heading, so we can populate the first line of our csv file properly
allHeaders :: [[(String, String)]] -> [String]
allHeaders = rmDups . flatten . map (map fst)

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

------------------------------------------------------------------------------------------------------------------------
-- ALL THE LINKS BETWEEN THE ACTORS ------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------

--links 

-- If I choose to compile this properly this is the function that will be called
main :: IO ()
main = do shows <- sJSONShows                       -- Take in the shows
          headerString <- return (allHeaders shows) -- Generate the column headers
          let showData = map (map snd . compareHeaders headerString) shows
          let csv = (flatten . intersperse "\n" . map (flatten . intersperse ",")) (headerString:showData)
          writeFile csvLocation csv


-- Code used for debugging here ----------------------------------------------------------------------------------------

ppData :: IO ()
ppData = test >>= putStrLn . flatten . intersperse "\n" . flatten . intersperse ["\n\n"] . map (map show)
