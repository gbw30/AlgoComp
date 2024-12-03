//
// Created by Gabriel Wong Chong on 12/3/2024.
//

#include <iostream>
#include "City.h"
#include "readerfile.h"

#include <string>
#include <iostream>

using namespace std;

int main()
{
    vector<City> cities = readFromCSV("../city1.txt");
    for (int i = 0; i < cities.size() / 1000; i++)
        cout << cities[i].getCityName() << endl;
}