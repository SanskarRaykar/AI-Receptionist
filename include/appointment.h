#pragma once
#include "customer.h"
#include<string>
class appointment{
private:
    customer cust;
    std::string appointmentId;
    std::string date, time, status;
    int duration;
public:
    appointment(customer c,std::string id,std::string d,std::string t);
    void displayApp() const;
    std::string getCustPhone() const;
    std::string getDate() const;
    std::string getTime() const;
    std::string getAppId() const;
    std::string getStatus() const;
    int getduration() const;
    bool setStatus(std::string a);
};