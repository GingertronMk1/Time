module Main where
import qualified Graphics.UI.Threepenny       as UI
import           Graphics.UI.Threepenny.Core
import Data.List (words)
import Data.Char (isDigit)

data Calc = Calc {working :: String,
                  ans :: String,
                  mem :: String}
                  deriving Show

data Op = Op {symbol :: String,
              precedence :: Int,
              associativity :: String}

testEqns = ["5 + 3 * ( 5 - 9 ) ", "5 + - + "]

errorMsg :: String
errorMsg = "Error_invalid_equation"

emptyCalc :: Calc
emptyCalc = Calc {working = "", ans = "0", mem = ""}

-------------------------------------------------------------------------------------------------
-- MAKING A CALCULATOR THAT WILL TAKE A STRING AND RETURN AN ANSWER, IN THE FORM OF MAYBE A FLOAT
-------------------------------------------------------------------------------------------------

ops :: [Op]
ops = [Op {symbol = "^", precedence = 5, associativity = "r"},
       Op {symbol = "/", precedence = 4, associativity = "l"},
       Op {symbol = "*", precedence = 3, associativity = "l"},
       Op {symbol = "+", precedence = 2, associativity = "l"},
       Op {symbol = "-", precedence = 1, associativity = "l"},
       Op {symbol = "(", precedence = 9, associativity = "u"},
       Op {symbol = ")", precedence = 9, associativity = "u"}]

fns :: [String]
fns = ["ln", "sin", "cos", "tan"]

specials :: [(String, Float)]
specials = [("pi", pi)]

isOp :: String -> Bool
isOp x = elem x (map symbol ops)

getOpPrec :: String -> Int
getOpPrec op = (precedence . head . filter ((==op) . symbol)) ops

getOpAss :: String -> String
getOpAss op = (associativity . head . filter ((==op) . symbol)) ops

isFn :: String -> Bool
isFn f = elem f fns

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

safeEvalRPN :: [String] -> Maybe Float
safeEvalRPN = head . foldl foldingFunction []
              where foldingFunction (x:y:ys) "^"          = (safeEval2 (**) y x):ys
                    foldingFunction (x:y:ys) "/"          = (safeEval2 (/) y x):ys
                    foldingFunction (x:y:ys) "*"          = (safeEval2 (*) y x):ys
                    foldingFunction (x:y:ys) "+"          = (safeEval2 (+) y x):ys
                    foldingFunction (x:y:ys) "-"          = (safeEval2 (-) y x):ys
                    foldingFunction (x:xs)   "ln"         = (safeEval1 log x):xs
                    foldingFunction (x:xs)   "sin"        = (safeEval1 sin x):xs
                    foldingFunction (x:xs)   "cos"        = (safeEval1 cos x):xs
                    foldingFunction (x:xs)   "tan"        = (safeEval1 tan x):xs
                    foldingFunction xs       numberString = (safeRead numberString):xs

safeEval2 :: Num a => (a -> a -> a) -> Maybe a -> Maybe a -> Maybe a
safeEval2 f x y = do x' <- x
                     y' <- y
                     return $ f x' y'

safeEval1 :: Num a => (a -> a) -> Maybe a -> Maybe a
safeEval1 f x = x >>= \x' -> return $ f x'

safeRead :: String -> Maybe Float
safeRead s = safeRead' s s
             where safeRead' s []       = Just (read s :: Float)
                   safeRead' s ('.':[]) = Nothing
                   safeRead' s (s':ss') = if s' == '.' || isDigit s'
                                          then safeRead' s ss'
                                          else Nothing

safeDo :: String -> Maybe Float
safeDo = safeEvalRPN . parseEqn

-----------------------------------------------------------------------------
-- IMPLEMENTING THE ABOVE IN A WEB BROWSER BY WAY OF THE THREEPENNY GUI SUITE
-----------------------------------------------------------------------------

btns :: [(UI Element, Element -> Event (Calc -> Calc))]
btns = [(newButton "ln",  makeEvent (calcUpdateWorking " ln ( ")),
        (newButton "sin", makeEvent (calcUpdateWorking " sin ( ")),
        (newButton "cos", makeEvent (calcUpdateWorking " cos ( ")),
        (newButton "tan", makeEvent (calcUpdateWorking " tan ( ")),
        (newButton "pi",  makeEvent (calcUpdateWorking " pi ")),
        (UI.br,           makeEvent id),
        (newButton "(",   makeEvent (calcUpdateWorking " ( ")),
        (newButton ")",   makeEvent (calcUpdateWorking " ) ")),
        (newButton "CE",  makeEvent (\c -> Calc {working = "", ans = ans c, mem = mem c})),
        (newButton "C",   makeEvent (\_ -> emptyCalc)),
        (newButton "+/-", makeEvent calcNeg),
        (UI.br,           makeEvent id),
        (newButton "7",   makeEvent (calcUpdateWorking "7")),
        (newButton "8",   makeEvent (calcUpdateWorking "8")),
        (newButton "9",   makeEvent (calcUpdateWorking "9")),
        (newButton "M+",  makeEvent (\c -> Calc {working = working c, ans = ans c, mem = ans c})),
        (newButton "M-",  makeEvent (\c -> Calc {working = working c ++ " " ++ mem c, ans = ans c, mem = mem c})),
        (UI.br,           makeEvent id),
        (newButton "4",   makeEvent (calcUpdateWorking "4")),
        (newButton "5",   makeEvent (calcUpdateWorking "5")),
        (newButton "6",   makeEvent (calcUpdateWorking "6")),
        (newButton "*",   makeEvent (calcUpdateWorking " * ")),
        (newButton "/",   makeEvent (calcUpdateWorking " / ")),
        (UI.br,           makeEvent id),
        (newButton "1",   makeEvent (calcUpdateWorking "1")),
        (newButton "2",   makeEvent (calcUpdateWorking "2")),
        (newButton "3",   makeEvent (calcUpdateWorking "3")),
        (newButton "+",   makeEvent (calcUpdateWorking " + ")),
        (newButton "-",   makeEvent (calcUpdateWorking " - ")),
        (UI.br,           makeEvent id),
        (newButton "0",   makeEvent (calcUpdateWorking "0")),
        (newButton ".",   makeEvent (calcUpdateWorking ".")),
        (newButton "Ans", makeEvent (\c -> calcUpdateWorking (ans c) c)),
        (newButton "=",   makeEvent calcEval)]
        where makeEvent c e = c <$ UI.click e
              newButton s   = UI.button # set UI.text s
              calcNeg c     = let a = ans c
                                  w = working c
                                  m = mem c
                               in if head a /= '-' then Calc {working = w, ans = '-':a, mem = m}
                                                   else Calc {working = w, ans = tail a, mem = m}

calcUpdateWorking :: String -> Calc -> Calc
calcUpdateWorking s c | (isOp (filter (/=' ') s) && (wc == ""))
                        = Calc {working = ac ++ s, ans = ac, mem = mc}
                      | wc == errorMsg
                        = calcUpdateWorking s (Calc {working = "", ans = ac, mem = mc})
                      | otherwise
                        = Calc {working = wc ++ s, ans = ac, mem = mc}
                      where wc = working c
                            ac = ans c
                            mc = mem c

calcEval :: Calc -> Calc
calcEval c = case (safeDo . working) c of Nothing -> Calc {working = errorMsg, ans = ans c,  mem = mem c}
                                          Just n  -> Calc {working = "",       ans = show n, mem = mem c}

setup :: Window -> UI ()
setup window = do
    return window # set UI.title "Calculator"
    buttons       <- (sequence . map fst) btns
    calc          <- accumB emptyCalc $ unionList const (zipWith ($) (fmap snd btns) buttons)
    workspace     <- UI.label # sink UI.text (fmap (filter (/=' ') . working) calc)
    answer        <- UI.label # sink UI.text (fmap ans calc)
    getBody window #+ [UI.center #+ ([element workspace, UI.br, element answer, UI.br] ++ (map element buttons))]
    return ()
    where unionList c (e:[]) = e
          unionList c (e:es) = unionWith c e (unionList c es)

main :: IO ()
main = do
    startGUI defaultConfig
        { jsPort       = Just 8023
        , jsStatic     = Just "../wwwroot"
        } setup
