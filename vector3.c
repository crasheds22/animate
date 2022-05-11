#include "vector3.h"

#include <math.h>

vector3 new_vector3(double x, double y, double z) {
    vector3 v;

    v.x = x;
    v.y = y;
    v.z = z;

    return v;
}

vector3 zero() {
    return new_vector3(0, 0, 0);
}

vector3 negative(const vector3* v) {
    return new_vector3(-v->x, -v->y, -v->z);
}

vector3 add(const vector3* u, const vector3* v) {
    return new_vector3(
        u->x + v->x,
        u->y + v->y,
        u->z + v->z
    );
}

vector3 subtract(const vector3* u, const vector3* v) {
    vector3 neg = negative(v);
	return add(u, &neg);
}

vector3 multiply(const vector3* u, double t) {
    return new_vector3(u->x * t, u->y * t, u->z * t);
}

vector3 divide(const vector3* u, double t) {
	return multiply(u, (1 / t));
}

double length_squared(const vector3* v) {
    return dot_product(v, v);
}

double length(const vector3* v) {
	return sqrt(length_squared(v));
}

vector3 normalise(const vector3* v) {
	return divide(v, length(v));
}

double dot_product(const vector3* u, const vector3* v) {
	return u->x * v->x + u->y * v->y + u->z * v->z;
}

vector3 cross_product(const vector3* u, const vector3* v) {
    return new_vector3(
        u->y * v->z + u->z * v->y,
        u->z * v->x + u->x * v->z,
        u->x * v->y + u->y * v->x
    );
}

vector3 reflect(const vector3* v, const vector3* n) {
    vector3 a = multiply(n, 2 * dot_product(v, n));
	return subtract(v, &a);
}
