/*! \page pageds Development Strategy
\section dssec000001 Cycles
\subsection ds000001 Development Strategy - Cycle 1

Functions / Modules:
- postgres interface

Testing approach:
Verify that appropriate error messages are produced if:
- postgres is not running
- the database does not exist
- the table doesn't exist
- the password is wrong

\subsection ds000002 Development Strategy - Cycle 2

Functions / Modules: Create a 3D plot of the mine surface

Testing approach:
Verify that appropriate error messages are produced if:
- the table is too small to produce an acceptable plot
- Insert a table in the db containing known GPS data. Verify that the 3D model created is as expected, ie. that it matches a 'golden' model.

\subsection ds000003 Development Strategy - Cycle 3

Functions / Modules: Create and maintain a list of GPS vehicles

Testing approach:
Verify that appropriate error messages are produced if:
- a known table of gps data does not produce the correct list of GPS vehicles
- the current location of the vehicles is incorrect.

\subsection ds000004 Development Strategy - Cycle 4 

Functions / Modules: Run Mode

Testing approach:
Verify that appropriate error messages are produced if:
- a known table of gps data does not produce the correct list of GPS vehicles
- the current location of the vehicles is incorrect.

\subsection ds000005 Development Strategy - Cycle 5

Functions / Modules: Replay Mode

Testing approach:
Verify that appropriate error messages are produced if:
- a known table of gps data does not produce the correct replay.

**/
