/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 6
*/

#include "sortingtime.h"

// default constructor
SortingTime::SortingTime() {
    arr = NULL;
    arrSize = 0;
}
// default destructor
SortingTime::~SortingTime() {
    if (arr != NULL) {
        delete [] arr;
    }
}
void SortingTime::initializeArrayFromFile(ifstream &readStream) {

    string line;
    int lineIdx = 0;

    // read array from file
    while (getline(readStream, line)) {
        if (lineIdx == 0) {
            arrSize = stoi(line);
            arr = new double[arrSize];
        }
        else {
            arr[lineIdx - 1] = stod(line);
        }
        lineIdx++;
    }
}
long SortingTime::getTime() {
    return chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
}
void SortingTime::printResult(string sortAlgorithm, long start, long end) {

    cout << "***** " << sortAlgorithm << " *****" << endl;
    cout << "Start time: " << start << " microseconds" << endl;
    cout << "End time  : " << end << " microseconds" << endl;
    cout << "Time used : " << end - start << " microseconds" << endl << endl;
}
double* SortingTime::copyArray() {
    double *tmpArr = new double[arrSize];

    for (int i = 0; i < arrSize; ++i) {
        tmpArr[i] = arr[i];
    }
    return tmpArr;
}
void SortingTime::swap(double &a, double &b) {
    double tmp = a;
    a = b;
    b = tmp;
}
void SortingTime::printArray(double *arr) {

    for (int i = 0; i < arrSize; ++i) {
        cout << arr[i];
        if (i == arrSize - 1) {
            cout << endl;
        }
        else {
            cout << ", ";
        }
    }
}
double* SortingTime::preMeasure(time_t &start) {
    double *tmpArr = copyArray();
    start = getTime();

    return tmpArr;
}
void SortingTime::postMeasure(string sortAlgorithm, double* arr, time_t &start) {

    time_t end = getTime();
    printResult(sortAlgorithm, start, end);
    delete [] arr;
}
void SortingTime::selectionSort(double *arr, int size) {
    int indexSmallest;

    for (int i = 0; i < size - 1; ++i) {
        indexSmallest = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[indexSmallest]) {
                indexSmallest = j;
            }
        }
        swap(arr[i], arr[indexSmallest]);
    }
}
void SortingTime::measureSelectionSort() {
    time_t start;
    double *tmpArr = preMeasure(start);

    selectionSort(tmpArr, arrSize);

    postMeasure("SelectionSort", tmpArr, start);
}
void SortingTime::insertionSort(double *arr, int size) {
    int j;

    for (int i = 1; i < size; ++i) {
        double temp = arr[i];
        int j = i;
        while (j > 0 && arr[j - 1] >= temp) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = temp;
    }
}
void SortingTime::measureInsertionSort() {
    time_t start;
    double *tmpArr = preMeasure(start);

    insertionSort(tmpArr, arrSize);

    postMeasure("InsertionSort", tmpArr, start);
}
int SortingTime::quickSortPartition(double *arr, int i, int k) {
    bool done = false;
    int mid = i + (k - i) / 2;
    double pivot = arr[mid];

    int l = i;
    int h = k;
    while (!done) {
        while (arr[l] < pivot) {
            ++l;
        }
        while (arr[h] > pivot) {
            --h;
        }
        if (l >= h) {
            done = true;
        }
        else {
            swap(arr[l], arr[h]);
            ++l;
            --h;
        }
    }

    return h;
}
void SortingTime::quickSort(double *arr, int i, int k) {
    int j = 0;

    if (i < k) {
        j = quickSortPartition(arr, i, k);

        quickSort(arr, i, j);
        quickSort(arr, j + 1, k);
    }
}
void SortingTime::measureQuickSort() {
    time_t start;
    double *tmpArr = preMeasure(start);

    quickSort(tmpArr, 0, arrSize - 1);

    postMeasure("QuickSort", tmpArr, start);
}
void SortingTime::merge(double *arr, int i, int j, int k) {
    int mSize = k - i + 1;
    double *mArr = new double[mSize];

    int m = 0;
    int l = i;
    int r = j + 1;

    while (l <= j && r <= k) {
        if (arr[l] <= arr[r]) {
            mArr[m] = arr[l++];
        }
        else {
            mArr[m] = arr[r++];
        }
        ++m;
    }
    while (l <= j) {
        mArr[m++] = arr[l++];
    }
    while (r <= k) {
        mArr[m++] = arr[r++];
    }
    for (int p = 0; p < mSize; ++p) {
        arr[i + p] = mArr[p];
    }

    delete [] mArr;
}
void SortingTime::mergeSort(double *arr, int i, int k) {
    int j;

    if (i < k) {
        j = (i + k) / 2;

        mergeSort(arr, i, j);
        mergeSort(arr, j + 1, k);
        merge(arr, i, j, k);
    }
}
void SortingTime::measureMergeSort() {
    time_t start;
    double *tmpArr = preMeasure(start);

    mergeSort(tmpArr, 0, arrSize - 1);

    postMeasure("MergeSort", tmpArr, start);
}
void SortingTime::bubbleSort(double *arr, int size) {

    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
void SortingTime::measureBubbleSort() {
    time_t start;
    double *tmpArr = preMeasure(start);

    bubbleSort(tmpArr, arrSize);

    postMeasure("BubbleSort", tmpArr, start);
}
void SortingTime::runSortingTimeMeasurement() {

    measureBubbleSort();
    measureSelectionSort();
    measureInsertionSort();
    measureMergeSort();
    measureQuickSort();
}
