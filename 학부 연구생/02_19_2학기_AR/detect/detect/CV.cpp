#pragma once

#pragma comment (lib, "lib/freeglut.lib") 
#pragma comment (lib, "lib/glew32.lib") 

#include <cmath>

#include "GL/glew.h" 
#include "GL/freeglut.h" 
#include "GL/freeglut_ext.h"


#include <iostream>
#include <opencv.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#include "MarkerDetector.h"



//       CV             //////////////////////////////////////////////
#if !defined VK_ESCAPE
#define VK_ESCAPE 0x1B      // Escape character (27)
#endif

const int DESIRED_CAMERA_WIDTH = 640;
const int DESIRED_CAMERA_HEIGHT = 480;

static const char *windowName = "Marker_AR";   // Name shown in the GUI window.

// Get access to the webcam.
void initWebcam(VideoCapture &videoCapture, int cameraNumber)
{
	// Get access to the default camera.
	try {   // Surround the OpenCV call by a try/catch block so we can give a useful error message!
		videoCapture.open(cameraNumber);
	}
	catch (cv::Exception &e) {}
	if (!videoCapture.isOpened()) {
		cerr << "ERROR: Could not access the camera!" << endl;
		exit(1);
	}
	cout << "Loaded camera " << cameraNumber << "." << endl;
}

#define WINDOW_NAME "ar"
#define WIDTH 640
#define HEIGHT 480
#define CAMERA_WIDTH WIDTH
#define CAMERA_HEIGHT HEIGHT

GLfloat lineX[] = { 0, 0, 0, 1, 0, 0 };
GLfloat lineY[] = { 0, 0, 0, 0, 1, 0 };
GLfloat lineZ[] = { 0, 0, 0, 0, 0, 1 };
GLuint backgroundTextureId;

const GLfloat squareVertices[] = {
	-0.5f, -0.5f,
	0.5f,  -0.5f,
	-0.5f,  0.5f,
	0.5f,   0.5f,
};
const GLubyte squareColors[] = {
	1,1,0,1,
	0,1,1,1,
	0,0,0,0,
	1,0,1,1,
	
	
	//255, 255,   0, 255,
	//0,   255, 255, 255,
	//0,     0,   0,   0,
	//255,   0, 255, 255,
};

Mat frame;
VideoCapture capture;

CameraCalibration calib = CameraCalibration(6.6023213196534357e+02, 6.5792746888702675e+02, 3.3156864715655962e+02, 2.4292404250751699e+02);
MarkerDetector markerDetector = MarkerDetector(calib);
Matrix44 transMat;

bool findMarker = false;

void buildProjectionMatrix(Matrix33 cameraMatrix, Matrix44& projectionMatrix) {
	GLfloat w = (GLfloat)WIDTH;
	GLfloat h = (GLfloat)HEIGHT;

	float m_near = 0.01;  // Near clipping distance
	float m_far = 100;  // Far clipping distance

	// Camera parameters
	float f_x = cameraMatrix.data[0]; // Focal length in x axis
	float f_y = cameraMatrix.data[4]; // Focal length in y axis (usually the same?)
	float c_x = cameraMatrix.data[2]; // Camera primary point x
	float c_y = cameraMatrix.data[5]; // Camera primary point y

	float size = 2.0;
	projectionMatrix.data[0] = -2.0 * f_x / w;
	projectionMatrix.data[1] = 0.0;
	projectionMatrix.data[2] = 0.0;
	projectionMatrix.data[3] = 0.0;

	projectionMatrix.data[4] = 0.0;
	projectionMatrix.data[5] = 2.0 * f_y / h;
	projectionMatrix.data[6] = 0.0;
	projectionMatrix.data[7] = 0.0;

	projectionMatrix.data[8] = size * c_x / w - 1.0;
	projectionMatrix.data[9] = size * c_y / h - 1.0;
	projectionMatrix.data[10] = -(m_far + m_near) / (m_far - m_near);
	projectionMatrix.data[11] = -1.0;

	projectionMatrix.data[12] = 0.0;
	projectionMatrix.data[13] = 0.0;
	projectionMatrix.data[14] = -2.0 * m_far * m_near / (m_far - m_near);
	projectionMatrix.data[15] = 0.0;
}

void drawBackground() {
	GLfloat w = (GLfloat)WIDTH;
	GLfloat h = (GLfloat)HEIGHT;

	const GLfloat squareVertices[] =
	{
		0, 0,
		w, 0,
		0, h,
		w, h
	};

	static const GLfloat textureVertices[] =
	{
	   1, 0,
	   1, 1,
	   0, 0,
	   0, 1
	};

	static const GLfloat proj[] =
	{
		0, -2.f / w, 0, 0,
		-2.f / h, 0, 0, 0,
		0, 0, 1, 0,
		1, 1, 0, 1
	};

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(proj);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDepthMask(false);
	glDisable(GL_COLOR_MATERIAL);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, backgroundTextureId);

	// Update attribute values.
	glVertexPointer(2, GL_FLOAT, 0, squareVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, textureVertices);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glColor4f(1, 1, 1, 1);
	glDrawArrays(GL_QUAD_STRIP, 0, 4);//ss GL_TRIANGLE_STRIP

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

void drawAR() {
	Matrix33 cameraMatrix = calib.getIntrinsic();
	Matrix44 proj;
	buildProjectionMatrix(cameraMatrix, proj);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(proj.data);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDepthMask(true);
	glEnable(GL_DEPTH_TEST);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glPushMatrix();
	glLineWidth(3.0f);

	if (findMarker) {
		glLoadMatrixf(reinterpret_cast<const GLfloat*>(&transMat.data[0]));

		glVertexPointer(2, GL_FLOAT, 0, squareVertices);
		//glVertexPointer(3, GL_FLOAT, 0, cubeVerts);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(4, GL_UNSIGNED_BYTE, 0, squareColors);
		glEnableClientState(GL_COLOR_ARRAY);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDisableClientState(GL_COLOR_ARRAY);

		float scale = 0.5;
		glScalef(scale, scale, scale);

		glTranslatef(0, 0, 0.1f);

		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glVertexPointer(3, GL_FLOAT, 0, lineX);
		glDrawArrays(GL_LINES, 0, 2);

		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glVertexPointer(3, GL_FLOAT, 0, lineY);
		glDrawArrays(GL_LINES, 0, 2);

		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glVertexPointer(3, GL_FLOAT, 0, lineZ);
		glDrawArrays(GL_LINES, 0, 2);
	}

	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
	//printf("display\n");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawBackground();
	drawAR();
	glutSwapBuffers();
}

void idle() {
	//printf("idle\n");
	capture >> frame;
	//cvtColor(frame, frame, CV_BGR2RGBA);

	//namedWindow("gray", WINDOW_AUTOSIZE);
	//namedWindow("edgeImage", WINDOW_AUTOSIZE);
	//namedWindow("colorEdgeImage", WINDOW_AUTOSIZE);

	imshow("frame", frame);

	markerDetector.processFrame(frame);
	std::vector<Transformation> transformations = markerDetector.getTransformations();
	if (transformations.size() > 0) {
		Transformation transformation = transformations[0];
		transMat = transformation.getMat44();
		findMarker = true;
	}
	else {
		findMarker = false;
	}
	printf("%lu\n", transformations.size());

	// ###debug###
	// Matrix44 tmp = { 0.04455F, 0.89660F, -0.44060F, 0.00000F, -0.98208F, -0.04154F, -0.18383F, 0.00000F, -0.18312F,
	//            0.44090F, 0.87868F, 0.00000F, 1.21119F, 0.98513F, -9.28195F, 1.00000F };
	// transMat = tmp;
	// findMarker = true;

	// update background texture
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, backgroundTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);

	int glErrorCode = glGetError();
	if (glErrorCode != GL_NO_ERROR) {
		cerr << "error:" << glErrorCode << std::endl;
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == '\x1b') {
		exit(-1);
	}
}

int main(int argc, char* argv[]) {
	{
		capture = VideoCapture(0);
		capture.set(CV_CAP_PROP_FRAME_WIDTH, CAMERA_WIDTH);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT, CAMERA_HEIGHT);
	}

	{
		glutInit(&argc, argv);
		glutCreateWindow(WINDOW_NAME);
		glutInitWindowSize(WIDTH, HEIGHT);
		glutInitWindowPosition(100, 100);
		// glutFullScreen();
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
		glutDisplayFunc(display);
		glutIdleFunc(idle);
		glutKeyboardFunc(keyboard);
	}

	// setup background texture
	{
		glGenTextures(1, &backgroundTextureId);
		glBindTexture(GL_TEXTURE_2D, backgroundTextureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// This is necessary for non-power-of-two textures
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);// GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);// _TO_EDGE);

		glEnable(GL_DEPTH_TEST);
	}

	glutMainLoop();
	return 0;
}