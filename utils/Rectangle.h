#ifndef Rectangle_h
#define Rectangle_h

namespace utils
{
  template <class Tx>
  class Width
  {
  public:
    Width(Tx x) : m_width(x) {}
    Tx m_width;
  };
  typedef Width<uint32_t> Width_t;

  template <class Ty>
  class Height
  {
  public:
    Height(Ty y) : m_height(y) {}
    Ty m_height;
  };
  typedef Height<uint32_t> Height_t;

  template <class Tx, class Ty>
  class CentrePoint
  {
  public:
    CentrePoint(Tx x, Ty y) : m_x(x), m_y(y) {}
    Tx m_x;
    Ty m_y;
  };
  typedef CentrePoint<uint32_t, uint32_t> CentrePoint_t;
  typedef CentrePoint<uint32_t, uint32_t> CenterPoint_t; // Americans :)

  template <class Tx, class Ty>
  class Rectangle
  {
  public:
    Rectangle(Tx x, Ty y) : m_width(x), m_xmin(0), m_xmax(x), m_height(y), m_ymin(0), m_ymax(y) {}
    Rectangle(const CentrePoint<Tx, Ty>& centrePoint, const Width<Tx>& width, const Height<Ty>& height) : m_width(width.m_width), m_height(height.m_height)
    {
      setCentre(centrePoint);
    }

    void setCentre(Tx x, Ty y)
    {
      m_xmin = x - (m_width / 2);
      m_xmax = x + (m_width / 2);
      m_ymin = y - (m_height / 2);
      m_ymax = y + (m_height / 2);
    }

    void setCentre(const CentrePoint_t& centrePoint) { setCentre(centrePoint.m_x, centrePoint.m_y); }
    CentrePoint<Tx, Ty> centrePoint(void) { return CentrePoint<Tx, Ty> (((m_xmin + m_xmax) / 2), ((m_ymin + m_ymax) /2)); }
    Tx xCentre(void) 	const { return ((m_xmin + m_xmax) / 2); }
    Ty yCentre(void) 	const { return ((m_ymin + m_ymax) / 2); }
    Tx xMin(void) 	const { return m_xmin;}
    Tx xMax(void) 	const { return m_xmax;}
    Tx width(void) 	const { return m_width;}
    Ty yMin(void) 	const { return m_ymin;}
    Ty yMax(void) 	const { return m_ymax;}
    Ty height(void) 	const { return m_height;}

  private:
    Tx m_width, m_xmin, m_xmax;
    Ty m_height, m_ymin, m_ymax;

  };

  typedef Rectangle<uint32_t, uint32_t> Rectangle_t;

  template <class Tx, class Ty>
  std::ostream& operator<<(std::ostream& os, const Rectangle<Tx, Ty>& rectangle)
  {
    os << " m_xmin: " << rectangle.xMin() << ", m_xmax: " << rectangle.xMax() << ", m_width: " << rectangle.width() << ", m_ymin: " << rectangle.yMin() << ", m_ymax: " << rectangle.yMax() << ", m_height: " << rectangle.height() ;
    return os;
  }

}
#endif
