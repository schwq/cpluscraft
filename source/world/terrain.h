#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "../common.h"
#include "../error.h"
#include "../objects/shapes.h"
#include "../objects/shader.h"

class Terrain {
public:

    Terrain(Cube& cube, float x, float y, float z);
    void draw(Shader& shader);
    void update(float x, float y, float z);
private:

    float fatorX;
    float fatorY;
    float fatorZ;
    Cube& cube;

};

#endif
