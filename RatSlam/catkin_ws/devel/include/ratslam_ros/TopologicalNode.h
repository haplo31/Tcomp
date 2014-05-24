/* Software License Agreement (BSD License)
 *
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of Willow Garage, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Auto-generated by genmsg_cpp from file /home/john/catkin_ws/src/ratslam_ros/msg/TopologicalNode.msg
 *
 */


#ifndef RATSLAM_ROS_MESSAGE_TOPOLOGICALNODE_H
#define RATSLAM_ROS_MESSAGE_TOPOLOGICALNODE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Pose.h>

namespace ratslam_ros
{
template <class ContainerAllocator>
struct TopologicalNode_
{
  typedef TopologicalNode_<ContainerAllocator> Type;

  TopologicalNode_()
    : id(0)
    , pose()  {
    }
  TopologicalNode_(const ContainerAllocator& _alloc)
    : id(0)
    , pose(_alloc)  {
    }



   typedef uint32_t _id_type;
  _id_type id;

   typedef  ::geometry_msgs::Pose_<ContainerAllocator>  _pose_type;
  _pose_type pose;




  typedef boost::shared_ptr< ::ratslam_ros::TopologicalNode_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ratslam_ros::TopologicalNode_<ContainerAllocator> const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;

}; // struct TopologicalNode_

typedef ::ratslam_ros::TopologicalNode_<std::allocator<void> > TopologicalNode;

typedef boost::shared_ptr< ::ratslam_ros::TopologicalNode > TopologicalNodePtr;
typedef boost::shared_ptr< ::ratslam_ros::TopologicalNode const> TopologicalNodeConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ratslam_ros::TopologicalNode_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ratslam_ros::TopologicalNode_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace ratslam_ros

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/hydro/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/hydro/share/geometry_msgs/cmake/../msg'], 'ratslam_ros': ['/home/john/catkin_ws/src/ratslam_ros/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::ratslam_ros::TopologicalNode_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ratslam_ros::TopologicalNode_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ratslam_ros::TopologicalNode_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ratslam_ros::TopologicalNode_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ratslam_ros::TopologicalNode_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ratslam_ros::TopologicalNode_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ratslam_ros::TopologicalNode_<ContainerAllocator> >
{
  static const char* value()
  {
    return "9ad7ea65113411e05ab5cf09fc962a2d";
  }

  static const char* value(const ::ratslam_ros::TopologicalNode_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x9ad7ea65113411e0ULL;
  static const uint64_t static_value2 = 0x5ab5cf09fc962a2dULL;
};

template<class ContainerAllocator>
struct DataType< ::ratslam_ros::TopologicalNode_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ratslam_ros/TopologicalNode";
  }

  static const char* value(const ::ratslam_ros::TopologicalNode_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ratslam_ros::TopologicalNode_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint32 id\n\
geometry_msgs/Pose pose\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of postion and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
";
  }

  static const char* value(const ::ratslam_ros::TopologicalNode_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ratslam_ros::TopologicalNode_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.id);
      stream.next(m.pose);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct TopologicalNode_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ratslam_ros::TopologicalNode_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ratslam_ros::TopologicalNode_<ContainerAllocator>& v)
  {
    s << indent << "id: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.id);
    s << indent << "pose: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose_<ContainerAllocator> >::stream(s, indent + "  ", v.pose);
  }
};

} // namespace message_operations
} // namespace ros

#endif // RATSLAM_ROS_MESSAGE_TOPOLOGICALNODE_H
