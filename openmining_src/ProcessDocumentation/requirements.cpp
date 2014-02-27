
/*! \page pagerequirements Requirements
\tableofcontents
\section secnfr Non-functional requirements:
\subsection subsectiondeps Dependency Management
In general, all dependencies shall be documented and kept to the bare minimum required to satisfy the requirements.

\subsection ssaff Affordability 
The system shall be developed in a manner calculated to minimize total cost over the entire project lifespan (development, installation, maintenance).

\subsection ssaud Auditability 
- bidirectional mapping: every functional requirement shall be mapped to its associated automated unit tests, so that it is easy to see which unit tests apply to a given requirement. Likewise, a unit test may be used by more than one requirement, so each unit test shall be mapped to its associated requirements.
- There shall be bidirectional mapping between every artifact in the system.
- System artifacts include: functional requirements, design artifacts, use cases, source and header files, free functions(not in a class), classes, enums, #defines, global variables, static variables. 
- every requirement shall document the following:
- functional dependencies (eg. application depends on Qt, postgres, etc.)
- build time dependencies (eg. header files, libraries etc.)
- every requirement's dependency on other requirements shall be recorded and mapped.
- all downloadable packages shall have a version number, which changes every time a new version is released.
	
\subsection sssim Simplicity 
- The project shall adhere to 'lesscode' principles.

\subsection ssreu Reusability
- Functions shall be as short as possible to facilitate code reuse. 

\subsection sstes Testability 
- every functional requirement shall have an associated automated unit test.

\subsection ssrel Reliability 
- the project shall never be released with known bugs. Issues shall be resolved before new features are developed, as per Spolsky's 'dogfood' arguments.

\subsection sseff Efficiency 
- the project shall consume the minimum amount of computer resources required to fulfil requirements.

\subsection ssbui Buildability
- every source file shall include every header file required for successful compilation, ie. if main.cpp depends on a.h and b.h, main.cpp shall explicitly include a.h and b.h, even if a.h includes b.h. This shall be proved by compiling every single source file into a standalone library.
- Compilation dependencies shall be mapped and minimized.
- Source files shall not include files that are not needed.
- Library dependencies shall be documented.

\subsection ssind Installability
- the system shall minimize the effort required to configure and use the software. Ideally, zero site specific configuration shall be required.
- the software shall utilize standard packaging, such as '.deb' packages for ubuntu and '.msi' or '.exe' for windows applications.
- see "http://www.producingoss.com/en/getting-started.html" for guidelines.

\subsection ssusa Usability
- Make it as simple as possible, then simplify some more. 
- Every request for technical assistance shall be recorded and categorised, and a 'heat map' developed to highlight problem areas. The ideal system would be so easy to use that nobody every needed help to use it. If you get asked to explain something, it is not simple enough.

\subsection sssel Self documenting 
- the source code shall contain the requirements documentation.
- the source code shall generate html documentation using doxygen

\subsection ssmai Maintainability
- All discussions shall be public unless there is a specific need for privacy.

\subsection ssdep Dependency Management
- Every 3rd party library that is required shall be documented, along with the license applicable to the library.

\subsection ssdesDesign Constraints
Follow the recommendations in "Beyond the C++ Standard Library: An introduction to boost"
- use smart_pointer library (shared_pointer, scoped_ptr, intrusive_ptr, weak_ptr) or similar whenever objects are created dynamically (ie. via 'new'). 
- scoped_ptr: calls 'delete' for you. Non-copyable.
- shared_ptr: reference counted pointer, deletes pointee when reference counts goes to 0.
- weak_ptr: observer of a shared_ptr, does not imply ownership. If the underlying object gets deleted, wek_ptr gets set to null. Avoids dangling pointer problem.

Casting & Conversions: The boost extensions allow you to unambiguously state your intent.
- polymorphic_cast: always throws an exception if the conversion fails. (dynamic_cast throws if a reference conversion fails, but doesn't throw if a ptr conversion fails). If a failed polymorphic pointer cast is not an error, you should use dynamic_cast).
- polymorphic_downcast: debug build: dynamic_cast. Release build: static_cast. Gives a performance increase for release builds. This is an optimization, and should only be used after profiling demonstrates the need for it. 
- numeric_cast: std::numeric_limits<int>::max(), ...::(min).
- lexical_cast:

\subsection sscod Coding Standard
- whenever a type conversion is performed between different numeric types, make the conversion safe by using numeric_cast.
- whenever a type conversion is performed to or from string types, make the conversion safe by using lexical_cast.
- prefer boost::checked_delete to delete. This adds zero runtime overhead.
- measure object size for each build.

\section secfr Functional Requirements
\subsection ssfr1 FR000001
- The application shall display a 3D scale model of the mine surface based on historical GPS vehicle data.
\see @ref ssBuild3DModel 
\see @ref OS1

\subsection ssfr2 FR000002
- The application shall maintain a list of GPS equipped vehicles and their most recent location.

\see \link ssvehiclelist Maintain a list of GPS vehicles \endlink

\subsection ssfr3 FR000003
- The application shall offer 2 modes, 'run' mode and 'replay' mode, as described below.
\subsection ssfr4 FR000004
- In 'run' mode, the applications shall display scale models of all vehicles on the mine surface at their last recorded lat / long on the mine surface.
\see \link ssrunmode \endlink
\subsection ssfr5 FR000005
- In 'replay' mode, the application shall show gps equipped vehicles moving around the mine according to the historical gps data. The user shall be able to select an arbitrary start time, and be able to start / stop / pause / resume the replay.
\see \link ssreplaymode \endlink
**/


