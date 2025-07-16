// farida boubekeur
// class that represents the patient
// header file of class Patient

#ifndef Patient_H
#define Patient_H

#include <iostream>
#include <string>

using namespace std;

class Patient
{
    friend class HashTable;

private:
    // personal information of the patient
    string FirstName;
    string LastName;
    unsigned int age;
    unsigned long ID;
    static unsigned long currentID;

    // utility funtion
    unsigned long determineID()
    {
        currentID++;
        return currentID;
    }

    // medical information of the patient
    struct MedicalInformation
    {
        struct bloodPressure
        {
            // blood pressure is misured by systolic and diastolic
            float systolic;
            float diastolic;
            bloodPressure() : systolic(0), diastolic(0) {}                               // default constructor
            bloodPressure(const float &s, const float &d) : systolic(s), diastolic(d) {} // parametrized constructor
            bloodPressure(float &&s, float &&d) : systolic(s), diastolic(d) {}           // move constructor
        };

        // setter of the heart Rate
        void setHr(float &h)
        {
            heartRate = h;
        }

        MedicalInformation() : heartRate(0) {} // default constructor
        MedicalInformation(float &h)           // parametrized constructor
        {
            setHr(h);
        }

        // heart rate of the patient
        float heartRate;
    };

public:
    // the state of the unit depending on his situation
    enum State
    {
        CRITICAL, // critical state unit
        ICU,      // ICU refers to intensive cate unit
        RELEASED, // realeased from the hospital
        DEAD
    };

    Patient();                                         // default constructor
    Patient(string n, string m, unsigned int a);       // parametrized constructor
    Patient(string &&n, string &&m, unsigned int &&a); // move constructor
    ~Patient();                                        // destructor

    // setters and getters of class Patient
    void setFirstname(string &n);
    void setLastname(string &m);
    string getFirstname() const;
    string getLastname() const;
    void setage(unsigned int &age);
    unsigned int getage() const;
    unsigned long getID() const;

    // show patient's data on the console
    void showPatientData();
    // add a patient to the file
    void addPatientFile();
    // print medical information of the patient
    void printinfo();

    // overloading of assignment operator
    Patient &operator=(const Patient &p);

    // overloading of < operator
    bool operator<(const Patient &p);

    // presence of the patient in the unit (used  in the hash table)
    enum validity // specify whether the vector cell is valid
    {
        ACTIVE,
        EMPTY
    };
    validity info;
};
#endif