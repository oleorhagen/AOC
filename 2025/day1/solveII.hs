{-# LANGUAGE OverloadedStrings #-}
module Main where

import System.IO

-- Wheel from 0 - 99
-- Dial starts pointing at 50 (always)

-- Map L(A) -> -A
-- Map R(A) -> +A

-- password method 0x434C49434B

-- Now count every time the dial goes past 0

-- So move to rem, as opposed to mod (?)

-- How do I check if the two numbers have zero in their range (?)

toValue :: String -> Integer
toValue (d:v) | d == 'L' = negate $ read v :: Integer
toValue (d:v) | d == 'R' = read v :: Integer

-- Since operations are distributive over addition and subtraction, we can do (a + b + c ) mod n

main :: IO ()
main = do
  fileLines <- lines <$> readFile "test-data.txt"
  let numbers = map toValue fileLines

  -- TODO - Explode the list to include all numbers scrolled past ?
  let modNrs = map (`mod` 100) $ scanl (+) 50 numbers
  print modNrs
  let nrZeros = filter (== 0) modNrs
  print  $ length nrZeros
  return ()
