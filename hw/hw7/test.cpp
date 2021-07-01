//
// Created by yeefongwu on 3/29/21.
//

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <utility>
using namespace std;

typedef map<pair<string,string>,pair<bool,string> >PEOPLE_TYPE;
int main(){
    PEOPLE_TYPE p;
    p[make_pair("jon","dam")];
    cout<<p[make_pair("jon","dam")].first;
}