#include "ShapeGenerator.h"
#include <glm\glm.hpp>
#include <Primitives\Vertex.h>
# define NUM_ARRAY_ELEMENTS(a) sizeof(a)/sizeof(*a)


ShapeData ShapeGenerator::makeTriangle()
{
	ShapeData ret;

	//Vertex array of points and color on a triangle
	Vertex myTri[] =
	{
		glm::vec3(+0.0f, +1.0f, +0.0f),
		glm::vec3(+1.0f, +0.0f, +0.0f),

		glm::vec3(-1.0f, -1.0f, +0.0f),
		glm::vec3(+0.0f, +1.0f, +0.0f),

		glm::vec3(+1.0f, -1.0f, +0.0f),
		glm::vec3(+0.0f, +0.0f, +1.0f),
	};

	//ret's number of vertices = total size of array/size of first element of array
	ret.numVertices = NUM_ARRAY_ELEMENTS(myTri);
	//assign vertices to above calcuated number of vertices
	ret.vertices = new Vertex[ret.numVertices];
	//copy bytes from size of myTri to ret.vertices
	memcpy(ret.vertices, myTri, sizeof(myTri));

	//declare indices array
	GLushort indices[] = {0, 1, 2};
	//ret's number of indices = total size of array/size of first element of array
	ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
	//assign indices to above calcuated number of indices
	ret.indices = new GLushort[ret.numIndices];
	//copy bytes from size of indices to ret.indices
	memcpy(ret.indices, myTri, sizeof(indices));

	return ret;
}
