// Farida Boubekeur
//  class that represents the hash table where to store patients
//  header file of class HashTable
#ifndef ICU_HASH_TABLE
#define ICU_HASH_TABLE

#include <iostream>
#include <vector>
#include <math.h>
#include "Patient.h"
#include <functional>
using namespace std;
int nextPrime(int n);

//----------Using hashTable to insert a new patient-------------
class HashTable
{
public:
    // parameterized constructor with maximal number
    // of the Hospital's ICU patients
    HashTable() : tableSize(14)
    {
        H_table.reserve(tableSize); // allocate memory for a max of 14 patients in the memory
        H_table.resize(tableSize);
        makeEmpty();
    }

    // explicit constructor
    explicit HashTable(int s) : tableSize(s)
    {
        H_table.reserve(tableSize); // allocate memory for a max of 14 patients in the memory
        H_table.resize(tableSize);
        makeEmpty();
    }
    ~HashTable() {} // destructor
    // make the hash table empty
    void makeEmpty()
    {
        totalPatients = 0;
        for (auto &entry : H_table)
            entry.info = Patient::EMPTY;
    }

    // insert a new record of the patient in the hashtbale
    bool insert(const Patient &);
    // remove a record of the patient from the hashtbale
    void remove(const Patient &);
    // check if a patient is already inserted in the hash table
    bool contains(const Patient &p);
    // printing the content of the hash table
    void print(void) const;
    // get the total number of patients
    int getTotalPatients(void) const { return totalPatients; }
    Patient getPatient(const unsigned long &ID);
    //---------------fuctions to calculate next Prime number---------
    bool isPrime(int n)
    {
        for (int i = 2; i <= n / 2; i++)
        {
            if (n % i == 0)
                return false;
        }

        return true;
    }
    int nextPrime(int n)
    {
        int nPrime = n;
        bool found = false;

        while (!found)
        {
            nPrime++;
            if (isPrime(nPrime))
                found = true;
        }

        return nPrime;
    }

private:
    vector<Patient> H_table; // hash table is a vector of Patient object
    int totalPatients;       // the current number of patients
    int tableSize;
    // check if a cell is active or not
    bool isActive(int currentPos) const
    {
        return H_table[currentPos].info == Patient::ACTIVE;
    }

    // The suitable hash function for the case(linear probing)
    int hashFun(const unsigned long x, const int y)
    {
        return (x % tableSize + y) % tableSize;
    }

    /*
    Even though there is no need for rehashing since there is a maximum
    number of patient in ICU all over the globe, but we did just for the 'in case'
    */

    vector<Patient> rehash()
    {
        // copy hash table elements to a temporary vector
        vector<Patient> H_helper = H_table;

        // delete all elements of the hash table
        H_table.clear();
        // resize the HashTable with next prime
        tableSize = nextPrime(2 * tableSize);
        H_table.reserve(tableSize);
        H_table.resize(tableSize);
        totalPatients = 0;
        for (auto &x : H_table)
            x.info = Patient::EMPTY;

        // copy old elements to the resized hashtable
        // deleting H_helper element to free memory using std::move
        for (auto &x : H_helper)
        {
            if (x.info == Patient::ACTIVE)
                insert(move(x));
        }

        return H_table;
    }
    // function to find empty cell to insert in
    int findPos(const unsigned long &x)
    {
        int count = 0; // utility counter for linear probing
        int currentPos = hashFun(x, count);

        // we verify if the cell is empty and if the x(the index in the hash table ) is equal to the ID of the patient
        while (H_table[currentPos].info != Patient::EMPTY && H_table[currentPos].getID() != x)
        {
            count++;
            currentPos = hashFun(x, count);
        }

        return currentPos;
    }
};

#endif
