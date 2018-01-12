echo "Usage: bash run.sh Folder_Path  Time Model_name1 Modek_name2 ..."

basepath=$(cd $(dirname $0); pwd)
# create the data folder
if [ ! -d $1 ]; then
  mkdir $1
fi

#### no background
for mdolename in SourceSoftware ShampooSoftware MilkteaSoftware MilkSoftware
do
  echo $mdolename
  cd $1
  software=software
  mkdir -p $software/blank/$mdolename
  software_blank_path=$(cd $software/blank/$mdolename;pwd)
  cd $software/blank/$mdolename
  rm -rf *
  gnome-terminal --geometry=80x25+10+10 -e 'bash -c "roslaunch train_pkg robot.launch  objectname:='$mdolename';exec bash"'
  gnome-terminal --geometry=80x25+10+10 -e 'bash -c "rosrun train_pkg  image.py  -p '$software_blank_path';exec bash"'


  echo $software_blank_path


  sleep $2

  ag=$(ps -aux | grep   "python $basepath/scripts" | awk '{print $2}'| xargs kill)
  $(ps -aux | grep   "gzserver" | awk '{print $2}'| xargs kill)
  $(ps -aux | grep   "gzclient" | awk '{print $2}'| xargs kill)


done
####  background
for mdolename in SourceSoftware ShampooSoftware MilkteaSoftware MilkSoftware
do
  echo $mdolename
  cd $1
  software=software
  mkdir -p $1/$software/background/$mdolename
  software_background_path=$(cd $software/background/$mdolename;pwd)
  cd $software/background/$mdolename
  rm -rf *
  gnome-terminal --geometry=80x25+10+10 -e 'bash -c "roslaunch train_pkg robot.launch  objectname:='$mdolename';exec bash"'
  gnome-terminal --geometry=80x25+10+10 -e 'bash -c "rosrun train_pkg  image.py  -p '$software_background_path';exec bash"'
  gnome-terminal --geometry=80x25+10+10 -e 'bash -c "rosrun train_pkg  spawn;exec bash"'

  sleep 1

  gnome-terminal --geometry=80x25+10+10 \
      --tab -e 'bash -c "rosrun train_pkg  dele;exec bash"'


  echo $software_background_path

  sleep $2

  ag=$(ps -aux | grep   "python $basepath/scripts" | awk '{print $2}'| xargs kill)
  $(ps -aux | grep   "gzserver" | awk '{print $2}'| xargs kill)
  $(ps -aux | grep   "gzclient" | awk '{print $2}'| xargs kill)


done
# # gnome-terminal --geometry=80x25+10+10 -e 'bash -c "rosrun train_pkg  spawn;exec bash"'
# #
# # sleep 1
#
# gnome-terminal --geometry=80x25+10+10 \
#     --tab -e 'bash -c "rosrun train_pkg  dele;exec bash"'

# sleep 8

# gnome-terminal --geometry=80x25+10+510 \
#     --tab -e 'bash -c "roslaunch kejia_gazebo plugins.launch;exec bash"' \
#     --tab -e 'bash -c "roslaunch mcs_driver platform.launch;exec bash"' \
#     --tab -e 'bash -c "roslaunch fake_vision vision.launch;exec bash"'

# gnome-terminal --geometry=80x25+810+10 \
#     --tab -e 'bash -c "ssh kejiab2@192.168.1.9;exec bash"' \
#     --tab -e 'bash -c "ssh kejiab2@192.168.1.9;exec bash"' \

#sleep 5

#gnome-terminal --geometry=80x25+810+510 \
#    --tab -e 'bash -c "rosrun we_python_sm dndec.py groceries;exec bash"'
