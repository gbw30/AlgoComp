//
// Created by Owner on 12/3/2024.
//

#ifndef ALGOCOMP_CITY_H
#define ALGOCOMP_CITY_H

#include "string"

using namespace std;

struct City {

    // Attributes
    int cityID;
    string name;
    string state;
    string country;
    float latitude;
    float longitude;
    int elevation;
    int population;
    string timezone;

    // Constructor
    City(int id, string n, string st, string cn, float lat, float lon, int elev, int pop, string tz);
};


#endif //ALGOCOMP_CITY_H
