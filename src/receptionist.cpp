#include "receptionist.h"
#include "businessConfig.h"
#include <iostream>
#include <cstddef>
#include<ctime>
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
    int timeToMin(string t){
        int min=(int)(t[3]-'0')*10+(int)(t[4]-'0');
        int hr=(int)(t[0]-'0')*10+(int)(t[1]-'0');
        return hr*60+min;
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
    bool isValidDate(string d){
        if(d.size()!=10) return false;
        else if(d[2]!='-' || d[5]!='-') return false;
        else if(!(isdigit(d[0])) || !(isdigit(d[1])) || !(isdigit(d[3])) || !(isdigit(d[4])) || !(isdigit(d[6])) || !(isdigit(d[7])) || !(isdigit(d[8])) || !(isdigit(d[9]))) return false;
        int month=(int)(d[3]-'0')*10+(int)(d[4]-'0');
        int date=(int)(d[0]-'0')*10+(int)(d[1]-'0');
        int year=(int)(d[6]-'0')*1000+(int)(d[7]-'0')*100+(int)(d[8]-'0')*10+(int)(d[9]-'0');
        if(date<1) return false;
        if(month<1 || month>12) return false;
        else if(month==1 ||month==3 ||month==5 ||month==7 ||month==8 ||month==10 ||month==12){
            if(date<=31) return true;
            else return false;
        }
        else if(month==4 ||month==6 ||month==9 ||month==11){
            if(date<=30) return true;
            else return false;
        }
        else{
            if((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)){
                if(date<=29) return true;
                else return false;
            }
            else{
                if(date<=28) return true;
                else return false;
            }
        }
    }
    bool isPastDate(string d){
        time_t now=time(nullptr);
        tm* current=localtime(&now);
        if(current==nullptr){
            cout<<"Error: Unable to retrive current date";
            return false;
        }
        int month=(int)(d[3]-'0')*10+(int)(d[4]-'0');
        int date=(int)(d[0]-'0')*10+(int)(d[1]-'0');
        int year=(int)(d[6]-'0')*1000+(int)(d[7]-'0')*100+(int)(d[8]-'0')*10+(int)(d[9]-'0');
        if(year<current->tm_year+1900) return true;
        else if(year==current->tm_year+1900 && month<current->tm_mon+1) return true;
        else if(year==current->tm_year+1900 && month==current->tm_mon+1 && date<current->tm_mday) return true;
        return false;
    }
    bool isToday(string d){
        time_t now=time(nullptr);
        tm* current=localtime(&now);
        if(current==nullptr){
            cout<<"Error: Unable to retrive current date";
            return false;
        }  
        int month=(int)(d[3]-'0')*10+(int)(d[4]-'0');
        int date=(int)(d[0]-'0')*10+(int)(d[1]-'0');
        int year=(int)(d[6]-'0')*1000+(int)(d[7]-'0')*100+(int)(d[8]-'0')*10+(int)(d[9]-'0');
        if(year==current->tm_year+1900 && month==current->tm_mon+1 && date==current->tm_mday) return true;
        return false; 
    }
    bool isPastTime(string t){
        time_t now=time(nullptr);
        tm* current=localtime(&now);
        if(current==nullptr){
            cout<<"Error: Unable to retrive current date";
            return false;
        }
        if(!isValidTime(t)) return false;
        int appt=timeToMin(t);
        int present = current->tm_hour*60 + current->tm_min;
        if(appt>present) return false;
        return true;
    }
    bool isSlotAvailable(vector<appointment>& a,const businessConfig& config,string d, string t) {
        for(size_t i=0; i<a.size(); i++){
            if(a[i].getDate()==d && a[i].getStatus()!="Cancelled" && timeToMin(t)<timeToMin(a[i].getTime())+config.getAppointmentDuration() && timeToMin(t)+config.getAppointmentDuration()>timeToMin(a[i].getTime())) return false;
        }
        return true;
    }
    bool isValidPhone(string p,const vector<customer>& c){
        if(p.size()!=10) return false;
        for(size_t i=0;i<p.size();i++){
            if(!isdigit(p[i])) return false;
        }
        for(size_t i=0;i<c.size();i++){
            if(p==c[i].getPhone()){
                cout<<"Phone No. already exixts"<<endl;
                return false;
            }
        }
        return true;
    }
}
void addCust(vector<customer>& c,string n, string p){
    if(isValidPhone(p,c)){
        string id=generateCustomerId();
        c.emplace_back(id,n,p);
        cout<<"Customer Added succesfully!!"<<endl;
    }
    else cout<<"Phone No. Issue!!"<<endl;
}
bool appointmentFit(const businessConfig& config,string t){
    if(!(isValidTime(t))) return false;
    if(timeToMin(t)>timeToMin(config.getCloseTime()) || timeToMin(t)<timeToMin(config.getOpenTime()) || timeToMin(t)+config.getAppointmentDuration() > timeToMin(config.getCloseTime())) return false;
    return true;
}
bool addApp(vector<appointment>& a,const businessConfig& config,customer c,string d,string t){
    if(isValidDate(d) && !isPastDate(d) && (!isToday(d) || !isPastTime(t)) && appointmentFit(config,t) && isSlotAvailable(a,config,d,t)){
        string id=generateAppointmentId();
        int ts=config.getAppointmentDuration();
        a.emplace_back(c,id,d,t,ts);
        return true;
    }
    if(!isValidDate(d)) cout << "Invalid date" << endl;
    if(isPastDate(d)) cout << "Past date Entered" << endl;
    if(isToday(d) || isPastTime(t)) cout<<"Time slot ended today."<<endl;
    if(!appointmentFit(config,t)) cout << "Invalid time/Outside working hours" << endl;
    if(!isSlotAvailable(a,config,d,t)) cout << "Slot conflict" << endl;
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