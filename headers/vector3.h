#ifndef VECTOR3_H
#define VECTOR3_H

typedef struct {
	double x, y, z;
} vector3;

vector3 new_vector3(double x, double y, double z);
vector3 zero();
vector3 negative(const vector3* v);

vector3 add(const vector3* u, const vector3* v);
vector3 subtract(const vector3* u, const vector3* v);

vector3 multiply(const vector3* u, double t);
vector3 divide(const vector3* u, double t);

double length_squared(const vector3* v);
double length(const vector3* v);

vector3 normalise(const vector3* v);

double dot_product(const vector3* u, const vector3* v);

vector3 cross_product(const vector3* u, const vector3* v);

vector3 reflect(const vector3* v, const vector3* n);

#endif
