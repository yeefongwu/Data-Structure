HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  < Yeefong(Wyatt) Wu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
beck, darius, john, chris,anthony

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 14 >



TESTING & DEBUGGING STRATEGY:
Please be concise!

using drmemeory to check the memory leak and unaddressable access
the more test case check the corner case for erase and insert
and pop and copy and destroy list for int number. beside it test
for two other type, char and float.



ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 


so list is most efficient, unrolledll is more like a nested list for me
compare to dslist which can only store one element per node.
the efficiency about the unrolledll is depend on how many element is store
in one node. If each node is full, in the given case where NUM_ELEMENTS_PER_NODE=6
if each node has 6 element it would be the most efficient. otherwise, if each
node only hold one element, which would become least efficient with average number
of 1 element per node.

push_front(1) only constant
pop_front(1) only constant
push_back(1) only constant
pop_back(1) only constant
erase(n) loop through number of element for normal case so linear
insert(n) loop through number of element for normal case so linear
copy_list(n) loop through all node so linear
destroy_list(n) loop through all node so linear
print(n^2) for each node output each element so n^2


EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


