#ifndef CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
#define CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Person{
    int type;
    int line, seatNumber;
    int type3LastOperation;

    Person(int type,int line,int seatNumber,int type3LastOperation){
        this->type = type;
        this->line = line;
        this->seatNumber = seatNumber;
        this->type3LastOperation = type3LastOperation;
    }
};

class SeatOperations{

private:
    vector<Person *> lines[2];
    int N, M;

public:
    SeatOperations(int N, int M);
    void addNewPerson(int personType, const string& ticketInfo);
    void printAllSeats(ofstream& outFile);
    void changeSeat(Person *person,int line,int place);
    vector<int> findNewPlace(Person *person,int line,int position);

    // YOU CAN ADD YOUR HELPER FUNCTIONS

};

#endif //CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
