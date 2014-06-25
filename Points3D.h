#ifndef Points3D_h
#define Points3D_h

//my includes
#include "mytypes.h"

class Points3D
{
public:
  Points3D() : m_changesNotSaved(false) {}
  //virtual z_int32_t getZ(const x_int32_t x, const y_int32_t y) = 0;
  bool m_changesNotSaved;
private:
};


#endif
