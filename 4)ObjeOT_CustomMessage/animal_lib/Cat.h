#ifndef CAT_H
#define CAT_H

#include <ros/ros.h>
#include <string>
#include "animal_msgs/catMsg.h"
#include "Animal.h"

enum HomeCountry {France, Italy, Japan, America};

class Cat : public Animal{
    private:
        HomeCountry homecountry;
    public:
        Cat(string Name, int Age, bool Sex, HomeCountry Country);
};

#endif
