//
// Created by Gabriel Wong Chong on 12/4/2024.
//

#ifndef ALGOCOMP_BINARYSEARCH_H
#define ALGOCOMP_BINARYSEARCH_H

#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include "City.h"
#include <utility> // For pair

using namespace std;

// Binary search function
template <typename T>
int binarySearch(const vector<City>& cities, T value, function<T(const City&)> getAttribute) {
    int left = 0;
    int right = cities.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        T midValue = getAttribute(cities[mid]);
        if (midValue == value) {
            return mid; // Found the value
        } else if (midValue < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Not found
}

// Binary search function to find the first and last occurrence of a value
template <typename T>
pair<int, int> binarySearchRange(
        const vector<City>& cities,
        T value,
        function<T(const City&)> getAttribute)
{
    int first = -1;
    int last = -1;
    int left = 0;
    int right = cities.size() - 1;
    // Find the first occurrence
    while (left <= right){
        int mid = left + (right - left) / 2;
        T midValue = getAttribute(cities[mid]);
        if (midValue == value) {
            first = mid;
            right = mid - 1; // Continue searching in the left half
        } else if (midValue < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    // Reset search range
    left = 0;
    right = cities.size() - 1;
    // Find the last occurrence
    while (left <= right){
        int mid = left + (right - left) / 2;
        T midValue = getAttribute(cities[mid]);
        if (midValue == value){
            last = mid;
            left = mid + 1; // Continue searching in the right half
        } else if (midValue < value){
            left = mid + 1;
        } else{
            right = mid - 1;
        }
    }

    return {first, last}; // Return the indices of the first and last occurrences
}



#endif //ALGOCOMP_BINARYSEARCH_H
