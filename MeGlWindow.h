#ifndef ME_GL_WINDOW
#define ME_GL_WINDOW
#include <QtOpenGL\qglwidget>

class MeGlWindow : public QGLWidget
{
	protected:
		void sendDataToOpenGL();
		void paintGL();
		void mouseMoveEvent(QMouseEvent * e);
		void keyPressEvent(QKeyEvent * e);
		void makeGrid();
		void initializeGL();

	public:
};

#endif

