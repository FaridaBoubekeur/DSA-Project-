// Farida BOUBEKEUR
//  driver program
//  the intensive care unit program (main)

#include "Patient.h"
#include "ICU_Hash_table.h"
#include "Critical_State_Unit.h"
#include "Intensive_care_unit.h"
#include <iostream>
#include <cstring>
#include <chrono>  // to calcualate the average time
#include <conio.h> // to use getch() funtion
#include <time.h>  //for srand (time(0))
#include <iomanip>
#include <fstream>    // for files
#include <functional> // for the hash function

// class objects for different services
// declared global in case we need them for a function
IntensiveCareUnit cardiology;
IntensiveCareUnit pneumology;
IntensiveCareUnit gynaecology;

using namespace std;

int main()
{

    // couting WELCOME

    cout << "\t\t\t WELCOME TO " << endl;
    cout << "\n\t\t Hospital Care Units System" << endl;
    cout << "**************************************************************************" << endl;

    // variables for counting average time
    int totalTime = 0, counter = 0;
    vector<int> times(10);

    bool EXIT = false;
    while (!EXIT)
    {

        // LOGIN

        unsigned long DoctorID = 2112000000, // presents the part of ID shared between all doctors: 2112******
            DirectorID = 2175634298;

        cout << endl
             << "\t\t LOGIN" << endl;
        cout << "Enter your ID: ";

        // entering the ID as ******
        char sID[10]; // ID is 10 chars long
        char ch;
        ch = getch();
        for (int i = 0; i < 10; i++)
        {
            sID[i] = ch;
            cout << '*';
            ch = getch();
        }

        unsigned long ID;
        char *end;
        ID = strtoul(sID, &end, 10);

        cout << endl
             << "_______________________________________________" << endl;

        /*___________________________DOCTOR/nurse SECTION__________________________________*/

        // display for doctors and nurses
        if (ID >= 2112000000 && ID <= 2112999999)
        { // because the IDs of different doctors are different

            bool exit = false;

            if (ID >= 2112350000 && ID <= 2112359999)
            { // cardiology service

                cout << "Welcome to the cardiology service" << endl;

                while (!exit)
                {

                    cout << "_____________________________________________" << endl;
                    cout << "Choose one of the following options: " << endl
                         << endl;

                    cout << "\t 1 >> Add a new patient to the service" << endl;
                    cout << "\t 2 >> Release a patient" << endl;
                    cout << "\t 3 >> Access the information of a patient" << endl;
                    cout << "\t 4 >> Track the status of a patient " << endl; // print cyclically the information of one of the patient
                    cout << "\t 5 >> Log out" << endl;
                    cout << "\t 6 >> Quit the system" << endl;

                    int choice;
                    cin >> choice;

                    cout << "____________________________________" << endl
                         << endl;

                    switch (choice)
                    {
                    case 1: // Adding a new patient
                    {
                        cout << "Enter the name of the new patient: ";
                        cout << "First Name: ";
                        string FirstName;
                        cin >> FirstName;
                        cout << "Last Name: ";
                        string LastName;
                        cin >> LastName;
                        cout << "Enter the age of this new patient: ";
                        unsigned int Age;
                        cin >> Age;
                        Patient NewPatient(FirstName, LastName, Age);
                        auto start = chrono::steady_clock::now();
                        cardiology.insert(NewPatient);
                        auto end = chrono::steady_clock::now();
                        times[counter] = chrono::duration_cast<chrono::milliseconds>(end - start).count();
                        totalTime += times[totalTime];
                        counter++;
                        break;
                    }

                    case 2: // Releasing a patient
                    {
                        cardiology.ICU_listPatient();
                        cout << "Enter the ID of the patient you want to release: ";
                        unsigned long patientID;
                        cin >> patientID;
                        cardiology.remove(cardiology.specifyPatient(patientID));
                        break;
                    }

                    case 3:
                    { // Accessing the info of a certain patient
                        cardiology.ICU_listPatient();
                        cout << "Select a patient by entering his ID: ";
                        unsigned long patientID;
                        cin >> patientID;
                        cardiology.patientInformation(cardiology.specifyPatient(patientID));

                        break;
                    }
                    case 4:
                    { // Track the status of a patient i.e. cyclically printing his information
                        cardiology.ICU_listPatient();
                        cout << "Select a patient by entering his ID:  ";
                        unsigned long patientID;
                        cin >> patientID;
                        for (int i = 0; i < 20; i++)
                        {

                            cardiology.specifyPatient(patientID).printinfo();
                            _sleep(1000);
                        }

                        break;
                    }
                    case 5:
                    {
                        exit = true;
                        break;
                    }
                    case 6:
                    {
                        EXIT = true;
                        cout << "\n\t\tThank you for using our system" << endl;
                    }
                    default:
                    {
                        exit = true;
                        break;
                    }
                    }
                }
            }

            else if (ID >= 2112690000 && ID <= 2112699999)
            { // pneumology service

                cout << "Welcome to the pneumology sevice" << endl;

                while (!exit)
                {

                    cout << "____________________________________" << endl;
                    cout << "Choose one of the following options: " << endl
                         << endl;

                    cout << "\t 1 >> Add a new patient to the service" << endl;
                    cout << "\t 2 >> Release a patient" << endl;
                    cout << "\t 3 >> Access the information of a patient" << endl;
                    cout << "\t 4 >> Track the status of a patient " << endl; // print cyclically the information of one of the patient
                    cout << "\t 5 >> Log out" << endl;
                    cout << "\t 6 >> Quit the system" << endl;

                    int choice;
                    cin >> choice;

                    cout << "____________________________________" << endl
                         << endl;

                    switch (choice)
                    {
                    case 1: // Adding a new patient
                    {
                        cout << "Enter the name of the new patient: ";
                        cout << "First Name: ";
                        string FirstName;
                        cin >> FirstName;
                        cout << "Last Name: ";
                        string LastName;
                        cin >> LastName;
                        cout << "Enter the age of this new patient: ";
                        unsigned int Age;
                        cin >> Age;
                        Patient NewPatient(FirstName, LastName, Age);
                        auto start = chrono::steady_clock::now();
                        pneumology.insert(NewPatient);
                        auto end = chrono::steady_clock::now();

                        times[counter] = chrono::duration_cast<chrono::milliseconds>(end - start).count();
                        totalTime += times[totalTime];
                        counter++;
                        break;
                    }

                    case 2:
                    { // Releasing a patient
                        pneumology.ICU_listPatient();
                        cout << "Enter the ID of the patient you want to release: ";
                        unsigned long patientID;
                        cin >> patientID;
                        pneumology.remove(pneumology.specifyPatient(patientID));
                        break;
                    }
                    case 3:
                    { // Accessing the info of a certain patient
                        pneumology.ICU_listPatient();
                        cout << "Select a patient by entering his ID: ";
                        unsigned long patientID;
                        cin >> patientID;
                        pneumology.patientInformation(pneumology.specifyPatient(patientID));

                        break;
                    }
                    case 4:
                    { // Track the status of a patient i.e. cyclically printing his information
                        pneumology.ICU_listPatient();
                        cout << "Select a patient by entering his ID:  ";
                        unsigned long patientID;
                        cin >> patientID;

                        for (int i = 0; i < 20; i++)
                        {

                            pneumology.specifyPatient(patientID).printinfo();
                            _sleep(1000);
                        }

                        break;
                    }
                    case 5:
                    {
                        exit = true;
                        break;
                    }
                    case 6:
                    {
                        EXIT = true;
                        cout << "\n\t\tThank you for using our system" << endl;
                    }
                    default:
                    {
                        exit = true;
                        break;
                    }
                    }
                }
            }

            else if (ID >= 2112880000 && ID <= 2112889999)
            { // gynaecology service

                cout << "Welcome to the gynaecology sevice" << endl;

                while (!exit)
                {

                    cout << "____________________________________" << endl;
                    cout << "Choose one of the following options: " << endl
                         << endl;

                    cout << "\t 1 >> Add a new patient to the service" << endl;
                    cout << "\t 2 >> Release a patient" << endl;
                    cout << "\t 3 >> Access the information of a patient" << endl;
                    cout << "\t 4 >> Track the status of a patient " << endl; // print cyclically the information of one of the patient
                    cout << "\t 5 >> Log out" << endl;
                    cout << "\t 6 >> Quit the system" << endl;

                    int choice;
                    cin >> choice;

                    cout << "____________________________________" << endl
                         << endl;

                    switch (choice)
                    {
                    case 1: // Adding a new patient
                    {
                        cout << "Enter the name of the new patient: ";
                        cout << "First Name: ";
                        string FirstName;
                        cin >> FirstName;
                        cout << "Last Name: ";
                        string LastName;
                        cin >> LastName;
                        cout << "Enter the age of this new patient: ";
                        unsigned int Age;
                        cin >> Age;
                        Patient NewPatient(FirstName, LastName, Age);
                        auto start = chrono::steady_clock::now();
                        gynaecology.insert(NewPatient);
                        auto end = chrono::steady_clock::now();

                        times[counter] = chrono::duration_cast<chrono::milliseconds>(end - start).count();
                        totalTime += times[totalTime];
                        counter++;
                        break;
                    }

                    case 2:
                    { // Releasing a patient
                        gynaecology.ICU_listPatient();
                        cout << "Enter the ID of the patient you want to release: ";
                        unsigned long patientID;
                        cin >> patientID;
                        gynaecology.remove(gynaecology.specifyPatient(patientID));
                        break;
                    }
                    case 3:
                    { // Accessing the info of a certain patient
                        gynaecology.ICU_listPatient();
                        cout << "Select a patient by entering his ID: ";
                        unsigned long patientID;
                        cin >> patientID;
                        gynaecology.patientInformation(gynaecology.specifyPatient(patientID));

                        break;
                    }
                    case 4:
                    { // Track the status of a patient i.e. cyclically printing his information
                        gynaecology.ICU_listPatient();
                        cout << "Select a patient by entering his ID:  ";
                        unsigned long patientID;
                        cin >> patientID;

                        for (int i = 0; i < 20; i++)
                        {

                            gynaecology.specifyPatient(patientID).printinfo();
                            _sleep(1000);
                        }

                        break;
                    }
                    case 5:
                    {
                        exit = true;
                        break;
                    }
                    case 6:
                    {
                        EXIT = true;
                        cout << "\n\t\tThank you for using our system" << endl;
                    }
                    default:
                    {
                        exit = true;
                        break;
                    }
                    }
                }
            }
        }
        /*___________________________DIRECTOR SECTION__________________________________*/

        // display for the director
        else if (ID == 2175634298)
        {
            // director monitoring everything about every patient in any service

            bool exit = false;

            while (!exit)
            {

                cout << endl
                     << "Choose one of the following options: " << endl
                     << endl;

                cout << "\t 1 >> Access the history of an intensive care unit" << endl;
                cout << "\t 2 >> Get the number of deaths in all intensive care units" << endl;
                cout << "\t 3 >> Get the list of patients under treatment in an intensive care unit " << endl;
                cout << "\t 4 >> Access the information of a patient under treatment " << endl;
                cout << "\t 5 >> Log out" << endl;
                cout << "\t 6 >> Quit the system" << endl;

                int choice;
                cin >> choice;

                cout << "________________________________" << endl;

                switch (choice)
                {
                case 1: // access the history of one service
                {
                    cout << "Choose a service" << endl;
                    cout << "\t 1 >> Cardiology Intensive Care Unit" << endl;
                    cout << "\t 2 >> Pneumology Intensive Care Unit" << endl;
                    cout << "\t 3 >> Gynaecology Intensive Care Unit" << endl;

                    int choice2;
                    cin >> choice2;

                    cout << "________________________________" << endl;

                    switch (choice2)
                    {
                    case 1:
                        cardiology.ICU_history();
                        break;
                    case 2:
                        pneumology.ICU_history();
                        break;
                    case 3:
                        gynaecology.ICU_history();
                        break;

                    default:
                        cout << "No Intensive care unit meets your choice." << endl;
                        break;
                    }
                    break;
                }
                case 2: // get the number of deaths in all intensive care units
                {
                    cout << "The number of deaths in all intensive care units is now: " << gynaecology.getNumOfDeaths() << endl;

                    break;
                }
                case 3: // list of patients in a service
                {
                    cout << "Choose a service" << endl;
                    cout << "\t 1 >> Cardiology Intensive Care Unit" << endl;
                    cout << "\t 2 >> Pneumology Intensive Care Unit" << endl;
                    cout << "\t 3 >> Gynaecology Intensive Care Unit" << endl;

                    int choice2;
                    cin >> choice2;

                    cout << "________________________________" << endl;

                    switch (choice2)
                    {
                    case 1:
                        cardiology.ICU_listPatient();
                        break;
                    case 2:
                        pneumology.ICU_listPatient();
                        break;
                    case 3:
                        gynaecology.ICU_listPatient();
                        break;

                    default:
                        cout << "No Intensive care unit meets your choice." << endl;
                        break;
                    }

                    break;
                }
                case 4: // access the info of a spesific  patient

                {
                    cout << "Choose a service" << endl;
                    cout << "\t 1 >> Cardiology Intensive Care Unit" << endl;
                    cout << "\t 2 >> Pneumology Intensive Care Unit" << endl;
                    cout << "\t 3 >> Gynaecology Intensive Care Unit" << endl;

                    int choice2;
                    cin >> choice2;

                    cout << "________________________________" << endl;

                    switch (choice2)
                    {
                    case 1:
                    {
                        cardiology.ICU_listPatient();
                        cout << "________________________________" << endl;
                        cout << "Select a patient by entering his ID: " << endl;
                        unsigned long patientID;
                        cin >> patientID;
                        cardiology.patientInformation(cardiology.specifyPatient(patientID));
                        break;
                    }
                    case 2:
                    {
                        pneumology.ICU_listPatient();
                        cout << "________________________________" << endl;
                        cout << "Select a patient by entering his ID: " << endl;
                        unsigned long patientID;
                        cin >> patientID;
                        pneumology.patientInformation(pneumology.specifyPatient(patientID));
                        break;
                    }
                    case 3:
                    {
                        pneumology.ICU_listPatient();
                        cout << "________________________________" << endl;
                        cout << "Select a patient by entering his ID: " << endl;
                        unsigned long patientID;
                        cin >> patientID;
                        pneumology.patientInformation(pneumology.specifyPatient(patientID));
                        break;
                    }
                    default:
                    {
                        cout << "No Intensive care unit meets your choice." << endl;
                        break;
                    }
                    }

                    break;
                }
                case 5:
                {
                    exit = true;
                    break;
                }
                case 6:
                {
                    EXIT = true;
                    cout << "\n\t\tThank you for using our system" << endl;
                }
                default:
                {
                    exit = true;
                    break;
                }
                }

                cout << "________________________________" << endl;
            }
        }
        else
        {
            cout << "This ID is wrong, please enter a correct ID." << endl;
        }
    }
    cout << endl
         << endl
         << "________________________________________" << endl;
    for (int i = 0; i < counter; i++)
    {
        cout << "operation " << i + 1 << " : " << times[i] << endl;
    }
    cout << "the average time of " << counter << " operations is: " << totalTime / counter << " milliseconds" << endl;

    return 0;
}