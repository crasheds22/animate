#ifndef PHYSICS_H
#define PHYSICS_H

#include "collider.h"
#include "vector3.h"
#include "transform.h"

vector3 gravity = {0, -9.8, 0};

typedef struct {
    double mass;

    vector3 acceleration;
    vector3 velocity;

    vector3 force;

    Transform* transform;

    int is_kinematic;
} Body;

#endif // PHYSICS_H
