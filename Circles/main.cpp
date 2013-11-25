#include <iostream>
#include <vector>
#include <cmath>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include "entities.h"
#include "glshapes.h"

using namespace std;

/*** Constants ***/
#define WIDTH 400
#define HEIGHT 400

/**** Clases ***/
//Clase circulo
class circle: public solidObject {
public:
    circle(float pos[2], float radius) : m_radius(radius) {
        m_pos[0] = pos[0];
        m_pos[1] = pos[1];
    }

    void draw() {
        float x, y;

        //Color of circle, rgb normalized from 0 to 1.0
        glColor3f(1.0,1.0,1.0);

        //Draw a vertex every grad
        glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i++) {
            x = m_pos[0] + m_radius*cos(i*M_PI/180.0);
            y = m_pos[1] + m_radius*sin(i*M_PI/180.0);

            //Normalize from -1.0 to 1.0
            x = (x/(WIDTH/2.0)) - 1.0;
            y = -(y/(HEIGHT/2.0)) + 1.0;
            glVertex2f(x,y);
        }
        glEnd();
    }

    float getRad() {return m_radius;}


private:
    float m_radius;
};

vector<circle*> Obj;

/*** Global Variables ***/
int obj_state = -1;
int prevX, prevY;
int currX, currY;
float dist;

/*** Functions ***/
void init(void);
void idle(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void ExitAndClean(void);

/*** Main function ***/
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("Circles");


    init();

    glutDisplayFunc(display);
    //glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();

    return 0;
}

void init() {
     float pos[2];
     float rad;

    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    pos[0] = 200.0;
    pos[1] = 200.0;
    rad = 10.0;
    Obj.push_back(new circle(pos,rad));

    pos[0] = 100.0;
    pos[1] = 200.0;
    rad = 5.0;
    Obj.push_back(new circle(pos,rad));

    pos[0] = 200.0;
    pos[1] = 100.0;
    rad = 8.0;
    Obj.push_back(new circle(pos,rad));

    pos[0] = 100.0;
    pos[1] = 100.0;
    rad = 2.0;
    Obj.push_back(new circle(pos,rad));
}

void idle() {

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    for(int i = 0; i < Obj.size(); i++)
        Obj.at(i)->draw();

    glutSwapBuffers();
    glFlush();

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
    case 27:
        ExitAndClean();
        break;
    }
}

void mouse(int button, int state, int x, int y) {
    //Arreglar segundo grab
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        for(int i = 0; i < Obj.size(); i++) {
            currX = Obj.at(i)->getPosX();
            currY = Obj.at(i)->getPosY();
            dist = (currX - x)*(currX - x) + (currY - y)*(currY - y);
            dist = sqrt(dist);

            if(dist < Obj.at(i)->getRad()) {
                obj_state = i;

                prevX = x;
                prevY = y;

                break;
            }
        }
    }
    else
        obj_state = -1;
}

void motion(int x, int y) {

    if(obj_state >= 0) {
        currX = Obj.at(obj_state)->getPosX();
        currY = Obj.at(obj_state)->getPosY();

        Obj.at(obj_state)->setPosX(currX+(x-prevX));
        Obj.at(obj_state)->setPosY(currY+(y-prevY));

       prevX = x;
       prevY = y;
    }
}

void ExitAndClean() {
    for(int i = 0; i < Obj.size(); i++)
        delete Obj.at(i);

    exit(0);
}
