// farida boubekeur
//  critical state unit class where we insert a patient when its state is "Critical"
//  header file of the class CriticalStateUnit

#include <iostream>
#include "AVL_Tree.h"
class CriticalStateUnit
{
public:
    CriticalStateUnit();
    bool insert(const Patient &); // function that inserts a patient in that unit after remove it from the ICU

private:
    AvlTree patients_list;
};

CriticalStateUnit::CriticalStateUnit()
{
}

bool CriticalStateUnit::insert(const Patient &p)
{
    if (patients_list.contains(p))
    {
        cout << "This patient is already in our service" << endl;
        return false;
    }
    patients_list.insert(p);
    return true;
}
