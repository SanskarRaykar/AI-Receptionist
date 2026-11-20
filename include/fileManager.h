#include "customer.h"
#include<vector>
#include<string>
class fileManager{
private:
    std::string customerData;
    std::string appointmentData;
public:
    void loadCustomer(std::vector<customer> c);
    void saveCustomer();
};