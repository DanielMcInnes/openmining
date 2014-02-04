#ifndef Point3D_h
#define Point3D_h

// my includes
#include "mytypes.h"
#include "Cube.h"

class Point3D
{
public:
  Point3D() : m_x(0), m_y(0), m_z(0) {}
  Point3D(const y_t y, const x_t x, const z_t z) : m_x(x), m_y(y), m_z(z) {}
  x_t m_x;
  y_t m_y;
  z_t m_z;
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
