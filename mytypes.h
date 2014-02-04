#ifndef mytypes_h
#define mytypes_h

// standard includes
#include <map>
#include <cstdint>

// boost includes

// Qt includes

// my includes
typedef int32_t x_t;
typedef int32_t y_t;
typedef int32_t z_t;


typedef int32_t latitude_t;
typedef int32_t longitude_t;
typedef int32_t elevation_t;
typedef std::map<latitude_t, elevation_t> latitudes_t;
typedef std::map<longitude_t, latitudes_t> longitudes_t; // long = x , lat = y, elev = z



#endif
