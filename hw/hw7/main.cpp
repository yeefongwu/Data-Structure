#include <iostream>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <utility>
using namespace std;

//costume shop map first string is the name of the costume
//the second is a pair, the first of pair is int for the num of costume available
//the second of pair is the list for customer who rent this costume and not return yet
//using list instead of vector because list do better of find and erase compare to vector
typedef map<string,pair<int,list<pair<string,string> > > >COSTUME_SHOP_TYPE;

//the people map first pair contain the last name and the first name, it goes like <last_name,first_name>
// the reason last name goes first because when sorting the map, last name came first and then first name
//the second of map is also a map, the first of pair is bool to determine whether this customer has a costumer or not
//the second of pair is the name of the costumer
typedef map<pair<string,string>,pair<bool,string> >PEOPLE_TYPE;

//sort operation for map to make smaller last name first, if same last name compare first name
bool operator< (const pair<string,string>& left, const pair<string,string>& right){
    return left.first<right.first ||
           (left.first==right.first && left.second<right.second);
}

// prototypes for the helper functions
void addCostume(COSTUME_SHOP_TYPE &costume_shop);
void rentCostume(COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people);
void lookup(COSTUME_SHOP_TYPE& costume_shop);
void printPeople(const PEOPLE_TYPE& people);

int main() {
    // two data structures store all of the information for efficiency
    COSTUME_SHOP_TYPE costume_shop;
    PEOPLE_TYPE people;
    char c;
    while (std::cin >> c) {
        if (c == 'a') {
            addCostume(costume_shop);
        } else if (c == 'r') {
            rentCostume(costume_shop,people);
        } else if (c == 'l') {
            lookup(costume_shop);
        } else if (c == 'p') {
            printPeople(people);
        } else {
            std::cerr << "error unknown char " << c << std::endl;
            exit(0);
        }
    }
}

//add costume will simply add the number of copies for costume in costume_shop map
void addCostume(COSTUME_SHOP_TYPE& costume_shop) {
    std::string costume_name;
    int num;
    std::cin >> costume_name >> num;
    costume_shop[costume_name].first+=num;
    cout << "Added " << num;
    cout << " "<<costume_name;
    if(num == 1){
        cout << " costume."<<endl;
    } else{
        cout << " costumes."<<endl;
    }

}

//rent costume will check whether the customer has the same costume,
//it will see if the costume is available or carry in the shop
//it will modify the people map and the costume map
void rentCostume(COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people) {
    std::string first_name;
    std::string last_name;
    std::string costume_name;
    std::cin >> first_name >> last_name >> costume_name;
    //in case customer has the same costume,if it does stop the function
    //also create a people in people map if it doesn't exist, but the bool for that will be false since it's not assign
    if(costume_name==people[make_pair(last_name,first_name)].second){
        cout<<first_name<<" "<<last_name<<" already has a "<<costume_name<<" costume."<<endl;
        return;
    }
    int exist;//0 for exist and available   1 for exist but not available    2 for not exist
    if(costume_shop.find(costume_name)!=costume_shop.end()){
        if(costume_shop[costume_name].first==0){exist=1;}
        else{exist=0;}
    }
    else{exist=2;}

    if(exist==0){
        //in case it costume exist and available, the customer has an old costume
        // customer will give back the old one and rent a new one
        //the number of old costume will increase and list of people rented will be increase
        //the number of new costume will decrease and list of people rented will be decrease
        //set the costume and bool as true for people under this name
        if(people[make_pair(last_name,first_name)].first==true){
            cout<<first_name<<" "<<last_name<<" returns a "<<people[make_pair(last_name,first_name)].second<<" costume before renting a "<<costume_name<<" costume."<<endl;
            //the number of old costume will increase and list of people rented will be decrease
            costume_shop[people[make_pair(last_name,first_name)].second].first+=1;
            list<pair<string,string> >::iterator l_itr=find(costume_shop[people[make_pair(last_name,first_name)].second].second.begin(),costume_shop[people[make_pair(last_name,first_name)].second].second.end(),make_pair(last_name,first_name));
            costume_shop[people[make_pair(last_name,first_name)].second].second.erase(l_itr);
            //the number of new costume will decrease and list of people rented will be increase
            costume_shop[costume_name].first-=1;
            costume_shop[costume_name].second.push_back(make_pair(last_name,first_name));
            people[make_pair(last_name,first_name)]=make_pair(true,costume_name);
        }
        else{
            //in case costume exist and available but costumer doesnt has an old costume
            cout<<first_name<<" "<<last_name<<" rents a "<<costume_name<<" costume."<<endl;
            costume_shop[costume_name].first-=1;
            costume_shop[costume_name].second.push_back(make_pair(last_name,first_name));
            people[make_pair(last_name,first_name)]=make_pair(true,costume_name);
        }

    }
    //in case costume not available
    else if(exist==1){
        cout<<"No "<<costume_name<<" costumes available."<<endl;
    }
    //in case not carry this costume
    else{
        cout<<"The shop doesn't carry "<<costume_name<<" costumes."<<endl;
    }

}



//lookup will output the information of the specific costume
//if there are customer rented, output their name in order of old to new
void lookup(COSTUME_SHOP_TYPE& costume_shop) {
    std::string costume_name;
    std::cin >> costume_name;
    if(costume_shop.find(costume_name)!=costume_shop.end()){
        cout<<"Shop info for "<<costume_name<<" costumes:"<<endl;
        if(costume_shop[costume_name].first>0) {
            if (costume_shop[costume_name].first > 1) {
                cout << "  " << costume_shop[costume_name].first << " copies available" << endl;
            } else {
                cout << "  " << costume_shop[costume_name].first << " copy available" << endl;
            }
        }
        if(costume_shop[costume_name].second.size()>0) {
            if (costume_shop[costume_name].second.size() > 1) {
                cout<<"  "<<costume_shop[costume_name].second.size()<<" copies rented by:"<<endl;
            }
            else{
                cout<<"  "<<costume_shop[costume_name].second.size()<<" copy rented by:"<<endl;
            }
            for(list<pair<string,string> >::iterator l_itr=costume_shop[costume_name].second.begin();l_itr!=costume_shop[costume_name].second.end();l_itr++){
                cout<<"    "<<l_itr->second<<" "<<l_itr->first<<endl;
            }
        }
    }
    else{
        cout<<"The shop doesn't carry "<<costume_name<<" costumes."<<endl;
    }
}

//print out all people intend to rent costume and whether they have one or not
void printPeople(const PEOPLE_TYPE& people) {
    if(people.size()==1){
        cout << "Costume info for the " << people.size() << " party attendee:" << endl;
    }
    else{cout << "Costume info for the " << people.size() << " party attendees:" << endl;}

    for(PEOPLE_TYPE::const_iterator p_itr=people.begin();p_itr!=people.end();p_itr++){
        //in case they have one
        if(p_itr->second.first){
            cout<<"  "<<p_itr->first.second<<" "<<p_itr->first.first<<" is wearing a "<<p_itr->second.second<<" costume."<<endl;
        }
        //in case they don't have one
        else{
            cout<<"  "<<p_itr->first.second<<" "<<p_itr->first.first<<" does not have a costume."<<endl;
        }
    }

}
