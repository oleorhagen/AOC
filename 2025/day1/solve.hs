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
  contents <- readFile "data.txt"
  let fileLines = lines contents
  -- putStr "First line: " ++ (head fileLines)
  putStr "First line: "
  print $ toValue $ head $ fileLines
  let numbers = 50 : map toValue fileLines
  print numbers
  print $ map (`mod` 100) numbers
  let modNrs = tail $ map (`mod` 100) $ scanl (+) 0 numbers
  print modNrs
  let nrZeros = filter (== 0) modNrs
  print nrZeros
  print  $ length nrZeros
  return ()
