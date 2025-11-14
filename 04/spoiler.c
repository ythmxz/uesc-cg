#define _USE_MATH_DEFINES

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int displayWidth = 0, displayHeight = 0;
int windowWidth = 0, windowHeight = 0;

// Posição, escala e ângulo do personagem

GLfloat posX = 405.0, posY = 405.0, scale = 1.5, angle = 0.0;

// Ângulos das articulações

GLfloat neck = 0.0;
GLfloat shoulderL = 0.0, elbowL = 0.0, wristL = 0.0;
GLfloat shoulderR = 0.0, elbowR = 0.0, wristR = 0.0;
GLfloat hipL = 0.0, kneeL = 0.0, ankleL = 0.0;
GLfloat hipR = 0.0, kneeR = 0.0, ankleR = 0.0;

// Variáveis para controlar a animação
GLfloat animationTime = 0.0;
GLboolean animating = GL_FALSE;
GLfloat backgroundOffset = 0.0;
GLfloat starBlinkTime = 0.0;

// Posições das estrelas (geradas aleatoriamente uma vez)
#define NUM_STARS 100
GLfloat starPositions[NUM_STARS][2]; // [x, y]

// Callbacks

void display(void);
void reshape(GLsizei width, GLsizei height);
void timer(int value);
void keyboard(unsigned char key, GLint x, GLint y);
void special(int key, GLint x, GLint y);

// Inicialização

void initStars();

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
void drawStrap(GLubyte r1, GLubyte g1, GLubyte b1, GLubyte r2, GLubyte g2, GLubyte b2);
void drawBody(GLfloat x, GLfloat y, GLubyte r1, GLubyte g1, GLubyte b1, GLubyte r2, GLubyte g2, GLubyte b2);

// Braço

void drawUpperArm(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);
void drawForearm(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);
void drawHand(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset);
void drawArm(GLfloat x,
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

// Cabeça

void drawHood(GLubyte r, GLubyte g, GLubyte b);
void drawFace(GLubyte r, GLubyte g, GLubyte b);
void drawEye(GLubyte r, GLubyte g, GLubyte b);
void drawHead(GLfloat x, GLfloat y, GLfloat angle, GLubyte r, GLubyte g, GLubyte b);

// Capa

void drawCape(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);

// Completo

void drawBackground();
void drawSpoiler(GLfloat x, GLfloat y, GLfloat scale, GLfloat angle);

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

    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Inicializa posições aleatórias das estrelas
    initStars();

    // Callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, timer, 0);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMainLoop();

    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBackground();
    drawSpoiler(posX, posY, scale, angle);
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

void timer(int value) {
    // Atualiza o tempo de piscar das estrelas (sempre, independente da animação)
    starBlinkTime += 0.05;

    if (animating) {
        angle = -10.0;
        animationTime += 0.15;

        hipR = (45.0 * sin(animationTime)) + 20.0;
        kneeR = -30.0 - 20.0 * cos(animationTime);
        ankleR = 0.0;

        hipL = (45.0 * sin(animationTime + M_PI)) + 20.0;
        kneeL = -30.0 - 20.0 * cos((animationTime + M_PI));
        ankleL = 0.0;

        shoulderR = 30.0 * sin(animationTime + M_PI);
        shoulderL = 30.0 * sin(animationTime);

        elbowR = 120.0 + 10.0 * sin(animationTime);
        elbowL = 120.0 + 10.0 * sin(animationTime + M_PI);

        // Move o cenário para a esquerda
        backgroundOffset -= 5.0;
        // Reseta quando ultrapassar a largura da janela (loop infinito)
        if (backgroundOffset <= -windowWidth) {
            backgroundOffset = 0.0;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
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

    case 'n':
        wristR = (wristR <= 10.0) ? wristR += 5.0 : wristR;
        break;

    case 'b':
        wristR = (wristR >= -5.0) ? wristR -= 5.0 : wristR;
        break;

        // Braço Esquerdo
    case 'i':
        shoulderL = (shoulderL <= 175.0) ? shoulderL += 5.0 : shoulderL;
        break;

    case 'u':
        shoulderL = (shoulderL >= -55.0) ? shoulderL -= 5.0 : shoulderL;
        break;

    case 'k':
        elbowL = (elbowL <= 145.0) ? elbowL += 5.0 : elbowL;
        break;

    case 'j':
        elbowL = (elbowL >= 5.0) ? elbowL -= 5.0 : elbowL;
        break;

    case ',':
        wristL = (wristL <= 10.0) ? wristL += 5.0 : wristL;
        break;

    case 'm':
        wristL = (wristL >= -5.0) ? wristL -= 5.0 : wristL;
        break;

    // Pescoço
    case 'o':
        neck = (neck <= 25.0) ? neck += 5.0 : neck;
        break;

    case 'p':
        neck = (neck >= -25.0) ? neck -= 5.0 : neck;
        break;

    // Restaurar
    case 13:
        posX = 405.0, posY = 405.0, scale = 1.5, angle = 0.0;
        neck = 0.0;
        shoulderL = 0.0, elbowL = 0.0, wristL = 0.0;
        shoulderR = 0.0, elbowR = 0.0, wristR = 0.0;
        hipL = 0.0, kneeL = 0.0, ankleL = 0.0;
        hipR = 0.0, kneeR = 0.0, ankleR = 0.0;
        break;

    // Iniciar/Parar animação
    case ' ': // Barra de espaço
        animating = !animating;
        if (!animating) {
            // Reseta todas as articulações para posição neutra
            animationTime = 0.0;
            angle = 0.0;
            neck = 0.0;
            shoulderL = 0.0;
            elbowL = 0.0;
            wristL = 0.0;
            shoulderR = 0.0;
            elbowR = 0.0;
            wristR = 0.0;
            hipL = 0.0;
            kneeL = 0.0;
            ankleL = 0.0;
            hipR = 0.0;
            kneeR = 0.0;
            ankleR = 0.0;
        }
        break;
    }

    glutPostRedisplay();
}

void special(int key, GLint x, GLint y) {
    switch (key) {
    // Posição
    case GLUT_KEY_UP:
        posY += 5.0;
        break;

    case GLUT_KEY_DOWN:
        posY -= 5.0;
        break;

    case GLUT_KEY_LEFT:
        posX -= 5.0;
        break;

    case GLUT_KEY_RIGHT:
        posX += 5.0;
        break;

    // Escala
    case GLUT_KEY_PAGE_UP:
        scale += 0.1;
        break;

    case GLUT_KEY_PAGE_DOWN:
        scale = (scale > 0.1) ? scale - 0.1 : scale;
        break;

    // Rotação
    case GLUT_KEY_HOME:
        angle += 5.0;
        break;

    case GLUT_KEY_END:
        angle -= 5.0;
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

void drawStrap(GLubyte r1, GLubyte g1, GLubyte b1, GLubyte r2, GLubyte g2, GLubyte b2) {
    glColor3ub(r2, g2, b2);

    glBegin(GL_QUADS);
    {
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 10.0);
        glVertex2f(70.0, 130.0);
        glVertex2f(75.0, 125.0);
    }
    glEnd();

    drawJoint(46.0, 80.0, 20.0, r2, g2, b2, 0);
    drawJoint(46.0, 80.0, 15.0, r1, g1, b1, 0);
}

void drawBelt(GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_QUADS);
    {
        glVertex2f(0.0, 0.0);
        glVertex2f(4.0, 10.0);
        glVertex2f(76.0, 10.0);
        glVertex2f(80.0, 0.0);
    }
    glEnd();
}

void drawBody(GLfloat x, GLfloat y, GLubyte r1, GLubyte g1, GLubyte b1, GLubyte r2, GLubyte g2, GLubyte b2) {
    // Peitoral
    glPushMatrix();
    {
        glTranslatef(x, y, 0.0);

        // Torso
        glPushMatrix();
        {
            drawTorso(r1, g1, b1);

            // Bandoleira
            glPushMatrix();
            {
                glTranslatef(0.0, 20.0, 0.0);
                drawStrap(r1, g1, b1, r2, g2, b2);
            }
            // Fim Bandoleira
            glPopMatrix();

            // Cinto
            glPushMatrix();
            {
                glTranslatef(0.0, 40.0, 0.0);
                drawBelt(r2, g2, b2);
            }
            // Fim Cinto
            glPopMatrix();
        }
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
        glVertex2f(35.0, 80.0);
        glVertex2f(40.0, 40.0);
        glVertex2f(35.0, 20.0);
        glVertex2f(30.0, 10.0);
        glVertex2f(30.0, 0.0);
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

void drawHand(GLubyte r, GLubyte g, GLubyte b, GLubyte colorOffset) {
    glColor3ub(r + colorOffset, g + colorOffset, b + colorOffset);

    glBegin(GL_POLYGON);
    {
        glVertex2f(0.0, 5.0);
        glVertex2f(5.0, 30.0);
        glVertex2f(25.0, 30.0);
        glVertex2f(25.0, 20.0);
        glVertex2f(30.0, 10.0);
        glVertex2f(30.0, 0.0);
    }
    glEnd();
}

void drawArm(GLfloat x,
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

            drawJoint(20.0, 80.0, 20.0, r1, g1, b1, colorOffset);
            drawUpperArm(r1, g1, b1, colorOffset);

            // Cotovelo
            glPushMatrix();
            {
                pivotX = 20.0, pivotY = 0.0;

                glTranslatef(pivotX, pivotY, 0.0);
                glRotatef(angleB, 0.0, 0.0, 1.0);
                glTranslatef(-pivotX, -pivotY, 0.0);

                drawJoint(20.0, 0.0, 15.0, r1, g1, b1, colorOffset);

                // Antebraço
                glPushMatrix();
                {
                    glTranslatef(5.0, -80.0, 0.0);
                    drawForearm(r1, g1, b1, colorOffset);

                    // Pulso
                    glPushMatrix();
                    {
                        pivotX = 15.0, pivotY = 0.0;

                        glTranslatef(pivotX, pivotY, 0.0);
                        glRotatef(angleC, 0.0, 0.0, 1.0);
                        glTranslatef(-pivotX, -pivotY, 0.0);

                        drawJoint(15.0, 0.0, 10.0, r1, g1, b1, colorOffset);

                        // Mão
                        glPushMatrix();
                        {
                            glTranslatef(0.0, -30.0, 0.0);
                            drawHand(r2, g2, b2, colorOffset);
                        }
                        // Fim Mão
                        glPopMatrix();
                    }
                    // Fim Pulso
                    glPopMatrix();
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

void drawHood(GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_POLYGON);
    {
        glVertex2f(60.0, 4.0);
        glVertex2f(56.0, 8.0);
        glVertex2f(48.0, 12.0);
        glVertex2f(44.0, 20.0);
        glVertex2f(40.0, 32.0);
        glVertex2f(40.0, 40.0);
        glVertex2f(44.0, 52.0);
        glVertex2f(48.0, 60.0);
        glVertex2f(52.0, 68.0);
        glVertex2f(56.0, 72.0);
        glVertex2f(60.0, 76.0);
        glVertex2f(64.0, 76.0);
        glVertex2f(48.0, 80.0);
        glVertex2f(32.0, 78.4);
        glVertex2f(19.2, 70.4);
        glVertex2f(12.8, 56.0);
        glVertex2f(4.8, 43.2);
        glVertex2f(1.6, 32.0);
        glVertex2f(0.0, 20.8);
        glVertex2f(4.0, 8.0);
        glVertex2f(12.0, 4.0);
        glVertex2f(24.0, 0.0);
        glVertex2f(40.0, 0.0);
        glVertex2f(68.0, 4.0);
    }
    glEnd();
}

void drawFace(GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_POLYGON);
    {
        glVertex2f(12.0, 4.0);
        glVertex2f(8.0, 12.0);
        glVertex2f(4.0, 20.0);
        glVertex2f(0.0, 30);
        glVertex2f(0.0, 36.0);
        glVertex2f(0.0, 42.0);
        glVertex2f(4.0, 52.0);
        glVertex2f(8.0, 60.0);
        glVertex2f(12.0, 68.0);
        glVertex2f(16.0, 70.4);
        glVertex2f(24.0, 72.0);
        glVertex2f(32.0, 70.4);
        glVertex2f(36.0, 68.0);
        glVertex2f(40.0, 60.0);
        glVertex2f(44.0, 52.0);
        glVertex2f(48.0, 42.0);
        glVertex2f(48.0, 36.0);
        glVertex2f(48.0, 30);
        glVertex2f(44.0, 20.0);
        glVertex2f(40.0, 12.0);
        glVertex2f(36.0, 4.0);
        glVertex2f(32.0, 1.6);
        glVertex2f(16.0, 1.6);
        glVertex2f(24.0, 0.0);
    }
    glEnd();
}

void drawEye(GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_POLYGON);
    {
        glVertex2f(0.0, 4.0);
        glVertex2f(8.0, 8.0);
        glVertex2f(16.0, 4.0);
        glVertex2f(8.0, 0.0);
    }
    glEnd();
}

void drawHead(GLfloat x, GLfloat y, GLfloat angle, GLubyte r, GLubyte g, GLubyte b) {
    GLfloat pivotX = 0.0, pivotY = 0.0;

    // Cabeça
    glPushMatrix();
    {
        glTranslatef(x, y, 0.0);

        // Pescoço
        glPushMatrix();
        {
            pivotX = 35.0, pivotY = 60.0;

            glTranslatef(pivotX, pivotY, 0.0);
            glRotatef(angle, 0.0, 0.0, 1.0);
            glTranslatef(-pivotX, -pivotY, 0.0);

            drawJoint(35.0, 60.0, 20.0, r, g, b, 0);

            // Capuz
            glPushMatrix();
            {
                glTranslatef(-5.0, 55.0, 0.0);
                drawHood(r, g, b);

                // Rosto
                glPushMatrix();
                {
                    glTranslatef(30.0, 2.0, 0.0);
                    drawFace(0, 0, 0);

                    // Olhos
                    glPushMatrix();
                    {
                        glTranslatef(8.0, 40.0, 0.0);
                        drawEye(255, 255, 255);

                        glTranslatef(20.0, 0.0, 0.0);
                        drawEye(255, 255, 255);
                    }
                    // Fim Olhos
                    glPopMatrix();
                }
                // Fim Rosto
                glPopMatrix();
            }
            // Fim Capuz
            glPopMatrix();
        }
        // Fim Pescoço
        glPopMatrix();
    }
    // Fim Cabeça
    glPopMatrix();
}

void drawCape(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glPushMatrix();
    {
        glTranslatef(x, y, 0.0);

        glBegin(GL_POLYGON);
        {
            glVertex2f(240.0, 0.0);
            glVertex2f(185.4, 13.8);
            glVertex2f(130.8, 31.2);
            glVertex2f(89.4, 33.6);
            glVertex2f(46.2, 64.8);
            glVertex2f(98.4, 111.6);
            glVertex2f(120.6, 165.0);
            glVertex2f(120.0, 240.0);
            glVertex2f(144.0, 286.8);
            glVertex2f(180.0, 351.0);
            glVertex2f(223.8, 345.0);
            glVertex2f(218.4, 280.2);
            glVertex2f(228.6, 184.8);
            glVertex2f(237.0, 91.8);
        }
        glEnd();
    }
    glPopMatrix();
}

void initStars() {
    // Inicializa posições aleatórias das estrelas (chamada uma vez no início)
    srand(time(NULL));
    for (int i = 0; i < NUM_STARS; i++) {
        starPositions[i][0] = (GLfloat)(rand() % (int)windowWidth);
        starPositions[i][1] = (windowHeight / 4.0) + (GLfloat)(rand() % (int)(windowHeight * 0.75));
    }
}

void drawStars() {
    // Habilita blending para transparência
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Desenha estrelas (pontos brancos) em posições fixas com efeito de piscar
    glPointSize(2.0);
    glBegin(GL_POINTS);
    {
        for (int i = 0; i < NUM_STARS; i++) {
            GLfloat x = starPositions[i][0];
            GLfloat y = starPositions[i][1];

            // Efeito de piscar: cada estrela tem sua própria fase baseada no índice
            GLfloat blinkPhase = starBlinkTime + (i * 0.3);  // offset diferente para cada estrela
            GLfloat opacity = (sin(blinkPhase) + 1.0) * 0.5; // varia entre 0.0 e 1.0

            // Varia a opacidade entre 0.3 e 1.0 (nunca totalmente transparente)
            GLfloat starOpacity = 0.3f + opacity * 0.7f;
            glColor4f(1.0f, 1.0f, 1.0f, starOpacity);

            glVertex2f(x, y);
        }
    }
    glEnd();

    // Desabilita blending
    glDisable(GL_BLEND);
}

void drawBuilding(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    // Corpo do prédio (cinza escuro)
    glColor3ub(30, 30, 40);
    glBegin(GL_QUADS);
    {
        glVertex2f(x, y);
        glVertex2f(x, y + height);
        glVertex2f(x + width, y + height);
        glVertex2f(x + width, y);
    }
    glEnd();

    // Janelas acesas (amarelo claro)
    glColor3ub(255, 255, 150);
    GLfloat windowWidth = width / 8.0;
    GLfloat windowHeight = height / 15.0;

    for (int row = 1; row < 14; row++) {
        for (int col = 1; col < 7; col++) {
            // Acende janelas de forma pseudo-aleatória (padrão baseado em posição)
            if ((row + col) % 3 != 0) {
                GLfloat wx = x + col * (width / 7.0);
                GLfloat wy = y + row * (height / 14.0);
                glBegin(GL_QUADS);
                {
                    glVertex2f(wx, wy);
                    glVertex2f(wx, wy + windowHeight);
                    glVertex2f(wx + windowWidth, wy + windowHeight);
                    glVertex2f(wx + windowWidth, wy);
                }
                glEnd();
            }
        }
    }
}

void drawRooftop() {
    // Telhado de prédio (cinza mais claro com detalhes)
    glColor3ub(50, 50, 60);
    glBegin(GL_QUADS);
    {
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, windowHeight / 4.0);
        glVertex2f(windowWidth, windowHeight / 4.0);
        glVertex2f(windowWidth, 0.0);
    }
    glEnd();

    // Batente superior (borda elevada no topo do telhado)
    GLfloat edgeHeight = 15.0;
    glColor3ub(60, 60, 70);
    glBegin(GL_QUADS);
    {
        glVertex2f(0.0, windowHeight / 4.0);
        glVertex2f(0.0, windowHeight / 4.0 + edgeHeight);
        glVertex2f(windowWidth, windowHeight / 4.0 + edgeHeight);
        glVertex2f(windowWidth, windowHeight / 4.0);
    }
    glEnd();

    // Sombra do batente
    glColor3ub(30, 30, 35);
    glBegin(GL_QUADS);
    {
        glVertex2f(0.0, windowHeight / 4.0);
        glVertex2f(0.0, windowHeight / 4.0 + 3.0);
        glVertex2f(windowWidth, windowHeight / 4.0 + 3.0);
        glVertex2f(windowWidth, windowHeight / 4.0);
    }
    glEnd();

    // Detalhes do telhado - linhas de ventilação
    glColor3ub(40, 40, 50);
    glLineWidth(3.0);
    for (int i = 1; i < 8; i++) {
        glBegin(GL_LINES);
        {
            GLfloat lineY = (windowHeight / 4.0) * (i / 8.0);
            glVertex2f(0.0, lineY);
            glVertex2f(windowWidth, lineY);
        }
        glEnd();
    }

    // Pequenos blocos/estruturas no telhado
    glColor3ub(35, 35, 45);
    for (int i = 0; i < 5; i++) {
        GLfloat blockX = (i + 1) * (windowWidth / 6.0);
        GLfloat blockH = 20.0 + (i * 10.0);
        glBegin(GL_QUADS);
        {
            glVertex2f(blockX, 0.0);
            glVertex2f(blockX, blockH);
            glVertex2f(blockX + 40.0, blockH);
            glVertex2f(blockX + 40.0, 0.0);
        }
        glEnd();
    }
}

void drawSkyline(GLfloat skylineY) {
    // Desenha todos os prédios - função auxiliar para reutilizar
    drawBuilding(0.0, skylineY, 130.0, 350.0);
    drawBuilding(180.0, skylineY, 150.0, 300.0);
    drawBuilding(380.0, skylineY, 130.0, 400.0);
    drawBuilding(540.0, skylineY, 140.0, 250.0);
}

void drawBackground() {
    // Céu noturno
    glColor3ub(10, 10, 30);
    glBegin(GL_QUADS);
    {
        glVertex2f(0.0, windowHeight / 4.0);
        glVertex2f(0.0, windowHeight);
        glVertex2f(windowWidth, windowHeight);
        glVertex2f(windowWidth, windowHeight / 4.0);
    }
    glEnd();

    // Lua (desenhada uma vez em posição fixa)
    drawJoint(windowWidth * 0.75, windowHeight * 0.75, 150.0, 255, 255, 235, 0);
    drawJoint((windowWidth * 0.75) + 75.0, windowHeight * 0.75, 150.0, 10, 10, 30, 0);

    // Estrelas (desenhadas uma vez, fixas)
    drawStars();

    // Desenha duas cópias do cenário (prédios e telhado) lado a lado para criar loop infinito
    GLfloat skylineY = windowHeight / 8.0;
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        {
            glTranslatef(backgroundOffset + (i * windowWidth), 0.0, 0.0);

            // Prédios ao fundo em diferentes alturas (mesmos em ambas as cópias)
            drawSkyline(skylineY);

            // Telhado do prédio (chão)
            drawRooftop();
        }
        glPopMatrix();
    }
}

void drawSpoiler(GLfloat x, GLfloat y, GLfloat scale, GLfloat angle) {
    GLfloat pivotX = 55.5, pivotY = 80.0;

    glPushMatrix();
    {
        glTranslatef(x, y, 0.0);
        glTranslatef(pivotX, pivotY, 0.0);
        glRotatef(angle, 0.0, 0.0, 1.0);
        glScalef(scale, scale, 1.0);
        glTranslatef(-pivotX, -pivotY, 0.0);

        drawArm(48.0, 120.0, shoulderL, elbowL, wristL, 60, 40, 80, 60, 60, 60, -15);
        drawCape(-160.0, -140.0, 40, 20, 60);
        drawLeg(46.0, 0.0, hipL, kneeL, ankleL, 60, 40, 80, 60, 60, 60, -10);
        drawBody(8.0, 60.0, 60, 40, 80, 60, 60, 60);
        drawHead(20.0, 160.0, neck, 60, 40, 80);
        drawLeg(0.0, 0.0, hipR, kneeR, ankleR, 60, 40, 80, 60, 60, 60, 10);
        drawArm(8.0, 120.0, shoulderR, elbowR, wristR, 60, 40, 80, 60, 60, 60, 15);
    }
    glPopMatrix();
}
