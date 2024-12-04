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
            "based on the parameter you specified and print out what you want!" << endl;
    cout << "What do you want printed? (Type 0-9)" << endl;
    cout << "0 - All cities in alphabetical order" << endl;
    cout << "1 - All cities with specified name" << endl;
    cout << "2 - All cities beginning with specified letter" << endl;
    cout << "3 - All cities in a specified timezone" << endl;
    cout << "4 - All cities with an exact specified population" << endl;
    cout << "5 - All cities under/over a specified population" << endl;
    cout << "6 - All cities in between two specified populations" << endl;
    cout << "7 - All cities under/over a specified latitude" << endl;
    cout << "8 - All cities under/over a specified longitude" << endl;
    cout << "9 - All cities in a specified state" << endl;
    cout << "10 - All cities under/over a specified elevation" << endl;
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

// still needs binary search and printing all the cities
void handleCase1(vector<City>& quick, vector<City>& merge)
{
    cout << "Which beginning character do you want to print? (Type a-zA-Z)" << endl;
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
                {
                    c = toupper(c);
                }
                break;
            }
            else
                cout << R"(Invalid input. Please enter a-zA-Z.)" << endl;
        }
        else
        {
            cout << R"(Invalid input. Please enter a-zA-Z.)" << endl;
            cin.clear();
        }
    }

    cout << "you want " << c << endl;

    pair<double, double> r = sorter(quick, merge);

    printResults(r.first, r.second);

}

void handleCase2(vector<City>& quick, vector<City>& merge){}

// still needs binary search and printing all the cities
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

    printResults(quickTime, mergeTime);

}

void handleCase4(vector<City>& quick, vector<City>& merge){}
void handleCase5(int ou, vector<City>& quick, vector<City>& merge){}
void handleCase6(vector<City>& quick, vector<City>& merge){}
void handleCase7(int ou, vector<City>& quick, vector<City>& merge){}
void handleCase8(int ou, vector<City>& quick, vector<City>& merge){}
void handleCase9(vector<City>& quick, vector<City>& merge){}
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
    pair<int, int> r = binarySearchRange<string>(quick, "Zythem", [](const City& city) {return city.getCityName();});

    cout << r.first << "   " << r.second << endl;

    for (int i = r.first; i <= r.second; i++)
    {
        cout << quick[i].getCityName() << endl;
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
            handleCase1(quick_cities, merge_cities);
            break;
        case 2:
            handleCase2(quick_cities, merge_cities);
            break;
        case 3:
            handleCase3(quick_cities, merge_cities);
            break;
        case 4:
            break;
        case 5:
            uo = underOver();
            break;
        case 6:
            break;
        case 7:
            uo = underOver();
            break;
        case 8:
            uo = underOver();
            break;
        case 9:
            testerStrings(quick_cities, merge_cities);
            break;
        case 10:
            uo = underOver();
            break;
    }

}