compilation:
catkin_make

run:

first terminal: 
source devel/setup.bach

and then

________
IRATAUS |
^^^^^^^^

roslaunch src/ratslam_ros/launch/irataus.launch

and second terminal: 
rosbag play ../irat_aus_28112011.bag

___________
NEWCOLLEGE |
^^^^^^^^^^^

roslaunch src/ratslam_ros/launch/oxford_newcollege.launch

and second terminal: 
rosbag play ../oxford_newcollege.bag

________
STLUCIA |
^^^^^^^^

roslaunch src/ratslam_ros/launch/stlucia.launch

and second terminal: 
rosbag play ../stlucia_2007.bag



!!!!!!
TODO!!
!!!!!!

annuler les commits "map for all"
NE PAS SUPPRIMER README ET SRC DE SANSIRRLICHT

> il faut mettre en place les autres TOTO (odo + camera):
1) modifier main_TOTO pour qu'il publie l'odométrie envoyée par l'arduino [nécessite rosserial... A INSTALLER]
2) modifier TOTO_video pour qu'il publie les images envoyée par le raspberry [EN COURS]

https://github.com/fpasteau/raspicam_node/tree/master/src

ou gscam ??

3) etudier et compléter local navigation et exploration (main_em/experience_map) [REPONSE SU ROS-RATSLAM?]
> utiliser la visual odometry? (main_vo)
