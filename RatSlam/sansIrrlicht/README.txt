compilation:
catkin_make

run:
first terminal: roslaunch src/ratslam_ros/launch/irataus.launch
second terminal: rosbag play ../irat_aus_28112011.bag

attention:
+ il faut rajouter le lancement de TOTO_map dans les launchs à la manière de irat
+ il faut mettre en place les autres TOTO (odo + camera)
