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

    string line;
    getLine(file, line);

    while (getLine(file, line))
    {
        stringstream ss(line);
        City place;
        string temp;

        getline(ss, temp, ','), place.cityID = stoi(temp);
        getline(ss, place.cityName, ',');
        getline(ss, place.stateName, ',');
        getline(ss, temp, ','), place.population = stoi(temp);
        getline(ss, temp, ','), place.elevation = stoi(temp);
        getline(ss, temp, ','), place.longitude = stod(temp);
        getline(ss, temp, ','); place.latitude = stod(temp);
        getline(ss, temp, ','); place.timezone = stoi(temp);

        cities.push_back(place);
    }
    file.close();
    return cities;
}

