#include <GL\glew.h>
#include <MeGlWindow.h>
#include <iostream>
#include <fstream>
#include <QtGui\qmouseevent>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <Vertex.h>
#include <ShapeGenerator.h>
#include "Camera.h"


//extern const char* vertexShaderCode;
//extern const char* fragmentShaderCode;

GLuint programID;

const float X_DELTA = 0.1;
const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOAT_PER_TRI = 6;
const uint TRI_BYTE_SIZE = NUM_VERTICES_PER_TRI*NUM_FLOAT_PER_TRI*sizeof(float);
uint numTris = 0;
GLint MAX_TRIS = 200;
GLuint numIndices;

Camera camera;


void MeGlWindow::sendDataToOpenGL()
{
	//ShapeData tri = ShapeGenerator::makeTriangle();
	ShapeData shape = ShapeGenerator::makeCube();

	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));

	GLuint indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);

	numIndices = shape.numIndices;
	shape.cleanUp();

	GLuint transformationMatrixBufferID;
	glGenBuffers(1, &transformationMatrixBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, transformationMatrixBufferID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * 2, 0, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 0));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 4));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 8));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 12));
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
}

void MeGlWindow::paintGL()
{
	glm::mat4 projectionMatrix = glm::perspective(45.0f, ((float)width()) / height(), 0.1f, 10.0f);
	glm::mat4 fullTransforms[] =
	{
		projectionMatrix * camera.getWorldToViewMatrix() * glm::translate(glm::mat4(), glm::vec3(-1.0f, 0.0f, -3.0f)) * glm::rotate(glm::mat4(), 90.0f, glm::vec3(1.0f, 0.0f, 0.0f)),
		projectionMatrix * camera.getWorldToViewMatrix() * glm::translate(glm::mat4(), glm::vec3(1.0f, 0.0f, -3.75f)) * glm::rotate(glm::mat4(), 126.0f, glm::vec3(0.0f, 1.0f, 0.0f))
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(fullTransforms), fullTransforms, GL_DYNAMIC_DRAW);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//glDepthFunc(GL_LESS);
	glViewport(0, 0, width(), height());
	glDrawElementsInstanced(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0, 2);
	makeGrid();
}

void MeGlWindow::mouseMoveEvent(QMouseEvent* e)
{
	camera.mouseUpdate(glm::vec2(e->x(), e->y()));
	repaint();
}
//
void MeGlWindow::keyPressEvent(QKeyEvent* e)
{
	switch (e->key())
	{
	case Qt::Key::Key_W:
		camera.moveForward();
		break;
	case Qt::Key::Key_S:
		camera.moveBackward();
		break;
	case Qt::Key::Key_A:
		camera.strafeLeft();
		break;
	case Qt::Key::Key_D:
		camera.strafeRight();
		break;
	case Qt::Key::Key_R:
		camera.moveUp();
		break;
	case Qt::Key::Key_F:
		camera.moveDown();
		break;
	}
	repaint();
}

void MeGlWindow::makeGrid() {
	
	glm::mat4 projectionMatrix = glm::perspective(45.0f, ((float)width()) / height(), 0.1f, 10.0f);
	glBegin(GL_LINES);
	for (int x = -10; x <= 10; x++) {
		glColor3f(1.0f, 1.0f, 1.0f);
		float temp = (float)x / 10.0;
		glm::vec4 t = glm::vec4(temp, -1.0f, 0.0f, 0.0f);
		glm::vec4 coor = projectionMatrix *
			glm::translate(glm::mat4(),glm::vec3(0.0f, 0.0f, -3.0f)) *
			glm::rotate(glm::mat4(), 45.0f, glm::vec3(1.0f, 1.0f, 0.0f)) *t;
		glVertex3f(coor.x, coor.y, coor.z);

		t = glm::vec4(temp, 1.0f, 0.0f, 0.0f);
		coor = projectionMatrix *
			glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -3.0f)) *
			glm::rotate(glm::mat4(), 45.0f, glm::vec3(1.0f, 1.0f, 0.0f)) *t;
		glVertex3f(coor.x, coor.y, coor.z);

		t = glm::vec4(-1.0f, temp, 0.0f, 0.0f);
		coor = projectionMatrix *
			glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -3.0f)) *
			glm::rotate(glm::mat4(), 45.0f, glm::vec3(1.0f, 1.0f, 0.0f)) *t;
		glVertex3f(coor.x, coor.y, coor.z);

		t = glm::vec4(1.0f, temp, 0.0f, 0.0f);
		coor = projectionMatrix *
			glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -3.0f)) *
			glm::rotate(glm::mat4(), 45.0f, glm::vec3(1.0f, 1.0f, 0.0f)) *t;
		glVertex3f(coor.x, coor.y, coor.z);

		//glVertex3f(temp, 1.0f, 0.0f);
		std::cout << x << std::endl;
		
	};
	glEnd();

	/*for (int y = 0; y < 10; y++) {
		glBegin(GL_LINES);
		glVertex3f(-1, y, 0);
		glVertex3f(1, y, 0);
		glEnd();
		
	};*/
	/*GLfloat glLineVertices[] = {
		1,1,0,
		0,0,0
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, glLineVertices);
	glDrawArrays(GL_LINES, 0, 2);
	glDisableClientState(GL_VERTEX_ARRAY);*/

	/*GLfloat verts[] =
	{
		+0.0f, +1.0f,
		-1.0f, -1.0f,
		+1.0f, -1.0f,
	};
	GLuint myBufferID;
	glGenBuffers(1, &myBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, myBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts),
		verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);*/

	//pushPOP

	/*for (int i = -20; i <= 20; i++) {
		glPushMatrix();
		if (i < 20) {
			glTranslatef(0, 0, -3);
			glRotatef(45, 1, 1, 0);
		}
		else {
			glTranslatef(0, 0, -3);
			glRotatef(45, 1, 1, 0);
		}
		glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f((float)i/20.0, -1.0f, 0.0f);
		glVertex3f((float)i / 20.0, 1.0f, 0.0f);
		glEnd();
		glPopMatrix();

	}*/
}

void makeAnotherTri()
{
	const GLfloat thisTri_X = -1 + numTris * X_DELTA;
	GLfloat thisTri[] = {
		thisTri_X, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		thisTri_X + X_DELTA, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		thisTri_X, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};
	glBufferSubData(GL_ARRAY_BUFFER, numTris * TRI_BYTE_SIZE,
		TRI_BYTE_SIZE, thisTri);
	numTris++;
}

bool checkCompileStatus(GLuint shaderID) {
	GLint result, length;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		char *log;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		log = (char*)malloc(length);
		glGetShaderInfoLog(shaderID, length, &result, log);
		printf("%s\n", log);
		delete[] log;
		return false;
	}
	return true;
}

bool checkProgramStatus(GLuint programID) {
	GLint linkStatus;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE) {
		GLint infoLogLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *buffer = new GLchar[infoLogLength];
		GLsizei bufferSize;
		glGetProgramInfoLog(programID, infoLogLength, &bufferSize, buffer);
		printf("%s\n", buffer);
		delete[] buffer;
		return false;
	}
	return true;
}

std::string readShaderCode(const char* filePath) {
	std::ifstream fileInput(filePath);
	if (!fileInput.good())
	{
		std::cout << "File failed to load" << filePath << std::endl;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char> (fileInput),
		std::istreambuf_iterator<char> ());
}

void installShaders()
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	const char* adapter[1];
	std::string temp = readShaderCode("VertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	temp = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);
	if (!checkCompileStatus(vertexShaderID) || !checkCompileStatus(fragmentShaderID))
		return;

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	if (!checkProgramStatus(programID))
		return;
	glUseProgram(programID);
}

void MeGlWindow::initializeGL()
{
	glewInit();
	glEnable(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	setMouseTracking(true);
	
	sendDataToOpenGL();
	
	installShaders();
}
