-- Same -> But patterns repeated _at least_ twice.
-- i.e., Repeat(s) >= 2
-- Naive solution:
-- Pick a Prefix, then check if it matches repeatedly throughout the whole string!
-- Smart ways of doing it (?)
-- I can start with the longest prefix, and keep decreasing it?
--- But more of an optimization
--- Remember: Not all the strings are even length anylonger (!)
-- Haskell generator for all the prefixs
-- Well haskell is lazy, so we can do this


substrings :: String -> [String]
substrings str = filter (\x -> (length x) < (length str)) [take len (drop start str) | start <- [0..length str - 1], len <- [1..length str - start]]

splitByDelimeter :: Char -> String -> [String]
splitByDelimeter d = foldr f [[]]
  where
    f c l@(x:xs) | c == d = []:l
                 | otherwise = (c:x):xs

-- Now try and map each substring to the whole string itself, one piece at a
-- time
isSubstringOverlapping :: String -> String -> Bool
isSubstringOverlapping _ "" = True
isSubstringOverlapping needle haystack = take (length needle) haystack == needle && isSubstringOverlapping needle (drop (length needle) haystack)


isInvalidID :: String -> Bool
isInvalidID s = any id $ map (uncurry isSubstringOverlapping) [ (a,b) | a <- (substrings s), b <- [s]]

main :: IO ()
main = do
  fileLines <- lines <$> readFile "data.txt"
  -- print fileLines
  let args = splitByDelimeter ',' (head fileLines)
  -- print args
  -- Now split the numbers in the array by -
  let ranges = splitByDelimeter '-' (head args)
  -- print ranges
  -- Now do this for all the elements, and collect into tuples
  let rs = map (splitByDelimeter '-') args
  -- print rs
  -- Now generate the range for the pairs
  let toInt (x:y:_) = [(read x :: Int)..(read y :: Int)]
  -- -- print ints
  let rangesInts = map toInt rs
  -- print rangesInts
  -- Now back to strings for all the numbers
  let rangesStrings = map toString (concat rangesInts) where
        toString  = show
  -- print rangesStrings

  ---
  -- Now do this for all strings
  ---
  -- map isInvalidID

  let l2Pals = filter isInvalidID rangesStrings
  -- print l2Pals

  let s2Int s = read s :: Int

  let res = map s2Int l2Pals
  -- print res
  print (sum res)
