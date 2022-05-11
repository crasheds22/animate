#ifndef MODEL_H
#define MODEL_H

#include "vector3.h"
#include "transform.h"

typedef struct {
    int v_count;
    int vn_count;
    int f_count;

    vector3* vertices;
    vector3* normals;
    vector3* faces;

    Transform* transform;
} Model;

Model LoadModel(const char* filename);
void DeleteModel(Model* model);
void DrawModel(Model* model);

#endif // MODEL_H
