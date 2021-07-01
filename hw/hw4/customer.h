//
// Created by yeefongwu on 2/28/21.
//

#ifndef HW4_CUSTOMER_H
#define HW4_CUSTOMER_H

#include <list>
#include<iostream>
#include <string>
using namespace std;

class Customer{
public:
    //constructor
    Customer(string name){m_name=name;}
    //accessor function
    list<string> &get_preferences(){return m_preference_movie;}
    string get_name(){return m_name;}
    list<string> &get_hold(){return m_hold_movie;}
    const int get_hold_number(){return m_hold_movie.size();}
    //helper function
    const bool has_max_num_movies(){return m_hold_movie.size()==3;}
    const bool preference_list_empty(){return m_preference_movie.size()==0;}
    //if receive a movie remove from preference list and add to hold list
    void receives(string preference_movie){m_preference_movie.remove(preference_movie);m_hold_movie.push_back(preference_movie);}
    void preference_list_pushback(string dvd_name){m_preference_movie.push_back(dvd_name);}
    const string return_both(string& token);//help for return oldest and return newest




private:
    string m_name;
    list<string> m_preference_movie;
    list<string> m_hold_movie;

};

const string Customer::return_both(string& token) {
    if(token=="return_oldest"){//if token is oldest pop out front
        string front=m_hold_movie.front();
        m_hold_movie.pop_front();
        return front;
    }
    else if(token=="return_newest"){//if token is newest pop out back
        string back=m_hold_movie.back();
        m_hold_movie.pop_back();
        return back;
    }
    else{return "WARNING";}
}

#endif //HW4_CUSTOMER_H

