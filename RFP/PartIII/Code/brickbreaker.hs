import qualified Graphics.UI.Threepenny       as UI
import           Graphics.UI.Threepenny.Core

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

data Block = Block {x         :: Double
                   ,y         :: Double
                   ,isHit     :: HitWhere
                   ,colour    :: UI.Color
                   ,scoreVal  :: Int
                   } deriving Show

data Env = Env {ballX     :: Double
               ,ballY     :: Double
               ,balldX    :: Double
               ,balldY    :: Double
               ,paddleX   :: Double
               ,paddleY   :: Double
               ,blocks    :: [Block]
               ,gameState :: GameState
               ,level     :: Int
               ,score     :: Int
               } deriving Show

canvWidth :: Double   -- The width of the playing canvas
canvWidth = 800.0

canvHeight :: Double  -- The height of the playing canvas
canvHeight = 480.0

blocksX :: Double   -- The number of blocks across
blocksX = 16.0

blocksY :: Double   -- The number of blocks up
blocksY = 10.0

blockGapX :: Double
blockGapX = canvWidth / blocksX

blockGapY :: Double
blockGapY = canvHeight / (3 * blocksY)

blockWidth :: Double
blockWidth = blockGapX * 0.9

blockHeight :: Double
blockHeight = blockGapY * 0.9

paddleWidth :: Double
paddleWidth = canvWidth * 0.2

paddleHeight :: Double
paddleHeight = paddleWidth * 0.1

ballSize :: Double
ballSize = 0.05 * minimum [canvWidth, canvHeight]

ballSpeed :: Double
ballSpeed = 5.0

initBlocks :: [Block]
initBlocks = let maxBlocksX = blocksX - 1
                 maxBlocksY = blocksY - 1
             in [Block {x = blockGapX * (0.5 + xs)
                       ,y = blockGapY * (0.5 + ys)
                       ,isHit = Not
                       ,colour = UI.RGB {UI.red = ceiling $ (((maxBlocksY - ys)) / maxBlocksY) * 255
                                        ,UI.green = 0
                                        ,UI.blue = 0
                                        }
                       ,scoreVal = round $ 100 * (blocksY - ys)
                       } | xs <- [0.0,1.0..maxBlocksX], ys <- [0.0,1.0..maxBlocksY]]

initEnv :: Env
initEnv = Env {ballX = canvWidth / 2
              ,ballY = canvHeight / 2
              ,balldX = 0
              ,balldY = ballSpeed
              ,paddleX = canvWidth / 2
              ,paddleY = 450
              ,blocks = initBlocks
              ,gameState = PreStart
              ,level = 1
              ,score = 0
              }

keyboardHandle :: UI.KeyCode -> Env -> Env
keyboardHandle c e = case gameState e of PreStart      -> kbhPreStart c e
                                         Going         -> kbhGoing c e
                                         Paused        -> kbhPaused c e
                                         LevelComplete -> kbhLevelComplete c e
                                         Dead          -> kbhDead c e

kbhGoing :: UI.KeyCode -> Env -> Env
kbhGoing 37 e = if paddleWidth/2 <= paddleX e             then e {paddleX = paddleX e - 10} else e
kbhGoing 65 e = kbhGoing 37 e
kbhGoing 39 e = if paddleX e <= canvWidth - paddleWidth/2 then e {paddleX = paddleX e + 10} else e
kbhGoing 68 e = kbhGoing 39 e
kbhGoing 32 e = e {gameState = Paused}
kbhGoing _ e = e

kbhPreStart :: UI.KeyCode -> Env -> Env
kbhPreStart 32 e = e {gameState = Going}
kbhPreStart _ e = e

kbhPaused :: UI.KeyCode -> Env -> Env
kbhPaused 32 e = e {gameState = Going}
kbhPaused _ e = e

kbhDead :: UI.KeyCode -> Env -> Env
kbhDead 32 e = initEnv
kbhDead _ e = e

kbhLevelComplete :: UI.KeyCode -> Env -> Env
kbhLevelComplete 32 e = let newLevel = level e + 1
                            prevdX = balldX e
                            prevdY = balldY e
                         in initEnv {gameState = PreStart
                                    ,level = level e + 1
                                    ,balldY = sqrt (prevdX * prevdX + prevdY * prevdY) * 1.05
                                    ,score = score e
                                    ,blocks = map (\b -> b {scoreVal = scoreVal b * newLevel}) initBlocks
                                    }
kbhLevelComplete _ e = e

paddleOffset :: Double -> Double -> Double
paddleOffset paddleX ballX = (2 * (paddleX - ballX))/paddleWidth

updateEnv :: Env -> Env
updateEnv e = case gameState e of Going -> let x = ballX e
                                               y = ballY e
                                               dX = balldX e
                                               dY = balldY e
                                               hit' = map (hitBlock x y) (blocks e)
                                               hit = map isHit hit'
                                               newBlocks = filter ((==Not) . isHit) hit'
                                               hitpaddle = hitCheck x y (paddleX e) (paddleY e) (paddleWidth/2) paddleHeight
                                               ballV = sqrt (dX * dX + dY * dY)
                                               bdx = if x < ballSize || x > canvWidth - ballSize  || elem InX hit || elem InBoth hit || hitpaddle == InX || hitpaddle == InBoth
                                                       then negate dX
                                                     else if hitpaddle == InY
                                                       then negate $ ballV * sin (paddleOffset (paddleX e) x)
                                                     else dX
                                               bdy = if y < ballSize || elem InY hit || elem InBoth hit || hitpaddle == InBoth
                                                     then negate dY
                                                     else if hitpaddle == InY
                                                       then (negate . abs) $ ballV * cos (paddleOffset (paddleX e) x)
                                                     else dY
                                               gs = if y > canvHeight - ballSize
                                                      then Dead
                                                    else if null newBlocks
                                                      then LevelComplete
                                                    else Going
                                               scoreUpdate = (sum . map scoreVal . filter ((/=Not) . isHit)) hit'
                                            in e {balldX = bdx
                                                 ,balldY = bdy
                                                 ,ballX = x + bdx
                                                 ,ballY = y + bdy
                                                 ,blocks = newBlocks
                                                 ,gameState = gs
                                                 ,score = score e + scoreUpdate}
                                  otherwise -> e

hitBlock :: Double -> Double -> Block -> Block
hitBlock cx cy b@(Block {x = bx, y = by}) = let hc = hitCheck cx cy bx by (blockWidth/2) blockHeight
                                            in if hc /= Not then b {isHit = hc}
                                                            else b

hitCheck :: Double -> Double -> Double -> Double -> Double -> Double -> HitWhere
hitCheck cx cy bx by bw bh = let deltaX = cx - maximum [bx-bw, minimum [cx, bx + bw]]
                                 deltaY = cy - maximum [by, minimum [cy, by+bh]]
                              in if (deltaX * deltaX + deltaY * deltaY) < (ballSize * ballSize)
                                   then if abs deltaX > abs deltaY
                                          then InX
                                        else if abs deltaY > abs deltaX
                                          then InY
                                        else InBoth
                                 else Not

drawBall :: Env -> UI.Canvas -> UI()
drawBall e c = do UI.beginPath c
                  UI.arc (ballX e, ballY e) ballSize 0.0 (2*pi) c
                  UI.fill c

drawRect :: Double -> Double -> Double -> Double -> UI.Canvas -> UI()
drawRect x y w h c = do UI.fillRect (x,y) (w/2.0) h c
                        UI.fillRect (x,y) (-w/2.0) h c

drawBlock :: UI.Canvas -> Block -> UI()
drawBlock c b = do c # set' UI.fillStyle (UI.solidColor (colour b))
                   drawRect (x b) (y b) blockWidth blockHeight c

setup :: Window -> UI ()
setup w = do return w # set title "BrickBreaker!"
             timer <- UI.timer # set UI.interval 10
             canv <- UI.canvas # set UI.width  (round canvWidth)
                               # set UI.height (round canvHeight)
                               # set style [("width", show canvWidth ++ "px")
                                           ,("height",show canvHeight ++ "px")
                                           ,("border","solid black 1px")]
             wrap <- UI.div #. "wrap"
                            # set style [("width", show canvWidth  ++ "px")
                                        ,("height",show canvHeight ++ "px")]
                            # set (attr "tabindex") "1"
                            # set (attr "id") "main"
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
                                           liftIO $ putStrLn "Game"
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

main :: IO ()
main = startGUI defaultConfig {jsPort = Just 8023
                              ,jsStatic = Just "../wwwroot"
                              } setup
