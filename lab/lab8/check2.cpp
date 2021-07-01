#include <map>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){
    ifstream istr(argv[1]);
    map<int, int> nums;
    int n;
    while( istr >> n ){
        //++nums[n];
        map<int, int>::iterator itr2 = nums.find(n);
        if( itr2 == nums.end() ){
            nums.insert( make_pair(n, 1) );
        } else{
            (itr2->second)++;
        }

    }
    map<int,int>::iterator itr;
    int max=0;
    for(itr=nums.begin();itr!=nums.end();itr++){
        if(itr->second>max){
            max=itr->second;
        }
    }
    cout<<"Mode: ";
    for(itr=nums.begin();itr!=nums.end();itr++){
        if(itr->second==max){
            cout<<itr->first<<" ";
        }
    }
}