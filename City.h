#pragma once

#include "string"
using namespace std;

struct City {
private:
    // Attributes
    unsigned int cityID;
    string cityName;
    string stateName;
    float latitude;
    float longitude;
    unsigned int elevation;
    unsigned int population;
    unsigned int timezone;

public:
    // Constructor
    City(unsigned int ID, const string& cityN, const string& stateN, float lat, float lon, unsigned int elev, unsigned int pop,
        unsigned int tz);

    // Getters
    unsigned int getCityID() const;

    string getCityName() const;

    string getStateName() const;

    float getLatitude() const;

    float getLongitude() const;

    unsigned int getElevation() const;

    unsigned int getPopulation() const;

    unsigned int getTimezone() const;
};
