module Chapter1 where

toDigits :: Integer -> [Integer]
toDigits n
  | n <= 0 = []
  | otherwise = toDigits (n `div` 10) ++ [n `mod` 10]

toDigitsRev :: Integer -> [Integer]
toDigitsRev = reverse . toDigits

doubleEveryOther :: [Integer] -> [Integer]
doubleEveryOther xs = reverse $ zipWith f (reverse xs) [1 ..]
  where
    f x i
      | even i = x * 2
      | otherwise = x
