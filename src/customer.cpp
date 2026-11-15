#include "customer.h"
#include <iostream>
#include <cctype>
using namespace std;
customer:: customer(){
    name="Not Filled";
    phone="Not Filled";
}
customer::customer(string id, string n, string p):name(n), phone(p), customerId(id) {}
void customer:: display() const{
    cout<<"ID of customer - "<<customerId<<endl;
    cout<<"Name of customer - "<<name<<endl;
    cout<<"Phone No. of customer - "<<phone<<endl;
}
string customer::getName() const{
    return name;
}
string customer:: getPhone() const{
    return phone;
}
string customer:: getCustomerId() const{
    return customerId;
}
void customer:: setPhone(string s){
    int n=s.size();
    int flag=1;
    if(n!=10) flag=0;
    for(int i=0;i<n;i++){
        if (isdigit(static_cast<unsigned char>(s[i]))) continue;
        else flag=0;
    }
    if(flag) phone=s;
    else cout<<"Wrong number entered cannot update"<<endl;
}