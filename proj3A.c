
#include <stdio.h>
#include <stdlib.h>

/* Place your struct definitions for Circle, Triangle, and Rectangle here */

typedef struct{
	double originX;
	double originY;
	double radius;
}Circle;
typedef struct{
	double pt1X;
	double pt2X;
	double minY;
	double maxY;
}Triangle;
typedef struct{
	double minX;
	double maxX;
	double minY;
	double maxY;
}Rectangle;

typedef struct{
	void *self;
	double (*ShapeArea)(void *); 
	void (*ShapeBoundingBox)(void *, double *);
}Shape;

/* Define these 9 functions */

double GetCircleArea(void *circ) // setting every data member, per shape, to the first letter of the shape. //
{
	Circle *c;
	c = (Circle *)circ;
	double area = 3.14159 * c->radius * c->radius; // circle arithmetic to find area using init. vals.//
	return area;
};

double GetRectangleArea(void *rect)
{
	Rectangle *r;
	r = (Rectangle *)rect;
	double area = (r->maxX - r->minX) * (r->maxY - r->minY); // same as GetCircleArea func, but rect. //
	return area;
};

double GetTriangleArea(void *tri) // same as GetCircleArea func, but triangle //
{
	Triangle *t;
	t = (Triangle *)tri;
	double area = (t->pt2X - t->pt1X) * (t->maxY - t->minY) * .5;
	return area;
};


void GetCircleBoundingBox(void *circ, double *bbox)
{
	Circle *c;
	c = (Circle *)circ;
	bbox[0] = c->originX - c->radius; // taking param "bbox" and assigning a value to each index of 4 //
	bbox[1] = c->originX + c->radius;
	bbox[2] = c->originY - c->radius;
	bbox[3] = c->originY + c->radius;

};

void GetRectangleBoundingBox(void *rect, double *bbox)
{
	Rectangle *r;
	r = (Rectangle *)rect;
	bbox[0] = r->minX; // Same as Circle bbox, but rectangle //
	bbox[1] = r->maxX;
	bbox[2] = r->minY;
	bbox[3] = r->maxY;

};

void GetTriangleBoundingBox(void *tri, double *bbox)
{
	Triangle *t;
	t = (Triangle *)tri;
	bbox[0] = t->pt1X; // Same as Circle bbox, but triangle //
	bbox[1] = t->pt2X;
	bbox[2] = t->minY;
	bbox[3] = t->maxY;
};

Shape *CreateCircle(double radius, double originX, double originY)
{
	Shape *s = malloc(sizeof(Shape));
	Circle *c = malloc(sizeof(Circle));
	c->originX = originX; // initializing the inputted "c"'s values//
	c->originY = originY;
	c->radius = radius;
	s->self = c;
	s->ShapeArea = GetCircleArea;
	s->ShapeBoundingBox = GetCircleBoundingBox;
	return s;
};

Shape *CreateRectangle(double minX, double maxX, double minY, double maxY)
{
	Shape *s = malloc(sizeof(Shape));
	Rectangle *r = malloc(sizeof(Rectangle));
	r->minX = minX; // initializing the inputted "r"'s values //
	r->maxX = maxX;
	r->minY = minY;
	r->maxY = maxY;
	s->self = r;
	s->ShapeArea = GetRectangleArea;
	s->ShapeBoundingBox = GetRectangleBoundingBox;
	return s;
};

Shape *CreateTriangle(double pt1X, double pt2X, double minY, double maxY)
{

	Shape *s = malloc(sizeof(Shape));
	Triangle *t = malloc(sizeof(Triangle));
	t->pt1X = pt1X; // initializing the inputted "t"'s values //
	t->pt2X = pt2X;
	t->minY = minY;
	t->maxY = maxY;
	s->self = t;
	s->ShapeArea = GetTriangleArea;
	s->ShapeBoundingBox = GetTriangleBoundingBox;
	return s;
};

void GetBoundingBox(Shape *s, double *bbox)
{
	s->ShapeBoundingBox(s->self, bbox);
}

double GetArea(Shape *s)
{
	return s->ShapeArea(s->self);
}
/* DO NOT MODIFY AFTER THIS POINT */


void
PrintTriangle(Triangle *t)
{
    double bbox[4];
    double area;
    area = GetTriangleArea(t);
    GetTriangleBoundingBox(t, bbox);
    printf("Triangle has area %f and bounding box [%f->%f], [%f->%f]\n",
           area, bbox[0], bbox[1], bbox[2], bbox[3]);
}

void
PrintRectangle(Rectangle *r)
{
    double bbox[4];
    double area;
    area = GetRectangleArea(r);
    GetRectangleBoundingBox(r, bbox);
    printf("Rectangle has area %f and bounding box [%f->%f], [%f->%f]\n",
           area, bbox[0], bbox[1], bbox[2], bbox[3]);
}




void
PrintCircle(Circle *c)
{
    double bbox[4];
    double area;
    area = GetCircleArea(c);
    GetCircleBoundingBox(c, bbox);
    printf("Circle has area %f and bounding box [%f->%f], [%f->%f]\n",
           area, bbox[0], bbox[1], bbox[2], bbox[3]);
}

int main()
{
	Shape *shapes[9];
	int i;
	shapes[0] = CreateCircle(1, 0, 0);
	shapes[1] = CreateCircle(1.5, 6, 8);
	shapes[2] = CreateCircle(0.5, -3, 4);

	shapes[3] = CreateRectangle(0, 1, 0, 1);
	shapes[4] = CreateRectangle(1, 1.1, 10, 20);
	shapes[5] = CreateRectangle(1.5, 3.5, 10, 12);

	shapes[6] = CreateTriangle(0, 1, 0, 1);
	shapes[7] = CreateTriangle(0, 1, 0, 0.1);
	shapes[8] = CreateTriangle(0, 10, 0, 50);

	for (i = 0; i < 9; i++)
	{
		double bbox[4];
		printf("Shape %d\n", i);
		printf("\tArea: %f\n", GetArea(shapes[i]));
		GetBoundingBox(shapes[i], bbox);
		printf("\tBbox: %f-%f, %f-%f\n", bbox[0], bbox[1], bbox[2], bbox[3]);
	}
}

