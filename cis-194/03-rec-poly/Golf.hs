module Gold where

skips :: [a] -> [[a]]
skips xs = map (map snd) $ map f $ zip [1 ..] $ replicate (length xs) $ zip [1 ..] xs
  where
    f (idx, sxs) = filter (ff idx) sxs
    ff idx x = fst x `mod` idx == 0
