#include "glos.h"
#include "gl.h"
#include "glu.h"
#include "glaux.h"
#include "math.h"
#include "glut.h"

float rotationAngleX = 0.0f;
float rotationAngleY = 0.0f;

GLfloat translateX = 0.0f;
GLfloat translateY = 0.0f;
GLfloat translateZ = 0.0f;
GLfloat rotateAngle = 0.0f;

GLfloat vertices[][3] = {
    {0, 1, 0},
    {1, -1, 1},
    {-1, -1, 1},
    {-1, -1, -1},
    {1, -1, -1}
};

GLint edges[][2] = {
    {0, 1},
    {0, 2},
    {0, 3},
    {0, 4},
    {1, 2},
    {2, 3},
    {3, 4},
    {4, 1},
};

void draw_pyramid() {
    glTranslatef(translateX, translateY, translateZ);

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for (int i = 0; i < 2; ++i) {
        glVertex3fv(vertices[edges[i][0]]);
        glVertex3fv(vertices[edges[i][1]]);
    }
    glVertex3fv(vertices[edges[4][0]]);
    glVertex3fv(vertices[edges[4][1]]);

    glEnd();

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xF0F0);
    glBegin(GL_LINES);
    for (int i = 2; i < 4; ++i) {
        glVertex3fv(vertices[edges[i][0]]);
        glVertex3fv(vertices[edges[i][1]]);
    }
    for (int i = 5; i < 8; ++i) {
        glVertex3fv(vertices[edges[i][0]]);
        glVertex3fv(vertices[edges[i][1]]);
    }
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -4.0f);
    glRotatef(rotationAngleX, 0.0f, 1.0f, 0.0f);
    glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);
    draw_pyramid();
    glutSwapBuffers();

}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (double)w / (double)h, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//mutare
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        translateY += 0.1f;
        break;
    case 's':
        translateY -= 0.1f;
        break;
    case 'a':
        translateX -= 0.1f;
        break;
    case 'd':
        translateX += 0.1f;
        break;
    case 'q':
        translateZ += 0.1f;
        break;
    case 'e':
        translateZ -= 0.1f;
        break;



    case 't':
        rotationAngleX += 5.0f;
        break;
    case 'g':
        rotationAngleX -= 5.0f;
        break;
    case 'f':
        rotationAngleY -= 5.0f;
        break;
    case 'h':
        rotationAngleY += 5.0f;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Wireframe Square Pyramid");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutMainLoop();
}