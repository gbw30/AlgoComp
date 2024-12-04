#ifndef ALGOCOMP_BINARYSEARCH_H
#define ALGOCOMP_BINARYSEARCH_H

#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include "City.h"
#include <utility>

using namespace std;

template <typename T>
pair<int, int> binarySearchClosestUpper(const vector<City>& cities, T value, function<T(const City&)> getAttribute) {
    int n = cities.size();
    int left = 0, right = n - 1;
    int closestUpper = -1;

    // Binary search to find the closest upper or exact value
    while (left <= right) {
        int mid = left + (right - left) / 2;
        T midValue = getAttribute(cities[mid]);

        if (midValue >= value) {
            closestUpper = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (closestUpper == -1) {
        // No upper value exists (x is larger than all elements)
        return {-1, -1};
    }

    // Find the range of the closest upper value
    auto closestValue = getAttribute(cities[closestUpper]);
    T first = closestUpper, last = closestUpper;

    // Expand to find the first occurrence
    while (first > 0 && getAttribute(cities[first - 1]) == closestValue) {
        --first;
    }

    // Expand to find the last occurrence
    while (last < n - 1 && getAttribute(cities[last + 1]) == closestValue) {
        ++last;
    }

    return {first, last};
}

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

// Binary search for a range of names starting with a specific prefix
pair<int, int> binarySearchByPrefix(
        const vector<City>& cities,
        char prefix,
        function<string(const City&)> getAttribute)
{
    int first = -1;
    int last = -1;
    int left = 0;
    int right = cities.size() - 1;
    string prefixStr(1, prefix); // Convert char to string for comparison
    // Find the first occurrence
    while (left <= right){
        int mid = left + (right - left) / 2;
        string midValue = getAttribute(cities[mid]);
        if (midValue.substr(0, 1) == prefixStr){
            first = mid;
            right = mid - 1; // Continue searching in the left half
        } else if (midValue < prefixStr){
            left = mid + 1;
        } else{
            right = mid - 1;
        }
    }
    // Reset search range
    left = 0;
    right = cities.size() - 1;

    // Find the last occurrence
    while (left <= right) {
        int mid = left + (right - left) / 2;
        string midValue = getAttribute(cities[mid]);

        if (midValue.substr(0, 1) == prefixStr) {
            last = mid;
            left = mid + 1; // Continue searching in the right half
        } else if (midValue < prefixStr) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return {first, last}; // Return the indices of the first and last occurrences
}

#endif //ALGOCOMP_BINARYSEARCH_H
