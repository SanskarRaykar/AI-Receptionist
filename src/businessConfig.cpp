#include<string>
#include<iostream>
#include <stdexcept>
#include "businessConfig.h"
using namespace std;
namespace{
    bool isValidTime(string t){
        if(t.size()!=5) return false;
        else if(t[2]!=':') return false;
        if(!(isdigit(t[0])) || !(isdigit(t[1])) || !(isdigit(t[3])) || !(isdigit(t[4]))) return false;
        int min=(int)(t[3]-'0')*10+(int)(t[4]-'0');
        int hr=(int)(t[0]-'0')*10+(int)(t[1]-'0');
        if(hr>=24) return false;
        else if(min>=60) return false;
        else return true;
    }
    int timeToMin(string t){
        int min=(int)(t[3]-'0')*10+(int)(t[4]-'0');
        int hr=(int)(t[0]-'0')*10+(int)(t[1]-'0');
        return hr*60+min;
    }
}
businessConfig::businessConfig(string ot,string ct){
    if(!(isValidTime(ct)) || !(isValidTime(ot))) throw invalid_argument("Wrong Time Entered");
    if(timeToMin(ct)<=timeToMin(ot)) throw invalid_argument("Close time Earlier then Open time");
    openTime=ot;
    closeTime=ct;
}
string businessConfig::getOpenTime() const{
    return openTime;
}
string businessConfig::getCloseTime() const{
    return closeTime;
}
int businessConfig::getAppointmentDuration() const{
    return appointmentDuration;
}
bool businessConfig::setAppointmentDuration(int ts) {
    if(ts>0){
        appointmentDuration=ts;
        return true;
    }
    return false;
}
bool businessConfig::setWorkingHours(string open,string close){
    if(!(isValidTime(open)) || !(isValidTime(close))) return false;
    if(timeToMin(close)<=timeToMin(open)) return false;
    openTime=open;
    closeTime=close;
    return true;
}
