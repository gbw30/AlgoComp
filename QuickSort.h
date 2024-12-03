#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <functional>

#include "City.h"

using namespace std;

template <typename Comparator>
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
bool compareByCityID(const City& a, const City& b){
    return a.cityID < b.cityID;
}

bool compareByName(const City& a, const City& b){
    return a.name < b.name;
}

bool compareByState(const City& a, const City& b){
    return a.state < b.state;
}

bool compareByCountry(const City& a, const City& b){
    return a.country < b.country;
}

bool compareByLatitude(const City& a, const City& b){
    return a.latitude < b.latitude;
}

bool compareByLongitude(const City& a, const City& b){
    return a.longitude < b.longitude;
}

bool compareByElevation(const City& a, const City& b){
    return a.elevation < b.elevation;
}

bool compareByPopulation(const City& a, const City& b){
    return a.population < b.population;
}

bool compareByTimezone(const City& a, const City& b){
    return a.timezone < b.timezone;
}
