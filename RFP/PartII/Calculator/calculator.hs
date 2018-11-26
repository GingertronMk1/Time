module Main where
import qualified Graphics.UI.Threepenny       as UI
import           Graphics.UI.Threepenny.Core
import Data.IORef
import Data.List (words)

data Calc = Calc {working :: String,    -- The working space
                  ans :: String,        -- The previous answer
                  mem :: String}        -- The calculator's memory

data Op = Op {symbol :: String,         -- The operator's symbol
              precedence :: Int,        -- Its precedence (used in Shunting Yard)
              associativity :: String}  -- Its associativity (also Shunting Yard)

testEqns = "5 + 3 * ( 5 - 9 )"

--------------------------------------------------------------------------------------------
-- MAKING A CALCULATOR THAT WILL TAKE A STRING AND RETURN AN ANSWER, IN THE FORM OF A STRING
--------------------------------------------------------------------------------------------

ops :: [Op]
ops = [Op {symbol = "^", precedence = 5, associativity = "r"},
       Op {symbol = "/", precedence = 4, associativity = "l"},
       Op {symbol = "*", precedence = 3, associativity = "l"},
       Op {symbol = "+", precedence = 2, associativity = "l"},
       Op {symbol = "-", precedence = 1, associativity = "l"},
       Op {symbol = "(", precedence = 9, associativity = "u"},
       Op {symbol = ")", precedence = 9, associativity = "u"}]

isOp :: String -> Bool
isOp x = elem x (map symbol ops)

getOpPrec :: String -> Int
getOpPrec op = (precedence . head . filter ((==op) . symbol)) ops

getOpAss :: String -> String
getOpAss op = (associativity . head . filter ((==op) . symbol)) ops

fns :: [String]
fns = ["ln", "sum", "sin", "cos", "tan"]

isFn :: String -> Bool
isFn f = elem f fns

specials :: [(String, Float)]
specials = [("pi", pi)]

isSpecial :: String -> Bool
isSpecial f = elem f (map fst specials)

specialConvert :: String -> String
specialConvert s = (show . snd . head . filter ((==s) . fst)) specials

parseEqn :: String -> [String]
parseEqn s = parseEqn' (words s) ([],[])

parseEqn' :: [String] -> ([String], [String]) -> [String]
parseEqn' [] (output, stack)     = output ++ stack
parseEqn' (s:ss) (output, stack) | isOp s                     = parseEqn' ss $ parseEqn'' s output stack
                                 | isFn s                     = parseEqn' ss (output, s:stack)
                                 | elem s (map fst specials)  = parseEqn' ss (output ++ [specialConvert s], stack)
                                 | otherwise                  = parseEqn' ss (output ++ [s], stack)

parseEqn'' :: String -> [String] -> [String] -> ([String], [String])
parseEqn'' op out [] = (out, [op])
parseEqn'' ")" out stack@(s:ss) = if s == "("
                                  then (out, ss)
                                  else parseEqn'' ")" (out++[s]) ss
parseEqn'' "(" out stack@(s:ss) = (out, "(":stack)
parseEqn'' op out stack@(s:ss)  = if s/="(" && (isFn s || getOpPrec s > getOpPrec op || ((getOpPrec s == getOpPrec op) && getOpAss s == "l"))
                                  then parseEqn'' op (out ++ [s]) ss
                                  else (out, op:stack)

evalRPN :: [String] -> String
evalRPN = show . head . foldl foldingFunction []
          where foldingFunction (x:y:ys) "*"          = (y * x):ys
                foldingFunction (x:y:ys) "+"          = (y + x):ys
                foldingFunction (x:y:ys) "-"          = (y - x):ys
                foldingFunction (x:y:ys) "/"          = (y / x):ys
                foldingFunction (x:y:ys) "^"          = (y ** x):ys
                foldingFunction (x:xs)   "ln"         = (log x):xs
                foldingFunction (x:xs)   "sin"        = (sin x):xs
                foldingFunction (x:xs)   "cos"        = (cos x):xs
                foldingFunction (x:xs)   "tan"        = (tan x):xs
                foldingFunction xs       "sum"        = [sum xs]
                foldingFunction xs       numberString = (read numberString :: Float):xs

doEqn :: String -> String
doEqn = evalRPN . parseEqn

-----------------------------------------------------------------------------
-- IMPLEMENTING THE ABOVE IN A WEB BROWSER BY WAY OF THE THREEPENNY GUI SUITE
-----------------------------------------------------------------------------

invalidMessage :: String
invalidMessage = "Error_invalid_equation"

emptyCalc :: Calc
emptyCalc = Calc {working = "", ans = "0", mem = ""}

btns :: [(UI Element, Element -> Event (Calc -> Calc))]
btns = [(newButton "0",   makeEvent (calcUpdateWorking "0")),
        (newButton "1",   makeEvent (calcUpdateWorking "1")),
        (newButton "2",   makeEvent (calcUpdateWorking "2")),
        (newButton "3",   makeEvent (calcUpdateWorking "3")),
        (newButton "4",   makeEvent (calcUpdateWorking "4")),
        (newButton "5",   makeEvent (calcUpdateWorking "5")),
        (newButton "6",   makeEvent (calcUpdateWorking "6")),
        (newButton "7",   makeEvent (calcUpdateWorking "7")),
        (newButton "8",   makeEvent (calcUpdateWorking "8")),
        (newButton "9",   makeEvent (calcUpdateWorking "9")),
        (UI.br,           makeEvent id),
        (newButton ".",   makeEvent (calcUpdateWorking ".")),
        (newButton "+",   makeEvent (calcUpdateWorking " + ")),
        (newButton "-",   makeEvent (calcUpdateWorking " - ")),
        (newButton "*",   makeEvent (calcUpdateWorking " * ")),
        (newButton "/",   makeEvent (calcUpdateWorking " / ")),
        (newButton "(",   makeEvent (calcUpdateWorking " ( ")),
        (newButton ")",   makeEvent (calcUpdateWorking " ) ")),
        (UI.br,           makeEvent id),
        (newButton "=",   makeEvent calcDo),
        (newButton "CE",  makeEvent (\c -> Calc {working = "", ans = ans c, mem = mem c})),
        (newButton "C",   makeEvent (\c -> emptyCalc)),
        (newButton "+/-", makeEvent calcNeg),
        (newButton "M+",  makeEvent (\c -> Calc {working = working c, ans = ans c, mem = ans c})),
        (newButton "M-",  makeEvent (\c -> Calc {working = working c ++ " " ++ mem c, ans = ans c, mem = mem c})),
        (newButton "Ans", makeEvent (\c -> calcUpdateWorking (ans c) c)),
        (UI.br,           makeEvent id),
        (newButton "ln",  makeEvent (calcUpdateWorking " ln ( ")),
        (newButton "sum", makeEvent (calcUpdateWorking " sum ( ")),
        (newButton "sin", makeEvent (calcUpdateWorking " sin ( ")),
        (newButton "cos", makeEvent (calcUpdateWorking " cos ( ")),
        (newButton "tan", makeEvent (calcUpdateWorking " tan ( ")),
        (newButton "pi",  makeEvent (calcUpdateWorking " pi "))]
        where makeEvent c e = (c <$ UI.click e)
              newButton s = UI.button # set UI.text s
              calcNeg c = let a = ans c
                              w = working c
                              m = mem c
                          in  if head a /= '-' then Calc {working = w, ans = '-':a, mem = m}
                                               else Calc {working = w, ans = tail a, mem = m}

calcUpdateWorking :: String -> Calc -> Calc
calcUpdateWorking s c | (isOp (filter (/=' ') s) && (working c == "")) = Calc {working = ans c ++ s, ans = ans c, mem = mem c}
                      -- If the working space is empty and the first entry is an operator, the start of the equation = the current answer value
                      | working c == invalidMessage = calcUpdateWorking s (Calc {working = "", ans = ans c, mem = mem c})
                      -- If working space contains an error message, write over it
                      | otherwise = Calc {working = (working c) ++ s, ans = ans c, mem = mem c}
                      -- Else just append to the working space

calcDo :: Calc -> Calc
--calcDo c = if (validEqn . working) c then Calc {working = "", ans = (doEqn . working) c, mem = mem c}
--                                     else Calc {working = invalidMessage, ans = ans c, mem = mem c}
calcDo c = Calc {working = "", ans = (doEqn . working) c, mem = mem c}

setup :: Window -> UI ()
setup window = do
    return window # set UI.title "Calculator"
    buttons       <- (sequence . map fst) btns
    calc          <- accumB emptyCalc (unionList const (zipWith ($) (fmap snd btns) buttons))
    workspace     <- UI.label # sink UI.text (fmap (filter (/=' ') . working) calc)
    answer        <- UI.label # sink UI.text (fmap ans calc)
    getBody window #+ [UI.center #+ ([element workspace, UI.br, element answer, UI.br] ++ (map element buttons))]
    return ()
    where unionList c (e:[]) = e
          unionList c (e:es) = unionWith c e (unionList c es)

allOpCombos :: [(String,String)]
allOpCombos = let opSym (o,_,_) = o
                  ops' = "." : map symbol ops
              in  [(a, b) | a <- ops', b <- ops']

validOps :: [String] -> Bool
validOps [] = True
validOps (s:[]) = not (isOp s)
validOps (s1:s2:ss) = if elem (s1,s2) allOpCombos then False else validOps (s2:ss)

validEqn :: String -> Bool
validEqn s = let ws = words s in validOps ws && matchedBrackets ws

matchedBrackets :: [String] -> Bool
matchedBrackets = matchedBrackets' 0

matchedBrackets' :: Int -> [String] -> Bool
matchedBrackets' n []       = n == 0
matchedBrackets' n ("(":ss) = matchedBrackets' (n+1) ss
matchedBrackets' n (")":ss) = matchedBrackets' (n-1) ss
matchedBrackets' n (_:ss)   = matchedBrackets' n ss

main :: IO ()
main = do
    startGUI defaultConfig
        { jsPort       = Just 8023
        , jsStatic     = Just "../wwwroot"
        } setup
