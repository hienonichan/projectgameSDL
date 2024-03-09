#ifndef __Vector__
#define __Vector__

#include<math.h>
class Vector {
public:
	Vector(double x,double y):xpos(x),ypos(y){}

	double getX() { return xpos; }
	double getY() { return ypos; }
	void setX(double x) { xpos = x; }
	void setY(double y) { ypos = y; }
	double length() { return sqrt(xpos * xpos + ypos * ypos); }
      

	Vector operator+(const Vector& v2) const { return Vector(xpos + v2.xpos, ypos + v2.ypos); }
	friend Vector& operator+=(Vector& v1,const Vector& v2) {
		v1.xpos += v2.xpos;
		v1.ypos += v2.ypos;
		return v1;
	}
	Vector operator*(double number) { return Vector(xpos * number, ypos * number); }
	Vector& operator*=(double number) {
		xpos *= number;
		ypos *= number;
		return *this;
	}
    


private:

	double xpos;
	double ypos;
};
#endif

