
#include "collider.h"
#include "utility.h"
#include <stdlib.h>

BoxCollider BoxFromPoints(const int point_count, const vector3* points) {
    vector3 min = zero();
    vector3 max = zero();

    for(int i = 0; i < point_count; i++ ) {
        if (points[i].x > max.x)
            max.x = points[i].x;
        if (points[i].y > max.y)
            max.y = points[i].y;
        if (points[i].z > max.z)
            max.z = points[i].z;

        if (points[i].x < min.x)
            min.x = points[i].x;
        if (points[i].y < min.y)
            min.y = points[i].y;
        if (points[i].z < min.z)
            min.z = points[i].z;
    }

    BoxCollider box;
    box.min = min;
    box.max = max;

    return box;
}

SphereCollider SphereFromPoints(const int point_count, const vector3* points) {
    vector3 max;

    for (int i = 0; i < point_count; i++) {
        if (abs(points[i].x) > max.x)
            max.x = abs(points[i].x);
        if (abs(points[i].y) > max.y)
            max.y = abs(points[i].y);
        if (abs(points[i].z) > max.z)
            max.z = abs(points[i].z);
    }

    double rad = length(&max);

    SphereCollider sphere;
    sphere.radius = rad;

    return sphere;
}

int Check_PointBox(const vector3* p, const BoxCollider* box) {
    vector3 real_max = add(&box->transform->position, &box->max);
    vector3 real_min = add(&box->transform->position, &box->min);

    return (p->x >= real_min.x && p->x <= real_max.x) &&
           (p->y >= real_min.y && p->y <= real_max.y) &&
           (p->z >= real_min.z && p->z <= real_max.z);
}

int Check_PointSphere(const vector3* p, const SphereCollider* sphere) {
    vector3 dist = subtract(p, &sphere->transform->position);

    return length(&dist) < sphere->radius;
}

int Check_BoxBox(const BoxCollider* box1, const BoxCollider* box2) {
    vector3 real_max1 = add(&box1->transform->position, &box1->max);
    vector3 real_min1 = add(&box1->transform->position, &box1->min);

    vector3 real_max2 = add(&box2->transform->position, &box2->max);
    vector3 real_min2 = add(&box2->transform->position, &box2->min);

    return (real_min1.x <= real_max2.x && real_max1.x >= real_min2.x) &&
           (real_min1.y <= real_max2.y && real_max1.y >= real_min2.y) &&
           (real_min1.z <= real_max2.z && real_max1.z >= real_min2.z);
}

int Check_SphereSphere(const SphereCollider* sphere1, const SphereCollider* sphere2) {
    vector3 dist = subtract(&sphere1->transform->position, &sphere2->transform->position);

    return length(&dist) < (sphere1->radius + sphere2->radius);
}

int Check_BoxSphere(const BoxCollider* box, const SphereCollider* sphere) {
    vector3 real_max = add(&box->transform->position, &box->max);
    vector3 real_min = add(&box->transform->position, &box->min);

    vector3 clamp = new_vector3(
        max(real_min.x, min(sphere->transform->position.x, real_max.x)),
        max(real_min.y, min(sphere->transform->position.y, real_max.y)),
        max(real_min.z, min(sphere->transform->position.z, real_max.z))
    );

    vector3 dist = subtract(&clamp, &sphere->transform->position);

    return length(&dist) < sphere->radius;
}
