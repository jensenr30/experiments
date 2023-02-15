-- this function checks if a string is a palindrome
-- returns true if input string is a palindrome, otherwise returns false.
function ispalindrome(str)
    return str == string.reverse(str)
end

-- ignroes spaces
function ispalindrome_ignore_spaces(str)
    str = string.gsub(str," ","")
    return ispalindrome(str)
end

-- ignores all characters except letters
-- ignores case
function ispalindrome_only_letters(str)
    return ispalindrome_ignore_spaces(
        string.lower(
            string.gsub(str,"%A","")
        )
    )
end