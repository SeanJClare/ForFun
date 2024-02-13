#include <iostream>
#include <string>
#include <chrono>
#include <cctype>
#include "date.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

using std::chrono::system_clock;
using std::chrono::time_point;
using std::chrono::duration;

int inputInt(int min, int max);




int main(int argc, char *argv[]){
    using namespace std::chrono;
    using namespace date;

    // Current time
    time_point<system_clock> clock;
    clock = system_clock::now();

    // Get a days-precision chrono::time_point (yyy-mm-dd)
    auto currDay = floor<days>(clock);
    // Record the time of day (Add back to system clock later)
    auto time_of_day = clock - currDay;
    // Convert to a y/m/d calendar data structure
    year_month_day ymd;
    
    // Current Date
    time_t timeNow = system_clock::to_time_t(clock);
    cout<<"date is: "<<ctime(&timeNow)<<endl<<" How many seconds to add? ";
    
    
    int toAdd = inputInt(0,60);
    cout<<"Adding "<<toAdd<<" seconds."<<endl<<" How many minutes to add? ";
    // Seconds
    time_of_day+= std::chrono::seconds(toAdd);

    toAdd = inputInt(0,60);
    cout<<"Adding "<<toAdd<<" minutes."<<endl<<" How many hours to add? ";
    // Minutes
    time_of_day+= std::chrono::minutes(toAdd);

    toAdd = inputInt(0,24);
    cout<<"Adding "<<toAdd<<" hours."<<endl<<" How many days to add? ";
    // Hours
    time_of_day+= std::chrono::hours(toAdd);

    toAdd = inputInt(0,31);
    cout<<"Adding "<<toAdd<<" days."<<endl<<" How many months to add? ";
    // Days
    ymd = currDay + days{toAdd};

    toAdd = inputInt(0,12);
    cout<<"Adding "<<toAdd<<" months."<<endl<<" How many years to add? ";
    // Months
    ymd += months{toAdd};

    toAdd = inputInt(-0,-0);
    cout<<"Adding "<<toAdd<<" years."<<endl;
    // Years
    ymd += years{toAdd};

    // Combine remaining time and calendar to make a readable time
    // time_t newTime = system_clock::to_time_t();
    long timeSec = std::chrono::seconds(time_of_day);
    cout<<"new time: "<<ymd+seconds{}<<" : "<<endl;
    return 0;
}

int inputInt(int min, int max){
    double toGet=-0;
    string strIn;
    bool isValid=false;
    while(!isValid){
        cin>>strIn;
        isValid=true;
        for(uint i=0;i<strIn.size();++i){
            if(isalpha(strIn[i])||isspace(strIn[i])||iscntrl(strIn[i])){
                isValid = false;
                cin.ignore();
                cin.clear();
                cout<<"Please enter numbers only."<<endl<<"How many Years to add? ";
            }
        }
        if(isValid){
            toGet = stoi(strIn);
            if(min!=-0&&toGet<min){
                isValid=false;
                cout<<"Please ensure number falls in range for time type.";
            }else if(max!=-0&&toGet>max){
                isValid=false;
                cout<<"Please ensure number falls in range for time type.";
            }
        }
    }
    return toGet;
}