#include <ros/ros.h>
#include <std_msgs/Int16.h>
#include <string>

using namespace std;

class Printer{
  private:
    ros::NodeHandle n;
    ros::Timer timer;
    ros::Publisher pub;
  public:
    Printer(){
      timer = n.createTimer(ros::Duration(5.0), boost::bind(&Printer::publishPrinter, this));
    }
    void publishPrinter(){
      pub = n.advertise<std_msgs::Int16>("printVec", 1000);
    }
};


int main(int argc, char**argv){
  init(argc, argv, "printer");
  Printer printer;
  ros::spin();
}
