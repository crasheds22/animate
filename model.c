
#include "model.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/freeglut.h>

Model LoadModel(const char* filename) {
    Model model;
    model.f_count = model.v_count = model.vn_count = 0;
    model.vertices = NULL;
    model.normals = NULL;
    model.faces = NULL;

    FILE* fp;
    fp = fopen(filename, "r");

    if (!fp)
        return model;

    char line[128] = {0};
    char type, type2;
    while (fgets(line, 128, fp)) {
        sscanf(line, "%c%c", &type, &type2);

        if (type == 'v') {
            if (type2 == 'n') {
                model.vn_count++;
            } else if (type2 == 't') {
            } else {
                model.v_count++;
            }
        }
        if (type == 'f') {
            model.f_count++;
        }
    }

    model.vertices = malloc(model.v_count);
    model.normals = malloc(model.vn_count);
    model.faces = malloc(3 * model.f_count);

    rewind(fp);

    float x, y, z;
    int v_count = 0, vn_count = 0, f_count = 0;
    char fp1[6], fp2[6], fp3[6];
    while(fgets(line, 128, fp)) {
        sscanf(line, "%c%c", &type, &type2);

        if (type == 'v') {
            sscanf(line, "%c%c %f %f %f", &type, &type2, &x, &y, &z);
            if (type2 == 'n') {
                model.normals[vn_count] = new_vector3(x, y, z);
                vn_count++;
            } else if (type2 == 't') {
            } else {
                model.vertices[v_count] = new_vector3(x, y, z);
                v_count++;
            }
        }

        if (type == 'f') {
            sscanf(line, "%c%c %s %s %s", &type, &type2, fp1, fp2, fp3);
            x = atoi(strtok(fp1, "/"));
            y = atoi(strtok(NULL, "/"));
            z = atoi(strtok(NULL, "/"));
            model.faces[f_count] = new_vector3(x, y, z);
            x = atoi(strtok(fp2, "/"));
            y = atoi(strtok(NULL, "/"));
            z = atoi(strtok(NULL, "/"));
            model.faces[f_count + 1] = new_vector3(x, y, z);
            x = atoi(strtok(fp3, "/"));
            y = atoi(strtok(NULL, "/"));
            z = atoi(strtok(NULL, "/"));
            model.faces[f_count + 2] = new_vector3(x, y, z);

            f_count += 3;
        }
    }

    fclose(fp);

    return model;
}

void DeleteModel(Model* model) {
    free(model->vertices);
    free(model->normals);
    free(model->faces);
}

void DrawModel(Model* model) {
    if (model) {
        glPushMatrix();
            glScalef(model->transform->scale.x, model->transform->scale.y, model->transform->scale.z);

            glRotatef(model->transform->rotation.x, 1, 0, 0);
            glRotatef(model->transform->rotation.y, 0, 1, 0);
            glRotatef(model->transform->rotation.z, 0, 0, 1);

            glTranslatef(model->transform->position.x, model->transform->position.y, model->transform->position.z);

            for (int i = 0; i < model->f_count; i++) {

            }
        glPopMatrix();
    }
}
