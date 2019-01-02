import qualified Graphics.UI.Threepenny       as UI
import           Graphics.UI.Threepenny.Core
import Data.List (words)
import Data.Char (isDigit)

data HitWhere = InX | InY | InBoth | Not deriving (Eq, Show)

data GameState = PreStart | Going | Paused | LevelComplete | Dead deriving (Eq, Show)

data Block = Block {x      :: Double
                   ,y      :: Double
                   ,isHit  :: HitWhere
                   } deriving Show

data Env = Env {ballX     :: Double
               ,ballY     :: Double
               ,balldX    :: Double
               ,balldY    :: Double
               ,batX      :: Double
               ,batY      :: Double
               ,blocks    :: [Block]
               ,gameState :: GameState
               ,level     :: Int
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

batHeight :: Double
batHeight = batWidth * 0.1

ballSize :: Double
ballSize = 0.05 * minimum [canvWidth, canvHeight]

ballSpeed :: Double
ballSpeed = 5.0

initBlocks :: [Block]
initBlocks = [Block {x = blockGapX * (0.5 + xs)
                    ,y = blockGapY * (0.5 + ys)
                    ,isHit = Not} | xs <- [0.0,1.0..(blocksX-1)], ys <- [0.0,1.0..(blocksY-1)]]

initEnv :: Env
initEnv = Env {ballX = canvWidth / 2
              ,ballY = canvHeight / 2
              ,balldX = 0
              ,balldY = ballSpeed
              ,batX = canvWidth / 2
              ,batY = 450
              ,blocks = initBlocks
              ,gameState = PreStart
              ,level = 1
              }

keyboardHandle :: Char -> Env -> Env
keyboardHandle c e = case gameState e of PreStart      -> kbhPreStart c e
                                         Going         -> kbhGoing c e
                                         Paused        -> kbhPaused c e
                                         LevelComplete -> kbhLevelComplete c e
                                         Dead          -> kbhDead c e

kbhGoing :: Char -> Env -> Env
kbhGoing 'a' e = if batWidth/2 <= batX e             then e {batX = batX e - 10} else e
kbhGoing 'd' e = if batX e <= canvWidth - batWidth/2 then e {batX = batX e + 10} else e
kbhGoing ' ' e = e {gameState = Paused}
kbhGoing _ e = e

kbhPreStart :: Char -> Env -> Env
kbhPreStart ' ' e = e {gameState = Going}
kbhPreStart _ e = e

kbhPaused :: Char -> Env -> Env
kbhPaused ' ' e = e {gameState = Going}
kbhPaused _ e = e

kbhDead :: Char -> Env -> Env
kbhDead ' ' e = initEnv
kbhDead _ e = e

kbhLevelComplete ' ' e = let newLevel = level e + 1
                             prevdX = balldX e
                             prevdY = balldY e
                          in initEnv {level = level e + 1
                                     ,balldY = sqrt (prevdX * prevdX + prevdY * prevdY) * (1 + (0.05 * fromIntegral newLevel))
                                     }
kbhLevelComplete _ e = e

drawBlock :: Double -> Double -> Double -> Double -> UI.Canvas -> UI()
drawBlock x y w h c = do UI.fillRect (x,y) (w/2.0) h c
                         UI.fillRect (x,y) (-w/2.0) h c

batOffset :: Double -> Double -> Double
batOffset batX ballX = (2 * (batX - ballX))/batWidth

updateEnv :: Env -> Env
updateEnv e = case gameState e of Going -> let x = ballX e
                                               y = ballY e
                                               dX = balldX e
                                               dY = balldY e
                                               hit' = map (hitBlock x y) (blocks e)
                                               hit = map isHit hit'
                                               newBlocks = filter ((==Not) . isHit) hit'
                                               hitBat = hitCheck x y (batX e) (batY e) (batWidth/2) batHeight
                                               ballV = sqrt (dX * dX + dY * dY)
                                               bdx = if x < ballSize || x > canvWidth - ballSize  || elem InX hit || elem InBoth hit || hitBat == InX || hitBat == InBoth
                                                       then negate $ dX
                                                     else if hitBat == InY
                                                       then negate $ ballV * sin (batOffset (batX e) x)
                                                     else dX
                                               bdy = if y < ballSize || elem InY hit || elem InBoth hit || hitBat == InBoth
                                                     then negate $ dY
                                                     else if hitBat == InY
                                                       then (negate . abs) $ ballV * cos (batOffset (batX e) x)
                                                     else dY
                                               gs = if y > canvHeight - ballSize 
                                                      then Dead 
                                                    else if null newBlocks
                                                      then LevelComplete
                                                    else Going
                                            in e {balldX = bdx
                                                 ,balldY = bdy
                                                 ,ballX = x + bdx
                                                 ,ballY = y + bdy
                                                 ,blocks = newBlocks
                                                 ,gameState = gs}
                                  otherwise -> e

hitBlock :: Double -> Double -> Block -> Block
hitBlock cx cy b@(Block {x = bx, y = by}) = let hc = hitCheck cx cy bx by (blockWidth/2) blockHeight
                                            in if hc /= Not then b {isHit = hc}
                                                            else b

hitCheck :: Double -> Double -> Double -> Double -> Double -> Double -> HitWhere
hitCheck cx cy bx by bw bh = let deltaX = cx - maximum [bx-bw, minimum [cx, bx + bw]]
                                 deltaY = cy - maximum [by, minimum [cy, by+bh]]
                              in if (deltaX * deltaX + deltaY * deltaY) < (ballSize * ballSize) then if      abs deltaX > abs deltaY then InX
                                                                                                     else if abs deltaY > abs deltaX then InY
                                                                                                                                     else InBoth
                                 else Not


setup :: Window -> UI ()
setup w = do return w # set title "BrickBreaker!"
             timer <- UI.timer # set UI.interval 10
             canv <- UI.canvas # set UI.width  (round canvWidth)
                               # set UI.height (round canvHeight)
                               # set style [("width",show canvWidth ++ "px")
                                           ,("height",show canvHeight ++ "px")
                                           ,("border","solid black 1px")]
             wrap <- UI.div #. "wrap"
                            # set style [("width",show canvWidth ++ "px")
                                        ,("height",show canvHeight ++ "px")]
                            # set (attr "tabindex") "1"
                            # set (attr "id") "main"
             let batMove = keyboardHandle <$> UI.keypress wrap
                 onTick = updateEnv <$ UI.tick timer
                 fns = unionWith const batMove onTick
             env <- accumB initEnv fns
             status <- UI.label # sink UI.text (fmap (\e -> show (gameState e) 
                                                         ++ ", Level " 
                                                         ++ show (level e) 
                                                         ++ " batX: " 
                                                         ++ (takeWhile (/='.') . show) (batX e) 
                                                         ++ ", ballX: " 
                                                         ++ (takeWhile (/='.') . show) (ballX e)) env)
             UI.start timer
             getBody w #+ [UI.center #+ ([element wrap #+ [element status, element canv]])]
             on UI.tick timer $ const $ do currEnv <- currentValue env
                                           UI.clearCanvas canv
                                           UI.beginPath canv
                                           UI.arc (ballX currEnv, ballY currEnv) ballSize 0.0 (2*pi) canv
                                           UI.fill canv
                                           drawBlock (batX currEnv) (batY currEnv) batWidth batHeight canv
                                           sequence $ map (\e -> drawBlock (x e) (y e) blockWidth blockHeight canv) (blocks currEnv)
             return ()

main :: IO ()
main = startGUI defaultConfig setup
