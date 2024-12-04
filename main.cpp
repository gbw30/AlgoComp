#include <iostream>
#include "City.h"
#include "readerfile.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "BinarySearch.h"

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

// done
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

// done
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

// done
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

//done
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

// BROKEN waiting for next binary search implementation
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

    pair<int, int> r = binarySearchRange<int>(quick, input, [](const City& city) {return city.getPopulation();});

    if (ou == 1)
    {
        if (input != 150)
        {
            cout << "POPULATION" << " | " << "CITY" << " | " << "STATE" << " | "
                 << "ELEVATION" << " | " << "LATITUDE" << " | " << "LONGITUDE" << " | " << "TIMEZONE"
                 << endl;
            for (int i = 0; i < r.first; i++)
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
        if (input != 9997672)
        {
            cout << "POPULATION" << " | " << "CITY" << " | " << "STATE" << " | "
                 << "ELEVATION" << " | " << "LATITUDE" << " | " << "LONGITUDE" << " | " << "TIMEZONE"
                 << endl;
            for (int i = r.second + 1; i <= 9997672; i++)
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

// waiting for next binary search implementation
void handleCase6(vector<City>& quick, vector<City>& merge){}
// waiting for next binary search implementation
void handleCase7(int ou, vector<City>& quick, vector<City>& merge){}
// waiting for next binary search implementation
void handleCase8(int ou, vector<City>& quick, vector<City>& merge){}

// fixed - done
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

// waiting for next binary search implementation
void handleCase10(int ou, vector<City>& quick, vector<City>& merge){}

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

    for (int i = quick.size(); i >= 0; i--)
    {
        cout << quick[i].getPopulation() << endl;
    }

}

int main()
{
    vector<City> quick_cities = readFromCSV("../test2.txt");
    vector<City> merge_cities = readFromCSV("../test2.txt");

    main_menu();
    int input;

    while (true)
    {
        if (cin >> input)
        {
            if (input >= 0 && input <= 10)
                break;
            else
                cout << "Invalid input. Please enter a number between 0 and 10." << endl;
        }
        else
        {
            cout << "Invalid input. Please enter a number between 0 and 10." << endl;
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
            handleCase10(uo, quick_cities, merge_cities);
            break;
    }

}