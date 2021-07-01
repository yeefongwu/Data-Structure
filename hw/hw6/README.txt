HOMEWORK 6: CROSSWORD BLACKOUT


NAME:  < Yeefong(Wyatt) Wu>



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
Leon Zhou, Chris, Henry Qi, Frost

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of words in the dictionary (d)? 
The total number of spaces with a letter (l)?
The total number of blacked out spaces (b)? 
The number of constraints (c)?
Etc. 
The size of seperated puzzle (sp)
The size of all_combination (ac)
The size of all_solution (as)
The size of one_combination (ob)

algorithm:
for each char in the grid called find word function, and within find word i have to go through dictionary.
after find the word, find all possible solution by go through each combination. after all combination are found
create black_out board and check each char in black_out board with check grid function, and within each check grid i have
to go through one of the combination vector. so totally the order notation for the algorithm would be O(w * h * O(log(c) * w)) or O(w * h * O(log(c) * h))
because findWord function has the largest order notation compare to other function

findWord_help: O(log(c) * w) or O(log(c) * h)
the order notation in findWord_help has find and while, because find take O(logn) and it loop through number of constraint
while takes O(d) because it loop through dictionary, so findWord_help is O(log(c)). but because its recursive, worst case it will recurse until it
hit the edge, but it can be either crossword or downword, we dont know w and h which one is longer so
order notation is (log(c) * w) or O(log(c) * h)

findWord: O(w * h * O(log(c) * w)) or O(w * h * O(log(c) * h))
each char in grid has to go through findWord_help each word loop through is O(w * h) with findWord_help
so O(w * h * O(log(c) * w)) or O(w * h * O(log(c) * h))

all_solution: O(sp*sp)
in all solution, it will keep recursive until the number of constraints of specific length is full or seperated puzzle is empty
for 'c' i mean like if only two 5 letters words are allowed c would be 2
and there is a while loop in all_solution so O(sp) and recursive for sp times

combine: O(sp * sp * sp)
for each seperated puzzle, it has to call all_solution, so it's O(sp * sp * sp)

check_board: O(w) or O(h)
this function is very much like the findWord_help function, it has to recursive until it hit edge
or meet '#', because the while loop only take place once, so it's just O(w) or O(h)

all_board: O(ac * w * h * w) or O(ac * w * h * h)
in worst case, for each combination, when black_out board is generate, it will check every grid
so O(ac * w * h) but for every space in grid, it will run check_board, so O(ac * w * h * w) or O(ac * w * h * h)



=======================================================================================

DESCRIPTION OF YOUR ADDTIONAL PUZZLES/DICTIONARIES:
Briefly explain the design of the puzzles or dictionaries and what
makes them "interesting" test cases (or why they aren't interesting).

boring test, just want to test the time consuming for the case
when the dictionary is large and the grid is large
and try to determine which one takes more percentage while executing

puzzle1.txt is a randomly type large puzzle  (p1)
puzzle2.txt is a normal puzzle  (p2)
puzzle_dic1 is a large dic (d1)
puzzle_dic2 is a small dic (d2)

with p2 and d2 its quick
with p1 and d2 its slightly slower but still quick
with p2 and d1 its quick

with p1 and d1 it takes over 7 min

i assume the time consuming is large when the dictionary and the grid ia both large
and the dictionary might be a litte bit more time relative because p2&d1 is faster than p1&d2

the other test is puzzle3 and puzzle_dic3
the puzzle_dic3 is the same as black_out_dic
the puzzle3 is similar to black_out1 except
i make the grid irregular to see if it works and it works

=======================================================================================

SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND 
ON YOUR ADDITIONAL PUZZLES/DICTIONARIES:
# of solutions & approximate wall clock running time for different
puzzles / dictionaries for a single solution or all solutions. Be
specific about which puzzle/dictionary/parameters you were timing.

my running time for single and all are the same because i seperate them during the
print function, not in the algorithm part so running time are same
===================================================================================
    dictionary   ||         grid          ||  # of solutions ||  running time
                                                                 single | all
===================================================================================
    reverse_ell  ||     reverse_ell_1     ||       1         ||   <1s   |  <1s
===================================================================================
    reverse_ell  ||     reverse_ell_2     ||       1         ||   <1s   |  <1s
===================================================================================
    nyt_mini_1   ||     nyt_mini_1        ||       1         ||   <1s   |  <1s
===================================================================================
    nyt_mini_1   ||     nyt_mini_2        ||       1         ||   <1s   |  <1s
===================================================================================
    nyt_mini_1   ||  nyt_mini_1_non_black ||       1         ||   <1s   |  <1s
===================================================================================
    black_out    ||      black_out_1      ||       3         ||   <1s   |  <1s
===================================================================================
    black_out    ||      black_out_2      ||       1         ||   <1s   |  <1s
===================================================================================
    puzzle_1     ||      puzzle_1         ||       0         ||  7min   |  7min
===================================================================================
    puzzle_2     ||      puzzle_2         ||       0         ||   <1s   |  <1s
===================================================================================
    puzzle_1     ||      puzzle_2         ||       3         ||   <2s   |  <2s
===================================================================================
    puzzle_2     ||      puzzle_1         ||       0         ||   <1s   |  <1s
===================================================================================

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
i havn't put the sporcle case in the summary because i dont know if my answer is correct or not



