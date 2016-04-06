#include <ros/ros.h>
 #include <tf/transform_listener.h>
#include"geometry_msgs/Twist.h"
#include <sstream>

    int main(int argc, char** argv){
      ros::init(argc, argv, "tf_listener");

     ros::NodeHandle node;
     ros::Publisher cmd_vel_pub = node.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
     tf::TransformListener listener;

     ros::Rate rate(5.0);
     double x,x_1,x_2,y,y_1,y_2,z,z_1,z_2;
      geometry_msgs::Twist msg;
      msg.linear.x = 0;
      msg.linear.y = 0;
      msg.linear.z = 0;
      msg.angular.z = 0;
     while (node.ok()){
       tf::StampedTransform transform;
       tf::StampedTransform transform_1;
       tf::StampedTransform transform_2;
       try{
         listener.lookupTransform("tracker/user_1/right_hand", "tracker/user_1/head",
                                  ros::Time(0), transform);
         listener.lookupTransform("tracker/user_1/left_hand", "tracker/user_1/head",
                                  ros::Time(0), transform_1);
         listener.lookupTransform("tracker/user_1/right_hand", "tracker/user_1/left_hand",
                                  ros::Time(0), transform_2);
       }
       catch (tf::TransformException &ex) {
        ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
         continue;
       }
     x=transform.getOrigin().x();
     x_1=transform_1.getOrigin().x();
     x_2=transform_2.getOrigin().x();
     y=transform.getOrigin().y();
     y_1=transform_1.getOrigin().y();
     y_2=transform_2.getOrigin().y();
     z=transform.getOrigin().z();
     z_1=transform_1.getOrigin().z();
     z_2=transform_2.getOrigin().z();
      // ROS_INFO("%f\t" "%f\t" "%f\t",transform_2.getOrigin().x(),
      //                          transform_2.getOrigin().y(),transform_2.getOrigin().z());
       if ((z>=-0.1&&z<=0.2)&&(z_1>=-0.1&&z_1<=0.2))
           {if(y_2>=-0.1&&y_2<=0.1)
           {ROS_INFO("xuanting");
               msg.linear.x = 0;
               msg.linear.y = 0;
               msg.linear.z = 0;
               msg.angular.z = 0;
           }
           else if(y_2>0.1)
           {ROS_INFO("youfei");
               msg.linear.x = 0;
               msg.linear.y = -0.1;
               msg.linear.z = 0;
               msg.angular.z = 0;
           }
           else if(y_2<-0.1)
           {ROS_INFO("zuofei");
               msg.linear.x = 0;
               msg.linear.y = 0.1;
               msg.linear.z = 0;
               msg.angular.z = 0;
           }
       }
       else if((z>0.2&&z_1>0.2))
       {ROS_INFO("qianfei");
           msg.linear.x = 0.1;
           msg.linear.y = 0;
           msg.linear.z = 0;
           msg.angular.z = 0;
       }
       else if(z<-0.1&&z_1<-0.1)
       {ROS_INFO("houfei");
           msg.linear.x = -0.1;
           msg.linear.y = 0;
           msg.linear.z = 0;
           msg.angular.z = 0;
       }
       else if((z>0.2&&z_1<-0.1))
          { ROS_INFO("zuoxuan");
           msg.linear.x = 0;
           msg.linear.y = 0;
           msg.linear.z = 0;
           msg.angular.z = 0.1;
       }
       else if((z<-0.1&&z_1>0.2))
       {ROS_INFO("youxuan");
           msg.linear.x = 0;
           msg.linear.y = 0;
           msg.linear.z = 0;
           msg.angular.z = -0.1;
       }
cmd_vel_pub.publish(msg);
      rate.sleep();
     }
     return 0;
   };
