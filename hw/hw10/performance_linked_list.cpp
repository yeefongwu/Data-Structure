#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// defined in performance.cpp
void usage();

//list sorted and output it
template<class T>
void list_sort(list<T>& l, ostream& ostr, int& output_count){
    l.sort();
    output_count=l.size();
    for(typename list<T>::iterator itr=l.begin();itr!=l.end();itr++){
        ostr<<*itr<<endl;
    }
}

//output without change order
template<class T>
void list_remove_duplicates(const list<T>& l, ostream& ostr, int& output_count){
    output_count=0;
    for(typename list<T>::const_iterator itr=l.begin();itr!=l.end();itr++){
        bool dup=false;
        for(typename list<T>::const_iterator itr2=l.begin();itr2!=itr;itr2++){
            if(*itr==*itr2){
                dup=true;
                break;
            }
        }
        if(!dup){
            ostr<<*itr<<endl;
            output_count++;
        }
    }
}

//sort it so if same it will appear nearby
template<class T>
void list_mode(list<T>& l, ostream& ostr, int& output_count){
    l.sort();
    int current_count=1;
    T mode;
    int mode_count=0;
    typename list<T>::iterator current=l.begin();
    ++current;
    typename list<T>::iterator previous=l.begin();
    for(;current!=l.end();++current, ++ previous){
        //same
        if(*current==*previous){
            current_count++;
        }
        //in case mode change
        else if(current_count>=mode_count){
            mode=*previous;
            mode_count=current_count;
            current_count=1;
        }
        else{
            current_count=1;
        }
    }
    //last one is new mode
    if(current_count>=mode_count){
        mode=*previous;
        mode_count=current_count;
    }
    output_count=1;
    ostr<<mode<<endl;
}

//sort it so closest have to be nearby
void list_closest_pair(list<int>& l, ostream& ostr, int& output_count){
    assert(l.size()>=2);
    l.sort();
    output_count=2;
    int best;
    list<int>::iterator best_iterator=l.end();
    list<int>::iterator itr1=l.begin();
    list<int>::iterator itr2=l.begin();
    itr2++;
    for(;itr2!=l.end();itr2++, itr1++){
        int diff=*itr2-*itr1;
        if(best_iterator==l.end() || diff<best){
            best=diff;
            best_iterator=itr1;
        }
    }
    ostr<<*best_iterator<<endl;
    best_iterator++;
    ostr<<*best_iterator<<endl;
}

//sort it and print out as required
template<class T>
void list_first_sorted(list<T>& l, ostream& ostr, int& output_count, int optional_arg){
    assert(optional_arg>=1);
    assert((int)l.size()>=optional_arg);
    l.sort();
    output_count=optional_arg;
    typename list<T>::iterator itr=l.begin();
    for(int i=0;i<output_count;i++){
        ostr<<*itr<<endl;
        itr++;
    }
}

//helper function to find substring from two string
string list_find_substring(const string& s1, const string& s2){
    string longest="";
    //for all char in s1
    for(int i=0;i<s1.length();i++){
        int pos=s2.find(s1[i],0);
        //in case same letter different location
        while(pos!=-1){
            string temp="";
            temp+=s1[i];
            //find follow up char if different break the loop
            for(int j=pos+1;j<s2.length();j++){
                temp+=s2[j];
                int pos2=s1.find(temp,0);
                if(pos2==-1){
                    break;
                }
                else{
                    if(temp.length()>longest.length()){
                        longest=temp;
                    }
                }
            }
            pos=s2.find(s1[i],pos+1);
        }
    }
    return longest;
}

//compare two string in list and find longest substring
void list_longest_substring(list<string>& l, ostream& ostr, int& output_count){
    string length_longest="";
    list<string>::iterator itr1=l.begin();
    list<string>::iterator itr2;
    for(;itr1!=l.end();itr1++){
        itr2=itr1;
        itr2++;
        for(;itr2!=l.end();itr2++){
            string temp= list_find_substring(*itr1,*itr2);
            if(length_longest.length()<temp.length()){
                length_longest=temp;
            }
        }
    }
    output_count=1;
    ostr<<length_longest<<endl;
}


void list_test(const std::string &operation, const std::string &type,
                 std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your list like this:
  // std::list<std::string> lst;

  if(type=="string"){
      list<string> l;
      string s;
      input_count=0;
      while(istr>>s){
          l.push_back(s);
          input_count++;
      }
      if      (operation == "sort")              { list_sort                (l,ostr,output_count); }
      else if (operation == "remove_duplicates") { list_remove_duplicates   (l,ostr,output_count); }
      else if (operation == "mode")              { list_mode                (l,ostr,output_count); }
          // "closest_pair" not available for strings
      else if (operation == "first_sorted")      { list_first_sorted        (l,ostr,output_count,optional_arg); }
      else if (operation == "longest_substring") { list_longest_substring   (l,ostr,output_count); }
      else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }

  }
  else if(type=="integer"){
      // load the data into a vector of integers
      list<int> l;
      int v;
      input_count = 0;
      while (istr >> v) {
          l.push_back(v);
          input_count++;
      }
      if      (operation == "sort")              { list_sort              (l,ostr,output_count); }
      else if (operation == "remove_duplicates") { list_remove_duplicates (l,ostr,output_count); }
      else if (operation == "mode")              { list_mode              (l,ostr,output_count); }
      else if (operation == "closest_pair")      { list_closest_pair      (l,ostr,output_count); }
      else if (operation == "first_sorted")      { list_first_sorted      (l,ostr,output_count,optional_arg); }
          // "longest_substring" not available for integers
      else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
  else {
      std::cerr << "Error: DATA STRUCTURE NOT IMPLEMENTED" << std::endl;
      exit(0);
  }
}
