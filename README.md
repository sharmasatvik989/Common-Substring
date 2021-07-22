# Common-Substring
The C program to determine a longest common substring of three input strings with no more than 500
symbols each. 
 1. Each input string will be on a line by itself. These strings will be readable using scanf, since they will
    include only upper/lowercase alphabetic symbols or digits. Your code should run in time , not including the time
    to compute the suffix array, where n is the total number of input symbols.
    
 2. Your output will be strings common to all three input strings with monotonically increasing (e.g. non-decreasing) lengths.
    That is, whenever you find a common substring you will check to see if its length is at least as long as the previous
    longest common substring. It is important to find substrings (i.e. contiguous symbols) rather than subsequences.
