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

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

float x = 5;
float y = 5;
struct hair{
    float x1;
    float y1;
    float x2;
    float y2;
};

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
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

    //First Box
	//glRotatef(-_angle, 1.0f, 1.0f, 0.0f);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    //vertex 1/2 for one line
    glColor3f( 1.0f, 1.0f, 1.0f);
    glVertex2f(-0.5f, -0.3f);
    //vertex 2/2 for one line
    glVertex2f(0.5f, 0.3f);

    glEnd();

/*
	glBegin(GL_TRIANGLES);

	//Tri1
	glColor3f(1.0f, 0.0f, 0.0f);
	//glNormal3f(0.0, 1.0f, 0.0f);
	glVertex3f(0.0f, 2*BOX_SIZE, 0.0f);
	glVertex3f(-BOX_SIZE, 0.0f, BOX_SIZE);
	glVertex3f(BOX_SIZE, 0.0f, BOX_SIZE);

    glColor3f(0.0f, 1.0f, 0.0f);
	//glNormal3f(0.0, 1.0f, 0.0f);
	glVertex3f(0.0f, 2*BOX_SIZE, 0.0f);
	glVertex3f(BOX_SIZE, 0.0f, -BOX_SIZE);
	glVertex3f(BOX_SIZE, 0.0f, BOX_SIZE);

	glColor3f(0.0f, 0.0f, 1.0f);
	//glNormal3f(0.0, 1.0f, 0.0f);
	glVertex3f(0.0f, 2*BOX_SIZE, 0.0f);
	glVertex3f(BOX_SIZE, 0.0f, -BOX_SIZE);
	glVertex3f(-BOX_SIZE, 0.0f, -BOX_SIZE);

	glColor3f(1.0f, 1.0f, 0.0f);
	//glNormal3f(0.0, 1.0f, 0.0f);
	glVertex3f(0.0f, 2*BOX_SIZE, 0.0f);
	glVertex3f(-BOX_SIZE, 0.0f, +BOX_SIZE);
	glVertex3f(-BOX_SIZE, 0.0f, -BOX_SIZE);

	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	//Down face
	//glNormal3f(0.0, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-BOX_SIZE, 0.0f, -BOX_SIZE);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(BOX_SIZE, 0.0f, -BOX_SIZE);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(BOX_SIZE, 0.0f, BOX_SIZE);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-BOX_SIZE, 0.0f, BOX_SIZE);

	glEnd();
*/
	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();
}

//Called every 25 milliseconds
void update(int value) {
	/*_angle += 0.8f;
	if (_angle > 360) {
		_angle -= 360;
	}
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);*/
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	glutCreateWindow("Putting It All Together - videotutorialsrock.com");
	initRendering();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	glutMainLoop();
	return 0;
}
