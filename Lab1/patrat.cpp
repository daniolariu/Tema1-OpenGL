#include "glos.h"
#include "gl.h"
#include "glaux.h"

static GLfloat x = 0;
static GLfloat y = 0;
static GLfloat z = -5.0;
static GLfloat originX = 0;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void CALLBACK MutaSus()
{
    y = y + 1;
}

void CALLBACK MutaJos()
{
    y = y - 1;
}

void CALLBACK MutaStanga()
{
    x = x - 1;
}

void CALLBACK MutaDreapta()
{
    x = x + 1;
}

void CALLBACK MutaInainte()
{
    z = z - 1;
}

void CALLBACK MutaInapoi()
{
    z = z + 1;
}

void drawOrigin() {
    glPointSize(5.0);
    glColor3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_POINTS);
    glVertex3f(originX, 0.0f, 0.0f);
    glEnd();
}

void updateOriginX(GLsizei w, GLsizei h) {
    originX = 0;
}

void CALLBACK display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity();                                 
    glTranslatef(x, y, z);                          

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);

    glBegin(GL_LINE_LOOP);
    {
        glColor3f(0.5f, 0.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
    }
    glEnd();

    glBegin(GL_LINES);
    {
        glColor3f(0.0f, 0.7f, 1.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);

        glColor3f(1.0f, 1.0f, 0.5f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
    }
    glEnd();

    glDisable(GL_LINE_STIPPLE);

    glBegin(GL_LINE_LOOP);
    {
        glColor3f(1.0f, 0.0f, 0.3f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);


        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
    }
    glEnd();

    drawOrigin();

    glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) {
        return;
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        glFrustum(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w, 2.0, 10.0);
    }
    else {
        glFrustum(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, 2.0, 10.0);
    }
    glMatrixMode(GL_MODELVIEW);

    updateOriginX(w, h);
}

int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH);
    auxInitPosition(0, 0, 800, 600);
    auxInitWindow("Piramida 3D");
    myInit();
    auxKeyFunc(AUX_LEFT, MutaStanga);
    auxKeyFunc(AUX_RIGHT, MutaDreapta);
    auxKeyFunc(AUX_UP, MutaSus);
    auxKeyFunc(AUX_DOWN, MutaJos);
    auxKeyFunc(AUX_W, MutaInainte);
    auxKeyFunc(AUX_S, MutaInapoi);

    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return(0);
}
