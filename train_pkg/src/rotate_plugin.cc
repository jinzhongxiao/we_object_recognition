#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>
#include <time.h>
#include "std_msgs/String.h"
#include <sstream>
#include <stdlib.h>
#include <ros/ros.h>
#define  random(x) (rand()%x)
namespace gazebo
{
  class ModelPush : public ModelPlugin
  {
    ~ModelPush(){
      this->rosnode_->shutdown();
      delete this->rosnode_;
    }
    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
    {
      srand((int)time(0));
      this->rosnode_ = new ros::NodeHandle("");
      this->pub = this->rosnode_->advertise<std_msgs::String>("rotate_count", 1);
      // Store the pointer to the model
      this->model = _parent;
      startx = this->model->GetWorld()->GetSimTime();
      // Listen to the update event. This event is broadcast every
      // simulation iteration.
      this->updateConnection = event::Events::ConnectWorldUpdateBegin(
          boost::bind(&ModelPush::OnUpdate, this, _1));
    }

    // Called by the world update start event
    public: void OnUpdate(const common::UpdateInfo & /*_info*/)
    {
  //     math::Pose p(2,2,2,2,2,2);

  // this->model->SetInitialRelativePose(p);
  // this->model->SetLinkWorldPose(p,"d");
  // this->model->SetRelativePose(p,false,false); this->model->SetWorldPose(p,false,false);
  // std::cout<<"oddk"<<std::endl;
      double vel = 1.4;
      int count  = 10;

      double  circle = 2*3.14;

      common::Time cur;
      if(i<count){

        if(flagx == 0){
          cur = this->model->GetWorld()->GetSimTime();
          Tx = (cur - startx).Double();
          // std::cout << Tx << std::endl;
          this->model->SetAngularVel(math::Vector3(vel,0,0));

        }
        if(vel*Tx > i * (circle)/count){
          //std::cout << "Tx" << std::endl;
          flagx = 1;
          this->model->SetAngularVel(math::Vector3(0,0,0));
          if(yy==0){yy=1;
          starty =  this->model->GetWorld()->GetSimTime();}
          if(j<count){
            if(flagy == 0){
              cur = this->model->GetWorld()->GetSimTime();
              //std::cout << "Ty" << Ty<< std::endl;
               Ty = (cur - starty).Double();
               // std::cout <<"Ty  " <<  Ty << std::endl;
               // std::cout << "i="<<i << "," << "j="<<j<<","<<"k="<<k<<",flagx="<<
               // flagx<<",flagy"<<flagy<<",Tx = " << Tx<<",Ty="<<Ty<<","<<Tz<<std::endl;
               this->model->SetAngularVel(math::Vector3(0,vel,0));
            }
            if(vel*Ty > (circle)/count){
                          //  std::cout << "k " <<j<<std::endl;

              flagy = 1;
              this->model->SetAngularVel(math::Vector3(0,0,0));
              if(zz==0){zz=1;startz = this->model->GetWorld()->GetSimTime();}
              if(k<count){

                 std::cout << i<<", " << j << ", "<<k << std::endl;
                 std_msgs::String msg;

                 std::stringstream ss;

                 ss << i*count*count+j*count+k;
                msg.data = ss.str();
                 this->pub.publish(msg);
                cur = this->model->GetWorld()->GetSimTime();

                Tz = (cur - startz).Double();
                 //                             std::cout << "Tz" << Tz<< std::endl;

                this->model->SetAngularVel(math::Vector3(0,0,vel));
                if(vel*Tz > k*circle/count){
                  k++;
                                  this->model->SetAngularVel(math::Vector3(0,0,0));

                }
              }
              //std::cout << "j " <<j<<std::endl;
              if(k>=count)
              {j++;starty = this->model->GetWorld()->GetSimTime();startz = starty;k=1;
              flagy = 0;}
            }
          }
          if(j>=count)
          {i++;startx = this->model->GetWorld()->GetSimTime();starty = startx;j=1;
              flagx = 0;}          //flagx = 0;
        }
      }
      if(i>=count)
          {i=0;
              flagy=0;  ; flagx = 0;
              }          //flagx = 0;
    // this->model->SetAngularVel(math::Vector3(.3,0,0));
    this->model->SetLinearVel(math::Vector3(.0,0,0));
    }


    // Pointer to the model
    private: physics::ModelPtr model;

    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;

    private:  common::Time last_update_time_;
  private:
    ros::NodeHandle *rosnode_;
    ros::Publisher pub;
    int flagx=0, flagy = 0;
    common::Time startx, starty, startz;
    int i=1,j=1,k=1;
    double Tx,Ty,Tz;
    int yy = 0,zz=0;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(ModelPush)
}
