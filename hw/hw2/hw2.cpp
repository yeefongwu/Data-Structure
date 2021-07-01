#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include<algorithm>
#include "player.h"

using namespace std;

int main(int argc,char** argv) {
if(argc!=4){
    cout<<"Not enough arguments value.";
    exit(1);
}
ifstream inf(argv[1]);
if(!inf.good())
{
    cout<<"Can't open "<<argv[1]<<" to read.";
    exit(1);
}
ofstream ouf(argv[2]);
if(!ouf.good())
{
    cout<<"Can't open "<<argv[2]<<" to write.";
    exit(1);
}
string mode(argv[3]);
if (!(mode=="custom" || mode=="standard"))
{
    cout<<"Wrong mode.";
    exit(1);
}

vector <Player> players;
Player one_player;
//read
while (one_player.read(inf)) {
    players.push_back(one_player);
}

//set max length for name
int max_l=0;
for(int i=0;i<players.size();i++){
    string name=players[i].first()+" "+players[i].last();
    int temp_l=name.size();
    max_l=max(max_l,temp_l);
}
//sort by name
std::sort(players.begin(),players.end(),name_alphabet);
//output form
for(int i=0;i<players.size();i++){
players[i].getFrame_in_round();
players[i].print_form(max_l,ouf);}
string bottom(max_l+66,'-');
ouf<<bottom<<"\n"<<endl;

//choose mode
if(mode=="standard") {
    std::sort(players.begin(), players.end(), score_sort);
    for (int i = 0; i < players.size(); i++) {
        string name = players[i].first() + " " + players[i].last();
        ouf << setw(max_l+2) << left << name;
        ouf << setw(3) << right << players[i].getFinal_score() << endl;
    }
}
if(mode=="custom"){
    std::sort(players.begin(),players.end(),plain_sort);
    for (int i = 0; i < players.size(); i++) {
        string name = players[i].first() + " " + players[i].last();
        ouf << setw(max_l+2) << left << name;
        ouf << setw(3) << right << players[i].getPlain_score() << endl;
    }
}

}

