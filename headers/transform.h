#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vector3.h"

typedef struct {
    vector3 position;
    vector3 rotation;
    vector3 scale;
} Transform;

#endif // TRANSFORM_H
