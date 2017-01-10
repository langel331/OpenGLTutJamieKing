#ifndef WINDOW_H
#define WINDOW_H
#include <QtOpenGL\qglwidget>


class Window : public QGLWidget
{
protected:
	void initializeGL();
	void paintGL();
	void mouseMoveEvent(QMouseEvent*);
	void keyPressEvent(QKeyEvent*);

public:
	void sendDatatoOpenGL();
	bool checkProgramStatus(GLuint programID);
	bool checkShaderStatus(GLuint shaderID);
	std::string readShaderCode(const char*fileName);
	void installShaders();
	~Window();

};
#endif 

