
splitByDelimeter :: Char -> String -> [String]
splitByDelimeter d = foldr f [[]]
  where
    f c l@(x:xs) | c == d = []:l
                 | otherwise = (c:x):xs

isPalindrome :: String -> Bool
isPalindrome s = all id (zipWith (==) left right) where
  (left, right) = splitAt (div (length s)  2) s
-- split [Char] in two, then reverse one string, and compare (?)

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
        toString = show
  -- print rangesStrings

  -- Beautiful - Now, the actual problem, duplicated IDs
  -- So searching for palindromes essentially!
  let l2Pals = filter isLength2 rangesStrings where
        isLength2 s = even (length s)
  let pals = filter isPalindrome l2Pals
  -- print pals

  -- Now, back to integers
  -- let toInt
  let s2Int s = read s :: Int

  let res = map s2Int pals
  -- print res
  print (sum res)

  -- Whoopsie, Palindrome is not quite correct!

  -- Double Whoopsie, we are not really looking for palindromes
  ---
  -- Really looking for sequence of digits repeated twice!
  ---
  -- i.e. They have to be even numbered in Length!

  -- My lord! This needs improvement!
  -- J-e-s-u-s: Printing makes it slow as dirt!
