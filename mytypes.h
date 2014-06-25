#ifndef mytypes_h
#define mytypes_h

// standard includes
#include <map>
#include <cstdint>

// boost includes

// Qt includes

// my includes
typedef int32_t y_int32_t;
typedef int32_t x_int32_t;
typedef int32_t z_int32_t;

typedef std::map<y_int32_t, z_int32_t> yzcoordinates32_t;
typedef std::map<x_int32_t, yzcoordinates32_t> xyzcoordinates32_t; // long = x , lat = y, elev = z

#endif
