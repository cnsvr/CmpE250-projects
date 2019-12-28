/*
Student Name:
Student Number:
Project Number: 5
Compile Status: [SUCCESS/FAIL]
Running Status: [SUCCESS/FAIL]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

void parseInput(ifstream& inFile,int &  N,int &  M,vector < long long int > & prices);


int main(int argc, char* argv[]){

    // Command line arguments are malformed
    if (argc != 3) {
        // cerr should be used for errors
        cerr << "Run the code with the following command: ./cmpe250-assignment4 [input_file] [output_file]" << endl;
        return 1;
    }

    // Open the input and output files, check for failures
    ifstream inFile(argv[1]);
    if (!inFile) { // operator! is synonymous to .fail(), checking if there was a failure
        cerr << "There was a problem opening \"" << argv[1] << "\" as input file" << endl;
        return 1;
    }

    ofstream outFile(argv[2]);
    if (!outFile) {
        cerr << "There was a problem opening \"" << argv[2] << "\" as output file" << endl;
        return 1;
    }

    int maxPrices = 200000;
    int N;
    int M;
    vector<long long int> prices;

    parseInput(inFile,N,M,prices);

    long long int sortedPrices[maxPrices+1];

    for (int k = 0; k <= maxPrices; ++k) {
        sortedPrices[k] = 0;
    }

    for (int l = 0; l < N ; ++l) {
        sortedPrices[prices[l]]++;
    }

    prices.clear();
    for (int m = 0; m <= maxPrices ; ++m) {
        while(sortedPrices[m]>0){
            prices.push_back(m);
            sortedPrices[m]--;
        }
    }
    prices.insert(prices.end(),200000,0);


    if(N <= 0 || M <= 0){
        return 0;
    } else{
        long long int K[N+1];
        long long int A[N+M+1];

        K[0] = 0;



        for (int j = 1; j <= M; ++j) {
            A[j] = prices[j-1];

        }


        for (int i = 1 ; i <= N ; ++i) {

            K[i] = K[i-1] + A[i];
            A[i+M] = A[i] + prices[i+M-1];

            outFile << K[i] << " ";
        }

    }



    return 0;
}

void parseInput(ifstream& inFile,int &  N,int &  M, vector < long long int > & prices) {
    string line, tmp;
    getline(inFile, line);
    istringstream linestream(line);
    getline(linestream, tmp, ' ');
    N = stoi(tmp);
    getline(linestream, tmp, ' ');
    M = stoi(tmp);
    getline(inFile, line);
    istringstream linestream2(line);
    string price;
    while (getline(linestream2, price, ' ')) {
        prices.push_back(stoi(price));
    }
    inFile.close();
}
