{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE OverloadedStrings #-}
module Main where

import System.IO

-- Wheel from 0 - 99
-- Dial starts pointing at 50 (always)

-- Map L(A) -> -A
-- Map R(A) -> +A

toValue :: String -> Integer
toValue (d:v) | d == 'L' = negate $ read v :: Integer
toValue (d:v) | d == 'R' = read v :: Integer

-- Since operations are distributive over addition and subtraction, we can do (a + b + c ) mod n

main :: IO ()
main = do
  fileLines <- lines <$> readFile "data.txt"
  let numbers = map toValue fileLines
  let modNrs = tail $ map (`mod` 100) $ scanl (+) 50 numbers
  let nrZeros = filter (== 0) modNrs
  print  $ length nrZeros
  return ()
