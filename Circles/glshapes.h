#ifndef GLSHAPES_H
#define GLSHAPES_H
#include <GL/gl.h>
#include <cmath>

void drawCircle(float radius, float center[2], float r, float g, float b) {
    float x;
    float y;

    //Color of circle, rgb normalized from 0 to 1.0
    glColor3f(r,g,b);

    //Draw a vertex every grad
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i++) {
        x = center[0] + radius*cos(i*M_PI/180.0);
        y = center[1] + radius*sin(i*M_PI/180.0);

        glVertex2f(x,y);
    }
    glEnd();
}

#endif // GLSHAPES_H
