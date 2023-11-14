#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

mt19937 random_mt;

int Random(int min, int max)
{
    uniform_int_distribution<int> dist(min, max);
    return dist(random_mt);
}

void RollDice(int numberOfRolls, int numberOfSides)
{
    map<int, int> resultsMap;

    for (int i = 1; i <= numberOfSides; i++)
    {
        resultsMap[i] = 0;
    }

    for (int i = 0; i < numberOfRolls; i++)
    {
        int total = 0;
        for (int j = 0; j < 30; j++)
        {
            total += Random(1, numberOfSides);
        }
        resultsMap[static_cast<int>(round(total/30))]++; 

    }

    for (const auto &pair : resultsMap)
    {
        cout << pair.first << ": " << pair.second << '\n';
    }
}

class State
{
public:
    string name;
    int perCapitaIncome;
    int population;
    int medianHouseholdIncome;
    int numberOfHouseholds;

    State() : name(""), perCapitaIncome(0), population(0), medianHouseholdIncome(0), numberOfHouseholds(0) {}

    State(string name, int perCapitaIncome, int population, int medianHouseholdIncome, int numberOfHouseholds)
        : name(name),
          perCapitaIncome(perCapitaIncome),
          population(population),
          medianHouseholdIncome(medianHouseholdIncome),
          numberOfHouseholds(numberOfHouseholds) {}

    void printState()
    {
        cout << name << '\n';
        cout << "Population: " << population << '\n';
        cout << "Per Capita Income: " << perCapitaIncome << '\n';
        cout << "Median Household Income: " << medianHouseholdIncome << '\n';
        cout << "Number of Households: " << numberOfHouseholds << '\n';
    }
};

map<string, State> getStates(const string &filename)
{
    map<string, State> stateMap;
    ifstream file(filename);

    string line;
    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);
        vector<int> stateData;

        string name;
        getline(ss, name, ',');

        string value;
        while (getline(ss, value, ','))
        {
            stateData.push_back(stoi(value));
        }

        stateMap[name] = State(name, stateData[0], stateData[1], stateData[2], stateData[3]);
    }
    file.close();

    return stateMap;
}

int main()
{
    cout << "1. Random Numbers\n";
    cout << "2. State Info\n";

    int option;
    cin >> option;

    if (option == 1)
    {
        int randomSeed;
        cout << "Random seed value: ";
        cin >> randomSeed;
        random_mt.seed(randomSeed);

        int numberOfRolls;
        cout << "Number of times to roll the die: ";
        cin >> numberOfRolls;
        // user input
        int numberOfSides;
        cout << "Number of sides on this die: ";
        cin >> numberOfSides;
        RollDice(numberOfRolls, numberOfSides);

        // Roll Dice
    }
    else if (option == 2)
    {
        map<string, State> stateMap = getStates("states.csv");
        cout << "1. Print all states\n";
        cout << "2. Search for a state\n";
        cin >> option;

        if (option == 1)
        {
            for (auto &pair : stateMap)
            {
                pair.second.printState();
            }
        }

        if (option == 2)
        {
            string name;
            cin >> name;
            auto pair = stateMap.find(name);
            if (pair == stateMap.end())
            {
                cout << "No match found for " << name << '\n';
            }
            else
            {
                stateMap[name].printState();
            }
        }
    }

    return 0;
}
