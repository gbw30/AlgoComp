//
// Created by Gabriel Wong Chong on 12/4/2024.
//

#ifndef ALGOCOMP_BINARYSEARCH_H
#define ALGOCOMP_BINARYSEARCH_H

#include <iostream>
#include <functional>
#include <vector>
#include <string>

// Binary search function
template <typename T>
int binarySearch(const std::vector<City>& cities, T value, std::function<T(const City&)> getAttribute) {
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


#endif //ALGOCOMP_BINARYSEARCH_H
