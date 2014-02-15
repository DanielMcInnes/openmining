#ifndef Points3D_h
#define Points3D_h

//my includes
#include "mytypes.h"

class Points3D
{
public:
  Points3D() : m_changesNotSaved(false) {}
  //virtual zcoordinate32_t getZ(const xcoordinate32_t x, const y_coordinate32_t y) = 0;
  bool m_changesNotSaved;
private:
};


#endif
