//
// Created by Yanka Deshkovski on 12/3/24.
//

#include "city.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<City> readFromCSV(string fileName)
{
    vector<City> cities;
    ifstream file(fileName);

    if (!file.is_open())
        cout << "File not opened!" << endl;

    return cities;
}

