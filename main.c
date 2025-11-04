#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <math.h>

int displayWidth = 0, displayHeight = 0;
int windowWidth = 0, windowHeight = 0;

void display();
void reshape(GLsizei width, GLsizei height);

// Perna
void drawFoot(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);
void drawCalf(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);
void drawKnee(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);
void drawThigh(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);
void drawLeg(GLfloat x,
             GLfloat y,
             GLfloat angleA,
             GLfloat angleB,
             GLfloat angleC,
             GLubyte r1,
             GLubyte g1,
             GLubyte b1,
             GLubyte r2,
             GLubyte g2,
             GLubyte b2,
             GLubyte colorOffset);

// Peitoral
void drawTorso(GLubyte r, GLubyte g, GLubyte b);
void drawBelt(GLubyte r, GLubyte g, GLubyte b);
void drawStrap(GLubyte r, GLubyte g, GLubyte b);

// Braço
void drawHand(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);
void drawForearm(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);
void drawUpperArm(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);

// Cabeça
void drawHood(GLubyte r, GLubyte g, GLubyte b);
void drawFace(GLubyte r, GLubyte g, GLubyte b);
void drawEye(GLubyte r, GLubyte g, GLubyte b);

// Extra
void drawCape(GLubyte r, GLubyte g, GLubyte b);

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    // Tamanho do monitor
    displayWidth = glutGet(GLUT_SCREEN_WIDTH);
    displayHeight = glutGet(GLUT_SCREEN_HEIGHT);

    // Tamanho da janela
    windowWidth = 500;
    windowHeight = 500;

    // Propriedades da janela
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((displayWidth - windowWidth) / 2, (displayHeight - windowHeight) / 2);
    glutCreateWindow("SPOILER");

    // Cor de fundo
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawLeg(50.0, 200.0, 30.0, -50.0, 0.0, 60, 40, 80, 60, 60, 60, 0);
    glFlush();
}

void reshape(GLsizei width, GLsizei height) {
    if (height == 0) {
        height = 1;
    }

    float desiredAspect = (float)windowWidth / (float)windowHeight;
    float windowAspect = (float)width / (float)height;

    int viewWidth = 0, viewHeight = 0;

    if (windowAspect >= desiredAspect) {
        // Janela muito larga
        viewWidth = (int)(height * desiredAspect + 0.5);
        viewHeight = height;
    } else {
        // Janela muito alta
        viewWidth = width;
        viewHeight = (int)(width / desiredAspect + 0.5);
    }

    // Centraliza o conteúdo
    int viewX = (width - viewWidth) / 2;
    int viewY = (height - viewHeight) / 2;
    glViewport(viewX, viewY, viewWidth, viewHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (double)windowWidth, 0.0, (double)windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawFoot(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset) {
    glColor3ub(r + colorOffset, g + colorOffset, b + colorOffset);

    glBegin(GL_POLYGON);
    {
        glVertex2f(5.00, 60.00);
        glVertex2f(0.00, 70.00);
        glVertex2f(0.00, 80.00);
        glVertex2f(40.00, 80.00);
        glVertex2f(40.00, 70.00);
        glVertex2f(35.00, 60.00);
    }
    glEnd();

    glBegin(GL_POLYGON);
    {
        glVertex2f(5.00, 0.00);
        glVertex2f(5.00, 60.00);
        glVertex2f(35.00, 60.00);
        glVertex2f(35.00, 25.00);
        glVertex2f(60.00, 25.00);
        glVertex2f(70.00, 20.00);
        glVertex2f(80.00, 10.00);
        glVertex2f(80.00, 0.00);
    }
    glEnd();
}

void drawCalf(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset) {
    glColor3ub(r + colorOffset, g + colorOffset, b + colorOffset);

    glBegin(GL_POLYGON);
    {
        glVertex2f(5.00, 0.00);
        glVertex2f(0.00, 35.00);
        glVertex2f(0.00, 55.00);
        glVertex2f(2.00, 70.00);
        glVertex2f(5.00, 80.00);
        glVertex2f(35.00, 80.00);
        glVertex2f(38.00, 70.00);
        glVertex2f(40.00, 55.00);
        glVertex2f(40.00, 35.00);
        glVertex2f(35.00, 0.00);
    }
    glEnd();
}

void drawKnee(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset) {
    glColor3ub(r + colorOffset, g + colorOffset, b + colorOffset);

    glBegin(GL_TRIANGLE_FAN);
    {
        glVertex2f(20.0, 20.0); // Center of the circle
        for (int i = 0; i <= 100; i++) {
            GLfloat angle = 2 * M_PI * i / 100;
            glVertex2f(20.0 + (15.0 * cos(angle)), 20.0 + (15.0 * sin(angle)));
        }
    }
    glEnd();
}

void drawThigh(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset) {
    glColor3ub(r + colorOffset, g + colorOffset, b + colorOffset);

    glBegin(GL_POLYGON);
    {
        glVertex2f(5.00, 0.00);
        glVertex2f(0.00, 35.00);
        glVertex2f(0.00, 55.00);
        glVertex2f(2.00, 70.00);
        glVertex2f(5.00, 80.00);
        glVertex2f(35.00, 80.00);
        glVertex2f(38.00, 70.00);
        glVertex2f(40.00, 55.00);
        glVertex2f(40.00, 35.00);
        glVertex2f(35.00, 0.00);
    }
    glEnd();
}

void drawLeg(GLfloat x,
             GLfloat y,
             GLfloat angleA,
             GLfloat angleB,
             GLfloat angleC,
             GLubyte r1,
             GLubyte g1,
             GLubyte b1,
             GLubyte r2,
             GLubyte g2,
             GLubyte b2,
             GLubyte colorOffset) {
    GLfloat pivotX = 0.0, pivotY = 0.0;

    glPushMatrix();
    {
        pivotX = 20.0, pivotY = 80.0;

        glTranslatef(x + pivotX, y + pivotY, 0.0);
        glRotatef(angleA, 0.0, 0.0, 1.0);
        glTranslatef(-pivotX, -pivotY, 0.0);

        drawThigh(r1, g1, b1, colorOffset);

        glPushMatrix();
        {
            pivotX = 15.0, pivotY = 15.0;

            glTranslatef(pivotX, pivotY - 15.0, 0.0);
            glRotatef(angleB, 0.0, 0.0, 1.0);
            glTranslatef(-pivotX, -pivotY, 0.0);

            drawKnee(r1, g1, b1, colorOffset);

            glPushMatrix();
            {
                pivotX = 20.0, pivotY = 80.0;

                glTranslatef(0.0, -65.0, 0.0);

                drawCalf(r1, g1, b1, colorOffset);

                glPushMatrix();
                {
                    pivotX = 20.0, pivotY = 80.0;

                    glTranslatef(pivotX, pivotY - 80.0, 0.0);
                    glRotatef(angleC, 0.0, 0.0, 1.0);
                    glTranslatef(-pivotX, -pivotY, 0.0);

                    drawFoot(r2, g2, b2, colorOffset);
                }
                glPopMatrix();
            }
            glPopMatrix();
        }
    }
    glPopMatrix();
}
