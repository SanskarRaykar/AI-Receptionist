#include "appointment.h"
#include <iostream>
using namespace std;
appointment::appointment(customer c,string id,string d,string t):cust(c),appointmentId(id),date(d),time(t),status("Pending"){}
void appointment::displayApp() const{
    cout<<"CustID: "<<cust.getCustomerId()<<endl;
    cout<<"Name: "<<cust.getName()<<endl;
    cout<<"Phone: "<<cust.getPhone()<<endl;
    cout<<"Date: "<<date<<endl;
    cout<<"Time: "<<time<<endl;
    cout<<"Status: "<<status<<endl;
}
string appointment::getCustPhone() const{
    return cust.getPhone();
}
string appointment::getDate() const{
    return date;
}
string appointment::getTime() const{
    return time;
}
string appointment::getAppId() const{
    return appointmentId;
}
string appointment::getStatus() const{
    return status;
}
bool appointment::setStatus(string a){
    if(a=="Completed"||a=="Cancelled"||a=="Confirmed"){ 
        status=a;
        return true;
    }
    else return false;
}