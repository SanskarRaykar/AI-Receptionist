#include<iostream>
#include<string>
#include<limits>
#include<vector>
#include "customer.h"
#include "appointment.h"
#include "receptionist.h"
#include "businessConfig.h"
using namespace std;
int main(){
    int n,b;
    string name,phone,date,time,status;
    vector<appointment> a;
    vector<customer> c;
    bool flag=true;
    businessConfig config("09:00", "18:00");
    config.setAppointmentDuration(30);
    do{
        cout<<"========================"<<endl;
        cout<<"AI Receptionist"<<endl;
        cout<<"========================"<<endl;
        cout<<"1. Register New Customer"<<endl;
        cout<<"2. View All Customers"<<endl;
        cout<<"3. Book Appointment"<<endl;
        cout<<"4. View All Appointments"<<endl;
        cout<<"5. Search Appointment"<<endl;
        cout<<"6. Update Appointment Status"<<endl;
        cout<<"7. Cancel Appointment"<<endl;
        cout<<"8. Exit"<<endl;
        cout<<"Enter Which thing you want to do - "<<endl;
        cin>>n;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"INVALID OPTION!!";
            continue;
        }
        switch(n){
            case 1:
                cout<<"Enter your Name- "<<endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin,name);
                cout<<"Enter your Phone- "<<endl;
                getline(cin,phone);
                addCust(c,name,phone);
                break;
            case 2:
                displayCust(c);
                break;
            case 3:
                cout<<"Enter your Phone- "<<endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin,phone);
                b=searchCust(c,phone);
                if(b>=0){
                    cout<<"Enter your Appointment Date- "<<endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin,date);
                    cout<<"Enter your Appointment Time- "<<endl;
                    getline(cin,time);
                    if(addApp(a,config,c[b],date,time)) cout<<"Appointment booked succesfully"<<endl;
                    else cout<<"Appointment is already booked/Not Available."<<endl;
                }
                else{
                    cout<<"Invalid Customer !!";
                }
                break;
            case 4:
                displayAp(a);
                break;
            case 5:
                cout<<"Enter your Phone- "<<endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin,phone);
                searchApp(a,phone);
                break;
            case 6:
                cout<<"Enter your Phone- "<<endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin,phone);
                cout<<"Enter your Appointment Date- "<<endl;
                getline(cin,date);
                cout<<"Enter your Appointment Time- "<<endl;
                getline(cin,time);
                cout<<"Enter your Status- "<<endl;
                getline(cin,status);
                updateApp(a,status,phone,time,date);
                break;
            case 7:
                cout<<"Enter your Phone- "<<endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin,phone);
                cout<<"Enter your Appointment Date- "<<endl;
                getline(cin,date);
                cancelApp(a,phone,date);
                break;
            case 8:
                flag=false;
                break;
            default:
                cout<<"Invalid Input!!";
        }
    }while(flag);
}