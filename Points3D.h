#ifndef Points3D_h
#define Points3D_h

//my includes
#include "mytypes.h"

class Points3D
{
public:
  Points3D() : m_changesNotSaved(false) {}
  //virtual z_t getZ(const x_t x, const y_t y) = 0;
  bool m_changesNotSaved;
private:
};


#endif
