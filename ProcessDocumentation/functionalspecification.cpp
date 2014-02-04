/** 

\page funcspec Functional Specifications
\section classes

\subsection ssclasscube 	class Cube
Parent Class:			none.
public Member Variables:	
				X_t m_minX
				X_t m_maxX
				Y_t m_minY
				Y_t m_maxY
				Z_t m_minZ
				Z_t m_maxZ
public Methods:			Cube( const X_t minX, const X_t maxX, const Y_t minY, const Y_t maxY, const Z_t minZ, const Z_t maxZ )


\subsection ssclass3DPoint 	class 3DPoint
Parent Class:			none.
public Member Variables:	
				X_t m_x
				Y_t m_y
				Z_t m_z
public Methods:			3DPoint(const X_t x, const Y_t y, const Z_t z)

\subsection ssclass3DPoints 	class 3DPoints // PURE VIRTUAL
Parent Class:			none.
public Member Variables:	
				X_t m_x
				Y_t m_y
				Z_t m_z
public Methods:			3DPoints()
                                virtual getZ(const X_t& x, const Y_t& y) = 0 		

\subsection ssclass3DPointsSqlQuery class 3DPointsSqlQuery
Parent Class:			3DPoints
public Member Variables:	none.
public Methods:			3DPointsSqlQuery()
                                virtual getZ(const X_t& x, const Y_t& y) const



\subsection ssclass3DPointsGrid	class 3DPointsGrid
Class Name: 	  		3DPointsGrid
Parent Class:			3DPoints
public Member Variables:	none.
public Methods:			3DPointsGrid(	
						const std::string& sqlQuery, 
						const Cube& boundary,
						const uint32_t numColumns,
						const uint32_t numRows
						)
                                virtual getZ(const X_t& x, const Y_t& y) const
				add(const 3DPoint& p)


**/
