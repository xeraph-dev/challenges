{-# OPTIONS_GHC -Wall #-}

module LogAnalysis where

import Log
import Text.Read

parseMessage :: String -> LogMessage
parseMessage = makeMessage . words
  where
    makeMessage ("I" : ts : msg)
      | Just timestamp <- readMaybe ts = LogMessage Info timestamp (unwords msg)
    makeMessage ("W" : ts : msg)
      | Just timestamp <- readMaybe ts = LogMessage Warning timestamp (unwords msg)
    makeMessage ("E" : l : ts : msg)
      | Just timestamp <- readMaybe ts, Just level <- readMaybe l = LogMessage (Error level) timestamp (unwords msg)
    makeMessage msg = Unknown $ unwords msg

parse :: String -> [LogMessage]
parse = map parseMessage . lines

insert :: LogMessage -> MessageTree -> MessageTree
insert (Unknown _) tree = tree
insert msg Leaf = Node Leaf msg Leaf
insert msg@(LogMessage _ msgTs _) (Node left treeMsg@(LogMessage _ treeMsgTs _) right)
  | msgTs <= treeMsgTs = Node (insert msg left) treeMsg right
  | otherwise = Node left treeMsg (insert msg right)
insert _ _ = undefined
