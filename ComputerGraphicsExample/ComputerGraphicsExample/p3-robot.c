/* created 3EP2-30 yuji toyama */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "drawer.h"
#include "animator.h"

static int head = 0, body_r = 0;
static int r_shoulder = -90, r_elbow = 0, r_groin = -90, r_knee = 0;
static int l_shoulder = -90, l_elbow = 0, l_groin = -90, l_knee = 0;
static int flag = 0, time = 0;

void myInit(char *progname) 
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		// camera
		gluLookAt(1.0, 1.0, 2.0,
			0.0, 0.0, 0.0,
			0.0, 1.0, 0.0);

		/* body */
		glTranslated(2.0, 1.0, 0.0);
		glRotated((double)body_r, 0.0, 1.0, 0.0);
		glPushMatrix();
			glScaled(1.0, 1.7, 1.7);
			glutWireCube(1.0);
		glPopMatrix();

		drawHead(head);
		drawRightArm(r_shoulder, r_elbow);
		drawLeftArm(l_shoulder, l_elbow);
		drawRightLeg(r_groin, r_knee);
		drawLeftLeg(l_groin, l_knee);
		
	glPopMatrix();

	glutSwapBuffers();
}

void myReshape (int width, int height)
{
	glViewport(0, 0, width, height); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)width/(double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(-2.0, 0.0, -5.0);				// move to enable viewing
	
}

void myKeyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 's':
			// 肩を360度回さないように分岐
			if (r_shoulder  >= -170 && r_shoulder  < 90) {
				r_shoulder  = (r_shoulder  + 5) % 360;
				printf("r_shoulder  = %d\n", r_shoulder );
				glutPostRedisplay();
			}
			break;
		case 'S':
			// 肩を360度回さないように分岐
			if (r_shoulder  > -170 && r_shoulder  <= 90) {
				r_shoulder  = (r_shoulder  - 5) % 360;
				printf("r_shoulder  = %d\n", r_shoulder );
				glutPostRedisplay();
			}
			break;
		case 'e':
			// 肘を後ろに回さないように分岐
			if (r_elbow >= 0 && r_elbow < 150) {
				r_elbow = (r_elbow + 5) % 360;
				printf("elbow = %d\n", r_elbow);
				glutPostRedisplay();
			}
			break;
		case 'E':
			// 肘を後ろに回さないように分岐
			if (r_elbow > 0 && r_elbow <= 150) {
				r_elbow = (r_elbow - 5) % 360;
				printf("elbow = %d\n", r_elbow);
				glutPostRedisplay();
			}
			break;
		case 'h':
			// 頭が360度回らないための分岐
			if (head >= -90 && head < 90) {
				head = (head + 5) % 360;
				glutPostRedisplay();
			}
			break;
		case 'H':
			// 頭が360度回らないための分岐
			if (head > -90 && head <= 90) {
				head = (head - 5) % 360;
				glutPostRedisplay();
			}
			break;
		case 'g':
			// 股関節が360度回らないための分岐
			if (r_groin >= -180 && r_groin < 60) {
				r_groin = (r_groin + 5) % 360;
				printf("groin = %d\n", r_groin);
				glutPostRedisplay();
			}
			break;
		case 'G':
			// 股関節が360度回らないための分岐
			if (r_groin > -180 && r_groin <= 60) {
				r_groin = (r_groin - 5) % 360;
				printf("groin = %d\n", r_groin);
				glutPostRedisplay();
			}
			break;
		case 'k':
			// 膝が360度回らないための分岐
			if (r_knee >= -170 && r_knee < 0) {
				r_knee = (r_knee + 5) % 360;
				printf("knee = %d\n", r_knee);
				glutPostRedisplay();
			}
			break;
		case 'K':
			// 膝が360度回らないための分岐
			if (r_knee > -170 && r_knee <= 0) {
				r_knee = (r_knee - 5) % 360;
				printf("knee = %d\n", r_knee);
				glutPostRedisplay();
			}
			break;
		case 'a':
			if (flag == 0) {
				time = 0;
				// elbow
				r_elbow = 30;
				l_elbow = 30;
				// shoulder
				l_shoulder = -125;
				r_shoulder = -65;
				// groin
				l_groin = -65;
				r_groin = -120;
				// knee
				r_knee = -5;
				l_knee = -5;
				flag = 1;
			}
			else {
				flag = 0;
			}
			printf("flag = %d\n", flag);
			break;
		case 'r':
			// 全体を回す
			body_r = (body_r + 5) % 360;
			glutPostRedisplay();
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}

void idle(int value) {
	time = time + 100;
	if (flag == 1) {
		r_shoulder  = r_animate(r_shoulder , time);
		l_shoulder = l_animate(l_shoulder, time);
		r_groin = l_animate(r_groin, time);
		l_groin = r_animate(l_groin, time);
	}
	else {
		glutPostRedisplay();
	}
	glutTimerFunc(50, idle, value);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutKeyboardFunc(myKeyboard);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);

	glutTimerFunc(1000, idle, 0);

	glutMainLoop();

	return 0;
}
