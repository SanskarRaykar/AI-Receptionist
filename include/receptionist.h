#pragma once
#include<vector>
#include <string>
#include "customer.h"
#include "appointment.h"
#include "businessConfig.h"

void addCust(std::vector<customer>& c,std::string n, std::string p);
bool addApp(std::vector<appointment>& a,const businessConfig& config,customer c,std::string d,std::string t);
void displayAp(const std::vector<appointment>& a);
void displayCust(const std::vector<customer>& c);
int searchCust(const std::vector<customer>& c,std::string p);
bool searchApp(const std::vector<appointment>& a,std::string p);
bool cancelApp(std::vector<appointment>& a,std::string p,std::string d);
bool updateApp(std::vector<appointment>& a,std::string s,std::string p,std::string t,std::string d);
