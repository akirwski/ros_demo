#ifndef BREEDER_H
#define BREEDER_H

#include <ros/ros.h>
#include "animal_lib/Animal.h"
#include "animal_lib/Dog.h"
#include "animal_lib/Cat.h"
#include "Breeder.h"

using namespace std;

int main(int argc, char **argv){

    ros::init(argc, argv, "breeder");
    Breeder listener("chatOne", "chatTwo", "response");

    ros::spin();

}

#endif
