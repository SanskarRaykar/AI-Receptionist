#pragma once
#include <string>
class customer{
private:
    std::string name,phone,customerId;
public:
    customer();
    customer(std::string id, std::string n,std::string p);
    void display() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string getCustomerId() const;
    void setPhone(std::string s);
};