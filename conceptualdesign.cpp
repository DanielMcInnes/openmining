/*! \page pagecd000001 Conceptual Design

\section seccd000001 Conceptual Design CD000001

\subsection sspostgresinterface Postgres Interface
- Import the GPS data from a postgres database.

\subsection ssBuild3DModel Conceptual Design CD000002 Build 3D Model
- Construct a 3D model based on the elevations at known points.

\subsection ssvehiclelist Maintain a list of GPS vehicles
- Every time a GPS record is received for an unknown GPS vehicle, add the vehicle to the vehicles list.

\subsection ssrunmode "Run Mode"
- Once every second, poll the db for any updated shift_gps records, and update the screen appropriately.

\subsection ssreplaymode Replay Mode
- Get the start time from the user.
- Get a list of all gps locations, ordered by time, starting at the specified time.
- Starting at the earliest record, update the location of the appropriate vehicle on the screen.
**/



