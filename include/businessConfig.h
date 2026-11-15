#pragma once
#include<string>
class businessConfig{
private:
    std::string openTime,closeTime;
    int appointmentDuration=30;
public:
    businessConfig(std::string openTime,std::string closeTime);
    std::string getOpenTime() const;
    std::string getCloseTime() const;
    bool setWorkingHours(std::string open, std::string close);
    int getAppointmentDuration() const;
    bool setAppointmentDuration(int ts);
};