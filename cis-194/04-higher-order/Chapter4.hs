module Chapter4 where

fun1 :: [Integer] -> Integer
fun1 = product . map (+ (-2)) . filter even

fun2 :: Integer -> Integer
fun2 = sum . filter even . takeWhile (> 1) . iterate f
  where
    f n
      | even n = n `div` 2
      | otherwise = 3 * n + 1

data Tree a
  = Leaf
  | Node Integer (Tree a) a (Tree a)
  deriving (Show, Eq)

foldTree :: [a] -> Tree a
foldTree [] = Leaf
foldTree [a] = Node 0 Leaf a Leaf
foldTree xs = Node h left a right
  where
    mid = length xs `div` 2
    (leftxs, a : rightxs) = splitAt mid xs
    (left, right) = (foldTree leftxs, foldTree rightxs)
    h = 1 + max (height left) (height right)

    height Leaf = 0
    height (Node h _ _ _) = h
