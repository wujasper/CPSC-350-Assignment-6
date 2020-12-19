/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 6
*/

#include <iostream>
#include <fstream>
#include <chrono>
#include "fileio.h"

using namespace std;

class SortingTime {
private:
    double *arr;
    int arrSize;

    double* preMeasure(time_t &start);
    void postMeasure(string sortAlgorithm, double* arr, time_t &start);
    long getTime();
    double* copyArray();
    void printResult(string sortAlgorithm, long start, long end);
    void swap(double &a, double &b);
    int quickSortPartition(double *arr, int i, int k);
    void quickSort(double *arr, int i, int k);
    void measureQuickSort();
    void merge(double *arr, int i, int j, int k);
    void mergeSort(double *arr, int i, int k);
    void measureMergeSort();
    void selectionSort(double *arr, int size);
    void measureSelectionSort();
    void insertionSort(double *arr, int size);
    void measureInsertionSort();
    void bubbleSort(double *arr, int size);
    void measureBubbleSort();
    void printArray(double *arr);

public:
    SortingTime();
    ~SortingTime();

    void initializeArrayFromFile(ifstream &readStream);
    void runSortingTimeMeasurement();
};
