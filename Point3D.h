#ifndef Point3D_h
#define Point3D_h

// my includes
#include "mytypes.h"
#include "Cube.h"

class Point3D
{
public:
  Point3D() : m_x(0), m_y(0), m_z(0) {}
  Point3D(const y_coordinate32_t y, const xcoordinate32_t x, const zcoordinate32_t z) : m_x(x), m_y(y), m_z(z) {}
  xcoordinate32_t m_x;
  y_coordinate32_t m_y;
  zcoordinate32_t m_z;
  bool inside(const Cube& cube) const;
  friend class boost::serialization::access;

private:
  // When the class Archive corresponds to an output archive, the
  // & operator is defined similar to <<.  Likewise, when the class Archive
  // is a type of input archive the & operator is defined similar to >>.
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & m_x;
    ar & m_y;
    ar & m_z;
    Q_UNUSED(version);
  }};


#endif
