/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* File for "Putting It All Together" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */



#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <vector>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

float x = 5;
float y = 5;
float anchorX = 0;
float anchorY = 0;
float mass = 5;
float gravity = -10;
float k = 30; //Spring constant
float damping = 10; //Damping constant
float timeStep = 0.07;


struct hair{
    float x1;
    float y1;
    float x2;
    float y2;
    float velocityX;
    float velocityY;
    float r;
    float g;
    float b;
};

struct hair hair1 = {.x1=0,.y1=0,.x2=10,.y2=5,.velocityX = 0 ,.velocityY=0,.r = 1.0f,.g = 0.0f,.b = 0.0f};
struct hair hair2 = {.x1=0.25,.y1=0,.x2=-5,.y2=16,.velocityX = 0 ,.velocityY=0,.r = 0.0f,.g = 1.0f,.b = 0.0f};
struct hair hair3 = {.x1=-0.1,.y1=0.25,.x2=-5,.y2=15,.velocityX = 0 ,.velocityY=0,.r = 0.0f,.g = 0.0f,.b = 1.0f};
struct hair hair4 = {.x1=0.1,.y1=0.5,.x2=-1,.y2=1,.velocityX = 0 ,.velocityY=0,.r = 0.0f,.g = 0.0f,.b = 1.0f};
struct hair hair5 = {.x1=0.24,.y1=0.35,.x2=10,.y2=10,.velocityX = 0 ,.velocityY=0,.r = 0.0f,.g = 0.0f,.b = .0f};
struct hair hair6 = {.x1=0.,.y1=0.25,.x2=15,.y2=17,.velocityX = 0 ,.velocityY=0,.r = 0.0f,.g = 0.0f,.b = .0f};
struct hair hair7 = {.x1=0.1,.y1=0.15,.x2=5,.y2=9,.velocityX = 0 ,.velocityY=0,.r = 0.0f,.g = 0.0f,.b = .0f};
struct hair hair8 = {.x1=0.15,.y1=0.5,.x2=1,.y2=12,.velocityX = 0 ,.velocityY=0,.r = 0.0f,.g = 0.0f,.b = .0f};
vector<struct hair> hairs;

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}

static BOOL g_bButton1Down = FALSE;
static int g_yClick = 0;
static int g_xClick = 0;
void MouseButton(int button, int state, int x, int y)
{
	// Respond to mouse button presses.
	// If button1 pressed, mark this state so we know in motion function.

	if (button == GLUT_LEFT_BUTTON)
	{
		g_bButton1Down = (state == GLUT_DOWN) ? TRUE : FALSE;
		g_yClick = y;
		g_xClick = x;
	}
}

void MouseMotion(int x, int y)
{
	// If button1 pressed, zoom in/out if mouse is moved up/down.

	if (g_bButton1Down)
	{
	    if (anchorY>7.8 && g_yClick-y>0) {
            anchorY=7.8;
            /*for (int i = 0; i<hairs.size();i++){
                hairs[i].y1 = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))+7.5;
            }*/
        }else if(anchorY<-7.8 && g_yClick-y<0){
            anchorY=-7.8;
            /*for (int i = 0; i<hairs.size();i++){
                //hairs[i].y1 = hairs[i].y1;
                hairs[i].y1 = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))-8.5;
            }*/
        }else{
            anchorY += (g_yClick - y)*0.0005 ;
            for (int i = 0; i<hairs.size();i++){
                if((anchorY<7.9) && (anchorY>-7.9)) hairs[i].y1 += (g_yClick - y)*0.0005;
                else hairs[i].y1 = hairs[i].y1;
            }
        }

        if (anchorX>7.8 && x-g_xClick>0){
            anchorX=7.8;
            /*for (int i = 0; i<hairs.size();i++){
                hairs[i].x1 = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))+7.5;
            }*/
        }else if (anchorX<-7.8 && x-g_xClick<0){
            anchorX=-7.8;
            /*for (int i = 0; i<hairs.size();i++){
                hairs[i].x1 = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))-8.5;
            }*/
        }else{
            anchorX += (x-g_xClick)*0.0005 ;
            for (int i = 0; i<hairs.size();i++){
                if((anchorX<8) && (anchorX>-8)) hairs[i].x1 += (x-g_xClick)*0.0005;
                else hairs[i].x1 = hairs[i].x1;
            }
        }
        //cout << "X" << x << "Y" << y << endl;
        cout << "xcli" << g_xClick-x << "  ycli" << g_yClick-y<< endl;
        cout << "hair x " << hairs[0].x1 << " y " << hairs[0].y1 << endl;

		glutPostRedisplay();
	}
}
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);*/
	glEnable(GL_COLOR_MATERIAL);
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -20.0f);

	GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat lightPos[] = {x, y, 4 , 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    //First Hair
    for(int i = 0;i<hairs.size(); i++){
        glLineWidth(1.0);
        glBegin(GL_LINES);
        glColor3f(hairs[i].r,hairs[i].g,hairs[i].b);
        glVertex2f(hairs[i].x1, hairs[i].y1);
        glVertex2f(hairs[i].x2, hairs[i].y2);
        glEnd();
    }

    //Sphere Anchor
    glPushMatrix();
    glTranslatef(anchorX,anchorY,0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutSolidSphere(0.7, 15, 15);
    glPopMatrix();

    //Background
    glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-400,400);
	glVertex2f(-400,-400);
	glVertex2f(400,-400);
	glVertex2f(400,400);
	glEnd();

	glutSwapBuffers();
}

void update(int value) {
    //hairs.push_back(hair1);
    for(int i=0;i<hairs.size();i++){
        float springForceY = -k*(hairs[i].y2 - hairs[i].y1);
        float springForceX = -k*(hairs[i].x2 - hairs[i].x1);

        float dampingForceY = damping * hairs[i].velocityY;
        float dampingForceX = damping * hairs[i].velocityX;

        float forceY = springForceY + mass * gravity  - dampingForceY;
        float forceX = springForceX - dampingForceX;

        float accelerationY = forceY/mass;
        float accelerationX = forceX/mass;

        hairs[i].velocityY += accelerationY*timeStep;
        hairs[i].velocityX += accelerationX*timeStep;

        hairs[i].x2 += hairs[i].velocityX*timeStep;
        hairs[i].y2 += hairs[i].velocityY*timeStep;

        /*cout<<"springForceY = "<<springForceY;
        cout<<"forceY = "<<forceY;
        cout<<"accelerationY = "<<accelerationY;
        cout<<"hair1.velocityY = "<<hairs[i].velocityY;
        cout<<"y2 = "<<hairs[i].y2;
        cout<<"DDD"<<hairs[i].y2;
        cout<<"\n";
        */
    }

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
    hairs.push_back(hair1);
    hairs.push_back(hair2);
    hairs.push_back(hair3);
    hairs.push_back(hair4);
    hairs.push_back(hair5);
    hairs.push_back(hair6);
    hairs.push_back(hair7);
    hairs.push_back(hair8);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);

	glutCreateWindow("Vorawee");
	initRendering();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
    glutMouseFunc (MouseButton);
	glutMotionFunc (MouseMotion);
	glutTimerFunc(25, update, 0);
	glutMainLoop();
	return 0;
}
