#ifndef COLLIDER_H
#define COLLIDER_H

#include "vector3.h"
#include "transform.h"

typedef struct {
    vector3 min;
    vector3 max;

    Transform* transform;
} BoxCollider;

typedef struct {
    double radius;

    Transform* transform;
} SphereCollider;

BoxCollider BoxFromPoints(const int point_count, const vector3* points);
SphereCollider SphereFromPoints(const int point_count, const vector3* points);

int Check_PointBox(const vector3* p, const BoxCollider* box);
int Check_PointSphere(const vector3* p, const SphereCollider* sphere);
int Check_BoxBox(const BoxCollider* box1, const BoxCollider* box2);
int Check_SphereSphere(const SphereCollider* sphere1, const SphereCollider* sphere2);
int Check_BoxSphere(const BoxCollider* box, const SphereCollider* sphere);

#endif // COLLIDER_H
