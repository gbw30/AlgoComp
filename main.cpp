#include <iostream>
#include "City.h"
#include "readerfile.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "BinarySearch.h"
#include "datasetGen.h"

#include <regex>
#include <string>
#include <time.h>
#include <cctype>
#include <iostream>

using namespace std;

// checked - tested
void main_menu()
{
    cout << "Welcome to SuburbanScope!" << endl;
    cout << "We are going to compare two sorting algorithms: QuickSort and MergeSort!" << endl;
    cout << "After reading in over 100,000 data points we will sort the data in ascending order" << endl <<
            "based on the parameter, in [], you specified and print out what you want using binary search!" << endl;
    cout << "What do you want printed? (Integer from 0 to 13)." << endl;
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
    cout << "11 - All urban (> 7 million) cities in alphabetical order [Population] [City Name]" << endl;
    cout << "12 - All suburban (> 3 million and < 7 million) cities in alphabetical order [Population] [City Name]" << endl;
    cout << "13 - All rural cities in alphabetical order [Population] [City Name]" << endl;
}

// REGEX ADDED 2 3 - tested
int underOver()
{
    cout << R"(Would you like under or over? (Single character 'O', 'o', 'U', or 'u').)" << endl;
    string input;
    regex pattern("^[OoUu]$");
    regex pattern1("^[Uu]$");

    while (true)
    {
        getline(cin, input);
        if (regex_match(input, pattern))
        {
            if (regex_match(input, pattern1))
                return 1;
            else
                return 2;
        }
        else
            cout << "Invalid Input. Please enter single character 'O', 'o', 'U', or 'u'." << endl;
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

// done - tested - REGEX ADDED 2 3 - tested
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

// done - tested - REGEX ADDED 2 3 - tested
void handleCase1(vector<City>& quick, vector<City>& merge)
{
    cout << "Enter city name. (First letter A-Z, rest a-z)." << endl;
    string input2;
    regex pattern("^[A-Z][a-z]*$");

    while (true)
    {
        getline(cin, input2);
        if (regex_match(input2, pattern)) break;
        else cout << "Invalid Input. Please enter first letter A-Z, rest a-z." << endl;
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

// FIXED - done - REGEX ADDED 2 3 - tested
void handleCase2(vector<City>& quick, vector<City>& merge)
{
    cout << "Enter first letter of city. (One character A-Z or a-z)." << endl;
    string input2;
    regex pattern("^[a-zA-Z]$");
    char c;

    while (true)
    {
        getline(cin, input2);
        if (regex_match(input2, pattern))
        {
            c = input2[0];
            if (islower(c))
                c = toupper(c);
            break;
        }
        else cout << "Invalid Input. Please enter one character A-Z or a-z." << endl;
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

// done - tested - REGEX ADDED 2 3 - tested
void handleCase3(vector<City>& quick, vector<City>& merge)
{
    cout << "Enter a timezone. (Single digit 0-6)." << endl;

    string input2;
    int input;
    regex pattern("^[0-6]$");

    while (true)
    {
        getline(cin, input2);
        if (regex_match(input2, pattern))
        {
            input = stoi(input2);
            break;
        }
        else
            cout << "Invalid Input. Please enter a single digit 0-6." << endl;

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

// done - tested - REGEX ADDED 2 3 - tested
void handleCase4(vector<City>& quick, vector<City>& merge)
{
    cout << "Enter exact population. (Integer from 150 to 9997672)." << endl;
    regex pattern("^([1-9][0-9]{2,6}|[1-9][0-9]{2,5}[0-9]{0,1})$");
    string input2;
    int input;

    while (true)
    {
        getline(cin, input2);
        if (regex_match(input2, pattern))
        {
            input = stoi(input2);
            if (input >= 150 && input <= 9997672)
                break;
            else
                cout << "Invalid Input. Please enter integer from 150 to 9997672." << endl;

        }
        else
            cout << "Invalid Input. Please enter integer from 150 to 9997672." << endl;
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

// FIXED - done - tested - REGEX ADDED 2 3 - tested
void handleCase5(int ou, vector<City>& quick, vector<City>& merge)
{
    if (ou == 1)
        cout << "Enter maximum population [non-inclusive]. (Integer from 150 to 9997672)." << endl;
    else
        cout << "Enter minimum population [non-inclusive]. (Integer from 150 to 9997672)." << endl;

    string input2;
    int input;
    regex pattern("^([1-9][0-9]{2,6}|[1-9][0-9]{2,5}[0-9]{0,1})$");

    while (true)
    {
        getline(cin, input2);

        if (regex_match(input2, pattern))
        {
            input = stoi(input2);
            if (input >= 150 && input <= 9997672)
                break;
            else
                cout << "Invalid Input. Please enter integer from 150 to 9997672." << endl;
        }
        else
            cout << "Invalid Input. Please enter integer from 150 to 9997672." << endl;
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

// done finally - REGEX ADDED 2 3 need bin search lower
void handleCase6(vector<City>& quick, vector<City>& merge)
{
    cout << "Enter a population range [non-inclusive]. (Integers from 150 to 9997672 with space in between. Integer 1 > Integer 2)." << endl;

    string input2;
    int lower, upper;
    regex pattern("^([1-9][0-9]{2,6})\\s([1-9][0-9]{2,6})$");

    while (true)
    {
        getline(cin, input2);
        if (regex_match(input2, pattern))
        {
            int num1;
            int num2;

            stringstream ss(input2);
            if (ss >> num1 >> num2)
            {
                lower = num1;
                upper = num2;
            }
            if (num1 < num2 && num1 >= 150 && num2 <= 9997672)
                break;
            else
                cout << "Invalid Input. Please enter integers from 150 to 9997672 with space in between. Integer 1 > Integer 2." << endl;
        }
        else
            cout << "Invalid Input. Please enter integers from 150 to 9997672 with space in between. Integer 1 > Integer 2." << endl;
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

    if (r.second <= r1.first)
    {
        cout << "POPULATION" << " | " << "CITY" << " | " << "STATE" << " | "
             << "ELEVATION" << " | " << "LATITUDE" << " | " << "LONGITUDE" << " | " << "TIMEZONE"
             << endl;
        for (int i = r.second + 1; i <= r1.first - 1; i++)
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

// done - tested - REGEX ADDED 2 3
void handleCase7(int ou, vector<City>& quick, vector<City>& merge)
{
    if (ou == 1)
        cout << "Enter maximum latitude [non-inclusive]. (Number from 30 to 49.999)." << endl;
    else
        cout << "Enter minimum latitude [non-inclusive]. (Number from 30 to 49.999)." << endl;

    float input;
    string input2;
    regex pattern("^(?:[3-4][0-9](?:\\.\\d{1,3})?|49(\\.9{1,3})?)$");

    while (true)
    {
        getline(cin, input2);
        if (regex_match(input2, pattern))
        {
            input = stof(input2);
            break;
        }
        else
            cout << "Invalid Input. Please enter number from 30 to 49.999." << endl;
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

// done - tested - REGEX ADDED 2 3
void handleCase8(int ou, vector<City>& quick, vector<City>& merge)
{
    if (ou == 1)
        cout << "Enter maximum longitude [non-inclusive]. (Number from 63 to 132.996)." << endl;
    else
        cout << "Enter minimum longitude [non-inclusive]. (Number from 63 to 132.996)." << endl;

    float input;
    string input2;
    regex pattern("^(?:[6-9][3-9](?:\\.\\d{1,3})?|1[0-2][0-9](?:\\.\\d{1,3})?|132(\\.0{1,3})?)$");

    while (true)
    {
        getline(cin, input2);
        if (regex_match(input2, pattern))
        {
            input = stof(input2);
            break;
        }
        else
            cout << "Invalid Input. Please enter number from 63 to 132.996." << endl;
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

// fixed - done - tested - REGEX ADDED 2 3
void handleCase9(vector<City>& quick, vector<City>& merge)
{
    cout << "Enter state name. (First letter A-Z, rest a-z. If two words, then separate by space)." << endl;
    string input2;
    regex pattern("^[A-Z][a-z]*$");

    while (true)
    {
        getline(cin, input2);
        if (regex_match(input2, pattern))
            break;
        else
            cout << "Invalid Input. Please enter first letter A-Z, rest a-z. If two words, then separate by space." << endl;
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

// done - tested - REGEX ADDED 2 3
void handleCase10(int ou, vector<City>& quick, vector<City>& merge)
{
    if (ou == 1)
        cout << "Enter maximum elevation [non-inclusive]. (Integer from 0 to 9999)." << endl;
    else
        cout << "Enter minimum elevation [non-inclusive]. (Integer from 0 to 9999)." << endl;

    string input2;
    int input;
    regex pattern("^([0-9]|[1-9][0-9]{1,3})$");

    while (true)
    {
        getline(cin, input2);
        if (regex_match(input2, pattern))
        {
            input = stoi(input2);
            break;
        }
        else
            cout << "Invalid Input. Please enter integer from 0 to 9999." << endl;

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

// done - tested - urban scope (pop > 7000000) 2 3
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

// done - tested - suburban scope (3000000 > pop > 7000000) 2 3
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

// rural scope (pop < 3000000) 2 3
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
    quicksort(quick, 0, quick.size() - 1, compareByPopulation);

    //cout << r.first << "  " << r.second << endl;

    // cout << quick[0].getLongitude() << "   " << quick[quick.size() - 1].getLongitude() << endl;
    for (int i = 0; i <= quick.size() - 1; i++)
    {
        cout << quick[i].getPopulation() << endl;
    }

}

// 3
int main()
{
    // dataSetCreator();

    vector<City> quick_cities = readFromCSV("../test.txt");
    vector<City> merge_cities = readFromCSV("../test.txt");

    tester3(quick_cities, merge_cities);

    main_menu();
    string inputBuffer;
    int input;
    regex pattern("^(?:[0-9]|1[0-3])$");


    while (true)
    {
        getline(cin, inputBuffer);
        if (regex_match(inputBuffer, pattern))
        {
            input = stoi(inputBuffer);
            break;
        }
        else
            cout << "Invalid Input. Please enter integer from 0 to 13." << endl;
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