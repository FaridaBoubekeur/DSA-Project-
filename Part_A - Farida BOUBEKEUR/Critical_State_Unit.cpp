// Farida Bouebekeur
// implementation file of class CriticalStateUnit
#include "Critical_State_Unit.h"
#include <iostream>

using namespace std;

CriticalStateUnit::CriticalStateUnit()
{
    HashTable patients_list(11); // initialize the hashtable with a prime size
                                 // for the sake of implementation good
}

CriticalStateUnit::~CriticalStateUnit() {}

bool CriticalStateUnit::insert(const Patient &p)
{
    if (patients_list.contains(p)) // Deny any patinet with same IDs
    {
        cout << "This patient is already in our service" << endl;
        return false;
    }
    patients_list.insert(p);
    return true;
}
