#include <ignition/math/Pose3.hh>
#include "gazebo/physics/physics.hh"
#include "gazebo/common/common.hh"
#include "gazebo/gazebo.hh"
#include "gazebo/transport/transport.hh"
#include "gazebo/msgs/msgs.hh"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
namespace gazebo
{
class Factory : public WorldPlugin
{
  public: void Load(physics::WorldPtr _parent, sdf::ElementPtr /*_sdf*/)
  {

     // Insert a sphere model from string
    sdf::SDF sphereSDF;

    count = 10;
     i = 0;
    this->updateConnection = event::Events::ConnectWorldUpdateBegin(boost::bind(&Factory::Update, this, _1));
    _par = _parent;
        old = this->_par->GetSimTime();
    st = "<sdf version ='1.4'>\
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
              <name>Box_target_green/0</name>\
            </script>\
          </material>\
        </visual>\
              </link>\
            </model>\
          </sdf>";
        sphereSDF.SetFromString(st);
        // Demonstrate using a custom model name.
        sdf::ElementPtr model = sphereSDF.Root()->GetElement("model");
         model->GetAttribute("name")->SetFromString("unique_sphere");
        _par->RemoveModel("unique_sphere");
         _par->InsertModelSDF(sphereSDF);
  }

  public: void Update(const common::UpdateInfo &_info)
  {

    
    // Insert a sphere model from string
    sdf::SDF sphereSDF;

    if((this->_par->GetSimTime() - old).Double()> 2){
          old = this->_par->GetSimTime();

      
        stringstream ss;
        ss << i;
            std::cout << ss.str() << std::endl;

sdf::SDF sphereSDF;
   
    
        // st = "<sdf version ='1.4'>\
        //     <model name ='box'>\
        //       <pose>5 0 0 0 1.57 0</pose>\
        //       <link name ='link'>\
        //         <pose>0 0 0 0 0 0</pose>\
        //         <collision name ='collision'>\
        //           <geometry>\
        //             <box><size>6 6 2</size></box>\
        //           </geometry>\
        //         </collision>\
        //     <visual name='visual'>\
        //   <geometry>\
        //     <mesh>\
        //       <uri>model://box_target_green/meshes/mesh.dae</uri>\
        //     </mesh>\
        //   </geometry>\
        //   <material>\
        //     <script>\
        //       <uri>model://box_target_green/materials/textures</uri>\
        //       <uri>model://box_target_green/materials/scripts</uri>\
        //       <name>Box_target_green/"+ss.str()+"</name>\
        //     </script>\
        //   </material>\
        // </visual>\
        //       </link>\
        //     </model>\
        //   </sdf>";
        // sphereSDF.SetFromString(st);
        // // Demonstrate using a custom model name.
        // sdf::ElementPtr model = sphereSDF.Root()->GetElement("model");
        //  model->GetAttribute("name")->SetFromString("unique_sphere");
        // _par->RemoveModel("unique_sphere");
        //  _par->InsertModelSDF(sphereSDF);
      i++;
      if(i>10)i=0;
    }

  }

  private:
    event::ConnectionPtr updateConnection;
    string st;
    int count , i;
    physics::WorldPtr _par;
    common::Time old;
};

// Register this plugin with the simulator
GZ_REGISTER_WORLD_PLUGIN(Factory)
}
