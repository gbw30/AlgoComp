//
// Created by Yanka Deshkovski on 12/4/24.
//

#ifndef ALGOCOMP_DATASETGEN_H
#define ALGOCOMP_DATASETGEN_H
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <cmath>

using namespace std;

vector<string> readWordsFromFile(const string& filename);

void writeToFile(string file, int cityID, string name, string state, int population, int elevation, float longitude,
                 float latitude, int timezone);

string namGen(vector<string>& names);

int popGen();

int eleGen();

float lonGen();

float latGen();

int stateGen();

string stateGen2(int val);

int tzGen(int val);

void dataSetCreator();

#endif //ALGOCOMP_DATASETGEN_H
