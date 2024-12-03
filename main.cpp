#include <iostream>
#include "City.h"
#include "readerfile.h"

#include <string>

#include "MergeSort.h"

using namespace std;

int main()
{
    vector<City> cities = readFromCSV("../test.txt");
    mergeSort(cities, 0, cities.size() - 1, compareByName);
    for (int i = 0; i < cities.size(); i++)
        cout << cities[i].getCityName() << endl;
}