#include "line.h"
#include<iostream>
using namespace std;

int main(){
    Point p1(1,2,3);
    Point p2(4,5,6);
    Point p3(7,8,9);
    Point p4(55,11,12);
    Line l1(Point(1,2,3),Point(2,3,4));
    Line l2(Point(1,2,3),Point(100,5,6));
    cout<<steeper_gradient(l1,l2)<<endl<<steeper_gradient(l2,l1);
}