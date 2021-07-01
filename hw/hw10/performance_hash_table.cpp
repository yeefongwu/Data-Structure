#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
using namespace std;

// defined in performance.cpp
void usage();

//hash is not able to sort
template<class T>
void hash_sort(unordered_map<T,pair<int,int> >um, ostream& ostr, int& output_count){
    output_count=0;
    ostr<<"X"<<endl;
}

//unorderd map save duplicate in their second's second so just loop through it and output the first
template<class T>
void hash_remove_duplicates(const unordered_map<T,pair<int,int> >um, ostream& ostr, int& output_count){
    for(int i=0;i<um.size();i++){
        for(typename unordered_map<T,pair<int,int> >::const_iterator itr=um.begin();itr!=um.end();itr++){
            if(itr->second.first==i){
                ostr<<itr->first<<endl;
                output_count+=1;
                break;
            }
        }
    }
}

//hash second's second contain number of that string or int, so find the largest one and output
template<class T>
void hash_mode(unordered_map<T,pair<int,int> >&um, ostream&ostr, int& output_count){
    output_count=1;
    int mode=0;
    for(typename unordered_map<T,pair<int,int> >::iterator itr=um.begin();itr!=um.end();itr++){
        if(itr->second.second>mode){
            mode=itr->second.second;
        }
    }
    for(typename unordered_map<T,pair<int,int> >::iterator itr=um.begin();itr!=um.end();itr++){
        if(itr->second.second==mode){
            ostr<<itr->first<<endl;
        }
    }
}

//compare every two since its not sorted and find smallest one
void hash_closest_pair(unordered_map<int,pair<int,int> >& um, ostream& ostr, int& output_count){
    output_count=2;
    int best;
    unordered_map<int,pair<int,int> >::iterator best_iterator1=um.end();
    unordered_map<int,pair<int,int> >::iterator best_iterator2=um.end();
    unordered_map<int,pair<int,int> >::iterator itr1=um.begin();
    unordered_map<int,pair<int,int> >::iterator itr2;
    for(;itr1!=um.end();itr1++){
        itr2=itr1;
        itr2++;
        for(;itr2!=um.end();itr2++){
            int diff= fabs(itr2->first-itr1->first);
            if(best_iterator1==um.end() || diff<best){
                best=diff;
                best_iterator1=itr1;
                best_iterator2=itr2;
            }
        }
    }
    ostr<<best_iterator1->first<<endl;
    ostr<<best_iterator2->first<<endl;
}

//hash sort is not possible without other data structure
template<class T>
void hash_first_sorted(unordered_map<T,pair<int,int> >& um, ostream& ostr, int& output_count, int optional_arg){
    output_count=0;
    ostr<<"X"<<endl;
}

//helper function take two string and find substring
string hash_find_substring(const string& s1, const string& s2){
    string longest="";
    //loop through char in s1
    for(int i=0;i<s1.length();i++){
        int pos=s2.find(s1[i],0);
        //for same char in different location
        while(pos!=-1){
            string temp="";
            temp+=s1[i];
            //keep adding word in s2 and compare to s1 if not the same break
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

//compare all two string and find longest one
void hash_longest_substring(unordered_map<string,pair<int,int> >& um, ostream& ostr, int& output_count){
    string length_longest="";
    unordered_map<string,pair<int,int> >::iterator itr1=um.begin();
    unordered_map<string,pair<int,int> >::iterator itr2;
    for(;itr1!=um.end();itr1++){
        itr2=itr1;
        itr2++;
        for(;itr2!=um.end();itr2++){
            string temp= hash_find_substring(itr1->first,itr2->first);
            if(length_longest.length()<temp.length()){
                length_longest=temp;
            }
        }
    }
    output_count=1;
    ostr<<length_longest<<endl;
}

void hash_table_test(const std::string &operation, const std::string &type,
                     std::istream &istr, std::ostream &ostr,
                     int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your hash table like this:
  // std::unordered_set<std::string> ht;
  // OR
  // std::unordered_map<std::string,int> ht;

    if(type=="string"){
        unordered_map<string,pair<int,int> > um;
        string mstring;
        int i=0;
        input_count=0;
        while(istr>>mstring){
            if(um.find(mstring)==um.end()){
                um.insert(make_pair(mstring, make_pair(i,1)));
                i++;
            }
            else{
                um[mstring].second+=1;
            }
            input_count++;
        }
        if      (operation == "sort")              { hash_sort                (um,ostr,output_count); }
        else if (operation == "remove_duplicates") { hash_remove_duplicates   (um,ostr,output_count); }
        else if (operation == "mode")              { hash_mode                (um,ostr,output_count); }
            // "closest_pair" not available for strings
        else if (operation == "first_sorted")      { hash_first_sorted        (um,ostr,output_count,optional_arg); }
        else if (operation == "longest_substring") { hash_longest_substring   (um,ostr,output_count); }
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }

    }
    else if(type=="integer"){
        unordered_map<int,pair<int,int> > um;
        int v;
        int i=0;
        input_count=0;
        while(istr>>v){
            if(um.find(v)==um.end()){
                um.insert(make_pair(v, make_pair(i,1)));
                i++;
            }
            else{
                um[v].second+=1;
            }
            input_count++;
        }
        if      (operation == "sort")              { hash_sort                (um,ostr,output_count); }
        else if (operation == "remove_duplicates") { hash_remove_duplicates   (um,ostr,output_count); }
        else if (operation == "mode")              { hash_mode                (um,ostr,output_count); }
        else if (operation == "closest_pair")      { hash_closest_pair        (um,ostr,output_count); }
        else if (operation == "first_sorted")      { hash_first_sorted        (um,ostr,output_count,optional_arg); }
            // "longest_substring" not available for integers
        else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }

    }
    else {
        std::cerr << "Error: DATA STRUCTURE NOT IMPLEMENTED" << std::endl;
        exit(0);
    }
}
