#include <iostream>

using namespace std;

class Vertex {
public:
	double x, y;
	Vertex(double, double);
};
Vertex::Vertex(double x=0, double y=0) {
	Vertex::x=x;
	Vertex::y=y;
}

class Shape {
public:
	virtual void draw()=0;
};

class OpenShape : public Shape {
	virtual double length()=0;
};

class ClosedShape : public Shape {
public:
	virtual double area()=0;
	virtual double perimeter()=0;
};

class Line : public OpenShape {
	Vertex v1, v2;
public:
	double length(){}
	void draw(){}
};

class Polygon : public ClosedShape {
	int n;
	Vertex *v;
public:
	Polygon(int);
	Vertex& vertex(int);
	double area(){}
	double perimeter(){}
	void draw(){}
};
Polygon::Polygon(int n) {
	Polygon::n=n;
	Polygon::v=new Vertex[n];
}
Vertex& Polygon::vertex(int i) {
	return Polygon::v[i];
}

class Circle : public ClosedShape {
	double r;
	Vertex c;
public:
	Circle(int, Vertex){}
	double area(){}
	double perimeter(){}
	void draw(){}
};

main() {
	Polygon square(4), triangle(3);
	Vertex v1(0, 0),v2(0, 1), v3(1, 1), v4(1, 0);
	square.vertex(0)=v1;
	square.vertex(1)=v2;
	square.vertex(2)=v3;
	square.vertex(3)=v4;
	triangle.vertex(0)=v1;
	triangle.vertex(1)=v2;
	triangle.vertex(2)=v3;
}
