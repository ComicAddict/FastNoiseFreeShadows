#include "Sphere.h"

Sphere::Sphere(int stack, int sector, bool smooth, float radius) : stack(stack), sector(sector), smooth(smooth), radius(radius){
	genVertices();
	genSmoothSphere();
}

void Sphere::setStack(int stack) {
	stack = stack;
	genVertices();
	if (smooth)
		genSmoothSphere();
	else
		genFlatSphere();
}
void Sphere::setSector(int sector) {
	sector = sector;
	genVertices();
	if (smooth)
		genSmoothSphere();
	else
		genFlatSphere();
}

void Sphere::setRadius(float radius) {
    radius = radius;
    genVertices();
    if (smooth)
        genSmoothSphere();
    else
        genFlatSphere();
}

void Sphere::setDims(int stack, int sector, float radius) {
    this->radius = radius;
    this->stack = stack;
    this->sector = sector;
    genVertices();
    if (smooth)
        genSmoothSphere();
    else
        genFlatSphere();
}

float* Sphere::getVertices() {
	return &vertices[0];
}

float* Sphere::getNormals() {
    return &normals[0];
}

int* Sphere::getIndices() {
	return &indices[0];
}

void Sphere::genVertices() {
    vertices.clear();
    normals.clear();
    const float PI = acos(-1);
    float x, y, z, nx, ny, nz;

    float stackStep = PI / stack;
    float sectorStep = 2 * PI / sector;
    float a_stack, a_sector;
    for (int i = 0; i <= stack; i++) {
        a_stack = PI / 2 - i * stackStep;
        nz = sinf(a_stack);
        for (int j = 0; j <= sector; j++) {
            a_sector = j * sectorStep;
            nx = cosf(a_stack) * cosf(a_sector);
            ny = cosf(a_stack) * sinf(a_sector);
            x = radius * nx;
            y = radius * ny;
            z = radius * nz;
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);
        }
    }
}

void Sphere::genSmoothSphere() {
    indices.clear();
    unsigned int k1, k2;
    for (int i = 0; i < stack; i++) {
        k1 = i * (sector + 1);
        k2 = k1 + sector + 1;
        for (int j = 0; j < sector; j++, k1++, k2++) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stack - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

void Sphere::genFlatSphere() {

}