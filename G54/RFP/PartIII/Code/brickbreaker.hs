import qualified Graphics.UI.Threepenny       as UI
import           Graphics.UI.Threepenny.Core

type Pos = Double

type Dim = Double

data HitWhere = InX
              | InY
              | InBoth
              | Not
              deriving (Eq, Show)

data GameState = PreStart
               | Going
               | Paused
               | LevelComplete
               | Dead
               deriving (Eq, Show)

data Block = Block {x         :: Pos
                   ,y         :: Pos
                   ,isHit     :: HitWhere
                   ,colour    :: UI.Color
                   ,points  :: Int
                   } deriving Show

data Env = Env {ballX     :: Pos
               ,ballY     :: Pos
               ,balldX    :: Double
               ,balldY    :: Double
               ,paddleX   :: Pos
               ,paddleY   :: Pos
               ,blocks    :: [Block]
               ,gameState :: GameState
               ,level     :: Int
               ,score     :: Int
               } deriving Show

canvWidth :: Dim
canvWidth = 800.0

canvHeight :: Dim
canvHeight = 480.0

blocksX :: Double
blocksX = 16.0

blocksY :: Double
blocksY = 10.0

blockGapX :: Double
blockGapX = canvWidth / blocksX

blockGapY :: Double
blockGapY = canvHeight / (3 * blocksY)

blockWidth :: Dim
blockWidth = blockGapX * 0.9

blockHeight :: Dim
blockHeight = blockGapY * 0.9

paddleWidth :: Dim
paddleWidth = canvWidth * 0.2

paddleHeight :: Dim
paddleHeight = canvWidth * 0.02

ballSize :: Dim
ballSize = 0.05 * minimum [canvWidth, canvHeight]

ballSpeed :: Double
ballSpeed = 5.0

initBlocks :: [Block]
initBlocks = let maxBlocksX = blocksX - 1
                 maxBlocksY = blocksY - 1
              in [Block {x         = blockGapX * (0.5 + x')
                        ,y         = blockGapY * (0.5 + y')
                        ,isHit     = Not
                        ,colour    = UI.RGB (ceiling (255 * ((maxBlocksY - y') / maxBlocksY))) 0 0
                        ,points  = (round $ 100 * (blocksY - y'))
                        } | x' <- [0.0,1.0..maxBlocksX], y' <- [0.0,1.0..maxBlocksY]]

blocksForLevel :: Int -> [Block]
blocksForLevel l = map (\b -> b {points = points b * l}) initBlocks

initEnv :: Env
initEnv = Env {ballX      = canvWidth / 2
              ,ballY      = canvHeight / 2
              ,balldX     = 0
              ,balldY     = ballSpeed
              ,paddleX    = canvWidth / 2
              ,paddleY    = canvHeight * 0.95
              ,blocks     = initBlocks
              ,gameState  = PreStart
              ,level      = 1
              ,score      = 0
              }

keyboardHandle :: UI.KeyCode -> Env -> Env
keyboardHandle c e 
  = case gameState e of Going ->          if (c == 39 || c == 68)
                                          && (paddleX e <= canvWidth - paddleWidth/2)
                                            then e {paddleX = paddleX e + 10}
                                          else if (c == 37 || c == 65)
                                               && (paddleWidth/2 <= paddleX e)
                                            then e {paddleX = paddleX e - 10}
                                          else if (c == 27 || c == 32)
                                            then e {gameState = Paused}
                                          else e
                        LevelComplete -> if c == 32
                                           then let level' = level e + 1
                                                    dBall' = sqrt ((balldX e)^2 + (balldY e)^2) * 1.1
                                                    blocks' = map (\b -> b {points = points b * level'}) initBlocks
                                                 in initEnv {gameState = PreStart
                                                            ,level = level'
                                                            ,balldY = dBall'
                                                            ,score = score e
                                                            ,blocks = blocks'
                                                            }
                                         else e
                        Dead ->          if c == 32 then initEnv else e
                        otherwise ->     if c == 32 then e {gameState = Going} else e

hitCheck :: Pos -> Pos -> Pos -> Pos -> Double -> Double -> HitWhere
hitCheck cx cy bx by bw bh = let deltaX = cx - (max (bx-bw) (min cx (bx + bw)))
                                 deltaY = cy - (max (by) (min cy (by+bh)))
                              in if (deltaX ^ 2 + deltaY ^ 2) < (ballSize ^ 2)
                                   then if abs deltaX > abs deltaY
                                          then InX
                                        else if abs deltaY > abs deltaX
                                          then InY
                                        else InBoth
                                 else Not

hitBlock :: Pos -> Pos -> Block -> Block
hitBlock cx cy b@(Block {x = bx, y = by}) = let hc = hitCheck cx cy bx by (blockWidth/2) blockHeight
                                             in if hc /= Not then b {isHit = hc}
                                                             else b

paddleOffset :: Pos -> Pos -> Double
paddleOffset paddleX ballX = (2 * (paddleX - ballX))/paddleWidth

splitList :: (a -> Bool) -> [a] -> ([a],[a])
splitList p as = splitList' p as ([],[])

splitList' :: (a -> Bool) -> [a] -> ([a],[a]) -> ([a],[a])
splitList' _ [] t            = t
splitList' p (a:as) (ys, ns) = if p a then splitList' p as (a:ys, ns)
                                      else splitList' p as (ys, a:ns)

updateEnv :: Env -> Env
updateEnv e = case gameState e of Going -> let x = ballX e
                                               y = ballY e
                                               dX = balldX e
                                               dY = balldY e
                                               pX = paddleX e
                                               pY = paddleY e
                                               hit = map (hitBlock x y) (blocks e)
                                               hitB = map isHit hit
                                               (nh, ih) = splitList ((==Not) . isHit) hit
                                               hitP = hitCheck x y pX pY (paddleWidth/2) paddleHeight
                                               ballV = sqrt ((balldX e)^2 + (balldY e)^2)
                                               bdx = if x < ballSize
                                                     || x > canvWidth - ballSize
                                                     || elem InX hitB
                                                     || elem InBoth hitB
                                                     || hitP == InX
                                                     || hitP == InBoth
                                                       then negate dX
                                                     else if hitP == InY
                                                       then negate $ ballV * sin ((pi/2) * paddleOffset pX x)
                                                     else dX
                                               bdy = if y < ballSize
                                                     || elem InY hitB
                                                     || elem InBoth hitB
                                                     || hitP == InBoth
                                                       then negate dY
                                                     else if hitP == InY
                                                       then negate $ abs $ ballV * cos ((pi/2) * paddleOffset pX x)
                                                     else dY
                                               gs = if y > (canvHeight - ballSize)
                                                      then Dead
                                                    else if null nh
                                                      then LevelComplete
                                                    else Going
                                               dS = (sum . map points) ih
                                           in e {balldX = bdx
                                                ,balldY = bdy
                                                ,ballX = x + bdx
                                                ,ballY = y + bdy
                                                ,blocks = nh
                                                ,gameState = gs
                                                ,score = score e + dS
                                                }
                                  otherwise -> e

drawBall :: Env -> UI.Canvas -> UI()
drawBall e c = do UI.beginPath c
                  UI.arc (ballX e, ballY e) ballSize 0.0 (2*pi) c
                  UI.fill c

drawRect :: Pos -> Pos -> Double -> Double -> UI.Canvas -> UI()
drawRect x y w h c = do UI.fillRect (x,y) (w/2.0) h c
                        UI.fillRect (x,y) (-w/2.0) h c

drawBlock :: UI.Canvas -> Block -> UI()
drawBlock c b = do c # set' UI.fillStyle (UI.solidColor (colour b))
                   drawRect (x b) (y b) blockWidth blockHeight c

setup :: Window -> UI ()
setup w = do return w # set title "BrickBreaker!"
             timer <- UI.timer # set UI.interval 10
             wrap <- UI.div #. "wrap"
                            # set style [("width", show canvWidth  ++ "px")
                                        ,("height",show canvHeight ++ "px")
                                        ,("font-family", "sans-serif")]
                            # set (attr "tabindex") "1"
                            # set (attr "id") "main"
             canv <- UI.canvas # set UI.width  (round canvWidth)
                               # set UI.height (round canvHeight)
                               # set style [("width", show canvWidth ++ "px")
                                           ,("height",show canvHeight ++ "px")
                                           ,("border","solid black 1px")]
             window <- getBody w
             let onKeydown = keyboardHandle <$> UI.keydown window
                 onTick = updateEnv <$ UI.tick timer
                 fns = unionWith const onKeydown onTick
             env <- accumB initEnv fns
             status <- UI.label # sink UI.text (fmap showStats env)
             UI.start timer
             getBody w #+ [UI.center #+ ([element wrap #+ [element status, element canv]])]
             on UI.tick timer $ const $ do currEnv <- currentValue env
                                           canv # set' UI.fillStyle (UI.solidColor (UI.RGB 0 0 0))
                                           UI.clearCanvas canv
                                           drawBall currEnv canv
                                           drawRect (paddleX currEnv) (paddleY currEnv) paddleWidth paddleHeight canv
                                           (sequence . map (drawBlock canv) . blocks) currEnv
          where showStats e = case (gameState e) of PreStart      -> "Press space to start level "
                                                                     ++ show (level e)
                                                                     ++ "!"
                                                    Going         -> "Level "
                                                                     ++ show (level e)
                                                                     ++ " / "
                                                                     ++ show (score e)
                                                                     ++ " points"
                                                    Paused        -> "Game paused, press space to resume"
                                                    LevelComplete -> "Congratulations! You finished this level on "
                                                                     ++ show (score e)
                                                                     ++ " points! Press space to advance to the next level!"
                                                    Dead          -> "You died! Final score: "
                                                                     ++ show (score e)
                                                                     ++ ". Press space to start again."
                                                    otherwise     -> "This shouldn't be possible"

main :: IO ()
main = startGUI defaultConfig {jsPort = Just 8023
                              ,jsStatic = Just "../wwwroot"
                              } setup
