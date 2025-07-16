// Farida BOUBEKEUR
//  critical state unit class where we insert a patient when its state is "Critical"
//   header file of the class CriticalStateUnit

#ifndef CRITICAL_STATE_UNIT_H
#define CRITICAL_STATE_UNIT_H

#include <iostream>
#include "ICU_Hash_table.h"

class CriticalStateUnit
{
public:
    CriticalStateUnit();          // default constructor
    ~CriticalStateUnit();         // destructor
    bool insert(const Patient &); // function that inserts a patient in that unit after remove it from the ICU

private:
    HashTable patients_list;
}; // end class CriticalStateUnit

#endif