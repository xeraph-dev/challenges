module Gold where

skips :: [a] -> [[a]]
skips xs = map (map snd) $ map f $ zip [1 ..] $ replicate (length xs) $ zip [1 ..] xs
  where
    f (idx, sxs) = filter (ff idx) sxs
    ff idx x = fst x `mod` idx == 0

localMaxima :: [Integer] -> [Integer]
localMaxima xs = map (!! 1) $ filter f $ map fm $ zip [-1 ..] $ replicate (length xs) xs
  where
    f xs = length xs == 3 && maximum xs == xs !! 1
    fm (idx, xs) = take (min 3 $ idx + 3) $ drop idx xs
