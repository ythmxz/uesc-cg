#define DISPLAY_WIDTH 1920
#define DISPLAY_HEIGHT 1080

#define WINDOW_WIDTH 540
#define WINDOW_HEIGHT 540

#include <GL/glut.h>
#include <stdio.h>

void drawThigh(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_POLYGON);
    {
        glVertex2f(x + 2.0, y + 0.0);
        glVertex2f(x + 1.0, y + 3.0);
        glVertex2f(x + 0.5, y + 8.0);
        glVertex2f(x + 0.0, y + 12.0);
        glVertex2f(x + 1.0, y + 18.0);
        glVertex2f(x + 2.0, y + 20.0);
        glVertex2f(x + 8.0, y + 20.0);
        glVertex2f(x + 10.0, y + 16.0);
        glVertex2f(x + 10.0, y + 12.0);
        glVertex2f(x + 10.0, y + 8.0);
        glVertex2f(x + 9.0, y + 4.0);
        glVertex2f(x + 7.0, y + 0.5);
    }
    glEnd();
}

void drawKnee(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_POLYGON);
    {
        glVertex2f(x + 0.0, y + 4.0);
        glVertex2f(x + 0.0, y + 6.0);
        glVertex2f(x + 4.0, y + 7.0);
        glVertex2f(x + 7.2, y + 10.0);
        glVertex2f(x + 8.0, y + 9.5);
        glVertex2f(x + 8.5, y + 8.8);
        glVertex2f(x + 9.0, y + 8.0);
        glVertex2f(x + 9.5, y + 7.0);
        glVertex2f(x + 10.0, y + 6.0);
        glVertex2f(x + 10.0, y + 4.0);
        glVertex2f(x + 9.5, y + 3.0);
        glVertex2f(x + 9.0, y + 2.0);
        glVertex2f(x + 8.5, y + 1.2);
        glVertex2f(x + 8.0, y + 0.5);
        glVertex2f(x + 7.2, y + 0.0);
        glVertex2f(x + 4.0, y + 3.0);
    }
    glEnd();
}

void drawCalf(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_POLYGON);
    {
        glVertex2f(x + 1.5, y + 0.0);
        glVertex2f(x + 0.5, y + 2.0);
        glVertex2f(x + 0.0, y + 6.0);
        glVertex2f(x + 0.3, y + 12.0);
        glVertex2f(x + 0.0, y + 18.0);
        glVertex2f(x + 0.5, y + 20.0);
        glVertex2f(x + 6.0, y + 20.0);
        glVertex2f(x + 6.5, y + 17.0);
        glVertex2f(x + 6.5, y + 12.0);
        glVertex2f(x + 6.3, y + 8.0);
        glVertex2f(x + 6.0, y + 4.0);
        glVertex2f(x + 5.5, y + 0.0);
    }
    glEnd();
}

void drawFoot(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_POLYGON);
    {
        glVertex2f(x + 0.2, y + 0.2);
        glVertex2f(x + 0.2, y + 4.0);
        glVertex2f(x + 0.5, y + 8.0);
        glVertex2f(x + 0.5, y + 12.0);
        glVertex2f(x + 0.0, y + 12.5);
        glVertex2f(x + 0.0, y + 14.0);
        glVertex2f(x + 7.0, y + 14.0);
        glVertex2f(x + 7.0, y + 12.5);
        glVertex2f(x + 6.5, y + 12.0);
        glVertex2f(x + 6.5, y + 8.0);
        glVertex2f(x + 6.7, y + 4.0);
        glVertex2f(x + 8.5, y + 4.0);
        glVertex2f(x + 11.0, y + 3.5);
        glVertex2f(x + 12.5, y + 2.0);
        glVertex2f(x + 12.2, y + 0.2);
        glVertex2f(x + 8.5, y + 0.0);
        glVertex2f(x + 4.5, y + 0.0);
    }
    glEnd();
}

void drawLegs(GLfloat x, GLfloat y, GLfloat offset) {
    // Perna Esquerda
    glPushMatrix();
    {
        glTranslatef(x + offset, y, 0.0);

        // Coxa
        glRotatef(20.0, 0.0, 0.0, 1.0);
        drawThigh(6.0, 20.0, 60, 40, 80);
        glRotatef(0.0, 0.0, 0.0, 1.0);

        // Panturrilha
        glRotatef(-20.0, 0.0, 0.0, 1.0);
        drawCalf(0.5, 0.0, 60, 40, 80);
        glRotatef(0.0, 0.0, 0.0, 1.0);

        // Joelho
        glRotatef(10.0, 0.0, 0.0, 1.0);
        drawKnee(3.5, 15.5, 40, 40, 40);
        glRotatef(0.0, 0.0, 0.0, 1.0);

        // Pé
        glRotatef(-12.5, 0.0, 0.0, 1.0);
        drawFoot(0.0, 0.0, 40, 40, 40);
        glRotatef(0.0, 0.0, 0.0, 1.0);
    }
    glPopMatrix();

    // Perna Direita
    glPushMatrix();
    {
        glTranslatef(x, y, 0.0);

        // Coxa
        glRotatef(10.0, 0.0, 0.0, 1.0);
        drawThigh(2.5, 20.0, 100, 80, 135);
        glRotatef(0.0, 0.0, 0.0, 1.0);

        // Panturrilha
        glRotatef(-10.0, 0.0, 0.0, 1.0);
        drawCalf(0.5, 0.0, 100, 80, 135);
        glRotatef(0.0, 0.0, 0.0, 1.0);

        // Joelho
        glRotatef(3.0, 0.0, 0.0, 1.0);
        drawKnee(1.2, 16.0, 60, 60, 60);
        glRotatef(0.0, 0.0, 0.0, 1.0);

        // Pé
        glRotatef(-5.0, 0.0, 0.0, 1.0);
        drawFoot(0.0, -0.0, 60, 60, 60);
        glRotatef(0.0, 0.0, 0.0, 1.0);
    }
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawLegs(60.0, 40.0, 12.0);
    glFlush();
}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition((DISPLAY_WIDTH - WINDOW_WIDTH) / 2, (DISPLAY_HEIGHT - WINDOW_HEIGHT) / 2);
    glutCreateWindow("Spoiler");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0.00, (double)WINDOW_WIDTH / 4.0, 0.00, (double)WINDOW_HEIGHT / 4.0);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
