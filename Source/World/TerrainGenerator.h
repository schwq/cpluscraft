#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "../Common.h"
#include "../LogSystem.h"
#include "../Objects/Shapes.h"
#include "../Objects/Shader.h"

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
