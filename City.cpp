#include <utility>
#include "City.h"

City::City(unsigned int ID, const string& cityN, const string& stateN, float lat, float lon, unsigned int elev, unsigned int pop,
    unsigned int tz) : cityID(ID), cityName(cityN), stateName(stateN), latitude(lat), longitude(lon),
    elevation(elev), population(pop), timezone(tz) {}

unsigned int City::getCityID() const { return cityID;}

string City::getCityName() const { return cityName;}

string City::getStateName() const { return stateName;}

float City::getLatitude() const { return latitude;}

float City::getLongitude() const { return longitude;}

unsigned int City::getElevation() const { return elevation;}

unsigned int City::getPopulation() const { return population;}

unsigned int City::getTimezone() const { return timezone;}
