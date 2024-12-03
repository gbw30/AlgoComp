#pragma once

#include "string"
using namespace std;

struct City {
private:
    // Attributes
    int cityID;
    string cityName;
    string stateName;
    float latitude;
    float longitude;
    int elevation;
    int population;
    int timezone;

public:
    // Constructor
    City(int ID, const string& cityN, const string& stateN, float lat, float lon, int elev, int pop,
        int tz);

    City();

    // Getters
    int getCityID() const;

    string getCityName() const;

    string getStateName() const;

    float getLatitude() const;

    float getLongitude() const;

    int getElevation() const;

    int getPopulation() const;

    int getTimezone() const;

    void setCityID(int val);

    void setCityName(string name);

    void setStateName(string state);

    void setPopulation(int val);

    void setElevation(int val);

    void setTimezone(int val);

    void setLongitude(float lon);

    void setLatitude(float lat);
};
