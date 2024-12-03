#include <utility>
#include "City.h"

// Definitions for constructors
City::City(int ID, const string& cityN, const string& stateN, float lat, float lon, int elev, int pop,
    int tz) : cityID(ID), cityName(cityN), stateName(stateN), latitude(lat), longitude(lon),
    elevation(elev), population(pop), timezone(tz) {}

City::City() {
    cityID = -1;
    cityName = "";
    stateName = "";
    latitude = -1.0;
    longitude = -1.0;
    population = -1;
    elevation = -1;
    timezone = -1;
}

// Definitions for getters
int City::getCityID() const { return cityID;}

string City::getCityName() const { return cityName;}

string City::getStateName() const { return stateName;}

float City::getLatitude() const { return latitude;}

float City::getLongitude() const { return longitude;}

int City::getElevation() const { return elevation;}

int City::getPopulation() const { return population;}

int City::getTimezone() const { return timezone;}

// Definitions for setters
void City::setCityID(int val) {cityID = val;}

void City::setCityName(string name) {cityName = name;}

void City::setStateName(string state) {stateName = state;}

void City::setPopulation(int val) {population = val;}

void City::setElevation(int val) {elevation = val;}

void City::setTimezone(int val) {timezone = val;}

void City::setLongitude(float lon) {longitude = lon;}

void City::setLatitude(float lat) {latitude = lat;}


