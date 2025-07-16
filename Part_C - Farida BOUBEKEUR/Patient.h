// farida boubekeur
//  class that represents the patient
//  header file of class Patient

#ifndef Patient_H
#define Patient_H

#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <fstream>

using namespace std;

class Patient
{

    friend class BSTree;

private:
    // personal information of the patient
    string FirstName;
    string LastName;
    unsigned int age;
    unsigned long ID;
    static unsigned long currentID;
    int key; // utility variable to avoid having degenerated tree

    // utility function
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
            bloodPressure() : systolic(0), diastolic(0) {}
            bloodPressure(const float &s, const float &d) : systolic(s), diastolic(d) {}
            bloodPressure(float &&s, float &&d) : systolic(s), diastolic(d) {}
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

    Patient();                                   // default constructor
    Patient(string n, string m, unsigned int a); // parametrized constructor

    // setters and getters of class Patient
    void setFirstname(string &n);
    void setLastname(string &m);
    string getFirstname() const;
    string getLastname() const;
    void setage(unsigned int &age);
    unsigned int getage() const;
    unsigned long getID() const;

    // get the key, used in BST and AVL tree version
    int getKey() const;

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

}; // end class Patient

unsigned long Patient::currentID = 2113000000;

Patient::Patient() : FirstName(" "), LastName(" "), age(0)
{
    srand(time(0));
    ID = determineID();
}

Patient::Patient(string n, string m, unsigned int a)
{
    srand(time(0));
    setFirstname(n);
    setLastname(m);
    setage(a);
    ID = determineID();
}

// using a  function  to check if a name is a string(not containing inapropriate characters )
bool containsOnlyLetters(string const &str)
{
    for (auto &c : str)
    {
        if (!isalpha(c))
        {
            return false;
        }
    }
    return true;
}

// setter and getters of class Patient
// setters

void Patient::setFirstname(string &n)
{
    FirstName = containsOnlyLetters(n) ? n : " ";
}

void Patient::setLastname(string &m)
{
    LastName = containsOnlyLetters(m) ? m : " ";
}

void Patient::setage(unsigned int &a)
{
    age = (a >= 0) ? a : 0;
}

// getters
string Patient::getFirstname() const
{
    return FirstName;
}
string Patient::getLastname() const
{
    return LastName;
}
unsigned int Patient::getage() const
{
    return age;
}

unsigned long Patient::getID() const
{
    return ID;
}

int Patient::getKey() const
{
    return key;
}

Patient &Patient::operator=(const Patient &p)
{
    FirstName = p.getFirstname();
    LastName = p.getLastname();
    age = p.getage();
    ID = p.getID();
    return *this;
}
// used to add patient to the file
void Patient::addPatientFile()
{

    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    cout << "\n\n\t\t\t\t\t\t\t\t" << asctime(timeinfo);
    fstream PatientDataBase;
    string fileName = "Patient " + to_string(ID) + " .txt";
    PatientDataBase.open(fileName, ios::out | ios::app);

    if (PatientDataBase.is_open())
    {
        cout << "\n***************************************\n";
        cout << "first Name : " << getFirstname() << endl;
        PatientDataBase << "first Name : ";
        PatientDataBase << getFirstname() << "\n";
        cout << "Last Name : " << getLastname() << endl;
        PatientDataBase << "last Name : ";
        PatientDataBase << getLastname() << "\n";
        cout << "Age :" << getage() << endl;
        PatientDataBase << "AGE : ";
        PatientDataBase << getage() << "\n";
        cout << "Patient ID : " << getID() << endl;
        PatientDataBase << "Patient ID : ";
        PatientDataBase << getID() << "\n";
        cout << "\n";
        cout
            << "\n***********************************************\n";
        PatientDataBase << "\n***********************************************\n\n";

        PatientDataBase << "BPS" << setw(12);

        PatientDataBase << "BPD"
                        << setw(12);

        PatientDataBase << "HEART RATE" << endl;
        cout << "\nInformation saved successfully \n";
    }
    system("pause");
    system("cls");
    PatientDataBase.close();
}

// show patient's data on the console
void Patient::showPatientData()
{
    fstream PatientDataBase;
    string fileName = "Patient " + to_string(ID) + " .txt";
    PatientDataBase.open(fileName, ios::in);
    if (!PatientDataBase)
    {
        cout << "\nError while opening the file \n";
    }
    else
    {
        cout << "\n\n\n\n\n\t........................................ Information "
             << "....................................\n\n";
        string info;
        while (PatientDataBase.good())
        {
            getline(PatientDataBase, info);
            cout << info << "\n";
        }
        cout << "\n";
    }
    PatientDataBase.close();
    system("pause");
    system("cls");
}

// print medical information of the patient
void Patient::printinfo()
{
    fstream PatientDataBase;
    time_t temps = time(0);
    tm *getTime = gmtime(&temps);
    cout << getTime->tm_hour << ":" << getTime->tm_min << ":" << getTime->tm_sec << endl;
    MedicalInformation::bloodPressure bpinfo;
    srand(time(0));
    bpinfo.systolic = 90 + rand() % 130; // interval between 90 and 220
    bpinfo.diastolic = 60 + rand() % 60; // interval between 60 and 120
    srand(time(0));
    MedicalInformation info;
    info.heartRate = 3 + rand() % 71; // interval between 3 and 74

    // print on the file
    string fileName = "Patient " + to_string(ID) + " .txt";
    PatientDataBase.open(fileName, ios::app);
    if (PatientDataBase.is_open())
    {
        cout << "\n***************************************\n";
        PatientDataBase << bpinfo.systolic << setw(20);

        PatientDataBase << bpinfo.diastolic
                        << setw(12);

        PatientDataBase << info.heartRate << endl;
        cout << "\n";
    }
    cout << "Blood Pressure:" << setw(20) << "SYSTOLIC:" << setw(20) << "DIASTOLIC:" << endl;
    cout << setw(35) << bpinfo.systolic << setw(20) << bpinfo.diastolic << endl;
    cout << "\nHeart Rate: " << setw(12) << info.heartRate << endl;
    PatientDataBase.close();
}
#endif