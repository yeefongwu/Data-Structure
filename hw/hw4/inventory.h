//
// Created by yeefongwu on 2/28/21.
//
#ifndef HW4_INVENTORY_H
#define HW4_INVENTORY_H

#include <list>
#include<iostream>
#include <string>
using namespace std;

class Inventory{
public:
    //constructor
    Inventory(string name, int number){movie_title=name;copies=number;sent=0;}
    //accessor
    string get_name(){return movie_title;}
    const int get_copies(){return copies;}
    const int get_sent(){return sent;}
    //helper function
    void copies_increase(int n){copies+=n;}
    bool available(){return copies>=1;}//if its available it has to have at least one copy
    void shipped(){copies-=1;sent+=1;}
    void returned(){copies+=1;sent-=1;}




private:
    string movie_title;
    int copies;
    int sent;



};
#endif //HW4_INVENTORY_H


