#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

// defined in performance.cpp
void usage();

//already sorted just print out
template<class T>
void bst_sort(map<T,pair<int,int> >& m, ostream& ostr, int& output_count){
    typename map<T,pair<int,int> >::iterator itr=m.begin();
    for(;itr!=m.end();itr++){
        for(int i=0;i<itr->second.second;i++){
            ostr<<itr->first<<endl;
            output_count+=1;
        }
    }
}

//there is not duplicate so just iterate through
template<class T>
void bst_remove_duplicates(const map<T,pair<int,int> >& m, ostream& ostr, int& output_count){
    for(int i=0;i<m.size();i++){
        for(typename map<T,pair<int,int> >::const_iterator itr=m.begin();itr!=m.end();itr++){
            if(itr->second.first==i){
                ostr<<itr->first<<endl;
                output_count+=1;
                break;
            }
        }
    }
}

//the map second's second is the number of string find the largest one and out put that
template<class T>
void bst_mode(map<T,pair<int,int> >& m, ostream& ostr, int& output_count){
    int mode=0;
    output_count=1;
    for(typename map<T,pair<int,int> >::iterator itr=m.begin();itr!=m.end();itr++){
        if(itr->second.second>mode){
            mode=itr->second.second;
        }
    }
    for(typename map<T,pair<int,int> >::const_iterator itr=m.begin();itr!=m.end();itr++){
        if(itr->second.second==mode){
            ostr<<itr->first<<endl;
        }
    }
}

//because it's sorted so closest can only appear nearby, find the most close one
void bst_closest_pair(map<int,pair<int,int> >& m, ostream& ostr, int& output_count){
    output_count=2;
    int best;
    map<int,pair<int,int> >::iterator best_iterator=m.end();
    map<int,pair<int,int> >::iterator itr1=m.begin();
    map<int,pair<int,int> >::iterator itr2=m.begin();
    itr2++;
    for(;itr2!=m.end();itr2++,itr1++){
        int diff=itr2->first-itr1->first;
        if(best_iterator==m.end() || diff<best){
            best=diff;
            best_iterator=itr1;
        }
    }
    ostr<<best_iterator->first<<endl;
    best_iterator++;
    ostr<<best_iterator->first<<endl;
}


//already sorted output as require
template<class T>
void bst_first_sorted(map<T,pair<int,int> >& m, ostream& ostr, int& output_count,int optional_arg){
    assert(optional_arg>=1);
    assert((int)m.size()>=optional_arg);
    output_count=optional_arg;
    typename map<T,pair<int,int> >::iterator itr=m.begin();
    int i=0;
    bool flag=true;
    while(flag){
        for(int j=0;j<itr->second.second;j++){
            ostr<<itr->first<<endl;
            i++;
            if(i==optional_arg){flag=false;break;}
        }
        itr++;
    }
}

//helper function, input two string and find their substring
string bst_find_substring(const string& s1, const string& s2){
    string longest="";
    //loop through each character in s1
    for(int i=0;i<s1.length();i++){
        int pos=s2.find(s1[i],0);
        //if its found, in case same letter has many locations
        while(pos!=-1){
            string temp="";
            temp+=s1[i];
            //keep looping for next word if not same break it
            for(int j=pos+1;j<s2.length();j++){
                temp+=s2[j];
                int pos2=s1.find(temp,0);
                if(pos2==-1){
                    break;
                }
                else{
                    //in case this is longer than origin one
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

//compare all two letter and find longest one
void bst_longest_substring(map<string,pair<int,int> >& m, ostream& ostr, int& output_count){
    string length_longest="";
    map<string,pair<int,int> >::iterator itr1=m.begin();
    map<string,pair<int,int> >::iterator itr2;
    for(;itr1!=m.end();itr1++){
        itr2=itr1;
        itr2++;
        for(;itr2!=m.end();itr2++){
            string temp= bst_find_substring(itr1->first,itr2->first);
            if(length_longest.length()<temp.length()){
                length_longest=temp;
            }
        }
    }
    output_count=1;
    ostr<<length_longest<<endl;
}



void bst_test(const std::string &operation, const std::string &type,
              std::istream &istr, std::ostream &ostr,
              int &input_count, int &output_count, int optional_arg) {

    // HINT: For the string element type, declare your binary search tree (BST) like this:
    // std::set<std::string> st;
    // OR
    // std::map<std::string,int> mp;

    if(type=="string"){
        map<string,pair<int,int> > m;
        string mstring;
        int i=0;
        input_count=0;
        while(istr>>mstring){
            if(m.find(mstring)==m.end()){
                m.insert(make_pair(mstring, make_pair(i,1)));
                i++;
            }
            else{
                m[mstring].second+=1;
            }
            input_count++;
        }
        if      (operation == "sort")              { bst_sort                (m,ostr,output_count); }
        else if (operation == "remove_duplicates") { bst_remove_duplicates   (m,ostr,output_count); }
        else if (operation == "mode")              { bst_mode                (m,ostr,output_count); }
            // "closest_pair" not available for strings
        else if (operation == "first_sorted")      { bst_first_sorted        (m,ostr,output_count,optional_arg); }
        else if (operation == "longest_substring") { bst_longest_substring   (m,ostr,output_count); }
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }

    }
    else if(type=="integer"){
        map<int,pair<int,int> > m;
        int v;
        int i=0;
        input_count=0;
        while(istr>>v){
            if(m.find(v)==m.end()){
                m.insert(make_pair(v, make_pair(i,1)));
                i++;
            }
            else{
                m[v].second+=1;
            }
            input_count++;
        }
        if      (operation == "sort")              { bst_sort                (m,ostr,output_count); }
        else if (operation == "remove_duplicates") { bst_remove_duplicates   (m,ostr,output_count); }
        else if (operation == "mode")              { bst_mode                (m,ostr,output_count); }
        else if (operation == "closest_pair")      { bst_closest_pair        (m,ostr,output_count); }
        else if (operation == "first_sorted")      { bst_first_sorted        (m,ostr,output_count,optional_arg); }
            // "longest_substring" not available for integers
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }

    }
    else {
        std::cerr << "Error: DATA STRUCTURE NOT IMPLEMENTED" << std::endl;
        exit(0);
    }
}
