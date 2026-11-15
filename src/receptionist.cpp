#include "receptionist.h"
#include "businessConfig.h"
#include <iostream>
#include <cstddef>
using namespace std;
namespace{
    int custCounter=1000;
    string generateCustomerId(){
        return "CUST-"+to_string(++custCounter);
    }
}
namespace{
    int appCounter=5000;
    string generateAppointmentId(){
        return "APT-"+to_string(++appCounter);
    }
}
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
    bool isSlotAvailable(vector<appointment>& a,const businessConfig& config,string d, string t) {
        for(size_t i=0; i<a.size(); i++){
            if(a[i].getDate()==d && a[i].getStatus()!="Cancelled" && timeToMin(t)<timeToMin(a[i].getTime())+config.getAppointmentDuration() && timeToMin(t)+config.getAppointmentDuration()>timeToMin(a[i].getTime())) return false;
        }
        return true;
    }
}
void addCust(vector<customer>& c,string n, string p){
    string id=generateCustomerId();
    c.emplace_back(id,n,p);
}
bool appointmentFit(const businessConfig& config,string t){
    if(!(isValidTime(t))) return false;
    if(timeToMin(t)>timeToMin(config.getCloseTime()) || timeToMin(t)<timeToMin(config.getOpenTime()) || timeToMin(t)+config.getAppointmentDuration() > timeToMin(config.getCloseTime())) return false;
    return true;
}
bool addApp(vector<appointment>& a,const businessConfig& config,customer c,string d,string t){
    if(appointmentFit(config,t) && isSlotAvailable(a,config,d,t)){
        string id=generateAppointmentId();
        a.emplace_back(c,id,d,t);
        return true;
    }
    return false;
}
void displayAp(const vector<appointment>& a){
    for(size_t i=0;i<a.size();i++){
        a[i].displayApp();
    }
}
void displayCust(const vector<customer>& c){
    for(size_t i=0;i<c.size();i++){
        c[i].display();
    }
}
int searchCust(const vector<customer>& c,string p){
    for(size_t i=0;i<c.size();i++){
        if(c[i].getPhone()==p){
            return i;
        }
    }
    return -1;
}
bool searchApp(const vector<appointment>& a,string p){
    bool flag=false;
    for(size_t i=0;i<a.size();i++){
        if(a[i].getCustPhone()==p){
            a[i].displayApp();
            flag=true;
        }
    }
    return flag;
}
bool cancelApp(vector<appointment>& a,string p,string d){
    for(size_t i=0;i<a.size();i++){
        if(a[i].getCustPhone()==p && a[i].getDate()==d){
            return a[i].setStatus("Cancelled");
        }
    }
    return false;
}
bool updateApp(vector<appointment>& a,string s,string p,string t,string d){
    for(size_t i=0;i<a.size();i++){
        if(a[i].getCustPhone()==p && a[i].getDate()==d && a[i].getTime()==t){
            return a[i].setStatus(s);
        }
    }
    return false;
}