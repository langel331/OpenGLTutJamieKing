#ifndef WINDOW_H
#define WINDOW_H
#include <QtOpenGL\qglwidget>

class Window : public QGLWidget
{
protected:
	void initializeGL();
	void paintGL();

public:

};
#endif 

