#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define SLICES 16
#define STACKS 16

int screenWidth = 0, screenHeight = 0;
int windowWidth = 0, windowHeight = 0;

GLfloat camRadius = 5.0;
GLfloat camAngleH = 0.0;
GLfloat camAngleV = 0.0;
GLfloat camMoveSpeed = 5.0;

void display(void);
void reshape(GLsizei width, GLsizei height);
void timer(int value);
void keyboard(unsigned char key, GLint x, GLint y);
void special(int key, GLint x, GLint y);

void drawSphere(GLfloat x, GLfloat y, GLfloat z, double radius, GLubyte r, GLubyte g, GLubyte b);
void drawBond(GLint x1, GLint y1, GLint z1, GLint x2, GLint y2, GLint z2, double radius);

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    windowWidth = screenWidth * 0.5;
    windowHeight = screenHeight * 0.5;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowWidth * 0.5, windowHeight * 0.5);
    glutCreateWindow("HCl - Cianeto de Hidrogênio");

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    GLfloat theta = camAngleH * M_PI / 180.0;
    GLfloat phi = camAngleV * M_PI / 180.0;

    GLfloat camX = camRadius * cos(phi) * sin(theta);
    GLfloat camY = camRadius * sin(phi);
    GLfloat camZ = camRadius * cos(phi) * cos(theta);

    GLfloat upY = (cos(phi) >= 0.0) ? 1.0 : -1.0;

    gluLookAt(camX, camY, camZ, 0.0, 0.0, 0.0, 0.0, upY, 0.0);

    drawSphere(1.0, 0.0, 0.0, 0.5, 127, 255, 255);
    drawSphere(0.0, 0.0, 0.0, 0.5, 255, 127, 255);
    drawSphere(0.0, 1.0, 0.0, 0.5, 255, 255, 127);
    // drawBond(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.5);

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {
    windowWidth = width;
    windowHeight = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, GLint x, GLint y) {
    switch (key) {

    case 27:
        exit(0);
        break;

    case '+':
    case '=':
        camRadius = (camRadius < 2.5) ? 2.0 : camRadius - 0.5;
        break;

    case '-':
    case '_':
        camRadius = (camRadius > 19.5) ? 20.0 : camRadius + 0.5;
        break;

    default:
        break;
    }

    glutPostRedisplay();
}

void special(int key, GLint x, GLint y) {
    switch (key) {

    case GLUT_KEY_LEFT:
        camAngleH -= camMoveSpeed;
        break;

    case GLUT_KEY_RIGHT:
        camAngleH += camMoveSpeed;
        break;

    case GLUT_KEY_UP:
        camAngleV += camMoveSpeed;
        break;

    case GLUT_KEY_DOWN:
        camAngleV -= camMoveSpeed;
        break;

    default:
        break;
    }

    glutPostRedisplay();
}

void drawSphere(GLfloat x, GLfloat y, GLfloat z, double radius, GLubyte r, GLubyte g, GLubyte b) {
    glPushMatrix();
    {
        glTranslatef(x, y, z);
        glColor3ub(r, g, b);
        glutSolidSphere(radius, SLICES, STACKS);
    }
    glPopMatrix();
}

void drawBond(GLint x1, GLint y1, GLint z1, GLint x2, GLint y2, GLint z2, double radius) {
    glPushMatrix();
    {
        glTranslatef(x1, y1, z1);
        glColor3ub(255, 255, 255);

        glBegin(GL_POLYGON);
        {
            glVertex3f(0.0, 0.0, 0.0);
            for (int i = 0; i <= 16; i++) {
                GLfloat angle = 2 * M_PI * i / 16;
                glVertex2f((radius * cos(angle)), (radius * sin(angle)));
            }

            glVertex3f(0.0, 0.0, z2);
            for (int i = 0; i <= 16; i++) {
                GLfloat angle = 2 * M_PI * i / 16;
                glVertex2f((radius * cos(angle)), (radius * sin(angle)));
            }
        }
        glEnd();
    }
}
