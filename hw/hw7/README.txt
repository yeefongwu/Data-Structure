HOMEWORK 7: HALLOWEEN COSTUME MAPS


NAME:  < Yeefong(Wyatt) Wu>


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 3 >



ORDER NOTATION ANALYSIS (ORIGINAL VERSION W/MAPS):
of each of the costume shop operations (please be concise!)
Let n be the number of different costumes in the shop,
m be the maximum number of copies of a given costume,
and c be the number of customers who visit the shop.

add costume: O(logn)
other are all constant, except when it call [] for costume_shop map which is O(logn) and since
it go through all different costumes, it will be O(logn)


rent costume: O(m+n)
in rent costume, there are two O(n) for find, other are all O(1) and O(logn)
and for the one find it's O(n) and go through the customer
who rent the specific costume, which in worst case all costumes are rented
will be c, O(m), and then the other find function go through
all different costume so O(n),so overall O(m+n)

look up: O(m)
the find function for if statement is O(logn), it go through all different costume in shop, So O(n)
but it only take place once,and the for loop under this condition is O(n) as it go through
all customer rent the costume, in worst case all costume are rented so O(m), overall it will be O(m)

print people: O(c)
the function go through all people attempt to rent a costume, other are all O(1), so overall O(c)

================================================================================================================================================
Order notation with respect to c for each costume shop operation in each function:

add costume: O(1)
nothing is related with c in this function, it only go through n the number of different costumes in shop

rent costume: O(logc)
for other operation like [], other are all constant, but for the people [], it takes O(logn) and it go through
all different customer visit the shop, so O(logc)

look up: O(1)
there are operation like find and [] but they are not related with c, so for c it's O(1)






EXTRA CREDIT (W/O MAPS)
What alternate data structures did you use?  What is the order
notation of each operation without maps?  What is the expected
performance difference?  Summarize the results of your testing.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)






