/*
Student Name: Furkan Cansever
Student Number: 2016400348
Project Number: 2
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "RestaurantOrganizer.h"

using namespace std;

void swap(int array[],int i,int j);
int findMaxIndex(int array[],int heap[],int l,int r);

RestaurantOrganizer::RestaurantOrganizer(const vector<int>& tableCapacityInput){
    numberOfTables = tableCapacityInput.size();
    for(int i=0;i<numberOfTables;i++){
        tableCapacity[i] = tableCapacityInput[i];
        heap[i] = i;
        heapUp(i);
    }

}

/*
 * If groupSize is bigger than max table size,output will -1,
 * otherwise its table number will printed into output file.
 */

void RestaurantOrganizer::addNewGroup(int groupSize, ofstream& outFile){

    if(groupSize > tableCapacity[0]){
        outFile << -1 << endl;
    } else{
       
        tableCapacity[0] = tableCapacity[0] - groupSize;
        outFile << heap[0] << endl;
        heapDown(0);
    }

}
/*
 * Hole at given index will swap with its parent by heaping up.
 */

void RestaurantOrganizer::heapUp(int index){

    // No need heap up for root
    if(index == 0){
        return;
    }else {
            /*
            if index is even,(index/2)-1 gives parent hole index,
            otherwise (index/2) gives parent hole index.
            */
            if (index % 2 == 0) {
                if (tableCapacity[index] > tableCapacity[(index / 2) - 1]) {
                    swap(tableCapacity,index,(index/2)-1);  // Heaping up bigger value to parent hole with swapping method.
                    swap(heap,index,(index/2)-1);          // Also,swapping their table number.
                    heapUp((index / 2) - 1);                // tableCapacity[0] is biggest table and heap[0] is its own table number.
                }
            } else {
                if (tableCapacity[index] > tableCapacity[index / 2]) {
                    swap(tableCapacity,index,index/2);
                    swap(heap,index,index/2);
                    heapUp(index / 2);
                }
            }
    }
}

/*
 * Hole at given index will swap with one of its children by heaping down.
 */

void RestaurantOrganizer::heapDown(int index) {

    int l = (index * 2) + 1; // left hole
    int r = (index * 2) + 2; // right hole

    int lastIndex = (numberOfTables / 2) - 1;

    if (index > lastIndex) {      // No need heaping down and looking for holes that have no child(->>leaf/terminal nodes).
        return;
    } else {

        /*
         * Returns the value of the larger of the left or right holes and,
         * if equal, returns the one with the smallest table number.
         */

        int maxIndex = findMaxIndex(tableCapacity, heap, l, r);

        // Checks parent hole has smaller value than their children or not.
        if (tableCapacity[index] < tableCapacity[l] || tableCapacity[index] < tableCapacity[r]) {
            // If left child is bigger than parent,they swap.
            if (maxIndex == l) {
                swap(tableCapacity, index, l);
                swap(heap, index, l);
                heapDown(l);
                // If left child is bigger than parent,they swap.
            } else {
                swap(tableCapacity, index, r);
                swap(heap, index, r);
                heapDown(r);
            }

            // Checks if they have same value or not.
        } else if (tableCapacity[index] == tableCapacity[l] || tableCapacity[index] == tableCapacity[r]) {

            // In equality situation, we head bigger table number down.
            if (heap[maxIndex] < heap[index]) {
                if (maxIndex == l) {
                    swap(tableCapacity, index, l);
                    swap(heap, index, l);
                    heapDown(l);
                } else {
                    swap(tableCapacity, index, r);
                    swap(heap, index, r);
                    heapDown(r);
                }
            }

        }
    }
}

/*
 * Sorted list of remaining capacities of tables, in descending order.
 */

void RestaurantOrganizer::printSorted(ofstream& outFile){


    for (int i=0;i<numberOfTables;i++){
        int n = tableCapacity[0];
        outFile << n << " ";
        tableCapacity[0] -= n;
        heapDown(0);
    }

}

/*
 * Swap function.
 */

void swap(int array[],int i,int j){
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

/*
 * Return index of hole which have bigger value or in equality situation, smaller table number.
 */

int findMaxIndex(int array[],int heap[],int l,int r){
    if(array[l] > array[r]){
        return l ;
    } else if(array[r] > array[l]){
        return r;
    } else{
        // Heaps keeps table number.
        if(heap[l] > heap[r]){
            return r;
        } else{
            return l;
        }
    }
}

