#pragma once

#include <vector>
#include "City.h"

template <typename Comparator>
void merge(vector<City>& cities, int left, int mid, int right, Comparator comp) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<City> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = cities[left+i];

    for (int j = 0; j < n2; j++) R[j] = cities[mid+1+j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            cities[k] = L[i];
            i++;

        } else {
            cities[k] = R[j];
            j++;
        }
    }

    while (i < n1) {
        cities[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        cities[k] = R[j];
        j++;
        k++;
    }
}

template <typename Comparator>
void mergeSort(vector<City>& cities, int left, int right, Comparator comp) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(cities, left, mid, comp);
    mergeSort(cities, mid + 1, right, comp);
    merge(cities, left, mid, right, comp);
}

bool compareByCityID(const City& a, const City& b){
    return a.getCityID() < b.getCityID();
}

bool compareByName(const City& a, const City& b){
    return a.getCityName() < b.getCityName();
}

bool compareByState(const City& a, const City& b){
    return a.getStateName() < b.getStateName();
}

bool compareByLatitude(const City& a, const City& b){
    return a.getLatitude() < b.getLatitude();
}

bool compareByLongitude(const City& a, const City& b){
    return a.getLongitude() < b.getLongitude();
}

bool compareByElevation(const City& a, const City& b){
    return a.getElevation() < b.getElevation();
}

bool compareByPopulation(const City& a, const City& b){
    return a.getPopulation() < b.getPopulation();
}

bool compareByTimezone(const City& a, const City& b) {
    return a.getTimezone() < b.getTimezone();
}

