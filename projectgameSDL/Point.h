#ifndef __Point__
#define __Point__
#include<iostream>
#include<string>
#include<SDL.h>
class Point {
public:
	Point(float x = 0,float y=0):x(x),y(y){}

	Point operator+(const Point& p2)const {
		return Point(x + p2.x, y + p2.y);
	}
	friend Point operator+=(Point& p1, const Point& p2) {
		p1.x += p2.x;
		p1.y += p2.y;
		return  p1;
	}


	Point operator-(const Point& p2) const { return Point(x - p2.x, y - p2. y); }
	friend Point operator-=(Point& p1, const Point& p2) {
		p1.x -= p2.x;
		p1.y -= p2.y;
		return p1;
	}

	Point operator*(const float cons) const { return Point(x * cons, y * cons); }



public:
	float x, y;
};
#endif
