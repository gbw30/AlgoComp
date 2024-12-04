//
// Created by Gabriel Wong Chong on 12/3/2024.
//

#ifndef ALGOCOMP_QUICKSORT_H
#define ALGOCOMP_QUICKSORT_H

#include <iostream>
#include <vector>
#include <string>
#include <functional> // For std::function

#include "City.h"

using namespace std;

// Quicksort function
template <typename Comparator> // template for the different comparators
void quicksort(vector<City>& cities, int left, int right, Comparator comparator) {
    if (left >= right){return;}
    int pivotIndex = left + (right - left) / 2;
    City pivot = cities[pivotIndex];
    int i = left, j = right;
    while (i <= j) {
        while (comparator(cities[i], pivot)){i++;}
        while (comparator(pivot, cities[j])){j--;}
        if (i <= j){
            swap(cities[i], cities[j]);
            i++;
            j--;
        }
    }
    if (left < j){quicksort(cities, left, j, comparator);}
    if (i < right){quicksort(cities, i, right, comparator);}
}

// Comparator functions
// already stated in mergesort.h
//bool compareByCityID(const City& a, const City& b){
//    return a.getCityID() < b.getCityID();
//}
//
//bool compareByName(const City& a, const City& b){
//    return a.getCityName() < b.getCityName();
//}
//
//bool compareByState(const City& a, const City& b){
//    return a.getStateName() < b.getStateName();
//}
//
//bool compareByLatitude(const City& a, const City& b){
//    return a.getLatitude() < b.getLatitude();
//}
//
//bool compareByLongitude(const City& a, const City& b){
//    return a.getLongitude() < b.getLongitude();
//}
//
//bool compareByElevation(const City& a, const City& b){
//    return a.getElevation() < b.getElevation();
//}
//
//bool compareByPopulation(const City& a, const City& b){
//    return a.getPopulation() < b.getPopulation();
//}
//
//bool compareByTimezone(const City& a, const City& b){
//    return a.getTimezone() < b.getTimezone();
//}

#endif //ALGOCOMP_QUICKSORT_H
