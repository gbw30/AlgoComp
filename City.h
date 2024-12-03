#pragma once

#include "string"
using namespace std;

struct City {
    // Attributes
    int cityID;
    string cityName;
    string stateName;
    float latitude;
    float longitude;
    int elevation;
    int population;
    string timezone;

    // Constructor
    City(int id, string n, string st, string cn, float lat, float lon, int elev, int pop, string tz);
};
