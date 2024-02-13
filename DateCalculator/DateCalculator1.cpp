#include <iostream>
#include <string>
#include <ctime>
#include <cctype>

using std::cin;
using std::cout;
using std::endl;
using std::string;

double inputDouble();

const time_t MINUTE = 60;
const time_t HOUR = MINUTE * 60;
const time_t DAY = HOUR * 24;
const time_t MONTH = DAY * 30;
const time_t YEAR = MONTH * 12;



int main(int argc, char *argv[]){
    time_t date = time(0);
    cout<<"date is: "<<ctime(&date)<<endl<<"How many Years to add? ";
    double toAdd=-0;
    toAdd = inputDouble();
    date += YEAR * toAdd;
    cout<<"Adding "<<toAdd<<" years."<<endl<<"How many months to add? ";
    toAdd = inputDouble();
    cout<<"Adding "<<toAdd<<" months."<<endl<<"How many days to add? ";
    date+= MONTH * toAdd;
    toAdd = inputDouble();
    date+= DAY * toAdd;
    cout<<"Adding "<<toAdd<<" days."<<endl<<"How many hours to add? ";
    toAdd = inputDouble();
    date+= HOUR * toAdd;
    cout<<"Adding "<<toAdd<<" hours."<<endl<<"How many minutes to add? ";
    toAdd = inputDouble();
    date+= MINUTE * toAdd;
    cout<<"Adding "<<toAdd<<" minutes."<<endl<<"How many seconds to add? ";
    toAdd = inputDouble();
    date+= toAdd;

    cout<<"new date is: "<<ctime(&date)<<endl;
    return EXIT_FAILURE;
}

double inputDouble(){
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
    }
    toGet = stod(strIn);
    return toGet;
}