#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <map>

using namespace std;

//hash function from http://www.partow.net/programming/hashfunctions/
int hash_function(const string& key, const int& size);
//hash table is used to set up the table with genome and kmer
void hash_table(vector<pair<string,vector<int> > >& genome_data, const string& genome, const int& kmer, const float& occupancy, int& table_size);
//query is used to find the query
void query(int& mismatch, string& sequence, vector<pair<string,vector<int> > >& genome_data, const string& genome, const int& kmer,const int& table_size);
//rehash is used to resize the hash table
void rehash(int& table_size, vector<pair<string,vector<int> > >& genome_data);

int main(){
    int table_size=100;
    float occupancy=0.5;
    string genome="";
    int kmer=0;
    string temp;
    //genome_data is a vector with pair,in the pair the first one is the sequence of genome, the vector with int is consist of the location of that sequence
    vector<pair<string,vector<int> > > genome_data;
    while(cin>>temp){
        if(temp=="genome"){
            cin>>temp;
            ifstream genome_file(temp);
            if(!genome_file.good()){
                cerr<<"Can't open "<<temp<<endl;
                exit(1);
            }
            while(genome_file>>temp){
                genome+=temp;
            }
        }
        else if(temp=="table_size"){
            cin>>temp;
            table_size= stoi(temp);
        }
        else if(temp=="occupancy"){
            cin>>temp;
            occupancy=stof(temp);
        }
        else if(temp=="kmer"){
            cin>>temp;
            kmer=stoi(temp);
            hash_table(genome_data,genome,kmer,occupancy,table_size);
        }
        else if(temp=="query"){
            int mismatch;
            cin>>mismatch>>temp;
            cout<<"Query: "<<temp<<endl;
            query(mismatch,temp,genome_data,genome,kmer,table_size);
        }
        else if(temp=="quit"){
            exit(1);
        }
        else{
            cout<<"command "<<temp<<" is not a valid command."<<endl;
        }
    }
}

//this function is from lecture 20
int hash_function(const string& key, const int& size){
    unsigned int value = 0;
    for (unsigned int i=0; i<key.size(); ++i)
        value = value*8 + key[i];  // conversion to int is automatic
    return value % size;
}

//hash table build the table distribute the genome according to the kmer length
void hash_table(vector<pair<string,vector<int> > >& genome_data, const string& genome, const int& kmer, const float& occupancy, int& table_size) {
    //for each genome_data given it an empty string and an empty vector
    for(int i=0;i<table_size;i++){
        vector<int> temp;
        genome_data.push_back(make_pair(" ",temp));
    }
    //for each sequence
    int unique_key=0;//if sequence have same name different location they are not counted as unique
    for (int i = 0; i < genome.length() - kmer + 1; i++) {
        string genome_sequence(genome, i, kmer);
        int hash = hash_function(genome_sequence, table_size);
        //when this slot is empty
        if (genome_data[hash].first == " ") {
            genome_data[hash].first = genome_sequence;
            genome_data[hash].second.push_back(i);
            unique_key+=1;
        //when this place has same sequence already just store the location
        } else if (genome_data[hash].first == genome_sequence) {
            genome_data[hash].second.push_back(i);
        //when the place is taken but not the same as sequence
        } else {
            //find an empty slot
            while (genome_data[hash].first != " ") {
                hash = (hash + 1) % table_size;
                //if the slot meet collision move to other slot, this will find that slot
                if(genome_data[hash].first==genome_sequence){unique_key-=1;break;}
            }
            unique_key+=1;
            genome_data[hash].first = genome_sequence;
            genome_data[hash].second.push_back(i);
        }
        float temp=(float)unique_key/table_size;
        if(temp>=occupancy){
            table_size=table_size*2;
            rehash(table_size,genome_data);
        }
    }
}

//rehash will double the table size and create a new table and put all data from previous table in it
void rehash(int& table_size, vector<pair<string,vector<int> > >& genome_data){
    vector<pair<string,vector<int> > > new_genome_table;
    for(int i=0;i<table_size;i++){
        vector<int> temp;
        new_genome_table.push_back(make_pair(" ",temp));
    }
    //for each sequence in genome_data
    for(int i=0;i<genome_data.size();i++){
        //if it's not empty
        if(genome_data[i].first!=" "){
            string temp=genome_data[i].first;
            int hash= hash_function(temp,table_size);
            while(new_genome_table[hash].first!=" "){
                hash=(hash+1)%table_size;
            }
            new_genome_table[hash]=genome_data[i];
        }
    }
    genome_data=new_genome_table;
}

//query will find the query and determine by the number of mismatch whether its valid or not
void query(int& mismatch, string& sequence, vector<pair<string,vector<int> > >& genome_data, const string& genome, const int& kmer,const int& table_size){
    string kmer_sequence(sequence,0,kmer);
    int hash= hash_function(kmer_sequence,table_size);
    //output store all possible query
    vector<pair<int,pair<int,string> > > output;
    int loop_through=0;
    //find the query
    while(genome_data[hash].first!=kmer_sequence){
        loop_through+=1;
        hash=(hash+1)%table_size;
        //if it doesnt exist
        if(loop_through==genome_data.size()){
            break;
        }
    }
    //find the query and loop through all the location it appears
    for(int i=0;i<genome_data[hash].second.size();i++){
        string found(genome,genome_data[hash].second[i],sequence.length());
        int different_letter=0;
        //find out different letters
        for(int j=0;j<sequence.length();j++){
            if(found[j]!=sequence[j]){different_letter+=1;}
        }
        //if its smaller than it will be added to output
        if(different_letter<=mismatch){
            output.push_back(make_pair(genome_data[hash].second[i], make_pair(different_letter,found)));
        }
    }
    if(output.empty()){cout<<"No Match"<<endl;}
    else{
        for(int i=0;i<output.size();i++){
            cout<<output[i].first<<" "<<output[i].second.first<<" "<<output[i].second.second<<endl;
        }
    }
}
