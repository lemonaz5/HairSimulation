/*
Hair Simulation
This code is edited by Vorawee and Wannita
For presenting in Realtime CG Physics Sim 2017
With AJ. Nuttapong Chentanez
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
float mass = 0.2;
float gravity = -10;
float k = 100; //Spring constant
float damping = 10; //Damping constant
float timeStep = 0.01;
int segment = 20;
float segmentLen = 0.1;
float headRadius = 0.25;


class HairSegment{
    public:
        float x;
        float y;
        float velocityX;
        float velocityY;
        HairSegment (float x1, float y1,float vX,float vY){
            x = x1; y = y1; velocityX = vX; velocityY = vY;
        }
};

class Hair{
    public:
        float x; //Anchor
        float y; //Anchor
        float r;
        float g;
        float b;
        vector<HairSegment> seg;
        vector<pair<float,float>> particles;
        Hair (){
            float maxX = anchorX + headRadius;
            float minX = anchorX - headRadius;
            x = (minX) + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxX-minX)));
            float maxY = anchorY + sqrt(headRadius*headRadius - (x*x));
            float minY = anchorY - sqrt(headRadius*headRadius - (x*x));
            y = maxY + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxY-minY)));

            particles.push_back(make_pair(x,y));

            /*
            r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
*/
            r = 1.0f;
            g = 0.0f;
            b = 0.0f;

            createSeg(segment,segmentLen);
        }
        Hair (float x1, float y1,float r1,float g1,float b1){
            x = x1; y = y1; r = r1; g = g1; b = b1;
            particles.push_back(make_pair(x1,y1));
        }
        void set_val (float x1, float y1,float r1,float g1,float b1){
            x = x1; y = y1; r = r1; g = g1; b = b1;
        }
        void createSeg(int s, float len){
            for(int i = 0;i<s;i++){
                HairSegment h (x+0.5, particles[i].second-len, 0.0f, 0.0f);
                seg.push_back(h);
                particles.push_back(make_pair(x,particles[i].second-len));
            }

        }
};

vector<Hair> hairs;


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
                if((anchorY<7.9) && (anchorY>-7.9)){
                    hairs[i].y += (g_yClick-y)*0.0005;
                    hairs[i].particles[0].second += (g_yClick-y)*0.0005;
                }
 /*               else hairs[i].y1 = hairs[i].y1;*/
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
                if((anchorX<8) && (anchorX>-8)){
                    hairs[i].x += (x-g_xClick)*0.0005;
                    hairs[i].particles[0].first += (x-g_xClick)*0.0005;
                }
 /*               else{
                    hairs[i].x1 = hairs[i].x1;
                }*/
            }
        }
        //cout << "X" << x << "Y" << y << endl;
   /*     cout << "xcli" << g_xClick-x << "  ycli" << g_yClick-y<< endl;
        cout << "hair x " << hairs[0].x1 << " y " << hairs[0].y1 << endl;*/
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
    for(unsigned i = 0;i < hairs.size(); i++){
        for(int j = 0; j < hairs[i].particles.size()-1; j++){ //Loop every particles - last particle
            glLineWidth(1.0);
            glBegin(GL_LINES);
            glColor3f(hairs[i].r,hairs[i].g,hairs[i].b);
            glVertex2f(hairs[i].particles[j].first, hairs[i].particles[j].second);
            glVertex2f(hairs[i].particles[j+1].first, hairs[i].particles[j+1].second);
            glEnd();
        }
    }


    //Sphere Anchor
    glPushMatrix();
    glTranslatef(anchorX,anchorY,0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutSolidSphere(headRadius+0.45, 15, 15);
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
        vector<float> springForceY, springForceX; //of each segments in a hair
        vector<float> dampingForceY, dampingForceX;

        //First segment
        float springForceY0 = -k*(hairs[i].seg[0].y - hairs[i].y);
        float springForceX0 = -k*(hairs[i].seg[0].x - hairs[i].x);

        float dampingForceY0 = damping * hairs[i].seg[0].velocityY;
        float dampingForceX0 = damping * hairs[i].seg[0].velocityX;

        springForceY.push_back(springForceY0);
        springForceX.push_back(springForceX0);
        dampingForceY.push_back(dampingForceY0);
        dampingForceX.push_back(dampingForceX0);

        for(int j=1; j<hairs[i].seg.size() ;j++){
            float springForceY1 = -k*(hairs[i].seg[j].y - hairs[i].seg[j-1].y);
            float springForceX1 = -k*(hairs[i].seg[j].x - hairs[i].seg[j-1].x);

            float dampingForceY1 = damping * hairs[i].seg[j].velocityY;
            float dampingForceX1 = damping * hairs[i].seg[j].velocityX;

            springForceY.push_back(springForceY1);
            springForceX.push_back(springForceX1);
            dampingForceY.push_back(dampingForceY1);
            dampingForceX.push_back(dampingForceX1);
        }

        //Net force
        for(int j=0; j<hairs[i].seg.size() ;j++){
            float prevX = hairs[i].particles[j].first;
            float prevY = hairs[i].particles[j].second;

            float thisX = hairs[i].particles[j+1].first;
            float thisY = hairs[i].particles[j+1].second;

            float len = sqrt((prevX - thisX)*(prevX - thisX) + (prevY - thisY)*(prevY - thisY));
/*
            if(len > segmentLen){
                float cosine = /len;

            }*/
            float forceY1 = springForceY[j] + mass * gravity  - dampingForceY[j];
            float forceX1 = springForceX[j] - dampingForceX[j];

            //Every segment but the last one
            if(j<hairs[i].seg.size()-1){
                forceY1 += -springForceY[j+1] + dampingForceY[j+1];
                forceX1 += -springForceX[j+1] + dampingForceX[j+1];
            }

            float accelerationY = forceY1/mass;
            float accelerationX = forceX1/mass;

            float velocityY = hairs[i].seg[j].velocityY + accelerationY*timeStep;
            float velocityX = hairs[i].seg[j].velocityX + accelerationX*timeStep;

            float posY = hairs[i].seg[j].y + velocityY * timeStep;
            float posX = hairs[i].seg[j].x + velocityX * timeStep;

            //update in hair
            hairs[i].seg[j].velocityY = velocityY;
            hairs[i].seg[j].velocityX = velocityX;

            hairs[i].seg[j].y = posY;
            hairs[i].seg[j].x = posX;

            hairs[i].particles[j+1].first = posX;
            hairs[i].particles[j+1].second = posY;


        }
/*
        cout<<"springForceY = "<<springForceY;
        cout<<"forceY = "<<forceY;
        cout<<"accelerationY = "<<accelerationY;
        cout<<"hair1.velocityY = "<<hairs[i].velocityY;
        cout<<"y2 = "<<hairs[i].y2;
        cout<<"DDD"<<hairs[i].y2;
        cout<<"\n";*/
    }

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
    for(int i = 0; i< 3 + rand()%7 ; i++){
        Hair h = Hair();
        hairs.push_back(h);
    }
/*    Hair h = Hair();
    hairs.push_back(h);*/

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
