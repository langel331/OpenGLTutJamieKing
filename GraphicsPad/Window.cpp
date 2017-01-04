#include <GL\glew.h>
#include <iostream>
#include <fstream>
#include "Window.h"

void sendDatatoOpenGL()
{
	// depth values for each triangle
	const float RED_TRIANGLE_Z = 0.5f;
	const float BLUE_TRIANGLE_Z = -0.5f;

	// Vertex array of points and color on a triangle
	GLfloat verts[]
	{
		-1.0f, -1.0f, RED_TRIANGLE_Z,
		+1.0f, +0.0f, +0.0f,
		+0.0f, +1.0f, RED_TRIANGLE_Z,
		+1.0f, +0.0f, +0.0f,
		+1.0f, -1.0f, RED_TRIANGLE_Z,
		+1.0f, +0.0f, +0.0f,

		+1.0f, +1.0f, BLUE_TRIANGLE_Z,
		+0.0f, +0.0f, +1.0f,
		+0.0f, -1.0f, BLUE_TRIANGLE_Z,
		+0.0f, +0.0f, +1.0f,
		-1.0f, +1.0f, BLUE_TRIANGLE_Z,
		+0.0f, +0.0f, +1.0f,
	};

	//declare vertex buffer Id
	GLuint vertexBufferID;
	//Create vertex buffer
	glGenBuffers(1, &vertexBufferID);
	//Bind vertex buffer to vertices
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	//Define which buffer to bind to vertex array to
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	//enable vertex position
	glEnableVertexAttribArray(0);
	//Describe type  of data to OpenGL (0 = position attribute, 2 = # of position floats, sizeof(float) * 6 = stride to next element)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	//enable vertex color data
	glEnableVertexAttribArray(1);
	//Describe type of data to OpenGL (1 = position attribute, 3 = # of color floats, sizeof(float) * 6 = stride t0 next element, (char*)(sizeof(float) * 2)) = where does color data begin in the element)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));

	// Index array of points on a triangle (store each vertex as an index)
	GLushort indices[] = { 0, 1, 2, 3, 4, 5};
	// declare index buffer Id
	GLuint indexBufferID;
	//Create index buffer
	glGenBuffers(1, &indexBufferID);
	//Bind index buffer to points elements
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	//Define which buffer to bind to index array to
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

bool checkStatus(GLuint objectID,PFNGLGETSHADERIVPROC objectPropertyGetterFunc,	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,GLenum statusType)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		std::cout << buffer << std::endl;
		delete[] buffer;
		return false;
	}
	return true;
}

bool checkShaderStatus(GLuint shaderID)
{
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

std::string readShaderCode(const char*fileName)
{
	//read shader file
	std::ifstream meInput(fileName);
	//throws error if failed to load
	if (!meInput.good())
	{
		std::cout << "File failed to load " << fileName;
		exit(1);
	}
	return std::string(std::istreambuf_iterator<char>(meInput), std::istreambuf_iterator<char>());
			
}

void installShaders()
{
	//create vertex shader object
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	//create fragment shader object
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);


	//assign source files to corresponding shaders
	const char* adapter[1];
	std::string temp = readShaderCode("VertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	std::string temp1 = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp1.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	//compile shaders
	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);
	//checks if either shaders failed to copmpile
	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
		return;

	//create program to link shaders
	GLuint programID = glCreateProgram();
	//attach shaders to program
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	//link program
	glLinkProgram(programID);
	//check for linking failture
	if (!checkProgramStatus(programID))
		return;

	//install shaders
	glUseProgram(programID);
}

//Iniitalize GL
void Window::initializeGL()
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	sendDatatoOpenGL();
	installShaders();
}


//Draw to window
void Window::paintGL()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width(), height());
	//glDrawArrays(GL_TRIANGLES, 0, 6); //if drawing from vertex array instead of indices
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}


