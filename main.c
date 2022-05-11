
#include <stdio.h>

#include "model.h"

Model model;

void init() {

    model = LoadModel("cube.obj");

    printf("model.vertices: %i\n", model.v_count);
    printf("model.normals: %i\n", model.vn_count);
    printf("model.faces: %i\n", model.f_count);

}

void animate(double dt) {

}

int main(int argc, char** argv) {

    init();

    char c = getchar();

    return 0;
}
