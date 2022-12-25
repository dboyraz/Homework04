//
// Created by deniz on 20-Dec-22.
//

#ifndef HOMEWORK04_CUSTOMER_H
#define HOMEWORK04_CUSTOMER_H

#include <string>

using namespace std;


class Customer {

private:
    string name;
    string carMake;
    string plateNumber;

public:
    Customer();

    Customer(string n, string c, string p);


    void setName(const string &name);

    void setCarMake(const string &carMake);

    void setPlateNumber(const string &plateNumber);

    const string &getName() const { return name; }

    const string &getPlateNumber() const { return plateNumber; }

    const string &getCarMake() const { return carMake; }

};


#endif //HOMEWORK04_CUSTOMER_H
