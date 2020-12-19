/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 6
*/

#include "sortingtime.h"

using namespace std;

int main(int argc, char** argv) {

    FileIo *files = new FileIo();

    // read the setup file
    if (argc != 2) {
        cout << "Missing file name" << endl;
        return -1;
    }
    if (!files->openFileForRead(argv[1])) {
        cout << "Cannot open " << argv[1] << endl;
        return -1;
    }

    //for (int i = 0; i < 1000; i++) {
        //cout << rand() % 10001 << endl;
    //}

    // instantiate sortingtime object
    SortingTime *sortingTime= new SortingTime();

    // initialize array from file
    sortingTime->initializeArrayFromFile(files->readStream);

    // run the sorting time measurement
    sortingTime->runSortingTimeMeasurement();

    files->closeFiles();

    return 0;
}
