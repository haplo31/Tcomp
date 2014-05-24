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
 * Auto-generated by genmsg_cpp from file /home/john/catkin_ws/src/ratslam_ros/msg/TopologicalAction.msg
 *
 */


#ifndef RATSLAM_ROS_MESSAGE_TOPOLOGICALACTION_H
#define RATSLAM_ROS_MESSAGE_TOPOLOGICALACTION_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace ratslam_ros
{
template <class ContainerAllocator>
struct TopologicalAction_
{
  typedef TopologicalAction_<ContainerAllocator> Type;

  TopologicalAction_()
    : header()
    , action(0)
    , src_id(0)
    , dest_id(0)
    , relative_rad(0.0)  {
    }
  TopologicalAction_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , action(0)
    , src_id(0)
    , dest_id(0)
    , relative_rad(0.0)  {
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef uint32_t _action_type;
  _action_type action;

   typedef uint32_t _src_id_type;
  _src_id_type src_id;

   typedef uint32_t _dest_id_type;
  _dest_id_type dest_id;

   typedef double _relative_rad_type;
  _relative_rad_type relative_rad;


    enum { CREATE_NODE = 1 };
     enum { CREATE_EDGE = 2 };
     enum { SET_NODE = 3 };
 

  typedef boost::shared_ptr< ::ratslam_ros::TopologicalAction_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ratslam_ros::TopologicalAction_<ContainerAllocator> const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;

}; // struct TopologicalAction_

typedef ::ratslam_ros::TopologicalAction_<std::allocator<void> > TopologicalAction;

typedef boost::shared_ptr< ::ratslam_ros::TopologicalAction > TopologicalActionPtr;
typedef boost::shared_ptr< ::ratslam_ros::TopologicalAction const> TopologicalActionConstPtr;

// constants requiring out of line definition

   

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ratslam_ros::TopologicalAction_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ratslam_ros::TopologicalAction_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace ratslam_ros

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/hydro/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/hydro/share/geometry_msgs/cmake/../msg'], 'ratslam_ros': ['/home/john/catkin_ws/src/ratslam_ros/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::ratslam_ros::TopologicalAction_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ratslam_ros::TopologicalAction_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ratslam_ros::TopologicalAction_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ratslam_ros::TopologicalAction_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ratslam_ros::TopologicalAction_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ratslam_ros::TopologicalAction_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ratslam_ros::TopologicalAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "365d6e23e0fb90a477e21472cd2edf80";
  }

  static const char* value(const ::ratslam_ros::TopologicalAction_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x365d6e23e0fb90a4ULL;
  static const uint64_t static_value2 = 0x77e21472cd2edf80ULL;
};

template<class ContainerAllocator>
struct DataType< ::ratslam_ros::TopologicalAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ratslam_ros/TopologicalAction";
  }

  static const char* value(const ::ratslam_ros::TopologicalAction_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ratslam_ros::TopologicalAction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# actions\n\
uint32 CREATE_NODE=1\n\
uint32 CREATE_EDGE=2\n\
uint32 SET_NODE=3\n\
\n\
Header header\n\
\n\
uint32 action\n\
\n\
uint32 src_id\n\
uint32 dest_id\n\
\n\
float64 relative_rad\n\
\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.secs: seconds (stamp_secs) since epoch\n\
# * stamp.nsecs: nanoseconds since stamp_secs\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
";
  }

  static const char* value(const ::ratslam_ros::TopologicalAction_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ratslam_ros::TopologicalAction_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.action);
      stream.next(m.src_id);
      stream.next(m.dest_id);
      stream.next(m.relative_rad);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct TopologicalAction_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ratslam_ros::TopologicalAction_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ratslam_ros::TopologicalAction_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "action: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.action);
    s << indent << "src_id: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.src_id);
    s << indent << "dest_id: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.dest_id);
    s << indent << "relative_rad: ";
    Printer<double>::stream(s, indent + "  ", v.relative_rad);
  }
};

} // namespace message_operations
} // namespace ros

#endif // RATSLAM_ROS_MESSAGE_TOPOLOGICALACTION_H
