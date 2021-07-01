HOMEWORK 3: JAGGED ARRAY


NAME:  < Yeefong(Wyatt) Wu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< beck,henry Qi, Chris K,Fu,Chris >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15>



ORDER NOTATION:
For each function, for each version (packed vs. unpacked).  
b = the number of bins
e = the number of elements
k = the number of elements in the largest bin

numElements
 unpacked:O(1)
 packed:O(1)

numBins
 unpacked:O(1)
 packed:O(1)

numElementsInBin
 unpacked:O(1)
 packed:O(1)

getElement
 unpacked:O(1)
 packed:O(1)

isPacked
 unpacked:O(1)
 packed:O(1)

clear
 unpacked:O(b)
 packed:O(b)

addElement
 unpacked:O(k)
 packed:O(1)

removeElement
 unpacked:O(k)
 packed:O(1)

pack
 unpacked:O(bk)
 packed:O(1)

unpack
 unpacked:O(1)
 packed:O(bk)

print 
 unpacked:O(bk)
 packed:O(e+b)

constructor w/ integer argument
 unpacked:O(b)
 packed:O(1)

copy constructor
 unpacked:O(be)
 packed:O(b+e)

destructor
 unpacked:O(b)
 packed:O(1)

assignment operator
 unpacked:O(be)
 packed:O(b+e)




MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


