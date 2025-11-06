#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <math.h>

int displayWidth = 0, displayHeight = 0;
int windowWidth = 0, windowHeight = 0;

// Ângulos das articulações

GLfloat neck = 0.0;
GLfloat shoulderL = 0.0, elbowL = 0.0, wristL = 0.0;
GLfloat shoulderR = 0.0, elbowR = 0.0, wristR = 0.0;
GLfloat hipL = 0.0, kneeL = 0.0, ankleL = 0.0;
GLfloat hipR = 0.0, kneeR = 0.0, ankleR = 0.0;

// Callbacks

void display(void);
void reshape(GLsizei width, GLsizei height);
void keyboard(unsigned char key, GLint x, GLint y);

// Articulação

void drawJoint(GLfloat x, GLfloat y, GLfloat radius, GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);

// Perna

void drawThigh(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);
void drawCalf(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);
void drawFoot(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);
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
void drawChest(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);

// Braço

void drawUpperArm(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);
void drawForearm(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);
void drawHand(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);
void drawArm(GLfloat x,
             GLfloat y,
             GLfloat angleA,
             GLfloat angleB,
             /*GLfloat angleC,*/
             GLubyte r1,
             GLubyte g1,
             GLubyte b1,
             /*GLubyte r2,
             GLubyte g2,
             GLubyte b2,*/
             GLubyte colorOffset);

// Cabeça

void drawHood(GLubyte r, GLubyte g, GLubyte b);
void drawFace(GLubyte r, GLubyte g, GLubyte b);
void drawEye(GLubyte r, GLubyte g, GLubyte b);
void drawHead(GLfloat x, GLfloat y, GLfloat angle, GLubyte r, GLubyte g, GLubyte b);

// Acessório

void drawCape(GLubyte r, GLubyte g, GLubyte b);

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    displayWidth = glutGet(GLUT_SCREEN_WIDTH);
    displayHeight = glutGet(GLUT_SCREEN_HEIGHT);

    windowWidth = displayHeight / 1.5;
    windowHeight = displayHeight / 1.5;

    // Propriedades da janela
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((displayWidth - windowWidth) / 2, (displayHeight - windowHeight) / 2);
    glutCreateWindow("SPOILER");

    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawLeg(98.0, 200.0, hipL, kneeL, ankleL, 60, 40, 80, 60, 60, 60, -10);
    drawChest(60.0, 260.0, 60, 40, 80);
    drawLeg(52.0, 200.0, hipR, kneeR, ankleR, 60, 40, 80, 60, 60, 60, 10);
    drawArm(60.0, 320.0, shoulderR, elbowR, 0, 40, 80, 0);
    glutSwapBuffers();
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

void keyboard(unsigned char key, GLint x, GLint y) {
    switch (key) {
    // Perna Direita
    case 'w':
        hipR = (hipR <= 75.0) ? hipR += 5.0 : hipR;
        break;

    case 'q':
        hipR = (hipR >= -75.0) ? hipR -= 5.0 : hipR;
        break;

    case 's':
        kneeR = (kneeR <= -5.0) ? kneeR += 5.0 : kneeR;
        break;

    case 'a':
        kneeR = (kneeR >= -130.0) ? kneeR -= 5.0 : kneeR;
        break;

    case 'x':
        ankleR = (ankleR <= 5.0) ? ankleR += 5.0 : ankleR;
        break;

    case 'z':
        ankleR = (ankleR >= -5.0) ? ankleR -= 5.0 : ankleR;
        break;

    // Perna Esquerda
    case 'r':
        hipL = (hipL <= 75.0) ? hipL += 5.0 : hipL;
        break;

    case 'e':
        hipL = (hipL >= -75.0) ? hipL -= 5.0 : hipL;
        break;

    case 'f':
        kneeL = (kneeL <= -5.0) ? kneeL += 5.0 : kneeL;
        break;

    case 'd':
        kneeL = (kneeL >= -130.0) ? kneeL -= 5.0 : kneeL;
        break;

    case 'v':
        ankleL = (ankleL <= 5.0) ? ankleL += 5.0 : ankleL;
        break;

    case 'c':
        ankleL = (ankleL >= -5.0) ? ankleL -= 5.0 : ankleL;
        break;

    // Braço Direito
    case 'y':
        shoulderR = (shoulderR <= 175.0) ? shoulderR += 5.0 : shoulderR;
        break;

    case 't':
        shoulderR = (shoulderR >= -55.0) ? shoulderR -= 5.0 : shoulderR;
        break;

    case 'h':
        elbowR = (elbowR <= 145.0) ? elbowR += 5.0 : elbowR;
        break;

    case 'g':
        elbowR = (elbowR >= 5.0) ? elbowR -= 5.0 : elbowR;
        break;
    }

    glutPostRedisplay();
}

void drawJoint(GLfloat x, GLfloat y, GLfloat radius, GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset) {
    glColor3ub(r + colorOffset, g + colorOffset, b + colorOffset);

    glBegin(GL_TRIANGLE_FAN);
    {
        glVertex2f(x, y);
        for (int i = 0; i <= 16; i++) {
            GLfloat angle = 2 * M_PI * i / 16;
            glVertex2f(x + (radius * cos(angle)), y + (radius * sin(angle)));
        }
    }
    glEnd();
}

void drawThigh(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset) {
    glColor3ub(r + colorOffset, g + colorOffset, b + colorOffset);

    glBegin(GL_POLYGON);
    {
        glVertex2f(10.0, 0.0);
        glVertex2f(3.0, 35.0);
        glVertex2f(0.0, 55.0);
        glVertex2f(0.0, 70.0);
        glVertex2f(0.0, 80.0);
        glVertex2f(50.0, 80.0);
        glVertex2f(50.0, 70.0);
        glVertex2f(50.0, 55.0);
        glVertex2f(47.0, 35.0);
        glVertex2f(40.0, 0.0);
    }
    glEnd();
}

void drawCalf(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset) {
    glColor3ub(r + colorOffset, g + colorOffset, b + colorOffset);

    glBegin(GL_POLYGON);
    {
        glVertex2f(5.0, 0.0);
        glVertex2f(0.0, 35.0);
        glVertex2f(0.0, 55.0);
        glVertex2f(2.0, 70.0);
        glVertex2f(5.0, 80.0);
        glVertex2f(35.0, 80.0);
        glVertex2f(38.0, 70.0);
        glVertex2f(40.0, 55.0);
        glVertex2f(40.0, 35.0);
        glVertex2f(35.0, 0.0);
    }
    glEnd();
}

void drawFoot(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset) {
    glColor3ub(r + colorOffset, g + colorOffset, b + colorOffset);

    glBegin(GL_POLYGON);
    {
        glVertex2f(5.0, 40.0);
        glVertex2f(0.0, 50.0);
        glVertex2f(0.0, 60.0);
        glVertex2f(40.0, 60.0);
        glVertex2f(40.0, 50.0);
        glVertex2f(35.0, 40.0);
    }
    glEnd();

    glBegin(GL_POLYGON);
    {
        glVertex2f(5.0, 0.0);
        glVertex2f(5.0, 40.0);
        glVertex2f(35.0, 40.0);
        glVertex2f(35.0, 25.0);
        glVertex2f(50.0, 25.0);
        glVertex2f(60.0, 20.0);
        glVertex2f(65.0, 10.0);
        glVertex2f(65.0, 0.0);
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

    // Perna
    glPushMatrix();
    {
        glTranslatef(x, y, 0.0);

        // Quadril e Coxa
        glPushMatrix();
        {
            pivotX = 25.0, pivotY = 80.0;

            glTranslatef(pivotX, pivotY, 0.0);
            glRotatef(angleA, 0.0, 0.0, 1.0);
            glTranslatef(-pivotX, -pivotY, 0.0);

            drawJoint(25.0, 80.0, 25.0, r1, g1, b1, colorOffset);
            drawThigh(r1, g1, b1, colorOffset);

            // Joelho
            glPushMatrix();
            {
                pivotX = 25.0, pivotY = 0.0;

                glTranslatef(pivotX, pivotY, 0.0);
                glRotatef(angleB, 0.0, 0.0, 1.0);
                glTranslatef(-pivotX, -pivotY, 0.0);

                drawJoint(25.0, 0.0, 15.0, r1, g1, b1, colorOffset);

                // Panturrilha
                glPushMatrix();
                {
                    glTranslatef(5.0, -80.0, 0.0);

                    drawCalf(r1, g1, b1, colorOffset);

                    // Tornozelo
                    glPushMatrix();
                    {
                        pivotX = 20.0, pivotY = 0.0;

                        glTranslatef(pivotX, pivotY, 0.0);
                        glRotatef(angleC, 0.0, 0.0, 1.0);
                        glTranslatef(-pivotX, -pivotY, 0.0);

                        drawJoint(20.0, 0.0, 15.0, r1, g1, b1, colorOffset);

                        // Pé
                        glPushMatrix();
                        {
                            glTranslatef(0.0, -60.0, 0.0);
                            drawFoot(r2, g2, b2, colorOffset);
                        }
                        // Fim Pé
                        glPopMatrix();
                    }
                    // Fim Tornozelo
                    glPopMatrix();
                }
                // Fim Panturrilha
                glPopMatrix();
            }
            // Fim Joelho
            glPopMatrix();
        }
        // Fim Quadril e Coxa
        glPopMatrix();
    }
    // Fim Perna
    glPopMatrix();
}

void drawTorso(GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_POLYGON);
    {
        glVertex2f(28.0, 0.0);
        glVertex2f(12.0, 8.0);
        glVertex2f(4.0, 20.0);
        glVertex2f(76.0, 20.0);
        glVertex2f(68.0, 8.0);
        glVertex2f(52.0, 0.0);
    }
    glEnd();

    glBegin(GL_POLYGON);
    {
        glVertex2f(4.0, 20.0);
        glVertex2f(0.0, 32.0);
        glVertex2f(0.0, 40.0);
        glVertex2f(4.0, 52.0);
        glVertex2f(76.0, 52.0);
        glVertex2f(80.0, 40.0);
        glVertex2f(80.0, 32.0);
        glVertex2f(76.0, 20.0);
    }
    glEnd();

    glBegin(GL_POLYGON);
    {
        glVertex2f(4.0, 52.0);
        glVertex2f(4.0, 80.0);
        glVertex2f(2.0, 100.0);
        glVertex2f(0.0, 120.0);
        glVertex2f(0.0, 140.0);
        glVertex2f(4.0, 150.0);
        glVertex2f(10.0, 160.0);
        glVertex2f(60.0, 160.0);
        glVertex2f(70.0, 150.0);
        glVertex2f(70.0, 78.0);
        glVertex2f(72.0, 68.0);
        glVertex2f(76.0, 52.0);
    }
    glEnd();

    glBegin(GL_POLYGON);
    {
        glVertex2f(60.0, 160.0);
        glVertex2f(70.0, 150.0);
        glVertex2f(80.0, 140.0);
        glVertex2f(86.0, 130.0);
        glVertex2f(82.0, 120.0);
        glVertex2f(70.0, 112.0);
    }
    glEnd();
}

void drawChest(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    // Peitoral
    glPushMatrix();
    {
        glTranslatef(x, y, 0.0);

        // Torso
        glPushMatrix();
        { drawTorso(r, g, b); }
        // Fim Torso
        glPopMatrix();
    }
    // Fim Peitoral
    glPopMatrix();
}

void drawUpperArm(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset) {
    glColor3ub(r + colorOffset, g + colorOffset, b + colorOffset);

    glBegin(GL_POLYGON);
    {
        glVertex2f(5.0, 0.0);
        glVertex2f(0.0, 80.0);
        glVertex2f(40.0, 80.0);
        glVertex2f(35.0, 0.0);
    }
    glEnd();
}

void drawForearm(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset) {
    glColor3ub(r + colorOffset, g + colorOffset, b + colorOffset);

    glBegin(GL_POLYGON);
    {
        glVertex2f(5.0, 0.0);
        glVertex2f(0.0, 80.0);
        glVertex2f(30.0, 80.0);
        glVertex2f(25.0, 0.0);
    }
    glEnd();
}

void drawArm(GLfloat x,
             GLfloat y,
             GLfloat angleA,
             GLfloat angleB,
             /*GLfloat angleC,*/
             GLubyte r1,
             GLubyte g1,
             GLubyte b1,
             /*GLubyte r2,
             GLubyte g2,
             GLubyte b2,*/
             GLubyte colorOffset) {
    GLfloat pivotX = 0.0, pivotY = 0.0;

    // Braço
    glPushMatrix();
    {
        glTranslatef(x, y, 0.0);

        // Braço Superior
        glPushMatrix();
        {
            pivotX = 20.0, pivotY = 80.0;

            glTranslatef(pivotX, pivotY, 0.0);
            glRotatef(angleA, 0.0, 0.0, 1.0);
            glTranslatef(-pivotX, -pivotY, 0.0);

            drawJoint(20.0, 80.0, 20.0, 255, 0, 0, colorOffset);
            drawUpperArm(40, 40, 40, colorOffset);

            // Cotovelo
            glPushMatrix();
            {
                pivotX = 20.0, pivotY = 0.0;

                glTranslatef(pivotX, pivotY, 0.0);
                glRotatef(angleB, 0.0, 0.0, 1.0);
                glTranslatef(-pivotX, -pivotY, 0.0);

                drawJoint(20.0, 0.0, 15.0, 0, 255, 0, colorOffset);

                // Antebraço
                glPushMatrix();
                {
                    glTranslatef(5.0, -80.0, 0.0);
                    drawForearm(120, 120, 120, colorOffset);
                }
                // Fim Antebraço
                glPopMatrix();
            }
            // Fim Cotovelo
            glPopMatrix();
        }
        // Fim Braço Superior
        glPopMatrix();
    }
    // Fim Braço
    glPopMatrix();
}
