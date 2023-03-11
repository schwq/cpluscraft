#include "TerrainGenerator.h"

    Terrain::Terrain(Cube& cube, float x, float y, float z) : cube(cube), fatorX(x), fatorY(y), fatorZ(z) {}
    void Terrain::draw(Shader& shader) {
        for(uint x = 0; x < fatorX; x++) {
            for(uint y = 0; y < fatorY; y++) {
                for(uint z = 0; z < fatorZ; z++) {
                    cube.translate(glm::vec3(x, y, z));
                    cube.draw(shader);
                }
            }
        }
    }

    void Terrain::update(float x, float y, float z) {
        fatorX = x;
        fatorY = y;
        fatorZ = z;
    }