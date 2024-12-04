#include <iostream>
#include "City.h"
#include "readerfile.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "BinarySearch.h"
#include "datasetGen.h"

#include <string>
#include <time.h>
#include <cctype>
#include <iostream>

using namespace std;

void main_menu()
{
    cout << "Welcome to SuburbanScope!" << endl;
    cout << "We are going to compare two sorting algorithms: QuickSort and MergeSort!" << endl;
    cout << "After reading in over 100,000 data points we will sort the data in ascending order" << endl <<
            "based on the parameter, in [], you specified and print out what you want using binary search!" << endl;
    cout << "What do you want printed? (Type 0-10)" << endl;
    cout << "0 - All cities in alphabetical order [City Name]" << endl;
    cout << "1 - All cities with specified name [City Name]" << endl;
    cout << "2 - All cities beginning with specified letter [City Name]" << endl;
    cout << "3 - All cities in a specified timezone [Timezone]" << endl;
    cout << "4 - All cities with an exact specified population [Population]" << endl;
    cout << "5 - All cities under/over a specified population [Population]" << endl;
    cout << "6 - All cities in between two specified populations [Population]" << endl;
    cout << "7 - All cities under/over a specified latitude [Latitude]" << endl;
    cout << "8 - All cities under/over a specified longitude [Longitude]" << endl;
    cout << "9 - All cities in a specified state [State Name]" << endl;
    cout << "10 - All cities under/over a specified elevation [Elevation]" << endl;
    cout << "11 - All urban (> 7 million) cities in alphabetical order [population] [City Name]" << endl;
    cout << "12 - All suburban (> 3 million and < 7 million) cities in alphabetical order [population] [City Name]" << endl;
    cout << "13 - All rural cities in alphabetical order [population] [City Name]" << endl;
}

int underOver()
{
    cout << R"(Would you like under or over? (Type "O" or "U"))" << endl;
    string input2;
    while (true)
    {
        if (cin >> input2)
        {
            if (input2 == "U" || input2 == "O")
                if (input2 == "U")
                    return 1;
                else
                    return 2;
            else
                cout << R"(Invalid input. Please enter "O" or "U".)" << endl;
        }
        else
        {
            cout << R"(Invalid input. Please enter "O" or "U".)" << endl;
            cin.clear();
        }
    }
}

void printResults(double quick, double merge)
{
    cout << endl << "QuickSort took " << quick << " seconds" << endl;
    cout << "MergeSort took " << merge << " seconds" << endl;
}

pair<double, double> sorter(vector<City>& quick, vector<City>& merge)
{
    double quickTime;
    double mergeTime;
    clock_t start, end;

    start = clock();
    quicksort(quick, 0, quick.size() - 1, compareByName);
    end = clock();

    quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(merge, 0, merge.size() - 1, compareByName);
    end = clock();

    mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    return make_pair(quickTime, mergeTime);
}

// done - tested
void handleCase0(vector<City>& quick, vector<City>& merge)
{
    pair<double, double> r = sorter(quick, merge);

    cout << "CITY" << " | " << "STATE" << " | " << "POPULATION" << " | "
         << "ELEVATION" << " | " << "LATITUDE"  << " | " << "LONGITUDE" << " | " << "TIMEZONE"
         << endl;
    for (City c : quick)
    {
        cout << c.getCityName() << " | " << c.getStateName() << " | " << c.getPopulation() << " | "
        << c.getElevation() << " | " << c.getLatitude()  << " | " << c.getLongitude() << " | " << c.getTimezone()
        << endl;
    }

    printResults(r.first, r.second);
}

// done - tested
void handleCase1(vector<City>& quick, vector<City>& merge)
{
    cout << "What named cities do you want to print? (Type A-Za-z)" << endl;
    string input2;

    while (true)
    {
        if (cin >> input2)
        {
            bool isString = true;
            for (int i = 0; i < input2.size(); i++)
                if (!isalpha(char(input2[i]))) isString = false;

            if (isString)
            {
                break;
            }
            else
                cout << R"(Invalid input. Please enter A-Za-z.)" << endl;
        }
        else
        {
            cout << R"(Invalid input. Please enter A-Za-z.)" << endl;
            cin.clear();
        }
    }

    pair<double, double> r = sorter(quick, merge);

    pair<int, int> r2 = binarySearchRange<string>(quick, input2, [](const City& city) {return city.getCityName();});

    if (r2.first != -1)
    {
        cout << "CITY" << " | " << "STATE" << " | " << "POPULATION" << " | "
             << "ELEVATION" << " | " << "LATITUDE" << " | " << "LONGITUDE" << " | " << "TIMEZONE"
             << endl;
        for (int i = r2.first; i <= r2.second; i++)
        {
            cout << quick[i].getCityName() << " | " << quick[i].getStateName() << " | " << quick[i].getPopulation() << " | "
                 << quick[i].getElevation() << " | " << quick[i].getLatitude()  << " | " << quick[i].getLongitude() <<
                 " | " << quick[i].getTimezone()
                 << endl;
        }
    }
    else
    {
        cout << "No such city exists." << endl;
    }

    printResults(r.first, r.second);
}

// FIXED - done
void handleCase2(vector<City>& quick, vector<City>& merge)
{
    cout << "What letter do you want the cities to begin with? (Type a-zA-Z)" << endl;
    string input2;
    char c;

    while (true)
    {
        if (cin >> input2)
        {
            if (input2.size() == 1 && isalpha(char(input2[0])))
            {
                c = char(input2[0]);
                if (islower(c))
                    c = toupper(c);
                break;
            }
            else
                cout << R"(Invalid input. Please enter A-Za-z.)" << endl;
        }
        else
        {
            cout << R"(Invalid input. Please enter A-Za-z.)" << endl;
            cin.clear();
        }
    }

    double quickTime;
    double mergeTime;
    clock_t start, end;

    start = clock();
    quicksort(quick, 0, quick.size() - 1, compareByName);
    end = clock();

    quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(merge, 0, merge.size() - 1, compareByName);
    end = clock();

    mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    pair<int, int> r2 = binarySearchByPrefix(quick, c, [](const City& city) {return city.getCityName();});

    cout << "CITY" << " | " << "STATE" << " | " << "POPULATION" << " | "
         << "ELEVATION" << " | " << "LATITUDE"  << " | " << "LONGITUDE" << " | " << "TIMEZONE"
         << endl;
    for (int i = r2.first; i <= r2.second; i++)
    {
        cout << quick[i].getCityName() << " | " << quick[i].getStateName() << " | " << quick[i].getPopulation() << " | "
             << quick[i].getElevation() << " | " << quick[i].getLatitude()  << " | " << quick[i].getLongitude() << " | "
             << quick[i].getTimezone() << endl;
    }

    printResults(quickTime, mergeTime);
}

// done - tested
void handleCase3(vector<City>& quick, vector<City>& merge)
{
    cout << "Which timezone do you want to print? (Type 0-6)" << endl;

    int input;
    while (true)
    {
        if (cin >> input)
        {
            if (input >= 0 && input <= 6)
                break;
            else
                cout << "Invalid input. Please enter a number between 0 and 6." << endl;
        }
        else
        {
            cout << "Invalid input. Please enter a number between 0 and 6." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    double quickTime;
    double mergeTime;
    clock_t start, end;

    start = clock();
    quicksort(quick, 0, quick.size() - 1, compareByTimezone);
    end = clock();

    quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(merge, 0, merge.size() - 1, compareByTimezone);
    end = clock();

    mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    pair<int, int> r = binarySearchRange<int>(quick, input, [](const City& city) {return city.getTimezone();});

    if (r.first != -1)
    {
        cout << "TIMEZONE" << " | " << "CITY" << " | " << "STATE" << " | " << "POPULATION" << " | "
             << "ELEVATION" << " | " << "LATITUDE" << " | " << "LONGITUDE"
             << endl;
        for (int i = r.first; i <= r.second; i++)
        {
            cout << quick[i].getTimezone() << " | " << quick[i].getCityName() << " | " << quick[i].getStateName() << " | " << quick[i].getPopulation() << " | "
                 << quick[i].getElevation() << " | " << quick[i].getLatitude()  << " | " << quick[i].getLongitude()
                 << endl;
        }
    }
    else
    {
        cout << "No such city exists." << endl;
    }

    printResults(quickTime, mergeTime);
}

// done - tested
void handleCase4(vector<City>& quick, vector<City>& merge)
{
    cout << "What exact population do you want? (Type 150-9997672)" << endl;

    int input;
    while (true)
    {
        if (cin >> input)
        {
            if (input >= 150 && input <= 9997672)
                break;
            else
                cout << "Invalid input. Please enter a number between 150 and 9997672." << endl;
        }
        else
        {
            cout << "Invalid input. Please enter a number between 150 and 9997672." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    double quickTime;
    double mergeTime;
    clock_t start, end;

    start = clock();
    quicksort(quick, 0, quick.size() - 1, compareByPopulation);
    end = clock();

    quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(merge, 0, merge.size() - 1, compareByPopulation);
    end = clock();

    mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    pair<int, int> r = binarySearchRange<int>(quick, input, [](const City& city) {return city.getPopulation();});

    if (r.first != -1)
    {
        cout << "POPULATION" << " | " << "CITY" << " | " << "STATE" << " | "
             << "ELEVATION" << " | " << "LATITUDE" << " | " << "LONGITUDE" << " | " << "TIMEZONE"
             << endl;
        for (int i = r.first; i <= r.second; i++)
        {
            cout << quick[i].getPopulation() << " | " << quick[i].getCityName() << " | " << quick[i].getStateName() << " | "
                 << quick[i].getElevation() << " | " << quick[i].getLatitude()  << " | " << quick[i].getLongitude() <<
                 " | " << quick[i].getTimezone()
                 << endl;
        }
    }
    else
    {
        cout << "No such city exists." << endl;
    }

    printResults(quickTime, mergeTime);
}

// FIXED - done - tested
void handleCase5(int ou, vector<City>& quick, vector<City>& merge)
{
    if (ou == 1)
        cout << "Under what population do you want the cities? (Type 150-9997672)" << endl;
    else
        cout << "Over what population do you want the cities? (Type 150-9997672)" << endl;

    int input;
    while (true)
    {
        if (cin >> input)
        {
            if (input >= 150 && input <= 9997672)
                break;
            else
                cout << "Invalid input. Please enter a number between 150 and 9997672." << endl;
        }
        else
        {
            cout << "Invalid input. Please enter a number between 150 and 9997672." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    double quickTime;
    double mergeTime;
    clock_t start, end;

    start = clock();
    quicksort(quick, 0, quick.size() - 1, compareByPopulation);
    end = clock();

    quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(merge, 0, merge.size() - 1, compareByPopulation);
    end = clock();

    mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    pair<int, int> r =
            binarySearchClosestUpper<int>(quick, input, [](const City& city) {return city.getPopulation();});

    if (ou == 1)
    {
        if (input != quick[0].getPopulation())
        {
            cout << "POPULATION" << " | " << "CITY" << " | " << "STATE" << " | "
                 << "ELEVATION" << " | " << "LATITUDE" << " | " << "LONGITUDE" << " | " << "TIMEZONE"
                 << endl;
            for (int i = 0; i < r.first - 1; i++)
            {
                cout << quick[i].getPopulation() << " | " << quick[i].getCityName() << " | " << quick[i].getStateName() << " | "
                     << quick[i].getElevation() << " | " << quick[i].getLatitude()  << " | " << quick[i].getLongitude() <<
                     " | " << quick[i].getTimezone()
                     << endl;
            }
        }
        else
        {
            cout << "No such city exists." << endl;
        }
    }
    else
    {
        if (input != quick[quick.size() - 1].getPopulation())
        {
            cout << "POPULATION" << " | " << "CITY" << " | " << "STATE" << " | "
                 << "ELEVATION" << " | " << "LATITUDE" << " | " << "LONGITUDE" << " | " << "TIMEZONE"
                 << endl;
            for (int i = r.second; i <= quick.size() - 1; i++)
            {
                cout << quick[i].getPopulation() << " | " << quick[i].getCityName() << " | " << quick[i].getStateName() << " | "
                     << quick[i].getElevation() << " | " << quick[i].getLatitude()  << " | " << quick[i].getLongitude() <<
                     " | " << quick[i].getTimezone()
                     << endl;
            }
        }
        else
        {
            cout << "No such city exists." << endl;
        }
    }

    printResults(quickTime, mergeTime);
}

// done finally - tested (maybe needs better string parsing?)
void handleCase6(vector<City>& quick, vector<City>& merge)
{
    cout << "Which populations do you want to be in between? (Type 150-9997672 150-9997672)" << endl;

    string input2;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, input2);
    int lower, upper;

    while (true)
    {
        bool isString = true;
        int counter = 0;
        if (input2[0] == ' ')
            isString = false;
        for (int i = 0; i < input2.size(); i++)
        {
            if (char(input2[i]) == ' ')
                counter++;
        }
        if (counter != 1)
            isString = false;

        for (int i = 0; i < input2.size(); i++)
            if (!(isdigit(char(input2[i])) || char(input2[i]) == ' ')) isString = false;

        if (isString)
        {
            int counter2 = 0;
            for (int i = 0; i < input2.size(); i++)
            {
                if (input2[i] == ' ')
                    break;
                counter2++;
            }
            lower = stoi(input2.substr(0, counter2));
            upper = stoi(input2.substr(counter2 + 1, input2.size() - counter2 + 1));
            if (!(lower >= 150 && upper <= 9997672 && upper >= lower))
                isString = false;
        }


        if (isString)
        {
            break;
        }
        else
            cout << R"(Invalid input. Please enter 150-9997672 150-9997672.)" << endl;

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, input2);
    }

    double quickTime;
    double mergeTime;
    clock_t start, end;

    start = clock();
    quicksort(quick, 0, quick.size() - 1, compareByPopulation);
    end = clock();

    quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(merge, 0, merge.size() - 1, compareByPopulation);
    end = clock();

    mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    pair<int, int> r = binarySearchClosestUpper<int>(quick, lower, [](const City& city) {return city.getPopulation();});
    pair<int, int> r1 = binarySearchClosestUpper<int>(quick, upper, [](const City& city) {return city.getPopulation();});

    if (r.second < r1.first)
    {
        cout << "POPULATION" << " | " << "CITY" << " | " << "STATE" << " | "
             << "ELEVATION" << " | " << "LATITUDE" << " | " << "LONGITUDE" << " | " << "TIMEZONE"
             << endl;
        for (int i = r.second + 1; i < r1.first - 1; i++)
        {
            cout << quick[i].getPopulation() << " | " << quick[i].getCityName() << " | " << quick[i].getStateName() << " | "
                 << quick[i].getElevation() << " | " << quick[i].getLatitude()  << " | " << quick[i].getLongitude() <<
                 " | " << quick[i].getTimezone()
                 << endl;
        }
    }
    else
    {
        cout << "No such city exists." << endl;
    }

    printResults(quickTime, mergeTime);
}

// done - tested
void handleCase7(int ou, vector<City>& quick, vector<City>& merge)
{
    if (ou == 1)
        cout << "Under what latitude do you want the cities? (Type 30.0-49.9999)" << endl;
    else
        cout << "Over what latitude do you want the cities? (Type 30.0-49.999)" << endl;

    float input;
    while (true)
    {
        if (cin >> input)
        {
            if (input >= 30.0 && input <= 49.999)
                break;
            else
                cout << "Invalid input. Please enter a number between 30 and 49.999." << endl;
        }
        else
        {
            cout << "Invalid input. Please enter a number between 40.0 and 49.999." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    double quickTime;
    double mergeTime;
    clock_t start, end;

    start = clock();
    quicksort(quick, 0, quick.size() - 1, compareByLatitude);
    end = clock();

    quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(merge, 0, merge.size() - 1, compareByLatitude);
    end = clock();

    mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    pair<int, int> r =
            binarySearchClosestUpper<float>(quick, input, [](const City& city) {return city.getLatitude();});

    if (ou == 1)
    {
        if (input != quick[0].getLatitude())
        {
            cout << "LATITUDE"  << " | " << "CITY" << " | " << "STATE" << " | " << "POPULATION" << " | "
                 << "ELEVATION" << " | " << "LONGITUDE" << " | " << "TIMEZONE"
                 << endl;
            for (int i = 0; i <= r.first - 1; i++)
            {
                cout << quick[i].getLatitude() << " | " << quick[i].getCityName() << " | " << quick[i].getStateName() << " | "
                     << quick[i].getPopulation() << " | " << quick[i].getElevation()  << " | " << quick[i].getLongitude() <<
                     " | " << quick[i].getTimezone()
                     << endl;
            }
        }
        else
        {
            cout << "No such city exists." << endl;
        }
    }
    else
    {
        if (input != quick[quick.size() - 1].getLatitude())
        {
            cout << "LATITUDE"  << " | " << "CITY" << " | " << "STATE" << " | " << "POPULATION" << " | "
                 << "ELEVATION" << " | " << "LONGITUDE" << " | " << "TIMEZONE"
                 << endl;
            for (int i = r.second + 1; i <= quick.size() - 1; i++)
            {
                cout << quick[i].getLatitude() << " | " << quick[i].getCityName() << " | " << quick[i].getStateName() << " | "
                     << quick[i].getPopulation() << " | " << quick[i].getElevation()  << " | " << quick[i].getLongitude() <<
                     " | " << quick[i].getTimezone()
                     << endl;
            }
        }
        else
        {
            cout << "No such city exists." << endl;
        }
    }

    printResults(quickTime, mergeTime);

    cout << r.first - 1 << endl;
}

// done - tested
void handleCase8(int ou, vector<City>& quick, vector<City>& merge)
{
    if (ou == 1)
        cout << "Under what longitude do you want the cities? (Type 63.0-132.996)" << endl;
    else
        cout << "Over what longitude do you want the cities? (Type 63.0-132.996)" << endl;

    float input;
    while (true)
    {
        if (cin >> input)
        {
            if (input >= 63.0 && input <= 132.996)
                break;
            else
                cout << "Invalid input. Please enter a number between 63.0 and 132.996." << endl;
        }
        else
        {
            cout << "Invalid input. Please enter a number between 63.0 and 132.996." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    double quickTime;
    double mergeTime;
    clock_t start, end;

    start = clock();
    quicksort(quick, 0, quick.size() - 1, compareByLongitude);
    end = clock();

    quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(merge, 0, merge.size() - 1, compareByLongitude);
    end = clock();

    mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    pair<int, int> r =
            binarySearchClosestUpper<float>(quick, input, [](const City& city) {return city.getLongitude();});

    if (ou == 1)
    {
        if (input != quick[0].getLongitude())
        {
            cout << "LONGITUDE"  << " | " << "CITY" << " | " << "STATE" << " | " << "POPULATION" << " | "
                 << "ELEVATION" << " | " << "LATITUDE" << " | " << "TIMEZONE" << r.first - 1
                 << endl;
            for (int i = 0; i <= r.first - 1; i++)
            {
                cout << quick[i].getLongitude() << " | " << quick[i].getCityName() << " | " << quick[i].getStateName() << " | "
                     << quick[i].getPopulation() << " | " << quick[i].getElevation()  << " | " << quick[i].getLatitude() <<
                     " | " << quick[i].getTimezone()
                     << endl;
            }
        }
        else
        {
            cout << "No such city exists." << endl;
        }
    }
    else
    {
        if (input != quick[quick.size() - 1].getLongitude())
        {
            cout << "LONGITUDE"  << " | " << "CITY" << " | " << "STATE" << " | " << "POPULATION" << " | "
                 << "ELEVATION" << " | " << "LATITUDE" << " | " << "TIMEZONE"
                 << endl;
            for (int i = r.second + 1; i <= quick.size() - 1; i++)
            {
                cout << quick[i].getLongitude() << " | " << quick[i].getCityName() << " | " << quick[i].getStateName() << " | "
                     << quick[i].getPopulation() << " | " << quick[i].getElevation()  << " | " << quick[i].getLatitude() <<
                     " | " << quick[i].getTimezone()
                     << endl;
            }
        }
        else
        {
            cout << "No such city exists." << endl;
        }
    }

    printResults(quickTime, mergeTime);
}

// fixed - done - tested
void handleCase9(vector<City>& quick, vector<City>& merge)
{
    cout << "What state do you want the cities to be from? (Type A-Za-z)" << endl;
    string input2;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, input2);

    while (true)
    {
        bool isString = true;
        for (int i = 0; i < input2.size(); i++)
            if (!(isalpha(char(input2[i])) || char(input2[i]) == ' ')) isString = false;

        if (isString)
        {
            break;
        }
        else
            cout << R"(Invalid input. Please enter A-Za-z.)" << endl;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, input2);
    }

    double quickTime;
    double mergeTime;
    clock_t start, end;

    start = clock();
    quicksort(quick, 0, quick.size() - 1, compareByState);
    end = clock();

    quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(merge, 0, merge.size() - 1, compareByState);
    end = clock();

    mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    pair<int, int> r2 = binarySearchRange<string>(quick, input2, [](const City& city) {return city.getStateName();});

    if (r2.first != -1)
    {
        cout << "STATE" << " | " << "CITY" << " | " << "POPULATION" << " | "
             << "ELEVATION" << " | " << "LATITUDE" << " | " << "LONGITUDE" << " | " << "TIMEZONE"
             << endl;
        for (int i = r2.first; i <= r2.second; i++)
        {
            cout << quick[i].getStateName() << " | " << quick[i].getCityName() << " | " << quick[i].getPopulation() << " | "
                 << quick[i].getElevation() << " | " << quick[i].getLatitude()  << " | " << quick[i].getLongitude() <<
                 " | " << quick[i].getTimezone()
                 << endl;
        }
    }
    else
    {
        cout << "No such state exists." << endl;
    }

    printResults(quickTime, mergeTime);
}

// done - tested
void handleCase10(int ou, vector<City>& quick, vector<City>& merge)
{
    if (ou == 1)
        cout << "Under what elevation do you want the cities? (Type 0-9999)" << endl;
    else
        cout << "Over what elevation do you want the cities? (Type 0-9999)" << endl;

    int input;
    while (true)
    {
        if (cin >> input)
        {
            if (input >= 0 && input <= 9999)
                break;
            else
                cout << "Invalid input. Please enter a number between 0 and 9999." << endl;
        }
        else
        {
            cout << "Invalid input. Please enter a number between 0 and 9999." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    double quickTime;
    double mergeTime;
    clock_t start, end;

    start = clock();
    quicksort(quick, 0, quick.size() - 1, compareByElevation);
    end = clock();

    quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(merge, 0, merge.size() - 1, compareByElevation);
    end = clock();

    mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    pair<int, int> r =
            binarySearchClosestUpper<int>(quick, input, [](const City& city) {return city.getElevation();});

    if (ou == 1)
    {
        if (input != quick[0].getElevation())
        {
            cout << "ELEVATION" << " | " << "CITY" << " | " << "STATE" << " | "
                 << "POPULATION" << " | " << "LATITUDE" << " | " << "LONGITUDE" << " | " << "TIMEZONE"
                 << endl;
            for (int i = 0; i < r.first - 1; i++)
            {
                cout << quick[i].getElevation() << " | " << quick[i].getCityName() << " | " << quick[i].getStateName() << " | "
                     << quick[i].getPopulation() << " | " << quick[i].getLatitude()  << " | " << quick[i].getLongitude() <<
                     " | " << quick[i].getTimezone()
                     << endl;
            }
        }
        else
        {
            cout << "No such city exists." << endl;
        }
    }
    else
    {
        if (input != quick[quick.size() - 1].getElevation())
        {
            cout << "ELEVATION" << " | " << "CITY" << " | " << "STATE" << " | "
                 << "POPULATION" << " | " << "LATITUDE" << " | " << "LONGITUDE" << " | " << "TIMEZONE"
                 << endl;
            for (int i = r.second + 1; i <= quick.size() - 1; i++)
            {
                cout << quick[i].getElevation() << " | " << quick[i].getCityName() << " | " << quick[i].getStateName() << " | "
                     << quick[i].getPopulation() << " | " << quick[i].getLatitude()  << " | " << quick[i].getLongitude() <<
                     " | " << quick[i].getTimezone()
                     << endl;
            }
        }
        else
        {
            cout << "No such city exists." << endl;
        }
    }

    printResults(quickTime, mergeTime);
}

// done - tested - urban scope (pop > 7000000)
void handleCase11(vector<City>& quick, vector<City>& merge) {
    int urban_pop = 7000000;
    double quickTime;
    double mergeTime;
    clock_t start, end;

    start = clock();
    quicksort(quick, 0, quick.size() - 1, compareByPopulation);
    end = clock();

    quickTime = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(merge, 0, merge.size() - 1, compareByPopulation);
    end = clock();

    mergeTime = ((double) (end - start)) / CLOCKS_PER_SEC;

    pair<int, int> r =
            binarySearchClosestUpper<int>(quick, urban_pop, [](const City &city) { return city.getPopulation(); });

    vector<City> newCities;
    vector<City> newCitiesM;
    for (int i = r.second + 1; i < quick.size(); i++)
    {
        newCities.push_back(quick[i]);
        newCitiesM.push_back(quick[i]);
    }
    double qTime;
    double mTime;

    start = clock();
    quicksort(newCities, 0, newCities.size() - 1, compareByName);
    end = clock();

    qTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(newCitiesM, 0, newCitiesM.size() - 1, compareByName);
    end = clock();

    mTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    cout << "POPULATION" << " | " << "CITY" << " | " << "STATE" << " | "
         << "ELEVATION" << " | " << "LATITUDE" << " | " << "LONGITUDE" << " | " << "TIMEZONE"
         << endl;
    for (int i = 0; i < newCities.size(); i++)
    {
        cout << newCities[i].getPopulation() << " | " << newCities[i].getCityName() << " | " << newCities[i].getStateName() << " | "
             << newCities[i].getElevation() << " | " << newCities[i].getLatitude()  << " | " << newCities[i].getLongitude() <<
             " | " << newCities[i].getTimezone()
             << endl;
    }

    cout << endl << "Sort by population:" << endl;

    printResults(quickTime, mergeTime);

    cout << endl << "Sort alphabetically:" << endl;

    printResults(qTime, mTime);

}

// done - tested - suburban scope (3000000 > pop > 7000000)
void handleCase12(vector<City>& quick, vector<City>& merge)
{
    int suburban_pop1 = 3000000;
    int suburban_pop2 = 7000000;

    double quickTime;
    double mergeTime;
    clock_t start, end;

    start = clock();
    quicksort(quick, 0, quick.size() - 1, compareByPopulation);
    end = clock();

    quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(merge, 0, merge.size() - 1, compareByPopulation);
    end = clock();

    mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    pair<int, int> r = binarySearchClosestUpper<int>(quick, suburban_pop1, [](const City& city) {return city.getPopulation();});
    pair<int, int> r1 = binarySearchClosestUpper<int>(quick, suburban_pop2, [](const City& city) {return city.getPopulation();});

    vector<City> newCitiesQ;
    vector<City> newCitiesM;

    for (int i = r.second + 1; i < r1.first - 1; i++)
    {
        newCitiesQ.push_back(quick[i]);
        newCitiesM.push_back(quick[i]);
    }

    double qTime;
    double mTime;

    start = clock();
    quicksort(newCitiesQ, 0, newCitiesQ.size() - 1, compareByName);
    end = clock();

    qTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(newCitiesM, 0, newCitiesM.size() - 1, compareByName);
    end = clock();

    mTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    cout << "POPULATION" << " | " << "CITY" << " | " << "STATE" << " | "
         << "ELEVATION" << " | " << "LATITUDE" << " | " << "LONGITUDE" << " | " << "TIMEZONE"
         << endl;
    for (int i = 0; i < newCitiesQ.size(); i++)
    {
        cout << newCitiesQ[i].getPopulation() << " | " << newCitiesQ[i].getCityName() << " | " << newCitiesQ[i].getStateName() << " | "
             << newCitiesQ[i].getElevation() << " | " << newCitiesQ[i].getLatitude()  << " | " << newCitiesQ[i].getLongitude() <<
             " | " << newCitiesQ[i].getTimezone()
             << endl;
    }

    cout << endl << "Sort by population:" << endl;

    printResults(quickTime, mergeTime);

    cout << endl << "Sort alphabetically:" << endl;

    printResults(qTime, mTime);
}

// rural scope (pop < 3000000)
void handleCase13(vector<City>& quick, vector<City>& merge)
{
    int rural_pop = 3000000;

    double quickTime;
    double mergeTime;
    clock_t start, end;

    start = clock();
    quicksort(quick, 0, quick.size() - 1, compareByPopulation);
    end = clock();

    quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(merge, 0, merge.size() - 1, compareByPopulation);
    end = clock();

    mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    pair<int, int> r =
            binarySearchClosestUpper<int>(quick, rural_pop, [](const City& city) {return city.getPopulation();});

    vector<City> newCitiesM;
    vector<City> newCitiesQ;

    for (int i = 0; i < r.first - 1; i++)
    {
        newCitiesQ.push_back(quick[i]);
        newCitiesM.push_back(quick[i]);
    }

    double qTime;
    double mTime;

    start = clock();
    quicksort(newCitiesQ, 0, newCitiesQ.size() - 1, compareByName);
    end = clock();

    qTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(newCitiesM, 0, newCitiesM.size() - 1, compareByName);
    end = clock();

    mTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    cout << "POPULATION" << " | " << "CITY" << " | " << "STATE" << " | "
         << "ELEVATION" << " | " << "LATITUDE" << " | " << "LONGITUDE" << " | " << "TIMEZONE"
         << endl;
    for (int i = 0; i < newCitiesQ.size(); i++)
    {
        cout << newCitiesQ[i].getPopulation() << " | " << newCitiesQ[i].getCityName() << " | " << newCitiesQ[i].getStateName() << " | "
             << newCitiesQ[i].getElevation() << " | " << newCitiesQ[i].getLatitude()  << " | " << newCitiesQ[i].getLongitude() <<
             " | " << newCitiesQ[i].getTimezone()
             << endl;
    }

    cout << endl << "Sort by population:" << endl;

    printResults(quickTime, mergeTime);

    cout << endl << "Sort alphabetically:" << endl;

    printResults(qTime, mTime);
}

void testerPopulation(vector<City>& quick, vector<City>& merge)
{
    double quickTime;
    double mergeTime;
    clock_t start, end;

    start = clock();
    quicksort(quick, 0, quick.size() - 1, compareByPopulation);
    end = clock();

    quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(merge, 0, merge.size() - 1, compareByPopulation);
    end = clock();

    mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    pair<int, int> r = binarySearchRange<int>(quick, 177, [](const City& city) {return city.getPopulation();});

    cout << r.first << "   " << r.second << endl;

    for (int i = r.first; i <= r.second; i++)
    {
        cout << quick[i].getPopulation() << endl;
    }
}

void testerStrings(vector<City>& quick, vector<City>& merge)
{
    sorter(quick, merge);
    pair<int, int> r = binarySearchByPrefix(quick, 'Z', [](const City& city) {return city.getCityName();});

    cout << r.first << "   " << r.second << endl;

    for (int i = r.first; i <= r.second; i++)
    {
        cout << quick[i].getCityName() << endl;
    }
}

void tester3(vector<City>& quick, vector<City>& merge)
{
    quicksort(quick, 0, quick.size() - 1, compareByLongitude);

    //cout << r.first << "  " << r.second << endl;

    cout << quick[0].getLongitude() << "   " << quick[quick.size() - 1].getLongitude() << endl;
//    for (int i = 0; i <= quick.size() - 1; i++)
//    {
//        cout << endl;
//    }

}

int main()
{
    // dataSetCreator();

    vector<City> quick_cities = readFromCSV("../test.txt");
    vector<City> merge_cities = readFromCSV("../test.txt");

    main_menu();
    int input;

    while (true)
    {
        if (cin >> input)
        {
            if (input >= 0 && input <= 13)
                break;
            else
                cout << "Invalid input. Please enter a number between 0 and 13." << endl;
        }
        else
        {
            cout << "Invalid input. Please enter a number between 0 and 13." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    int uo;
    switch (input)
    {
        case 0:
            handleCase0(quick_cities, merge_cities);
            break;
        case 1:
            handleCase1(quick_cities, merge_cities);
            break;
        case 2:
            handleCase2(quick_cities, merge_cities);
            break;
        case 3:
            handleCase3(quick_cities, merge_cities);
            break;
        case 4:
            handleCase4(quick_cities, merge_cities);
            break;
        case 5:
            uo = underOver();
            handleCase5(uo, quick_cities, merge_cities);
            break;
        case 6:
            handleCase6(quick_cities, merge_cities);
            break;
        case 7:
            uo = underOver();
            handleCase7(uo, quick_cities, merge_cities);
            break;
        case 8:
            uo = underOver();
            handleCase8(uo, quick_cities, merge_cities);
            break;
        case 9:
            handleCase9(quick_cities, merge_cities);
            break;
        case 10:
            uo = underOver();
            //tester3(quick_cities, merge_cities);
            handleCase10(uo, quick_cities, merge_cities);
            break;
        case 11:
            handleCase11(quick_cities, merge_cities);
            break;
        case 12:
            handleCase12(quick_cities, merge_cities);
            break;
        case 13:
            handleCase13(quick_cities, merge_cities);
            break;
    }

}