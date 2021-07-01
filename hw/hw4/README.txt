 HOMEWORK 4: DVD LISTS


NAME:  < Yeefong(Wyatt) Wu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.


< Leon, Henry, Chris>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.
 

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 14 >


ORDER NOTATION:
For each function, using the variables:
  d = number of different movie DVD titles
  k = average or maximum copies of each DVD
  c = number of customers
  p = average or maximum movies ranked on each customer’s preference list
Include a short description of your order notation analysis.


dvd:O(d)
in dvd, the for loop is O(d) as it go through inventory and other are all O(1) so sum it up would be O(d)


customer:O(cp+pk+pp)
for each customer check each preference so O(cp), for each preference check each inventory so O(pk), for each preference check each customer preference so O(pp)
other are all constant O(1) and linear, so sum up would be O(cp+pk+pp)

add_preference:O(c+d+p)
check through customer and inventory and preference list, all linear so O(c+d+p), other are all constant and linear
so sum up would be O(c+d+p)

ship:O(cp)
for each customer check each preference so O(cp), other are all constant O(1), so sum it up would be O(cp)


return_oldest:O(d+c)
check through customer and inventory, all linear so O(d+c), other are all constant so sum up would be O(d+c)

return_newest:O(d+c)
check through customer and inventory, all linear so O(d+c), other are all constant so sum up would be O(d+c)


print_customer:O(c+p)
check through customer and preference, all linear so O(p+c), other are all constant so sum up would be O(p+c)

print_dvd:O(d)
check through inventory, all linear so O(d), other are all constant so sum up would be O(d)



EXTRA CREDIT:
Describe the analysis you performed on customer satisfaction.  Paste
in a small amount of sample analysis output and/or specify a sample
output file.  Describe your improved algorithm and compare the
analysis results of your new algorithm.  Please be concise!



MISC. COMMENTS TO GRADER:  
Optional, please be concise!






