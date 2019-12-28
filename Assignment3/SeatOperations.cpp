/*
Student Name: Furkan Cansever
Student Number: 2016400348
Project Number: 3
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: In my code,I used dynamic allocation and I don't know exactly to need this but I started like that in first
       day and I continued like that.Then, I checked and no memory leaks were found. It is working correctly.
*/
#include "SeatOperations.h"

using namespace std;

SeatOperations::SeatOperations(int N, int M){
     this->N = N;
     this->M = M;

     for (int i = 0; i <= N ; ++i) {
         auto *person = new Person(0, 0, 0, 0);
         lines[0].push_back(person);
     }

     for (int i = 0; i <= M ; ++i) {
        auto *person = new Person(0,0,0,0);
        lines[1].push_back(person);
    }
}

/*
 * Adds coming person the corresponding line.
 * If seat is empty,he/she will be seated there,otherwise
 * after coming person is seated there,the person is seated will move new proper place.
 *
 */

void SeatOperations::addNewPerson(int personType, const string& ticketInfo){
    int type  = personType;
    int line = (ticketInfo.substr(0,1)) == "A" ? 0 : 1;
    int seatNumber = (stoi)(ticketInfo.substr(1));

    auto *person = new Person(type,line,seatNumber,0);

    int mod;
    vector<int>info;
    if(person->line == 0){
        mod = (person->seatNumber % N == 0) ? N : person->seatNumber % N;
        if(lines[0][mod]->type == 0){
            delete(lines[0][mod]);
            lines[0][mod] = person;
        } else{
            Person *ptr;
            ptr = lines[0][mod];
            info = findNewPlace(ptr,0,mod);
            auto *temp = new Person(ptr->type,ptr->line,ptr->seatNumber,ptr->type3LastOperation);
            delete(ptr);
            lines[0][mod] = person;
            changeSeat(temp,info[0],info[1]);

        }
    } else{
        mod = (person->seatNumber % M == 0) ? M : person->seatNumber % M;
        if(lines[1][mod]->type == 0){
            delete(lines[1][mod]);
            lines[1][mod] = person;
        } else{
            Person *ptr;
            ptr = lines[1][mod];
            info = findNewPlace(ptr,1,mod);
            auto *temp = new Person(ptr->type,ptr->line,ptr->seatNumber,ptr->type3LastOperation);
            delete(ptr);
            lines[1][mod] = person;
            changeSeat(temp,info[0],info[1]);

        }
    }
}

/*
 * Prints all person properties on corresponding line.
 */

void SeatOperations::printAllSeats(ofstream& outFile) {
    delete (lines[0][0]);
    delete (lines[1][0]);

    for (int i = 1; i <= lines[0].size() - 1; ++i) {
        Person *person = lines[0].at(i);

        if (person->type == 0) {
            outFile << "0\n";
        } else {
            outFile << person->type << " " << ((person->line == 0) ? "A" : "B") << person->seatNumber
                    << endl;
        }
        delete person;
    }

    lines[0].clear();

    for (int j = 1; j <= lines[1].size() - 1; ++j) {
        Person *person = lines[1].at(j);

        if (person->type == 0) {
            outFile << "0\n";
        } else {
            outFile << person->type << " " << ((person->line == 0) ? "A" : "B") << person->seatNumber
                    << endl;
        }
        delete person;
    }
    lines[1].clear();
}

/*
 * Returns new line and new place of corresponding person.
 */

vector<int> SeatOperations::findNewPlace(Person *person,int line,int position){

    vector<int> info; // First num is new line and second num is new seat number.

    //LINE 0->A , LINE 1->B
    switch (person->type){
        case 1:
            if(line == 0){
                info.push_back(1);
                info.push_back((person->seatNumber%M == 0) ? M : person->seatNumber%M);
            } else{
                info.push_back(0);
                info.push_back((person->seatNumber%N) == 0 ? N : person->seatNumber%N);
            }
            break;

        case 2:
            if(position == N && line == 0){
                info.push_back(1);
                info.push_back(1);
            } else if(position == M && line == 1){
                info.push_back(0);
                info.push_back(1);
            } else{
                if(line == 0){
                    info.push_back(0);
                    info.push_back(position+1);
                } else{
                    info.push_back(1);
                    info.push_back(position+1);
                }
                break;
            }

        case 3:
            int mod;
            if(person->line == 0){
                person->type3LastOperation = person->type3LastOperation + 1;
                int seatNum = (person->seatNumber % N) == 0 ? N : person->seatNumber % N;
                mod = seatNum + (person->type3LastOperation*person->type3LastOperation);
                if(mod <= N){
                    info.push_back(0);
                    info.push_back(mod);

                } else if( mod <= N + M){
                    info.push_back(1);
                    info.push_back(mod-N);
                } else {
                    int totalSeatNum = N+M;
                    while (mod > N+M){
                        mod = mod - totalSeatNum;
                    }

                    if(mod == 0){
                        info.push_back(0);
                        info.push_back(seatNum);
                    }else if(mod <= N){
                        info.push_back(0);
                        info.push_back(mod);
                    }else{
                        info.push_back(1);
                        info.push_back(mod-(N));
                    }

                }

            } else{
                person->type3LastOperation = person->type3LastOperation + 1;
                int seatNum = (person->seatNumber % M) == 0 ? M : person->seatNumber % M;
                mod = seatNum + (person->type3LastOperation*person->type3LastOperation);
                if(mod <= M){
                    info.push_back(1);
                    info.push_back(mod);
                }else if( mod <= M + N ){
                    info.push_back(0);
                    info.push_back(mod-M);
                } else{
                        int totalSeatNum = N+M;
                        while (mod > N+M){
                            mod = mod - totalSeatNum;
                        }

                        if(mod == 0){
                            info.push_back(1);
                            info.push_back(seatNum);
                        } else if(mod <= M){
                            info.push_back(1);
                            info.push_back(mod);

                        } else{
                            info.push_back(0);
                            info.push_back(mod-M);
                        }
                }
            }

            break;
    }
    return  info;
}

/*
 * Change seat of corressonding person.
 */

void SeatOperations::changeSeat(Person *person, int line, int place) {
    if (line == 0 && lines[0][place]->seatNumber == 0) { // This expression means that seat is empty.
            delete(lines[0][place]);
            lines[0][place] = person;
            return;
    } else if (line == 1 && lines[1][place]->seatNumber == 0) {
            delete(lines[1][place]);
            lines[1][place] = person;
            return;
    } else {
            // Swap seats
            Person *previous;
            Person *temp;
            vector<int> info;
            if (line == 0) {
                previous = lines[0][place];
                info = findNewPlace(previous, 0, place);
                temp = new Person(previous->type,previous->line,previous->seatNumber,previous->type3LastOperation);
                delete (previous);
                lines[0][place] = person;
                changeSeat(temp, info[0], info[1]);
            } else {
                previous = lines[1][place];
                info = findNewPlace(previous, 1, place);
                temp = new Person(previous->type,previous->line,previous->seatNumber,previous->type3LastOperation);
                delete(previous);
                lines[1][place] = person;
                changeSeat(temp, info[0], info[1]);
            }
    }
}

