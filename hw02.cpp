/* Blessing Yeboah
 * boy205
 * 09/18/2024
 * hw02: Functions, structs, vectors and file I/O
 */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


struct Warrior {
    string warriorname;
    int strength;
};

void displayWarriors(const vector<Warrior>& warriorsList);
void createWarrior(const string& name, vector<Warrior>& warriors, int strength);
void openStream(ifstream& warriorsFile);
size_t findWarriors(const vector<Warrior>& warriors, const string& name);
void battles(Warrior& warrior1, Warrior& warrior2);

int main() {
    ifstream warriorsFile;
    openStream(warriorsFile);

    vector<Warrior> warriors;

    string cue;
    while (warriorsFile >> cue) {
        //the input file will be split into 3 sections based on the cue

        if (cue == "Warrior") {

            string name;
            int strength;

            warriorsFile >> name;
            warriorsFile >> strength;
            createWarrior(name, warriors, strength);

        } else if (cue == "Status") {
            displayWarriors(warriors);

        } else {
            string warrior1, warrior2;

            warriorsFile >> warrior1 >> warrior2;

            //searching for the warrior by index

            size_t warrior1indx = findWarriors(warriors, warrior1);
            size_t warrior2indx = findWarriors(warriors, warrior2);

               if (warrior1indx == warriors.size() && warrior2indx == warriors.size()) {
                cout << "Both warriors " << warrior1 << " and " << warrior2 << " do not exist." << endl;
                } else if (warrior1indx == warriors.size()) {
                     cout << "Warrior " << warrior1 << " does not exist." << endl;
                     } else if (warrior2indx == warriors.size()) {
                        cout << "Warrior " << warrior2 << " does not exist." << endl;
                        } else {
                            battles(warriors[warrior1indx], warriors[warrior2indx]);
                }
        }
    }

    warriorsFile.close();
}


void openStream(ifstream& warriorsFile) {
    //attempts to open file and outputs a string and int if failed
    warriorsFile.open("warriors.txt");

    if (!warriorsFile.is_open()) {
        cout << "Error opening file" << endl;
        exit(1);
    }

}

void displayWarriors(const vector<Warrior>& warriorsList) {
    cout << "There are: "  << warriorsList.size() << " warriors" << endl;
    for (const Warrior& warname: warriorsList) {
        //iterating through vector and displaying warriors
        cout << "Warrior: "<< warname.warriorname << ", strength: " << warname.strength << endl;
    }
}
//keep pass by reference to change the vector, we don't need a copy each time!
void createWarrior(const string& name, vector<Warrior>& warriors, int strength) {
    size_t indx = findWarriors(warriors, name);
    if (indx == warriors.size()) {
        //creating warrior name based off of input name and strength into vector
        Warrior newName;
        newName.warriorname = name;
        newName.strength = strength;
        warriors.push_back(newName);
    }
    //warrior exists
}

size_t findWarriors(const vector<Warrior>& warriors, const string& name) {

    //checking if the warrior exists, if so the index of the warrior will be returned
    for(size_t i = 0 ; i < warriors.size(); i++) {
        if(warriors[i].warriorname == name) {
            return i;
        }
    }
    return warriors.size();
}

void battles(Warrior& warrior1, Warrior& warrior2) {
    //warriors battle, their strengths determine end output
    cout << warrior1.warriorname << " battles " << warrior2.warriorname << endl;
    if (warrior1.strength == 0 && warrior2.strength ==0 ) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if (warrior1.strength == 0) {
        cout << "He's dead, " << warrior2.warriorname << endl;
    }
    else if (warrior2.strength == 0) {
        cout << "He's dead, " << warrior1.warriorname << endl;
    }
    else {
        if (warrior1.strength == warrior2.strength) {
            warrior1.strength = 0;
            warrior2.strength = 0;
            cout << "Mutual Annihilation: " << warrior1.warriorname << " and "
            << warrior2.warriorname << " die at each other's hands" << endl;
        }
        else if (warrior1.strength > warrior2.strength) {
            warrior1.strength -= warrior2.strength;
            warrior2.strength = 0;
            cout << warrior1.warriorname << " defeats " << warrior2.warriorname << endl;
        }
        else if (warrior2.strength > warrior1.strength) {
            warrior2.strength -= warrior1.strength;
            warrior1.strength = 0;
            cout << warrior2.warriorname << " defeats " << warrior1.warriorname << endl;
        }

    }
}