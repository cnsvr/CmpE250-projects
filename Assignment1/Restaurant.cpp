/*
Student Name: Furkan Cansever 
Student Number: 2016400348
Project Number: 1
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/

#include "Restaurant.h"

using namespace std;

void Restaurant::execute(const vector<string>& operations) {
    for (const string& op : operations){
        cout << "Operation: " << op << "\t";
        if(op == "N"){
            int i = 0;
            while (tables[i].isOccupied() && i < tables.size()){
                i++;
            }
            tables[i].occupy();
        } else if(op == "S"){
            int k = tables.size()-1;
            while (tables[k].isOccupied() && k >= 0){
                k--;
            }
            tables[k].occupy();
        } else{
            tables[stoi(op)-1].empty();
        }


        cout << "State: " << *this << endl;
    }
}

Restaurant::Restaurant(unsigned int N)
	: tables{N}
{
    cout << "-Starting- \tState: " << *this << endl;
}

ostream &operator<<(ostream &out, Restaurant &restaurant) {
    for (Table table : restaurant.tables) {
        out << table.isOccupied();
    }
	return out;
}

