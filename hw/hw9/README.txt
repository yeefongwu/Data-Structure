HOMEWORK 9: MINIBLAST


NAME:  <Yeefong(Wyatt) Wu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.


< insert collaborators / resources >
Leon, Sweet, Henry,Zhengneng
http://www.partow.net/programming/hashfunctions/
https://stackoverflow.com/questions/98153/whats-the-best-hashing-algorithm-to-use-on-a-stl-string-when-using-hash-map
lecture 20

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 >


HASH FUNCTION DESCRIPTION
hash function is given in lecture 20, it might not work as fast as others
but for this assignment its good enough so i just use it




HASH TABLE IMPLEMENTATION

my hash table is a vector of pair, in the pair the first one is a string, refer to the sequence
the second part of pair is a vector of int fill with location of that sequence vector<pair<string,vector<int> > >
when there is collision it will follow the linear opening addressing, the problem about this approach is that hash is
not going to spread to far when it met collision but it sufficient for this miniblast.



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the hash table data structure require (order notation for memory use)?
O((l-k+1)*p) because for example if a genome is AGGTC and kmer is 2, the number of unique key is 4, AG,GG,GT,TC, which is genome -kmer + 1
so it means the table has to be O((l-k+1)*p) because each sequence can have p number of location where key is found


What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?
for 'genome' it will be O(l) because it read the whole genome from file
for 'table_size' it's O(1) because it change the table size
for 'occupancy' it's O(1) because it change the occupancy
for 'kmer' it's O((l-k+1)*p) because it also build up the hash table which describe above
for 'query' it's O((L-K)*p) because it's constant to find the query with kmer , in worst case it have
to loop through all different query in hash table to find the position which is O(L-K) and in
that vector loop through all possible location so overall O((L-K)*p)
for 'quit' it's O(1) because it exist the execution



EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


