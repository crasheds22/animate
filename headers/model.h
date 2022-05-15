#ifndef MODEL_H
#define MODEL_H

#include "vector3.h"
#include "transform.h"

typedef struct {
    const char* name;

    vector3 ka; // ambient
    vector3 kd; // diffuse
    vector3 ks; // specular
    vector3 ke; // emmissive

    double ns; // specular exponent
    double ni; // refraction index

    double d; // dissolve (1.0: fully opaque)
} Material;

typedef struct {
    const char* name;

    int v_count;
    int vn_count;
    int f_count;
    int vt_count;

    vector3* vertices;
    vector3* normals;
    vector3* tex_coords;
    vector3** faces;

    Material* material;

    Transform* transform;
} Model;

Model LoadModel(const char* filename);
void DeleteModel(Model* model);
void DrawModel(Model* model);

Material LoadMaterial(const char* filename);

#endif // MODEL_H
