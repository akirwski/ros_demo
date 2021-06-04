#ifndef LISTENER_CLASS_H
#define LISTENER_CLASS_HP

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <string>

using namespace std;

template<typename subOneType, typename subTwoType, typename pubType>
class ListenerClass {
    private:
    ros::Subscriber subOne;
    ros::Subscriber subTwo;
    ros::Publisher pub;
    ros::NodeHandle n;
    ros::Timer publishTimer;

    bool receivedOne;
    int receivedTwo;


    public:
    ListenerClass(){}
    ListenerClass(string subTopicOne, string subTopicTwo, string pubTopic){
        subOne = n.subscribe<subOneType>(subTopicOne, 1000, &ListenerClass::chatterCallBackOne, this );
        subTwo = n.subscribe<subTwoType>(subTopicTwo, 1000, &ListenerClass::chatterCallBackTwo, this );
        pub = n.advertise<pubType>(pubTopic, 1000);
        receivedOne = false;
        receivedTwo = 0;
        publishTimer = n.createTimer( ros::Duration(1.0), boost::bind( &ListenerClass::publishResponse, this ) );
    }

    ros::NodeHandle& get_n(){ return n; }
    void chatterCallBackOne(const typename subOneType::ConstPtr& receivedMsg);
    void chatterCallBackTwo(const typename subTwoType::ConstPtr& receivedMsg);
    void publishResponse();
    int calculate();

};

#endif
