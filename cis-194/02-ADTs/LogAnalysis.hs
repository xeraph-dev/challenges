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
