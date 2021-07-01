#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "blackout.h"
using namespace std;

bool findWord_help(Puzzle& p, const vector<vector<char> >&grid,vector<string>&dictionary,const vector<int> require_length);
void findWord(const vector<vector<char> >&grid,const vector<string>dictionary,const vector<int>require_length,vector<Puzzle>& QualifyPuzzle);
template <class T> void all_solution(const int num_length,vector<T> one_solution,vector<T> seperated_puzzle, vector<vector<T> >& solution);
void combine(const vector<Puzzle>& QualifyPuzzle, const vector<int>& require_length, vector<vector<Puzzle> >&all_combination,const vector<vector<char> >grid);
int all_board(const vector<vector<Puzzle> > & all_combination, const vector<vector<char> >&grid,vector<vector<vector<char> > >&output_board,const vector<string> dictionary, const vector<int>require_length);
bool check_board(Puzzle& p,const vector<vector<char> >&black_out,const vector<Puzzle>&one_combination,const vector<vector<char> >&grid);
void readDic(ifstream& dic, vector<string>&dictionary);
void readGrid(ifstream& gridFile,vector<vector<char> >&grid,vector<int>&require_length);
void print(const string solution_mode, const string output_mode,const int num_of_solution, const vector<vector<vector<char> > >&output_board);

int main(int argc, char**argv){
    if(argc<5){
        cout<<"Not enough argument"<<endl;
        exit(1);
    }
    ifstream dictFile(argv[1]);
    if(!dictFile.good()){
        cout<<"unable to open "<<argv[1]<<endl;
        exit(1);
    }
    ifstream gridFile(argv[2]);
    if(!gridFile.good()){
        cout<<"unable to open "<<argv[2]<<endl;
        exit(1);
    }
    string solution_mode=argv[3];
    string output_mode=argv[4];


    vector<string> dictionary;
    vector<vector<char> >grid;
    vector<int> require_length;
    vector<Puzzle> QualifyPuzzle;
    vector<vector<Puzzle> >all_combination;
    vector<vector<vector<char> > > output_board;

    //read the dictionary store them into a string vector
    readDic(dictFile,dictionary);
    //read the grid file, store number into require length, char into 2D vector grid
    readGrid(gridFile,grid,require_length);
    //find all the word fit the require length and dictionary in grid, put them into a Puzzle vector QualifyPuzzle
    findWord(grid,dictionary,require_length,QualifyPuzzle);
    //find and combine all the possible solution from QualifyPuzzle store them into a 2D puzzle vector all_combination
    //for example there are [1,2,3], only ask two in array, combine will generate [ [1,2], [1,3], [2,3] ]
    combine(QualifyPuzzle,require_length,all_combination,grid);
    //all board will return num of solution and generate a 3D char vector store all the possible black_out board in the output_board
    int num_of_solution=all_board(all_combination,grid,output_board,dictionary,require_length);
    //print out
    print(solution_mode,output_mode,num_of_solution,output_board);

}


void readDic(ifstream& dic, vector<string>&dictionary){
    string line;
    while(dic>>line){
        dictionary.push_back(line);
    }
}


void readGrid(ifstream& gridFile,vector<vector<char> >&grid,vector<int>&require_length){
    string line;
    while(gridFile>>line){
        if(line[0]=='!'){
            continue;
        }
        else if(line[0]=='+'){
            require_length.push_back(stoi(line.substr(1,line.size()-1)));
            sort()
        }
        else{
            grid.push_back(vector<char>());
            for(int i=0;i<line.size();i++){grid.back().push_back(line[i]);}
        }
    }
}


void print(const string solution_mode, const string output_mode, int num_of_solution, const vector<vector<vector<char> > >&output_board){
    bool output_solution;//true output al solution, false only output one solution
    if(solution_mode=="all_solutions"){
        output_solution=true;
    }
    else if(solution_mode=="one_solution"){
        output_solution=false;
        num_of_solution=min(1,num_of_solution);
    }
    else{
        cout<<"No solution mode "<<solution_mode<<endl;
        exit(1);
    }

    if(output_mode=="print_boards"){
        cout<<"Numbr of solution: "<<num_of_solution<<endl;
        for(int i=0;i<output_board.size();i++){
            cout<<"Board: "<<endl;
            for(int j=0;j<output_board[i].size();j++){
                for(int k=0;k<output_board[i][j].size();k++){
                    cout<<output_board[i][j][k];
                }
                cout<<endl;
            }
        if(!output_solution){break;}
        }
    }
    else if(output_mode=="count_only"){
        cout<<"Numbr of solution: "<<num_of_solution<<endl;
    }
    else{
        cout<<"No output mode "<<output_mode<<endl;
        exit(1);
    }
}


//helper function for findWord, also a recursive function,take a Puzzle, recursively increase it
//if it exist return true, else return false,  it will stop either the dictionary is empty or the word if found
bool findWord_help(Puzzle& p, const vector<vector<char> >&grid,vector<string>&dictionary,const vector<int> require_length){
    if(dictionary.size()==0){return false;}
    //not only the word has to be in the dictionary, it also have to appear in the require_length
    if(p.word(grid)==dictionary[0] && find(require_length.begin(),require_length.end(),p.word_length())!=require_length.end()){return true;}
    p.increase();
    vector<string>::iterator itr=dictionary.begin();
    //loop through all word in dictionary, if the char of the puzzle is not the same as the one in dictionary erase the word in dictionary
    while(itr!=dictionary.end()){
        if((*itr)[p.word_length()-1]!=*(p.word(grid).rbegin())){itr=dictionary.erase(itr);}
        else{itr++;}
    }
    return findWord_help(p,grid,dictionary,require_length);
}

//find word will find all the word in grid fit the dictionary and the require length and add them in the QualifyPuzzle
void findWord(const vector<vector<char> >&grid,const vector<string>dictionary,const vector<int>require_length,vector<Puzzle>& QualifyPuzzle){
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[i].size();j++){
            //consider both side cross and down
            Puzzle cross(i,j,i,j,true);
            Puzzle down(i,j,i,j,false);
            //because dictionary will be modify in findWord_help so create a copy of them
            vector<string>dic1=dictionary;
            vector<string>dic2=dictionary;
            if(findWord_help(cross,grid,dic1,require_length)){QualifyPuzzle.push_back(cross);}
            if(findWord_help(down,grid,dic2,require_length)){QualifyPuzzle.push_back(down);}
        }
    }
}

//find and combine all the possible solution from QualifyPuzzle store them into a 2D puzzle vector all_combination
//for example there are [1,2,3], only ask two in array, combine will generate [ [1,2], [1,3], [2,3] ] in all_combination
void combine(const vector<Puzzle>& QualifyPuzzle, const vector<int>& require_length, vector<vector<Puzzle> >&all_combination,const vector<vector<char> >grid){
    vector<vector<Puzzle> > seperated_puzzle;
    //seperate the qualify puzzle by their length, same length goes into the same vector,
    // then push all into a 2D vector
    //for example if QualifyPuzzle is [blues,flees,use,ski,eke,sis], seperated puzzle will be [ [blues,flees], [use,ski,eke,sis] ]
    for(int i=0;i<QualifyPuzzle.size();i++){
        bool exist=false;
        //find it the length already exist or not, if exist push back the word in that vector
        for(int j=0;j<seperated_puzzle.size();j++){
            if(seperated_puzzle[j][0].word_length()==QualifyPuzzle[i].word_length()){
                exist=true;
                seperated_puzzle[j].push_back(QualifyPuzzle[i]);
            }
        }
        //if not exist add one vector in the seperated_puzzle and push the Puzzle in that vector
        if(!exist){
            seperated_puzzle.push_back(vector<Puzzle>());
            seperated_puzzle.back().push_back(QualifyPuzzle[i]);
        }
    }

    //find all possible combination for Qualify puzzle
    for(int i=0;i<seperated_puzzle.size();i++){
        //for specific length of word how many of them are allowed according to require length
        int num_length=0;
        for(int j=0;j<require_length.size();j++){
            if(require_length[j]==seperated_puzzle[i][0].word_length()){num_length+=1;}
        }
        //contain all possible solution
        vector<vector<Puzzle> > solution;
        all_solution(num_length,vector<Puzzle>(),seperated_puzzle[i],solution);

        //if all_combination is empty
        if(all_combination.size()==0){
            for(int j=0;j<solution.size();j++){all_combination.push_back(solution[j]);}
        }
        //if its not empty pair each one
        else{
            vector<vector<Puzzle> > temp_combination;
            for(int j=0;j<all_combination.size();j++){
                for(int k=0;k<solution.size();k++){temp_combination.push_back(all_combination[j]);}
            }
            int x=0;
            for(int j=0;j<temp_combination.size();j++){
                if(x==solution.size()){x=0;}
                for(int k=0;k<solution[x].size();k++){
                    temp_combination[j].push_back(solution[x][k]);
                }
                x+=1;
            }
            all_combination=temp_combination;
        }
    }
}

//all solution is also a recursive function it will modify the 2D vector solution with all possible combination
//it will stop either it reachs the limit number, or the seperated_puzzle is empty
//use template because sometimes it can be a 2D vector
template <class T>
void all_solution(const int num_length,vector<T> one_solution,vector<T> seperated_puzzle, vector<vector<T> >& solution){
    if(one_solution.size()==num_length){solution.push_back(one_solution);return;}
    else if(seperated_puzzle.empty()){return;}

    typename vector<T>::iterator itr=seperated_puzzle.begin();
    vector<T> temp = one_solution;
    while(itr!=seperated_puzzle.end()){
        one_solution=temp;
        one_solution.push_back(*itr);
        itr=seperated_puzzle.erase(itr);
        all_solution(num_length,one_solution,seperated_puzzle,solution);
    }
}

//all board will return the number of board and generate a 3D vector output_board contain all possible board output
int all_board(const vector<vector<Puzzle> > & all_combination, const vector<vector<char> >&grid,vector<vector<vector<char> > >&output_board,const vector<string> dictionary, const vector<int>require_length){
    //black out board for each combination
    vector<vector<char> > black_out;
    for(int i=0;i<all_combination.size();i++){
        black_out.clear();
        //create a board fill with #
        for(int j=0;j<grid.size();j++){
        black_out.push_back(vector<char>(grid[0].size(),'#'));
        }
        //chang ethe # with char if there is a word in their
        for(int j=0;j<all_combination[i].size();j++){
            Puzzle temp=all_combination[i][j];
            if(temp.cross()){
                for(int k=0;k<temp.word(grid).size();k++){
                    black_out[temp.get_x1()][temp.get_y1()+k]=temp.word(grid)[k];
                }
            }
            else{
                for(int k=0;k<temp.word(grid).size();k++){
                    black_out[temp.get_x1()+k][temp.get_y1()]=temp.word(grid)[k];
                }
            }
        }
        //determine whether this board work or not
        bool work=true;

        //first use the find word function to find out how many word can be found in the black out board
        //if the number of word found is not the same as required turn work into false and stop this loop
        //this is sometimes faster and more direct than using the next method,
        // for example when find out the blackout_dict1 with blackout_1,
        //we can see if go with sis, there will be more word found than required
        vector<Puzzle> tempPuzzle;
        vector<string> tempDic=dictionary;
        findWord(black_out,tempDic,require_length,tempPuzzle);
        if(tempPuzzle.size()!=require_length.size()){work=false;continue;}

        //another way to find out if the black out board works or not, by calling check_board
        //it will loop through all location in black out board, to see if the word can be found
        //fit the require length and possible generate a new word
        //if the new word can't be found break the loop and turn work into false
        for(int j=0;j<black_out.size();j++){
            for(int k=0;k<black_out[0].size();k++){
                if(black_out[j][k]=='#'){continue;}
                if(k==0 || black_out[j][k-1]=='#'){
                    Puzzle cross(j,k,j,k,true);
                    if(!check_board(cross,black_out,all_combination[i],grid)){work=false;}
                    if(!work){break;}
                }
                if(j==0 || black_out[j-1][k]=='#'){
                    Puzzle down(j,k,j,k,false);
                    if(!check_board(down,black_out,all_combination[i],grid)){work=false;}
                    if(!work){break;}
                }
            }
            if(!work){break;}
        }

        if(work){output_board.push_back(black_out);}
    }
    return output_board.size();
}


//recursive function increase the puzzle everytime
//it will stop either it reach a # or hit the edge
// when it stop check the board to see if word in the combination or not
// if it does return false, else return true
//or in case it's just one char that's also acceptable
//all three implementation for if statement are same
//i seperate them to make it clear for the situation
// 1)  corss word hit the edge
// 2)  down word hit the edge
// 3)  all word reach the #
bool check_board(Puzzle& p,const vector<vector<char> >&black_out,const vector<Puzzle>&one_combination,const vector<vector<char> >&grid){
    p.increase();
    if(p.cross()&&p.get_y2()==black_out[0].size()){
        for(int i=0;i<one_combination.size();i++)
        {
            if(p.word(grid)==one_combination[i].word(grid)){return true;}
        }
        if(p.word_length()==1){return true;}
        return false;
    }
    if(!p.cross()&&p.get_x2()==black_out.size()){
        for(int i=0;i<one_combination.size();i++)
        {
            if(p.word(grid)==one_combination[i].word(grid)){return true;}
        }
        if(p.word_length()==1){return true;}
        return false;
    }
    if(black_out[p.get_x2()][p.get_y2()]=='#'){
        for(int i=0;i<one_combination.size();i++)
        {
            if(p.word(grid)==one_combination[i].word(grid)){return true;}
        }
        if(p.word_length()==1){return true;}
        return false;
    }
    return check_board(p,black_out,one_combination,grid);
}
