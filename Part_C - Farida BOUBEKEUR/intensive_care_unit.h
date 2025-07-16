// farida boubekeur
//  class that represents the intensive care unit
//  header file of class IntensiveCareUnit with its functions
#include <iostream>
#include "Critical_State_Unit.h"
#include <cstring>
#include <time.h>
#include <iomanip>
#include <fstream>
using namespace std;
CriticalStateUnit unit;

class IntensiveCareUnit
{
public:
    IntensiveCareUnit();                                     // constructor
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
    int getNumOfPatients(void) const { return patients_list.getTotalPatient(); }

    // get a specific patient
    Patient specifyPatient(unsigned long);
    // get total number of deaths in the unit
    int getNumOfDeaths() const { return numOfDeaths; }

private:
    AvlTree patients_list; // the patients are added in a hash table
    static int numOfDeaths;
    static int numOfFile;
    string FileName;
};

int IntensiveCareUnit::numOfFile = 0;
int IntensiveCareUnit::numOfDeaths = 0;

IntensiveCareUnit::IntensiveCareUnit()
{

    numOfFile++;
    FileName = "ICU_history " + to_string(numOfFile) + " .txt";
}

bool IntensiveCareUnit::insert(const Patient &p)
{
    if (patients_list.contains(p))
    {
        cout << "This patient is already in our service" << endl;
        return false;
    }
    insertHistory_insertion(p); // add patient to the history of the ICU
    patients_list.insert(p);
    return true;
}

bool IntensiveCareUnit::remove(const Patient &p)
{
    if (!patients_list.contains(p))
    {
        cout << "No patient with this ID" << endl;
        return false;
    }
    cout << "Enter reason why Patient is removed: "
            "\n1:Patient passed away"
            "\n2:Patient is allowed to go"
            "\n3:Patient moved to Critical State Unit"
         << endl;
    int choice;
    cin >> choice;
    // Save in ICU history
    switch (choice)
    {
    case 1:
        insertHistory_remove(p, 1);
        numOfDeaths++;
        break;
    case 2:
        insertHistory_remove(p, 2);
        break;
    case 3:
        unit.insert(p);
        insertHistory_remove(p, 3);
        break;
    }
    patients_list.remove(p);
    return true;
}

void IntensiveCareUnit::insertHistory_insertion(const Patient &p)
{
    fstream history;
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    cout << "\n\n\t\t\t\t\t\t\t\t" << asctime(timeinfo);

    // append at the end of the file
    history.open(FileName, ios::out | ios::app);
    if (history.is_open())
    {

        history << "\n\n\t\t\t\t\t\t\t\t" << asctime(timeinfo);
        timeinfo = localtime(&rawtime);
        history << "\n"
                << p.getFirstname() << " "
                << p.getLastname() << " ---- " << p.getage() << " years old "
                << " ---- "
                << " Entered to ICU service." << endl;

        system("pause");
        system("cls");
        history.close();
    }

    else
        cout << "Could not open hsitory due to some technical issues!" << endl;
}
void IntensiveCareUnit::insertHistory_remove(const Patient &p, const int &which)
{
    fstream history;
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    cout << "\n\n\t\t\t\t\t\t\t\t" << asctime(timeinfo);

    // append at the end of the file
    history.open(FileName, ios::out | ios::app);
    if (history.is_open())
    {
        switch (which)
        {
        case 1:
        {

            history << "\n\n\t\t\t\t\t\t\t\t" << asctime(timeinfo);
            timeinfo = localtime(&rawtime);
            history << "\n"
                    << p.getFirstname() << " "
                    << p.getLastname() << " ---- " << p.getage() << " years old "
                    << " ---- "
                    << " Passed away." << endl;
            break;
        }
        case 2:
        {
            history << "\n\n\t\t\t\t\t\t\t\t" << asctime(timeinfo);
            timeinfo = localtime(&rawtime);
            history << "\n"
                    << p.getFirstname() << " "
                    << p.getLastname() << " ---- " << p.getage() << "years old "
                    << " ---- "
                    << " Released." << endl;
            break;
        }
        case 3:
        {

            history << "\n\n\t\t\t\t\t\t\t\t" << asctime(timeinfo);
            timeinfo = localtime(&rawtime);
            history << "\n"
                    << p.getFirstname() << " "
                    << p.getLastname() << " ---- " << p.getage() << "years old "
                    << " ---- "
                    << " Moved to CSU service." << endl;
            break;
        }
        }
        system("pause");
        system("cls");
        history.close();
    }

    else
        cout << "Could not open hsitory due to some technical issues!" << endl;
}

void IntensiveCareUnit::ICU_history(void) const
{
    fstream history;
    history.open(FileName, ios::in);
    if (history.is_open())
    {
        string line;
        while (getline(history, line))
            cout << line << endl;

        cout << endl;
        system("pause");
        system("cls");
        history.close();
    }
    else
    {
        cout << "Couldn't open ICU history due to some technical issue" << endl;
        return;
    }
}
void IntensiveCareUnit::ICU_listPatient() const
{
    patients_list.print();
}
void IntensiveCareUnit::patientInformation(Patient p) { p.showPatientData(); }

Patient IntensiveCareUnit::specifyPatient(unsigned long id)
{
    return patients_list.getPatient(id);
}
