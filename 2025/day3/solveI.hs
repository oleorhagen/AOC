-- Day 3 - Part I

-- 1. - Do create each valid pair of numbers in order from the
--      input string

createPairs :: String -> [Int]
createPairs s = [ s2Int [ s !! a,s !! b ] | a <- [0..(l-1)], let i = a +1, b <- [i..(l-1)]] where
  l = length s


s2Int :: String -> Int
s2Int s = read s :: Int

main :: IO ()
main = do
  fileLines <- lines <$> readFile "data.txt"
  -- print fileLines

  let f = maximum . createPairs

  let r = map f fileLines
  -- print r

  print $ sum r
