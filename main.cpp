//
//  main.cpp
//  OmniSched: Polymorphic Appointment Planner
//
//  Created by Henry Warmerdam on 11/17/24.
//

#include <iostream>
#include <vector>
using namespace std;

// Appointment Class
class Appointment {
    public:
        // Default constructor
        Appointment();

        // Parameterized constructor
        Appointment(const string &description, int year, int month, int day, int hour, int minute);

        // Setters
        void setDescription(const string &description);
        void setDate(int year, int month, int day);
        void setTime(int hour, int minute);

        // Getters
        string getDescription() const;
        int getYear() const;
        int getMonth() const;
        int getDay() const;
        int getHour() const;
        int getMinute() const;

        virtual bool occurs_on(int year, int month, int day);

        // Print function
        virtual void Print() const;

    private:
        string description;
        int year;
        int month;
        int day;
        int hour;
        int minute;
};

// Appointment class function definitions

Appointment::Appointment() {
    this->description = "";
    this->year = 0;
    this->month = 0;
    this->day = 0;
    this->hour = 0;
    this->minute = 0;
}

Appointment::Appointment(const string &description, int year, int month, int day, int hour, int minute) {
    this->description = description;
    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
}

void Appointment::setDescription(const string &description) {
    this->description = description;
}

void Appointment::setDate(int year, int month, int day) {
    this->year = year;
    this->month = month;
    this->day = day;
}

void Appointment::setTime(int hour, int minute) {
    this->hour = hour;
    this->minute = minute;
}

string Appointment::getDescription() const {
    return description;
}

int Appointment::getYear() const {
    return year;
}

int Appointment::getMonth() const {
    return month;
}

int Appointment::getDay() const {
    return day;
}

int Appointment::getHour() const {
    return hour;
}

int Appointment::getMinute() const {
    return minute;
}

bool Appointment::occurs_on(int year, int month, int day) {
    return false;
}

void Appointment::Print() const {
    cout << "Appointment on " << month << "/" << day << "/" << year << " at " << hour << ":";
    if (minute < 10) {
        cout << "0" << minute;
    }
    else {
        cout << minute;
    }
    cout << " - " << description << endl;
}


// Onetime Class
class Onetime : public Appointment {
    public:
        // Default constructor
        Onetime();

        // Parameterized constructor
        Onetime(const string &description, int year, int month, int day, int hour, int minute);

        // occurs_on function
        bool occurs_on(int year, int month, int day);

        // Print function
        void Print() const;
};

// Onetime class function definitions

Onetime::Onetime() : Appointment() {}

Onetime::Onetime(const string &description, int year, int month, int day, int hour, int minute)
    : Appointment(description, year, month, day, hour, minute) {}

bool Onetime::occurs_on(int year, int month, int day) {
    return (getYear() == year && getMonth() == month && getDay() == day);
}

void Onetime::Print() const {
    cout << "Onetime ";
    Appointment::Print();
}


// Daily Class
class Daily : public Appointment {
    public:
        // Default constructor
        Daily();

        // Parameterized constructor
        Daily(const string &description, int hour, int minute);

        // occurs_on function
        bool occurs_on(int year, int month, int day);

        // Print function
        void Print() const;
};

// Daily class function definitions

Daily::Daily() : Appointment() {}

Daily::Daily(const string &description, int hour, int minute)
    : Appointment(description, 0, 0, 0, hour, minute) {}

bool Daily::occurs_on(int year, int month, int day) {
    return true;
}

void Daily::Print() const {
    cout << "Daily Appointment at " << getHour() << ":";
    if (getMinute() < 10) {
        cout << "0" << getMinute();
    }
    else {
        cout << getMinute();
    }
    cout << " - " << getDescription() << endl;
}


// Weekly Class
class Weekly : public Appointment {
    public:
        // Default constructor
        Weekly();

        // Parameterized constructor
        Weekly(const string &description, int weekday, int hour, int minute);

        // occurs_on function
        bool occurs_on(int year, int month, int day);

        // Print function
        void Print() const;

    private:
        int weekday;
};

// Weekly class function definitions

Weekly::Weekly() : Appointment(), weekday(0) {}

Weekly::Weekly(const string &description, int weekday, int hour, int minute)
    : Appointment(description, 0, 0, 0, hour, minute), weekday(weekday) {}

bool Weekly::occurs_on(int year, int month, int day) {
    return (day % 7 == weekday);
}

void Weekly::Print() const {
    cout << "Weekly Appointment on weekday " << weekday << " at " << getHour() << ":";
    if (getMinute() < 10) {
        cout << "0" << getMinute();
    }
    else {
        cout << getMinute();
    }
    cout << " - " << getDescription() << endl;
}

// Monthly Class
class Monthly : public Appointment {
    public:
        // Default constructor
        Monthly();

        // Parameterized constructor
        Monthly(const string &description, int day, int hour, int minute);

        // occurs_on function
        bool occurs_on(int year, int month, int day);

        // Print function
        void Print() const;

    private:
        int day_of_month;
};

// Monthly class function definitions

Monthly::Monthly() : Appointment(), day_of_month(0) {}

Monthly::Monthly(const string &description, int day, int hour, int minute)
    : Appointment(description, 0, 0, day, hour, minute), day_of_month(day) {}

bool Monthly::occurs_on(int year, int month, int day) {
    return (day == day_of_month);
}

void Monthly::Print() const {
    cout << "Monthly Appointment on day " << day_of_month << " at " << getHour() << ":";
    if (getMinute() < 10) {
        cout << "0" << getMinute();
    }
    else {
        cout << getMinute();
    }
    cout << " - " << getDescription() << endl;
}


int main() {
    vector<Appointment*> appointments;
    int userYear;
    int userMonth;
    int userDay;
    
    // Fill appointments vector with a mixture of appointments
    Onetime* appt1 = new Onetime("Orthodontist appointment", 2024, 12, 3, 9, 0);   // December 3, 2024 at 9:00 AM
    appointments.push_back(appt1);

    Daily* appt2 = new Daily("Chest day", 6, 0);   // Every day at 6:00 PM
    appointments.push_back(appt2);

    Weekly* appt3 = new Weekly("COMP-200-1201: Object Oriented Prog. C++", 1, 17, 20);   // Every Monday at 5:20 PM
    appointments.push_back(appt3);

    Monthly* appt4 = new Monthly("Pay credit card", 30, 8, 45);   // Every month on the 30th at 8:45 AM
    appointments.push_back(appt4);
    
    // Get date from user
    cout << "Enter a date to print out all appointments on that date." << endl;
    cout << "Enter year: ";
    cin >> userYear;
    cout << "Enter month: ";
    cin >> userMonth;
    cout << "Enter day: ";
    cin >> userDay;

    cout << endl << "All appointments on " << userMonth << "/" << userDay << "/" << userYear << ":" << endl;

    // Print appointments on given date
    for (int i = 0; i < appointments.size(); ++i) {
        if (appointments[i]->occurs_on(userYear, userMonth, userDay)) {
            appointments[i]->Print();
        }
    }
    cout << endl;
    
    for (int i = 0; i < appointments.size(); ++i) {
        delete appointments[i];
    }

    return 0;
}
