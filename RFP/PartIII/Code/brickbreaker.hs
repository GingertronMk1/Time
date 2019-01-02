import qualified Graphics.UI.Threepenny       as UI
import           Graphics.UI.Threepenny.Core
import Data.List (words)
import Data.Char (isDigit)

data Block = Block {x      :: Double
                   ,y      :: Double
                   ,colour :: String
                   ,notHit :: Bool
                   } deriving Show

data Env = Env {ballX   :: Double
               ,ballY   :: Double
               ,balldX  :: Double
               ,balldY  :: Double
               ,batX    :: Double
               ,batY    :: Double
               ,blocks  :: [Block]
               } deriving Show

canvWidth :: Double
canvWidth = 800.0

canvHeight :: Double
canvHeight = 480.0

blocksX :: Double
blocksX = 16.0

blocksY :: Double
blocksY = 8.0

blockGapX :: Double
blockGapX = canvWidth / blocksX

blockGapY :: Double
blockGapY = canvHeight / (3 * blocksY)

blockWidth :: Double
blockWidth = blockGapX * 0.9

blockHeight :: Double
blockHeight = blockGapY * 0.9

batWidth :: Double
batWidth = canvWidth * 0.2

initBlocks :: [Block]
initBlocks = [Block {x = blockGapX * (0.5 + xs)
                    ,y = blockGapY * ys
                    ,colour = "Red"
                    ,notHit = True} | xs <- [0.0,1.0..(blocksX-1)], ys <- [0.0,1.0..(blocksY-1)]]

initEnv :: Env
initEnv = Env {ballX = canvWidth / 2
              ,ballY = canvHeight / 2
              ,balldX = 1
              ,balldY = 1
              ,batX = (canvWidth - batWidth) / 2
              ,batY = 450
              ,blocks = initBlocks
              }

batMove' :: Char -> Env -> Env
batMove' 'a' e = e {batX = batX e - 1}
batMove' 'd' e = e {batX = batX e + 1}

drawBlock :: Double -> Double -> Double -> Double -> UI.Canvas -> UI()
drawBlock x y w h c = do UI.fillRect (x,y) (w/2.0) h c
                         UI.fillRect (x,y) (-w/2.0) h c

updateEnv :: Env -> Env
updateEnv e = e {ballX = ballX e + balldX e
                ,ballY = ballY e + balldY e
                ,blocks = filter notHit (blocks e)}

setup :: Window -> UI ()
setup w = do return w # set title "BrickBreaker!"
             timer <- UI.timer # set UI.interval 10
             canv <- UI.canvas # set UI.width  (round canvWidth)
                               # set UI.height (round canvHeight)
             wrap <- UI.div #. "wrap"
                            # set style [("width",show canvWidth ++ "px"),("height",show canvHeight ++ "px"),("border","solid black 1px")]
                            # set (attr "tabindex") "1" -- allow key presses
                            # set (attr "id") "main"
             let batMove = batMove' <$> UI.keypress wrap
                 onTick = updateEnv <$ UI.tick timer
                 fns = unionWith const batMove onTick
             env <- accumB initEnv fns
             out <- UI.span # sink UI.text (fmap (show . ballX) env)
             UI.fillRect (batX initEnv, batY initEnv) batWidth 10.0 canv
             sequence $ map (\e -> drawBlock (x e) (y e) blockWidth blockHeight canv) (blocks initEnv)
             UI.arc (ballX initEnv, ballY initEnv) 16.0 0.0 (2*pi) canv
             UI.fill canv
             UI.start timer
             getBody w #+ [UI.center #+ ([element wrap #+ [element out, element canv]])]
             return ()

main :: IO ()
main = startGUI defaultConfig setup
