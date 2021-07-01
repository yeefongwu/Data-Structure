// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cassert>
#include <iomanip>
#include "inventory.h"
#include "customer.h"
using namespace std;

// several type defs to keep things neat
// (hint, these are STL lists)
typedef list<Inventory> inventory_type;
typedef list<Customer> customers_type;
typedef list<string> preference_type;
inventory_type::iterator i_itr;
customers_type::iterator c_itr;
preference_type::iterator p_itr;



// ==================================================================

// Helper function prototypes
std::string read_customer_name(std::istream &istr);
std::string read_dvd_name(std::istream &istr);
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name);
void dvd(int copies,const string& dvd_name,inventory_type& inventory,ofstream& ostr);
void customer(int num_movies,inventory_type& inventory,customers_type& customers,const string& customer_name,ofstream& ostr,ifstream& istr);
void return_on(string token,customers_type& customers,const string& customer_name,ofstream& ostr,inventory_type& inventory);
void print_customer(const string& customer_name,customers_type& customers,ofstream& ostr);
void print_dvd(inventory_type& inventory,const string& dvd_name,ofstream& ostr);
void add_preference(const string& customer_name,const string& dvd_name,customers_type& customers, inventory_type& inventory,ofstream& ostr);

// The main algorithm for DVD distribution
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr);

// ==================================================================


void usage(const char* program_name) {
  std::cerr << "Usage: " << program_name << " <input_file> <output_file>" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --analysis" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved" << std::endl;
  std::cerr << " -or-  " << program_name << " <input_file> <output_file> --improved --analysis" << std::endl;
  exit(1);
}


int main(int argc, char* argv[]) {

    if (argc < 3 || argc > 5) {
        usage(argv[0]);
    }

    // open input and output file streams
    std::ifstream istr(argv[1]);
    if (!istr) {
        std::cerr << "ERROR: Could not open " << argv[1] << " for reading." << std::endl;
        usage(argv[0]);
    }
    std::ofstream ostr(argv[2]);
    if (!ostr) {
        std::cerr << "ERROR: Could not open " << argv[2] << " for writing." << std::endl;
        usage(argv[0]);
    }


    // stores information about the DVDs
    inventory_type inventory;
    // stores information about the customers
    customers_type customers;


    // read in and handle each of the 8 keyword tokens
    std::string token;
    while (istr >> token) {
        if (token == "dvd") {
            std::string dvd_name = read_dvd_name(istr);
            int copies;
            istr >> copies;
            dvd(copies, dvd_name, inventory, ostr);

        } else if (token == "customer") {
            std::string customer_name = read_customer_name(istr);
            int num_movies;
            istr >> num_movies;
            customer(num_movies, inventory, customers, customer_name, ostr, istr);

        } else if (token == "ship") {
            shipping_algorithm(inventory, customers, ostr);

        } else if (token == "return_oldest") {
            std::string customer_name = read_customer_name(istr);
            return_on(token, customers, customer_name, ostr, inventory);

        } else if (token == "return_newest") {
            std::string customer_name = read_customer_name(istr);
            return_on(token, customers, customer_name, ostr, inventory);

        } else if (token == "print_customer") {
            std::string customer_name = read_customer_name(istr);
            print_customer(customer_name, customers, ostr);

        } else if (token == "print_dvd") {
            std::string dvd_name = read_dvd_name(istr);
            print_dvd(inventory, dvd_name, ostr);

        } else if (token == "add_preference") {
            std::string customer_name = read_customer_name(istr);
            std::string dvd_name = read_dvd_name(istr);
            add_preference(customer_name,dvd_name,customers, inventory,ostr);
        } else {
            std::cerr << "ERROR: Unknown token " << token << std::endl;
            exit(1);
        }
    }
}



// ==================================================================


// A customer name is simply two strings, first & last name
std::string read_customer_name(std::istream &istr) {
  std::string first, last;
  istr >> first >> last;
  return first + " " + last;
}


// A movie name is one or more strings inside of double quotes
std::string read_dvd_name(std::istream &istr) {
  std::string token;
  istr >> token;
  assert (token[0] == '"');
  std::string answer = token;
  while (answer[answer.size()-1] != '"') {
    istr >> token;
    answer += " " + token;
  }
  return answer;
}


// A helper function to find a DVD from the inventory
inventory_type::iterator find_DVD(inventory_type &inventory, const std::string &dvd_name) {
    for (inventory_type::iterator inventory_itr = inventory.begin();
         inventory_itr != inventory.end(); inventory_itr++) {
        if (inventory_itr->get_name() == dvd_name) {
            return inventory_itr;
        }
    }
    // if the DVD is not found, return the .end() iterator
    return inventory.end();
}

//find if dvd exist, if exist add copies otherwise add movie into the inventory
void dvd(int copies,const string& dvd_name,inventory_type& inventory,ofstream& ostr){
    bool dvd_in_inventory=false;
    for(i_itr=inventory.begin();i_itr!=inventory.end();i_itr++){//see if dvd exist in inventory
        if(i_itr->get_name()==dvd_name){
            i_itr->copies_increase(copies);//if exist increase copies
            dvd_in_inventory=true;
        }
    }
    if(!dvd_in_inventory){inventory.push_back(Inventory(dvd_name,copies));}//if not push back in inventory
    if(copies==1){
        ostr<<copies<<" copy of "<<dvd_name<<" added"<<endl;
    }
    else if(copies>1){
        ostr<<copies<<" copies of "<<dvd_name<<" added"<<endl;
    }
}

//find if customer exist, if exist check if there is duplicate or movie doesnt exist in inventory for preference list
void customer(int num_movies,inventory_type& inventory,customers_type& customers,const string& customer_name,ofstream& ostr,ifstream& istr){
    for(c_itr=customers.begin();c_itr!=customers.end();c_itr++){//check customer exist
        if(c_itr->get_name()==customer_name){
            ostr<<"WARNING: Already have a customer named "<<customer_name<<endl;
            for(int i=0;i<num_movies;i++){string dvd_name=read_dvd_name(istr);}//in case already exist read through following preference list
            return;
        }
    }
    customers.push_back(Customer(customer_name));
    for (int i = 0; i < num_movies; i++) {
        std::string dvd_name = read_dvd_name(istr);
        bool dvd_exist = false;
        customers_type::iterator temp_itr;
        for (i_itr = inventory.begin(); i_itr != inventory.end(); i_itr++) {
            if (i_itr->get_name() == dvd_name) {//check dvd exist in inventory
                dvd_exist = true;
            }
        }
        if (dvd_exist) {//exist in inventory
            for (c_itr = customers.begin(); c_itr != customers.end(); c_itr++) {
                if (c_itr->get_name() == customer_name) {
                    temp_itr = c_itr;
                }
            }
            bool duplicate = false;
            preference_type customer_preference = temp_itr->get_preferences();
            for (p_itr = customer_preference.begin(); p_itr != customer_preference.end(); p_itr++) {
                if (*p_itr == dvd_name) {//if duplicate in preference list
                    duplicate = true;
                    ostr << "WARNING: Duplicate movie " << dvd_name << " on preference list!" << endl;
                }
            }
            if (!duplicate) { temp_itr->preference_list_pushback(dvd_name); }//if not duplicate
        } else {//not exist in inventory
            ostr << "WARNING: No movie named " << dvd_name << " in the inventory" << endl;
        }
    }
    ostr<<"new customer: "<<customer_name<<endl;
}


//check customer exist, movie exist, then return
//put return new and return old into one function as they are similar exist the return_both function
//return_both function take the 'token' to determine if pop_front or pop_back
void return_on(string token,customers_type& customers,const string& customer_name,ofstream& ostr,inventory_type& inventory){
    bool customer_exist=false;
    customers_type::iterator temp_itr;
    for(c_itr=customers.begin();c_itr!=customers.end();c_itr++){
        if(c_itr->get_name()==customer_name){
            temp_itr=c_itr;
            customer_exist=true;
        }
    }
    if(!customer_exist){ostr<<"WARNING: No customer named "<<customer_name<<endl;}
    else {
        if(temp_itr->get_hold_number()!=0){
            string temp_string=temp_itr->return_both(token);//the return both function take the "token" to determine if return the newest or oldest
            ostr<<customer_name<<" returns "<<temp_string<<endl;
            bool dvd_in_inventory=false;
            for(i_itr=inventory.begin();i_itr!=inventory.end();i_itr++){
                if(i_itr->get_name()==temp_string){//if already has copy in inventory
                    i_itr->returned();//increase copies available in inventory
                    dvd_in_inventory=true;
                }
            }
            if(!dvd_in_inventory){//no copie in inventory
                inventory.push_back(Inventory(temp_string,1));
            }
        }
        else{ostr<<"WARNING: "<<customer_name<<" has no DVDs to return!"<<endl;}
    }
}

//check if customer exist, check the hold list and the preference list for customer
void print_customer(const string& customer_name,customers_type& customers,ofstream& ostr){
    bool customer_exist=false;
    customers_type::iterator temp_itr;
    for(c_itr=customers.begin();c_itr!=customers.end();c_itr++){
        if(c_itr->get_name()==customer_name){
            temp_itr=c_itr;
            customer_exist=true;
        }
    }
    if(!customer_exist){ostr<<"WARNING: No customer named "<<customer_name<<endl;}
    if(customer_exist){
        preference_type hold=temp_itr->get_hold();
        if(hold.empty()){ostr<<customer_name<<" has no movies"<<endl;}
        else {
            if (hold.size() == 1) { ostr << customer_name << " has 1 movie:" << endl; }
            else if (hold.size() > 1) { ostr << customer_name << " has " << hold.size() << " movies:" << endl; }
            for(p_itr=hold.begin();p_itr!=hold.end();p_itr++){
                ostr<<"    "<<*p_itr<<endl;
            }
        }
        preference_type preference=temp_itr->get_preferences();
        if(!preference.empty()){
            ostr<<"  preference list:"<<endl;
            for(p_itr=preference.begin();p_itr!=preference.end();p_itr++){
                ostr<<"    "<<*p_itr<<endl;
            }
        }
    }
}


//check dvd exist, print out checked out and available
void print_dvd(inventory_type& inventory,const string& dvd_name,ofstream& ostr){
    bool dvd_in_inventory=false;
    inventory_type::iterator temp_itr;
    for(i_itr=inventory.begin();i_itr!=inventory.end();i_itr++){
        if(i_itr->get_name()==dvd_name){
            temp_itr=i_itr;
            dvd_in_inventory= true;
        }
    }
    if(!dvd_in_inventory){ostr<<"WARNING: No movie named "<<dvd_name<<" in the inventory"<<endl;}
    else{
        ostr<<dvd_name<<":"<<endl;
        if(temp_itr->get_sent()==0){//no check out
            if(temp_itr->get_copies()==1){ostr<<"  1 copy available"<<endl;}//one in stock
            else{ostr<<setw(3)<<temp_itr->get_copies()<<" copies available"<<endl;}//more than one in stock
        }
        else if(temp_itr->get_sent()==1){//one check out
            if(temp_itr->get_copies()==0){ostr<<"  1 copy checked out"<<endl;}
            else if(temp_itr->get_copies()==1){ostr<<"  1 copy checked out and 1 copy available"<<endl;}
            else{ostr<<"  1 copy checked out and "<<temp_itr->get_copies()<<" copies available"<<endl;}
        }
        else{//more than one check out
            if(temp_itr->get_copies()==0){ostr<<setw(3)<<temp_itr->get_sent()<<" copies checked out"<<endl;}
            else if(temp_itr->get_copies()==1){ostr<<setw(3)<<temp_itr->get_sent()<<" copies checked out and 1 copy available"<<endl;}
            else{ostr<<setw(3)<<temp_itr->get_sent()<<" copies checked out and "<<temp_itr->get_copies()<<" copies available"<<endl;}
        }
    }
}

//add preference, first check if customer and movie exist then check if there is duplicate then add to preference list
void add_preference(const string& customer_name,const string& dvd_name,customers_type& customers, inventory_type& inventory,ofstream& ostr){
     bool customer_exist=false;
     bool dvd_in_inventory=false;
     bool duplicate=false;
     customers_type::iterator temp_itr;
     for(c_itr=customers.begin();c_itr!=customers.end();c_itr++){
         if(c_itr->get_name()==customer_name){
             customer_exist=true;
             temp_itr=c_itr;
         }
     }
     if(!customer_exist){ostr<<"WARNING: No customer named "<<customer_name<<endl;}//customer not exist
     else{//customer exist
         for (i_itr = inventory.begin(); i_itr != inventory.end(); i_itr++) {//check if movie exist
             if (i_itr->get_name() == dvd_name) {
                 dvd_in_inventory = true;
             }
         }
         if(!dvd_in_inventory){ostr<<"WARNING: No movie named "<<dvd_name<<" in the inventory"<<endl;}//movie not exist
         else{//movie exist
            for(p_itr=temp_itr->get_preferences().begin();p_itr!=temp_itr->get_preferences().end();p_itr++){//duplicate in preference list
                if(*p_itr==dvd_name){
                    ostr<<"WARNING: "<<customer_name<<" already has "<<dvd_name<<" on his/her preference list!"<<endl;
                    duplicate=true;
                }
            }
             for(p_itr=temp_itr->get_hold().begin();p_itr!=temp_itr->get_hold().end();p_itr++){//duplicate in hold list
                 if(*p_itr==dvd_name){
                     ostr << "WARNING: " << customer_name << " currently has " << dvd_name << "!"<<endl;
                     duplicate=true;
                 }
             }
             if(!duplicate){temp_itr->preference_list_pushback(dvd_name);}//if not add into preference list
         }
     }
}



// ==================================================================

//
// A basic algorithm for determining which movies to ship to each customer
//
void shipping_algorithm(inventory_type &inventory, customers_type &customers, std::ostream &ostr) {


  ostr << "Ship DVDs" << std::endl;

  // Loop over the customers in priority order
  //
  // Note that we edit the customers list as we go, to add customers
  // to the back of the list if they receive a DVD.  This allows a
  // customer to receive multiple DVDs in one shipment cycle, but only
  // after all other customers have had a chance to receive DVDs.
  //
  customers_type::iterator customer_itr = customers.begin();
  while (customer_itr != customers.end()) {

    // skip this customer if they already have 3 movies or if their
    // preference list is empty (no outstanding requests)
    if (customer_itr->has_max_num_movies() || customer_itr->preference_list_empty()) {
      // move on to the next customer
      customer_itr++;
      continue;
    }

    // a helper flag variable
    bool sent_dvd = false;
 
    // loop over the customer's preferences
    const preference_type &preferences = customer_itr->get_preferences();
    for (preference_type::const_iterator preferences_itr = preferences.begin(); 
         preferences_itr != preferences.end(); preferences_itr++) {

      // locate this DVD in the inventory
      inventory_type::iterator inventory_itr = find_DVD(inventory,*preferences_itr);
      if (inventory_itr != inventory.end() && inventory_itr->available()) { 

        // if the DVD is available, ship it to the customer!
        ostr << "  " << customer_itr->get_name() << " receives " << *preferences_itr << std::endl;
        inventory_itr->shipped();
        customer_itr->receives(*preferences_itr);
        
        // move this customer to the back of the priority queue
        // they will get a chance to receive another DVD, but only
        // after everyone else gets a chance
        customers.push_back(*customer_itr);
        customer_itr = customers.erase(customer_itr);

        // after setting the flag to true, leave the iteration over preferences
        sent_dvd = true;        
        break;
      }
    }

    // if no DVD was sent to this customer, then we move on to the next customer 
    // (do not change this customer's priority for tomorrow's shipment)
    if (!sent_dvd) {
      customer_itr++;
    }
  }


}

// ==================================================================
