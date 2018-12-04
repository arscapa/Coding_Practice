#include <iostream>
#include <cmath>

class Point2d
	{
		double m_x;
		double m_y;
		
		public:
			Point2d(double x = 0.0, double y = 0.0)		// defaults m_x and m_y to zero if no value passed in when creating class
			{
				m_x = x;
				m_y = y;
			}
		
			void print()
			{
				std::cout << "Point2d(" << m_x << ", " << m_y << ");" << std::endl;
			}
			
			double distanceTo(const Point2d & val2) const 					// const before Point2d from being altered. 
																			// const after function declaration prevents class function from changing member varialbe of the class (implicit this pointer)
			{				
				sqrt((m_x - val2.m_x)*(m_x - val2.m_x) + (m_y - val2.m_y)*(m_y - val2.m_y));
			}
			
			friend double distanceFrom(const Point2d &x, const Point2d &y); // allows non-member fucntion 'distanceFrom' to access private member variables
	};
	


double distanceFrom(const Point2d &x, const Point2d &y) 
// implemented member function distanceTo as a nonmember function 
{
	sqrt((x.m_x - y.m_x)*(x.m_x - y.m_x) + (x.m_y - y.m_y) * (x.m_y - y.m_y));
}

int main()
{
	Point2d first;
	Point2d second(3.0, 4.0);
	first.print();
	second.print();
	std::cout << "Distance between two points: " << first.distanceTo(second) << " - member function" << '\n';
	std::cout << "Distance between two points: " << distanceFrom(first,second) << " - non-member function" << '\n';
	return 0;
}
