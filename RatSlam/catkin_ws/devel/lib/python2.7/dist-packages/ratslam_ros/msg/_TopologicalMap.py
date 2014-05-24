"""autogenerated by genpy from ratslam_ros/TopologicalMap.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import geometry_msgs.msg
import ratslam_ros.msg
import genpy
import std_msgs.msg

class TopologicalMap(genpy.Message):
  _md5sum = "deefb2c5a22caaa16af4e1b64a821bdc"
  _type = "ratslam_ros/TopologicalMap"
  _has_header = True #flag to mark the presence of a Header object
  _full_text = """Header header
uint32 node_count
TopologicalNode[] node
uint32 edge_count
TopologicalEdge[] edge

	

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.secs: seconds (stamp_secs) since epoch
# * stamp.nsecs: nanoseconds since stamp_secs
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: ratslam_ros/TopologicalNode
uint32 id
geometry_msgs/Pose pose
================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of postion and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

================================================================================
MSG: ratslam_ros/TopologicalEdge
uint32 id
uint32 source_id
uint32 destination_id
duration duration
geometry_msgs/Transform transform
================================================================================
MSG: geometry_msgs/Transform
# This represents the transform between two coordinate frames in free space.

Vector3 translation
Quaternion rotation

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 

float64 x
float64 y
float64 z
"""
  __slots__ = ['header','node_count','node','edge_count','edge']
  _slot_types = ['std_msgs/Header','uint32','ratslam_ros/TopologicalNode[]','uint32','ratslam_ros/TopologicalEdge[]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       header,node_count,node,edge_count,edge

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(TopologicalMap, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.node_count is None:
        self.node_count = 0
      if self.node is None:
        self.node = []
      if self.edge_count is None:
        self.edge_count = 0
      if self.edge is None:
        self.edge = []
    else:
      self.header = std_msgs.msg.Header()
      self.node_count = 0
      self.node = []
      self.edge_count = 0
      self.edge = []

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_3I.pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_struct_I.pack(self.node_count))
      length = len(self.node)
      buff.write(_struct_I.pack(length))
      for val1 in self.node:
        buff.write(_struct_I.pack(val1.id))
        _v1 = val1.pose
        _v2 = _v1.position
        _x = _v2
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
        _v3 = _v1.orientation
        _x = _v3
        buff.write(_struct_4d.pack(_x.x, _x.y, _x.z, _x.w))
      buff.write(_struct_I.pack(self.edge_count))
      length = len(self.edge)
      buff.write(_struct_I.pack(length))
      for val1 in self.edge:
        _x = val1
        buff.write(_struct_3I.pack(_x.id, _x.source_id, _x.destination_id))
        _v4 = val1.duration
        _x = _v4
        buff.write(_struct_2i.pack(_x.secs, _x.nsecs))
        _v5 = val1.transform
        _v6 = _v5.translation
        _x = _v6
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
        _v7 = _v5.rotation
        _x = _v7
        buff.write(_struct_4d.pack(_x.x, _x.y, _x.z, _x.w))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(_x))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(_x))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.node is None:
        self.node = None
      if self.edge is None:
        self.edge = None
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.header.frame_id = str[start:end]
      start = end
      end += 4
      (self.node_count,) = _struct_I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.node = []
      for i in range(0, length):
        val1 = ratslam_ros.msg.TopologicalNode()
        start = end
        end += 4
        (val1.id,) = _struct_I.unpack(str[start:end])
        _v8 = val1.pose
        _v9 = _v8.position
        _x = _v9
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        _v10 = _v8.orientation
        _x = _v10
        start = end
        end += 32
        (_x.x, _x.y, _x.z, _x.w,) = _struct_4d.unpack(str[start:end])
        self.node.append(val1)
      start = end
      end += 4
      (self.edge_count,) = _struct_I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.edge = []
      for i in range(0, length):
        val1 = ratslam_ros.msg.TopologicalEdge()
        _x = val1
        start = end
        end += 12
        (_x.id, _x.source_id, _x.destination_id,) = _struct_3I.unpack(str[start:end])
        _v11 = val1.duration
        _x = _v11
        start = end
        end += 8
        (_x.secs, _x.nsecs,) = _struct_2i.unpack(str[start:end])
        _v12 = val1.transform
        _v13 = _v12.translation
        _x = _v13
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        _v14 = _v12.rotation
        _x = _v14
        start = end
        end += 32
        (_x.x, _x.y, _x.z, _x.w,) = _struct_4d.unpack(str[start:end])
        self.edge.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_3I.pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      if python3:
        buff.write(struct.pack('<I%sB'%length, length, *_x))
      else:
        buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_struct_I.pack(self.node_count))
      length = len(self.node)
      buff.write(_struct_I.pack(length))
      for val1 in self.node:
        buff.write(_struct_I.pack(val1.id))
        _v15 = val1.pose
        _v16 = _v15.position
        _x = _v16
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
        _v17 = _v15.orientation
        _x = _v17
        buff.write(_struct_4d.pack(_x.x, _x.y, _x.z, _x.w))
      buff.write(_struct_I.pack(self.edge_count))
      length = len(self.edge)
      buff.write(_struct_I.pack(length))
      for val1 in self.edge:
        _x = val1
        buff.write(_struct_3I.pack(_x.id, _x.source_id, _x.destination_id))
        _v18 = val1.duration
        _x = _v18
        buff.write(_struct_2i.pack(_x.secs, _x.nsecs))
        _v19 = val1.transform
        _v20 = _v19.translation
        _x = _v20
        buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
        _v21 = _v19.rotation
        _x = _v21
        buff.write(_struct_4d.pack(_x.x, _x.y, _x.z, _x.w))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(_x))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(_x))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.node is None:
        self.node = None
      if self.edge is None:
        self.edge = None
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.header.frame_id = str[start:end]
      start = end
      end += 4
      (self.node_count,) = _struct_I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.node = []
      for i in range(0, length):
        val1 = ratslam_ros.msg.TopologicalNode()
        start = end
        end += 4
        (val1.id,) = _struct_I.unpack(str[start:end])
        _v22 = val1.pose
        _v23 = _v22.position
        _x = _v23
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        _v24 = _v22.orientation
        _x = _v24
        start = end
        end += 32
        (_x.x, _x.y, _x.z, _x.w,) = _struct_4d.unpack(str[start:end])
        self.node.append(val1)
      start = end
      end += 4
      (self.edge_count,) = _struct_I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.edge = []
      for i in range(0, length):
        val1 = ratslam_ros.msg.TopologicalEdge()
        _x = val1
        start = end
        end += 12
        (_x.id, _x.source_id, _x.destination_id,) = _struct_3I.unpack(str[start:end])
        _v25 = val1.duration
        _x = _v25
        start = end
        end += 8
        (_x.secs, _x.nsecs,) = _struct_2i.unpack(str[start:end])
        _v26 = val1.transform
        _v27 = _v26.translation
        _x = _v27
        start = end
        end += 24
        (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
        _v28 = _v26.rotation
        _x = _v28
        start = end
        end += 32
        (_x.x, _x.y, _x.z, _x.w,) = _struct_4d.unpack(str[start:end])
        self.edge.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_3I = struct.Struct("<3I")
_struct_2i = struct.Struct("<2i")
_struct_4d = struct.Struct("<4d")
_struct_3d = struct.Struct("<3d")