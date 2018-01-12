#include "ros/ros.h"
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PointStamped.h>
#include <gazebo_msgs/SpawnModel.h>
#include <stdlib.h>
#include<iostream>
#include<fstream>
using namespace std;
#include <sstream>
#include <string>
#include <tf/transform_datatypes.h>
 #include "gazebo_msgs/GetWorldProperties.h"
 #include "gazebo_msgs/DeleteModel.h"

  #include<time.h>
  #include<stdlib.h>


int main(int argc, char **argv) { ros::init(argc, argv, "comkkmander"); // Node setup ros::NodeHandle nh;
    ros::init(argc,argv, "ed");
    ros::NodeHandle nh;
    srand((unsigned)time( NULL ) );

    int t = 3;
    ros::Rate r(0.2);
    string sdf_str;
    stringstream ss;
    ss << t;
    sdf_str="<sdf version ='1.4'>\
          <model name ='box'>\
            <pose>5 0 0 0 1.57 0</pose>\
            <link name ='link'>\
              <pose>0 0 0 0 0 0</pose>\
              <collision name ='collision'>\
                <geometry>\
                  <box><size>6 6 2</size></box>\
                </geometry>\
              </collision>\
          <visual name='visual'>\
        <geometry>\
          <mesh>\
            <uri>model://box_target_green/meshes/mesh.dae</uri>\
          </mesh>\
        </geometry>\
        <material>\
          <script>\
            <uri>model://box_target_green/materials/textures</uri>\
            <uri>model://box_target_green/materials/scripts</uri>\
            <name>Box_target_green/"+ss.str()+"</name>\
          </script>\
        </material>\
      </visual>\
            </link>\
          </model>\
        </sdf>";

    ros::ServiceClient spawn = nh.serviceClient< gazebo_msgs::SpawnModel> ("/gazebo/spawn_sdf_model");



   ros::service::waitForService("gazebo/delete_model");
   ros::ServiceClient delete_model_client = nh.serviceClient<gazebo_msgs::DeleteModel>("gazebo/delete_model");
   gazebo_msgs::DeleteModel delete_model;
 // model names to delete
   ros::service::waitForService("gazebo/get_world_properties");
   // ros::ServiceClient check_model_client = nh.serviceClient<gazebo_msgs::GetWorldProperties>("gazebo/get_world_properties");
   // gazebo_msgs::GetWorldProperties world_properties;
   // check_model_client.call(world_properties);


    gazebo_msgs::SpawnModel s1;
    geometry_msgs::Pose p1;
    s1.request.model_name = "er";
    s1.request.model_xml  = sdf_str;
    s1.request.robot_namespace = "uav39";
    p1.position.x = -10.0;
    p1.position.y = 0.0;
    p1.position.z = 0.0;
    p1.orientation = tf::createQuaternionMsgFromYaw(0.0);
    s1.request.initial_pose = p1;
    s1.request.reference_frame = "";

    spawn.call(s1);

    while (ros::ok()){

 delete_model.request.model_name = "er";
     delete_model_client.call(delete_model);
     s1.request.model_xml  = sdf_str;

stringstream ss;
t=rand()%1000+1;

        ss << t;
        t+=1;
        if(t>1000)t=0;
    sdf_str="<sdf version ='1.4'>\
          <model name ='box'>\
            <pose>5 0 0 0 1.57 0</pose>\
            <link name ='link'>\
              <pose>0 0 0 0 0 0</pose>\
              <collision name ='collision'>\
                <geometry>\
                  <box><size>6 6 2</size></box>\
                </geometry>\
              </collision>\
          <visual name='visual'>\
        <geometry>\
          <mesh>\
            <uri>model://box_target_green/meshes/mesh.dae</uri>\
          </mesh>\
        </geometry>\
        <material>\
          <script>\
            <uri>model://box_target_green/materials/textures</uri>\
            <uri>model://box_target_green/materials/scripts</uri>\
            <name>Box_target_green/"+ss.str()+"</name>\
          </script>\
        </material>\
      </visual>\
            </link>\
          </model>\
        </sdf>";
         s1.request.model_xml  = sdf_str;
spawn.call(s1);

std::cout << t <<std::endl;
     //ROS_INFO("success");
      r.sleep();

}
return 0; }
