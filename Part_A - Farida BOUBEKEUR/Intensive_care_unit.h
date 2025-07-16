// Farida Boubekeur
// class that represents the intensive care unit
// header file of class IntensiveCareUnit

#ifndef INTENSIVE_CARE_UNIT
#define INTENSIVE_CARE_UNIT

#include <iostream>
#include <ctime>
#include <string>
#include "Patient.h"
#include "ICU_Hash_table.h"

class IntensiveCareUnit
{
public:
    IntensiveCareUnit();                                     // constructor
    ~IntensiveCareUnit();                                    // destructor
    bool insert(const Patient &);                            // add patient to the unit
    bool remove(const Patient &);                            // remove a patient from the unit
    void insertHistory_remove(const Patient &, const int &); // insert the patient in the history of the unit (in the hospital) when leaving the ICU
    void insertHistory_insertion(const Patient &p);          // insert the patient in the history of the unit (in the hospital) when entring the ICU

    // printing functions
    // prints the information of the patient in the unit
    void patientInformation(Patient); // not const because showPatientData modifies the object

    // prints the content of the history
    void ICU_history(void) const;
    // prints the patients that are in the unit
    void ICU_listPatient(void) const;

    // gets the total number of patients in the unit
    int getNumOfPatients(void) const { return patients_list.getTotalPatients(); }

    // get a specific patient
    Patient specifyPatient(unsigned long);
    // get total number of deaths in the unit
    int getNumOfDeaths() const { return numOfDeaths; }

private:
    HashTable patients_list; // the patients are added in a hash table
    static int numOfDeaths;  // keep track of the number of deaths in each service of the unit
    static int numOfFile;    // used in insertHistory function
    string FileName;         // file name of the unit's history
};

#endif