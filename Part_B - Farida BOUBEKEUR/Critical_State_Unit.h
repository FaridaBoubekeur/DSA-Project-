// Farida Boubekeur
//  critical state unit class where we insert a patient when its state is "Critical"
//  header file of the class CriticalStateUnit

#include <iostream>
#include "Binary_Search_Tree.h"

class CriticalStateUnit
{
public:
    CriticalStateUnit(); // default constructor

    bool insert(const Patient &); // function that inserts a patient in that unit after remove it from the ICU

private:
    BSTree patients_list;
}; // end class CriticalStateUnit

CriticalStateUnit::CriticalStateUnit() {}

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
