#ifndef WINDOW_H
#define WINDOW_H
#include <QtOpenGL\qglwidget>


class Window : public QGLWidget
{
protected:
	void initializeGL();
	void paintGL();

public:
	void sendDatatoOpenGL();
	//bool checkStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType);
	bool checkProgramStatus(GLuint programID);
	bool checkShaderStatus(GLuint shaderID);
	std::string readShaderCode(const char*fileName);
	void installShaders();
	~Window();

};
#endif 

