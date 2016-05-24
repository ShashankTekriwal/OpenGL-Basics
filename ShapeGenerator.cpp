#include <glm\glm.hpp>
#include "ShapeGenerator.h"

#define NUM_ARRAY_ELEMENTS(a) sizeof(a)/sizeof(*a);

ShapeData ShapeGenerator::makeTriangle()
{
	ShapeData ret;
	Vertex tri[] = {
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),

		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),

		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	};
	GLushort indices[] = { 0, 1, 2 };

	ret.numVertices = NUM_ARRAY_ELEMENTS(tri);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, tri, sizeof(tri));

	ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}

ShapeData ShapeGenerator::makeCube() {
	ShapeData ret;
	Vertex stackVerts[] = {
		//backface
		glm::vec3(-1.0f, +1.0f, +1.0f), // 0
		glm::vec3(+1.0f, +0.0f, +0.0f), // Color
		glm::vec3(+1.0f, +1.0f, +1.0f), // 1
		glm::vec3(+1.0f, +0.0f, +0.0f), // Color
		glm::vec3(+1.0f, +1.0f, -1.0f), // 2
		glm::vec3(+1.0f, +0.0f, +0.0f), // Color
		glm::vec3(-1.0f, +1.0f, -1.0f), // 3
		glm::vec3(+1.0f, +0.0f, +0.0f), // Color
		
		//downface
		glm::vec3(-1.0f, +1.0f, -1.0f), // 4
		glm::vec3(+0.0f, +1.0f, +0.0f), // Color
		glm::vec3(+1.0f, +1.0f, -1.0f), // 5
		glm::vec3(+0.0f, +1.0f, +0.0f), // Color
		glm::vec3(+1.0f, -1.0f, -1.0f), // 6
		glm::vec3(+0.0f, +1.0f, +0.0f), // Color
		glm::vec3(-1.0f, -1.0f, -1.0f), // 7
		glm::vec3(+0.0f, +1.0f, +0.0f), // Color
		
		//rightface
		glm::vec3(+1.0f, +1.0f, -1.0f), // 8
		glm::vec3(+0.0f, +0.0f, +1.0f), // Color
		glm::vec3(+1.0f, +1.0f, +1.0f), // 9
		glm::vec3(+0.0f, +0.0f, +1.0f), // Color
		glm::vec3(+1.0f, -1.0f, +1.0f), // 10
		glm::vec3(+0.0f, +0.0f, +1.0f), // Color
		glm::vec3(+1.0f, -1.0f, -1.0f), // 11
		glm::vec3(+0.0f, +0.0f, +1.0f), // Color
		
		//leftface
		glm::vec3(-1.0f, +1.0f, +1.0f), // 12
		glm::vec3(+0.0f, +0.0f, +1.0f), // Color
		glm::vec3(-1.0f, +1.0f, -1.0f), // 13
		glm::vec3(+0.0f, +0.0f, +1.0f), // Color
		glm::vec3(-1.0f, -1.0f, -1.0f), // 14
		glm::vec3(+0.0f, +0.0f, +1.0f), // Color
		glm::vec3(-1.0f, -1.0f, +1.0f), // 15
		glm::vec3(+0.0f, +0.0f, +1.0f), // Color
		
		//topface
		glm::vec3(+1.0f, +1.0f, +1.0f), // 16
		glm::vec3(+0.0f, +1.0f, +0.0f), // Color
		glm::vec3(-1.0f, +1.0f, +1.0f), // 17
		glm::vec3(+0.0f, +1.0f, +0.0f), // Color
		glm::vec3(-1.0f, -1.0f, +1.0f), // 18
		glm::vec3(+0.0f, +1.0f, +0.0f), // Color
		glm::vec3(+1.0f, -1.0f, +1.0f), // 19
		glm::vec3(+0.0f, +1.0f, +0.0f), // Color
		
		//frontface
		glm::vec3(+1.0f, -1.0f, -1.0f), // 20
		glm::vec3(+1.0f, +0.0f, +0.0f), // Color
		glm::vec3(-1.0f, -1.0f, -1.0f), // 21
		glm::vec3(+1.0f, +0.0f, +0.0f), // Color
		glm::vec3(-1.0f, -1.0f, +1.0f), // 22
		glm::vec3(+1.0f, +0.0f, +0.0f), // Color
		glm::vec3(+1.0f, -1.0f, +1.0f), // 23
		glm::vec3(+1.0f, +0.0f, +0.0f), // Color
	};

	ret.numVertices = NUM_ARRAY_ELEMENTS(stackVerts);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, stackVerts, sizeof(stackVerts));

	unsigned short stackIndices[] = {
		0,   1,  2,  0,  2,  3, // Top
		4,   5,  6,  4,  6,  7, // Front
		8,   9, 10,  8, 10, 11, // Right
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Back
		20, 21, 22, 20, 22, 23, // Bottom
	};
	ret.numIndices = NUM_ARRAY_ELEMENTS(stackIndices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, stackIndices, sizeof(stackIndices));

	return ret;
}
