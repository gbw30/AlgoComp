#include <iostream>
#include "City.h"
#include "readerfile.h"
#include "MergeSort.h"
#include "QuickSort.h"

#include <string>
#include <time.h>
#include <iostream>

using namespace std;

void main_menu()
{
    cout << "Welcome to SuburbanScope!" << endl;
    cout << "We are going to compare two sorting algorithms: QuickSort and MergeSort!" << endl;
    cout << "After reading in over 100,000 data points we will sort the data in ascending order" << endl <<
            "based on the parameter you specified and print out what you want!" << endl;
    cout << "What do you want printed? (Type 0-9)" << endl;
    cout << "0 - All cities in alphabetical order" << endl;
    cout << "1 - All cities beginning with specified letter" << endl;
    cout << "2 - All cities in a specified timezone" << endl;
    cout << "3 - All cities with an exact specified population" << endl;
    cout << "4 - All cities under/over a specified population" << endl;
    cout << "5 - All cities in between two specified populations" << endl;
    cout << "6 - All cities under/over a specified latitude" << endl;
    cout << "7 - All cities under/over a specified longitude" << endl;
    cout << "8 - All cities in a specified state" << endl;
    cout << "9 - All cities under/over a specified elevation" << endl;
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

void handleCase0(vector<City>& quick, vector<City>& merge)
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

    cout << "CITY" << " | " << "STATE" << " | " << "POPULATION" << " | "
         << "ELEVATION" << " | " << "LATITUDE"  << " | " << "LONGITUDE" << " | " << "TIMEZONE"
         << endl;
    for (City c : quick)
    {
        cout << c.getCityName() << " | " << c.getStateName() << " | " << c.getPopulation() << " | "
        << c.getElevation() << " | " << c.getLatitude()  << " | " << c.getLongitude() << " | " << c.getTimezone()
        << endl;
    }

    printResults(quickTime, mergeTime);
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
            if (input >= 0 && input <= 9)
                break;
            else
                cout << "Invalid input. Please enter a number between 0 and 9." << endl;
        }
        else
        {
            cout << "Invalid input. Please enter a number between 0 and 9." << endl;
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
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            uo = underOver();
            break;
        case 5:
            break;
        case 6:
            uo = underOver();
            break;
        case 7:
            uo = underOver();
            break;
        case 8:
            break;
        case 9:
            uo = underOver();
            break;
    }

}