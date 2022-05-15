
#include "model.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/freeglut.h>

Model LoadModel(const char* filename) {
    Model model;
    model.f_count = model.v_count = model.vn_count = 0;
    model.faces = NULL;
    model.vertices = model.normals = NULL;

    FILE* fp = NULL;
    char line[128];
    char type1, type2;

    fp = fopen(filename, "r");
    if (!fp)
        return model;
    while(fgets(line, 128, fp)) {
        sscanf(line, "%c%c", &type1, &type2);

        if (type1 == 'v') {
            if (type2 == 'n') {
                model.vn_count++;
            } else if (type2 == 't') {
            } else {
                model.v_count++;
            }
        } else if (type1 == 'f') {
            model.f_count++;
        }
    }

    rewind(fp);

    model.faces = malloc(model.f_count * sizeof(vector3));
    for (int i = 0; i < model.f_count; i++) {
        model.faces[i] = malloc(3 * sizeof(vector3));
    }
    model.vertices = malloc(model.v_count * sizeof(vector3));
    model.normals = malloc(model.vn_count * sizeof(vector3));

    double x = 0, y = 0, z = 0;
    int f = 0, n = 0, v = 0;
    char a[10], b[10], c[10];

    while(fgets(line, 128, fp)) {
        sscanf(line, "%c%c %s %s %s", &type1, &type2, a, b, c);
        if (type1 == 'v') {
            if (type2 == 'n') {
                model.normals[n] = new_vector3(atof(a), atof(b), atof(c));
                n++;
            } else if (type2 == 't') {
            } else {
                model.vertices[v] = new_vector3(atof(a), atof(b), atof(c));
                v++;
            }
        } else if (type1 == 'f') {
            x = atof(strtok(a, "/"));
            y = atof(strtok(NULL, "/"));
            z = atof(strtok(NULL, "/"));
            model.faces[f][0] = new_vector3(x, y, z);
            x = atof(strtok(b, "/"));
            y = atof(strtok(NULL, "/"));
            z = atof(strtok(NULL, "/"));
            model.faces[f][1] = new_vector3(x, y, z);
            x = atof(strtok(c, "/"));
            y = atof(strtok(NULL, "/"));
            z = atof(strtok(NULL, "/"));
            model.faces[f][2] = new_vector3(x, y, z);
            f++;
        }
    }
    fclose(fp);

    return model;
}

void DeleteModel(Model* model) {
    for(int i = 0; i < model->f_count; i++) {
        free(model->faces[i]);
    }
    free(model->faces);
    free(model->normals);
    free(model->vertices);
}

void DrawModel(Model* model) {
    if (model) {
        glPushMatrix();
            glScalef(model->transform->scale.x, model->transform->scale.y, model->transform->scale.z);

            glRotatef(model->transform->rotation.x, 1, 0, 0);
            glRotatef(model->transform->rotation.y, 0, 1, 0);
            glRotatef(model->transform->rotation.z, 0, 0, 1);

            glTranslatef(model->transform->position.x, model->transform->position.y, model->transform->position.z);

            glBegin(GL_TRIANGLES);
            for (int i = 0; i < model->f_count; i++) {
                glVertex3f(
                    model->vertices[(int)model->faces[i][0].x].x,
                    model->vertices[(int)model->faces[i][1].x].y,
                    model->vertices[(int)model->faces[i][2].x].z
                );
            }
            glEnd();
        glPopMatrix();
    }
}

Material LoadMaterial(const char* filename) {
    Material mat;
    return mat;
}
