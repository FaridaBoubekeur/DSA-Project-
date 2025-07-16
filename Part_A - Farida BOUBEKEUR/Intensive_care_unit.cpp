// farida boubekeur
//  imeplementation of class ICU functions
#include <iostream>
#include "Intensive_care_unit.h"
#include "Patient.h"
#include "ICU_Hash_table.h"
#include "Critical_State_Unit.h"
#include <cstring>
#include <time.h>
#include <iomanip>
#include <fstream>

CriticalStateUnit unit;

int IntensiveCareUnit::numOfFile = 0;
int IntensiveCareUnit::numOfDeaths = 0;

IntensiveCareUnit::IntensiveCareUnit()
{
    HashTable patients_list(14);
    numOfFile++;
    FileName = "ICU_history " + to_string(numOfFile) + " .txt";
}
IntensiveCareUnit::~IntensiveCareUnit()
{
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
            history << "\n"
                    << p.getFirstname() << " "
                    << p.getLastname() << " ---- " << p.getage() << " years old "
                    << " ---- "
                    << " Passed away." << endl;
            break;
        }
        case 2:
        {
            history << "\n"
                    << p.getFirstname() << " "
                    << p.getLastname() << " ---- " << p.getage() << "years old "
                    << " ---- "
                    << " Released." << endl;
            break;
        }
        case 3:
        {
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
