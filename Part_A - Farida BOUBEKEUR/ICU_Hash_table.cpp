// Farida BOUBEKEUR
//  implementation file of class HashTable
#include "ICU_Hash_table.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <functional>

using namespace std;

bool HashTable::insert(const Patient &p)
{
    // no need to check if the patient is already in the table since
    // it was checked in ICU insert function
    int currentPos = findPos(p.getID());
    if (isActive(currentPos))
        return false;

    if (++totalPatients >= tableSize)
        H_table = rehash();

    H_table[currentPos].info = Patient::ACTIVE;
    H_table[currentPos] = p;
    Patient temp;
    temp = p;
    temp.addPatientFile();
}

void HashTable::remove(const Patient &p)
{
    // no need to check if the patient is not in the table since
    // it was checked in ICU remove function

    H_table[findPos(p.getID())].info = Patient::EMPTY;
    totalPatients--;
}

bool HashTable::contains(const Patient &p)
{
    for (auto &x : H_table)
        if (x.info != Patient::EMPTY && x.getID() == p.getID())
            return true;

    return false;
}

void HashTable::print(void) const
{
    if (totalPatients == 0)
    {
        cout << " No Patient In Here!" << endl;
        return;
    }
    cout << "\nList of current patients in the service:" << endl;
    int count = 0;
    for (auto &x : H_table)
    {
        if (x.info != Patient::EMPTY)
        {
            count++;
            cout << "Patient " << count << " : " << endl;

            cout << "first Name:   "
                 << x.getFirstname() << endl;
            cout << "last Name:   "
                 << x.getLastname() << endl;
            cout << "Age:    "
                 << x.getage() << endl;
            cout << "ID:     "
                 << x.getID() << endl;
        }
    }
    cout << "\nThere is/are " << totalPatients << " patient(s) in total in the unit " << endl;
}

Patient HashTable::getPatient(const unsigned long &ID)
{
    return H_table[findPos(ID)];
}
