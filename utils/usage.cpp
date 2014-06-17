#include <iostream>

using namespace std;

namespace utils
{
  void usage()
  {
    cout << "Usage: ./openmining -host localhost -database mydbname -username myname -password mypassword -minlat -117000000 -maxlat -116000000 -minlong 543000000 -maxlong 544000000 -minel 0 -maxel 100000 --locations-query \"SELECT latitudes, longitudes, elevations from shift_gps LIMIT 100;\" " << endl;
    cout << "eg. ./openmining -host localhost -database db123 -username me -password mypassword -minlat -117000000 -maxlat -116000000 -minlong 543000000 -maxlong 544000000 -minel 0 -maxel 100000 --locations-query \"SELECT latitudes, longitudes, elevations from shift_gps LIMIT 100;\"" << endl;
  }
}

