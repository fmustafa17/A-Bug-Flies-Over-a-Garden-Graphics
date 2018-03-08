/******************************************************************************
*
* Official Name:  Farhana Mustafa
*
* E-mail:  fmustafa@syr.edu
*
* Assignment:  Homework 3
*
* Environment/Compiler:  Visual Studio 2015
*
* Date:  March 5th, 2018
*
* References:  none
*
* Interactions:
Press f to let the bug do its thing.
Press w to let the bug flap its wings.
Press s to tell the bug to chill out.
Press r to reset all settings.
Press 1 to set the view to the north view.
Press 2 to set the view to the east view.
Press 3 to set the view to the south view.
Press 4 to set the view to the west view.
Press 0 to set the view to the overhead view.

Press the Escape key to exit
******************************************************************************/

#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define OVER 0
#define NORTH 1
#define EAST 2
#define SOUTH 3
#define WEST 4

using namespace std;

// Globals. 
static GLUquadricObj *qobj; // Create a pointer to a quadric object.
static GLsizei width, height; // OpenGL window size.
static float latAngle = 0.0; // Latitudinal angle.
static float longAngle = 0.0; // Longitudinal angle.
static int isAnimate = 0; // Animated?
static int animationPeriod = 100; // Time interval between frames.
static float xTrans = -10.0;
static float yTransBody = 11.0;
static float yTransWings = 12.5;
static float yTransProb = 2.0;
static float xCoordFour = 0.0;
static float xCoordTwo = 20.0;
static float xCoordOne = -7.0;
static float xCoordThree = -20.0;

static float zBug = -20.0;
static float zFour = 0.0;
static float zTwo = 10.0;
static float zOne = 25.0;
static float zThree = 15.0;

static bool visitFour = 0;
static bool visitTwo = 0;
static bool visitOne = 0;
static bool visitThree = 0;

static int direction = 1;
static int view = NORTH;
static int isOrtho = 0;

void drawFlowerOne(int shadow)
{
	//Stem
	glPushMatrix();
	glTranslatef(-6.0, 4.0, 23.0);
	glScalef(0.2, 4.0, 0.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(0.196078, 0.8, 0.196078);
	glutSolidCube(2.0);
	glPopMatrix();

	//Petals
	glPushMatrix();
	glTranslatef(-6.0, 8.0, 23.0);
	glScalef(3.0, 3.0, 0.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(1.0, 1.0, 0.0);
	glutSolidTetrahedron();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6.0, 8.0, 23.0);
	glRotatef(90.0, 0.0, 5.0, 0.0);
	glScalef(3.0, 3.0, 0.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(1.0, 1.0, 0.0);
	glutSolidTetrahedron();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6.0, 8.0, 23.0);
	glRotatef(45.0, 0.0, 5.0, 0.0);
	glScalef(3.0, 3.0, 0.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(1.0, 0.5, 0.0);
	glutSolidTetrahedron();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6.0, 8.0, 23.0);
	glRotatef(-45.0, 0.0, 5.0, 0.0);
	glScalef(3.0, 3.0, 0.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(1.0, 0.5, 0.0);
	glutSolidTetrahedron();
	glPopMatrix();
}

void drawFlowerTwo(int shadow)
{
	//Stem
	glPushMatrix();
	glTranslatef(20.0, 2.0, 10.0);
	glScalef(0.2, 4.0, 0.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(0.196078, 0.8, 0.196078);
	glutSolidCube(2.0);
	glPopMatrix();

	//Center of flower head
	glPushMatrix();
	glTranslatef(20.0, 7.0, 10.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(0.6, 0.2, 0.2);
	glutSolidSphere(1.0, 10.0, 30.0);
	glPopMatrix();

	//Petals
	glPushMatrix();
	glTranslatef(20.0, 6.0, 10.0);
	glRotatef(-45.0, 1.0, 0.0, 0.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(1.0, 0.7, 0.1);
	glutSolidTorus(1.5, 2.0, 10.0, 5.0);
	glPopMatrix();
}

void drawFlowerThree(int shadow)
{
	//Stem
	glPushMatrix();
	glTranslatef(-18.0, 2.0, 8.0);
	glScalef(0.2, 4.0, 0.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(0.196078, 0.8, 0.196078);
	glutSolidCube(2.0);
	glPopMatrix();

	//petal
	glPushMatrix();
	glTranslatef(-18.0, 7.0, 8.0);
	glScalef(0.5, 2.0, 1.0);
	glRotatef(90.0, 1.0, 1.0, 0.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(1.0, 0.3, 0.5);
	glutSolidDodecahedron();
	glPopMatrix();

}

void drawFlowerFour(int shadow){
	//Stem
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glScalef(0.2, 4.0, 0.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(0.196078, 0.8, 0.196078);
	glutSolidCube(2.0);
	glPopMatrix();

	//Petal
	glPushMatrix();
	glTranslatef(0.0, 5.0, 0.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(1.0, 0.0, 0.0);
	glutSolidTeapot(2.0);
	glPopMatrix();
}

void drawBug(int shadow)
{
	//body
	glPushMatrix();
	glTranslatef(xTrans, yTransBody, zBug);
	glRotatef(45.0, 0.0, 1.0, 0.0);
	glScalef(1.5, 1.0, 1.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(1.0, 1.0, 0.0);
	glutSolidSphere(2.0, 10.0, 30.0);
	glPopMatrix();
}

void drawWings(int shadow)
{
	//Left
	glPushMatrix();
	glTranslatef(xTrans, yTransWings, zBug);
	glRotatef(latAngle + 45.0, 0.0, 0.0, 5.0);
	glScalef(0.7, 3.0, 1.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(1.0, 10.0, 30.0);
	glPopMatrix();

	//Right
	glPushMatrix();
	glTranslatef(xTrans, yTransWings, zBug);
	glRotatef(latAngle + -45.0, 0.0, 0.0, 5.0);
	glScalef(0.7, 3.0, 1.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(1.0, 10.0, 30.0);
	glPopMatrix();
}

void drawProboscis(int shadow) {
	//proboscis
	glPushMatrix();
	glTranslatef(xTrans, yTransProb + 9.0, zBug);
	glScalef(0.5, 1.0, 1.0);
	glRotatef(-5.0, 1.0, 0.0, 0.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(1.0, 0.0, 0.16);
	glutSolidCone(1.0, 4.0, 20, 20);
	glPopMatrix();
}

void drawTree(int shadow)
{
	glPushMatrix();
	glTranslatef(-39.0, 17.0, -13.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(0.0, 1.0, 0.0);
	glutSolidSphere(8.0, 10.0, 30.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-39.0, 14.0, -13.0);
	glRotatef(90.0, 5.0, 0.0, 0.0);
	glColor3f(0.65, 0.16, 0.16);
	gluCylinder(qobj, 5, 5, 25, 15, 5);
	glPopMatrix();
}

void drawBalloon(int shadow) {

	//Balloon
	glPushMatrix();
	glTranslatef(11.0, 11.0, -8.0);
	glScalef(1.7, 2.0, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3f(1.0, 0.3, 0.7);
	glutSolidSphere(1.0, 10.0, 30.0);
	glPopMatrix();

	//String
	glPushMatrix();
	glTranslatef(11.0, 9.0, -8.0);
	glScalef(0.05, 1.0, 1.0);
	glRotatef(90.0, 5.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	gluCylinder(qobj, 1, 1, 8, 15, 5);
	glPopMatrix();

	//Stone
	glPushMatrix();
	glTranslatef(11.0, 1.0, -8.0);
	glScalef(2.0, 1.0, 1.0);
	glColor3f(0.658824, 0.658824, 0.658824);
	glutSolidSphere(1.5, 10.0, 10.0);
	glPopMatrix();

}

/*
//Stipple
glEnable(GL_LINE_STIPPLE); // Enable line stippling.
glRasterPos3f(xTrans, yTransBody, zBug);
glLineStipple(4, 0x00FF);
glBegin(GL_LINES);
glVertex3f(xTrans, yTransBody, zBug);
glEnd();

glDisable(GL_LINE_STIPPLE); // Disable line stippling. */

// Routine to increase the rotation angle.
void increaseAngle(void)
{
	latAngle += 1.0;
	if (latAngle > 360.0)
		latAngle -= 360.0;
	glutPostRedisplay();
}

// Timer function.
//Fly bug to flowers 4, 2, 1, 3
void animate(int value)
{
	if (isAnimate)
	{
		//flowerFour: 0.0, 0.0, 0.0 
		/*
		visitFour = 1;
		if (visitFour) {
			if (xTrans != 0) {
				xTrans += 1.0; 
				//cout << xTrans << endl;
			}
			if (zBug != 0) {
				zBug += 1.0;
			}
		}



		visitFour = 0;
		*/

			if (xTrans <= 0)
			{
				xTrans += 1;
			}
			if (zBug <= 0)
			{
				zBug += 1;
			}
			//xTrans = 0.0 now
			//zBug = 0.0 now



		//flowerTwo: 20.0, 2.0, 10.0
		/*
		visitTwo = 1;
		if (visitTwo) {
			if (zBug != zTwo) {
				zBug += 1.0;
				//cout << zBug << endl;
			}
			if (xTrans != xCoordTwo) {
				xTrans += 1.0;
			}
		}

		//flowerOne: -7.0, 4.0, 25.0
		if (xTrans != xCoordOne) {
			xTrans += 1.0;
		}
		if (zBug != zOne) {
			zBug += 1.0;
		}

		//flowerThree: -20.0, 2.0, 15.0
		if (xTrans != xCoordThree) {
			xTrans += 1.0;
		}
		if (zBug != zThree) {
			zBug += 1.0;
		}*/
	}
	glutTimerFunc(animationPeriod, animate, 1);
	glutPostRedisplay();
}

// Initialization routine.
void setup(void)
{
	glClearColor(0.22, 0.69, 0.87, 0.0);
	glEnable(GL_DEPTH_TEST); // Enable depth testing.

	// Turn on OpenGL lighting.
	glEnable(GL_LIGHTING);

	// Light property vectors.
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float lightPos[] = { 0.0, 1.0, 0.0, 0.0 }; // Overhead directional light source (e.g., sun).
	float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };

	// Light properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0); // Enable particular light source.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

	// Material property vectors.
	//float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	//float matShine[] = { 50.0 };

	// Material properties.
	//glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	//glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

	// Enable color material mode.
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Cull back faces.
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	// Create the new quadric object.
	qobj = gluNewQuadric();
}

void drawGrass() {
	for (float z = 100.0; z > -100.0; z -= 5.0)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (float x = -100.0; x < 100.0; x += 5.0)
		{
			glColor3f(0.0, 1.0, 0.498039);
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(x, 0.0, z - 5.0);
			glVertex3f(x, 0.0, z);
		}
		glEnd();
	}
}

// The mouse callback routine.
void mouseControl(int button, int state, int x, int y)
{
	y = height - y; // Correct from mouse to OpenGL co-ordinates.
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		cout << x << endl;
		cout << y << endl;
	}
	glutPostRedisplay();
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if (view == NORTH)
		gluLookAt(0.0, 8.0, 40.0, 0.0, 10.0, 0.0, 0.0, 1.0, 0.0);
	if (view == EAST)
		gluLookAt(-40.0, 8.0, 0.0, 0.0, 10.0, 0.0, 0.0, 1.0, 0.0);
	if (view == SOUTH)
		gluLookAt(0.0, 8.0, -40.0, 0.0, 10.0, 0.0, 0.0, 1.0, 0.0);
	if (view == WEST)
		gluLookAt(40.0, 8.0, 0.0, 0.0, 10.0, 0.0, 0.0, 1.0, 0.0);
	if (view == OVER)
		gluLookAt(0.0, 60.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
		//glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
		//glOrtho(0.0, 10.0, 0.0, 40.0, 10.0, 10.0); //this looks up at bug

	drawGrass();

	glDisable(GL_LIGHTING); // Turn off lighting as shadows are not lit.
	


	glDisable(GL_DEPTH_TEST); // Turn off depth testing so that shadows are drawn over the
							  // floor without comparing distance from the viewer.

							  // Draw shadows of the real ball and torus by projecting them onto the xz-plane using
							  // a degenerate scaling transformation that collapses y-values.
	

	glPushMatrix();
	glScalef(1.0, 0.0, 1.0);
	drawBug(1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.0, 0.0, 1.0);
	drawWings(1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.0, 0.0, 1.0);
	drawProboscis(1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.0, 0.0, 1.0);
	drawTree(1);
	glPopMatrix();

	//Flower One Shadow
	glPushMatrix();
	glScalef(1.0, 0.0, 1.0);
	drawFlowerOne(1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.0, 0.0, 1.0);
	drawFlowerTwo(1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.0, 0.0, 1.0);
	drawFlowerThree(1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.0, 0.0, 1.0);
	drawFlowerFour(1);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.0, 0.0, 1.0);
	drawBalloon(1);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST); // Restore depth testing.
	glEnable(GL_LIGHTING); // Restore lighting.


	drawBug(0);
	drawWings(0);
	drawProboscis(0);
	drawTree(0);
	drawFlowerOne(0);
	drawFlowerTwo(0);
	drawFlowerThree(0);
	drawFlowerFour(0);
	drawBalloon(0);

	glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'r': //reset
		isAnimate = 0;
		xTrans = -10.0;
		yTransBody = 11.0;
		yTransProb = 2.0;
		zBug = -20.0;
		view = NORTH;
		glutPostRedisplay();
		break;
	case 's': //stop bug
		isAnimate = 0;
		yTransBody = 11.0;
		yTransProb = 2.0;
		glutPostRedisplay();
		break;
	case 'f': // flight of bug
		if (!isAnimate) isAnimate = 1;
		glutPostRedisplay();
		break;
	case 'w': // flap wings
		if (isAnimate)
		{
			isAnimate = 0;
			glutIdleFunc(NULL);
		}
		else
		{
			isAnimate = 1;
			glutIdleFunc(increaseAngle);
		}
		break;
	case '1':
		view = NORTH;
		isOrtho = 0;
		glutPostRedisplay();
		break;
	case '2':
		view = EAST;
		isOrtho = 0;
		glutPostRedisplay();
		break;
	case '3':
		view = SOUTH;
		isOrtho = 0;
		glutPostRedisplay();
		break;
	case '4':
		view = WEST;
		isOrtho = 0;
		glutPostRedisplay();
		break;
	case '0':
		view = OVER;
		isOrtho = 1;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_DOWN) animationPeriod += 5;
	if (key == GLUT_KEY_UP) if (animationPeriod > 5) animationPeriod -= 5;
	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	cout << "Interactions:" << endl;
	cout << "" << endl;
	cout << "Press f to let the bug do its thing." << endl;
	cout << "Press w to let the bug flap its wings." << endl;
	cout << "Press s to tell the bug to chill out." << endl;
	cout << "Press r to reset all settings." << endl;
	cout << "Press 1 to set the view to the north view." << endl;
	cout << "Press 2 to set the view to the east view." << endl;
	cout << "Press 3 to set the view to the south view." << endl;
	cout << "Press 4 to set the view to the west view." << endl;
	cout << "Press 0 to set the view to the overhead view." << endl;
	cout << "Press the Escape key to exit" << endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("A Bug Flies Over a Garden");
	setup();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);
	glutTimerFunc(5, animate, 1);
	glutMainLoop();

	return 0;
}
