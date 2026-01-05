-- Day 3 - Part I

-- 1. - Do create each valid 12-tuple of numbers in order from the
--      input string

import Data.Char (digitToInt)
import Data.List (elemIndex)
import Data.Maybe (fromJust)

createPairs :: String -> [Int]
createPairs s = [ s2Int [ s !! a,s !! b ] | a <- [0..(l-1)], let i = a +1, b <- [i..(l-1)]] where
  l = length s

createStringArray :: String -> [Int]
createStringArray s = [ digitToInt c | c <- s]

-- maxFromString :: String -> Int -> Int
-- maxFromString s nr = maximum (createStringArray (take (l - nr + 1) s)) + maxFromString


-- We want the max for each range, that is first, from the 12 - len str, then 12
-- - first length removed, etc, etc.
-- How do I implement this?

maxFrom :: [Int] -> Int -> [ Int ]
--         Int Array, Length, result
maxFrom _ 0 = []
maxFrom ints nrRem = maxFound : maxFrom (drop maxPos ints) newRem where
  curlen = (length ints) - nrRem + 1
  newRem = nrRem - 1
  -- Need the index of the maximum returned to pass on
  maxFound = maximum (take curlen ints)
  maxPos = (fromJust $ elemIndex maxFound ints) + 1

-- Create array of ints from string


s2Int :: String -> Int
s2Int s = read s :: Int

main :: IO ()
main = do
  fileLines <- lines <$> readFile "test-data.txt"
  print fileLines

  -- Create an array of ints for each battery bank
  let f = map digitToInt
  let nrs = map f fileLines
  print nrs
