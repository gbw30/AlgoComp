//
// Created by Yanka Deshkovski on 12/4/24.
//
#include "datasetGen.h"

const vector<string> vect = {"Alabama", "Alaska", "Arizona", "Arkansas", "California", "Colorado", "Connecticut",
                             "Delaware", "Florida", "Georgia", "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa",
                             "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland", "Massachusetts", "Michigan",
                             "Minnesota", "Mississippi", "Missouri", "Montana", "Nebraska", "Nevada", "New Hampshire",
                             "New Jersey", "New Mexico", "New York", "North Carolina", "North Dakota", "Ohio",
                             "Oklahoma", "Oregon", "Pennsylvania", "Rhode Island", "South Carolina", "South Dakota",
                             "Tennessee", "Texas", "Utah", "Vermont", "Virginia", "Washington", "West Virginia",
                             "Wisconsin", "Wyoming"};

const vector<int> vect2 = {-6, -9, -7, -6, -8, -7, -5, -5, -5, -5,
                           -10, -7, -6, -5, -6, -6, -5, -6, -5, -5,
                           -5, -6, -6, -5, -6, -6, -7, -5, -7, -5,
                           -4, -5, -5, -6, -7, -7, -7, -8, -7, -6,
                           -5, -5, -5, -7, -6, -6, -6, -6, -6, -7,
                           -7, -7};

vector<string> readWordsFromFile(const string& filename) {
    ifstream file(filename);
    vector<string> words;
    string word;

    if (file.is_open()) {
        while (getline(file, word)) {
            words.push_back(word);
        }
    }
    file.close();
    return words;
}

void writeToFile(string file, int cityID, string name, string state, int population, int elevation, float longitude,
                 float latitude, int timezone) {
    ofstream f;
    f.open(file, ios_base::app);

    if (!f.is_open()) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    f << cityID << "," << name << ","  << state << "," << population << "," << elevation << "," << longitude << "," << latitude <<
      "," << timezone << endl;

    f.close();
}

string namGen(vector<string>& names)
{
    string name = names[random() % names.size()];
    if (name.size() > 0) {
        name[0] = toupper(name[0]);
    }
    return name;
}


int popGen()
{
    int size = random() % 7 + 1;
    return random() % int(pow(10, size)) + 150;
}

int eleGen()
{
    int size = random() % 4 + 1;
    return random() % int(pow(10, size));
}

float lonGen()
{
    return (random() % 70000) / 10000.0 + 63;
}

float latGen()
{
    return (random() % 20000) / 10000.0 + 30;
}

int stateGen()
{
    return random() % 50;
}

string stateGen2(int val)
{
    return vect[val];
}

int tzGen(int val)
{
    return vect2[val] + 10;
}

void dataSetCreator()
{
    vector<string> words = readWordsFromFile("/usr/share/dict/words");

    for (int i = 0; i < 100000; i++)
    {
        int value = stateGen();
        writeToFile("../test.txt", i + 1,
                    namGen(words), stateGen2(value),
                    popGen(), eleGen(), lonGen(), latGen(),
                    tzGen(value));
    }
}