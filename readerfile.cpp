//
// Created by Yanka Deshkovski on 12/3/24.
//
#include "readerfile.h"

using namespace std;

vector<City> readFromCSV(string fileName) {
    vector<City> cities;
    ifstream file;
    file.open(fileName);

    if (!file.is_open())
    {
        cout << "File not opened" << endl;
        perror("Error");
        cout << "Error code: " << errno << ", " << strerror(errno) << endl;
        return cities;
    }

    string line;
    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);
        City place = City();
        string temp;

        getline(ss, temp, ','), place.setCityID(stoi(temp));
        getline(ss, temp, ','), place.setCityName(temp);
        getline(ss, temp, ','), place.setStateName(temp);
        getline(ss, temp, ','), place.setPopulation(stoi(temp));
        getline(ss, temp, ','), place.setElevation(stoi(temp));
        getline(ss, temp, ','), place.setLongitude(stod(temp));
        getline(ss, temp, ','); place.setLatitude(stod(temp));
        getline(ss, temp, ','); place.setTimezone(stoi(temp));

        cities.push_back(place);
    }
    file.close();
    return cities;
}

