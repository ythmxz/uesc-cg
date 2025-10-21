#include <GL/glut.h>
#include <stdio.h>

// Parte inferior
void drawThigh(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);
void drawKnee(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);
void drawCalf(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);
void drawFoot(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);
void drawLeg(GLfloat x, GLfloat y, GLubyte r1, GLubyte g1, GLubyte b1, GLubyte r2, GLubyte g2, GLubyte b2, GLubyte colorOffset);

// Parte superior
void drawTorso(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);
void drawStrap(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);
void drawBelt(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);
void drawChest(GLfloat x, GLfloat y, GLubyte r1, GLubyte g1, GLubyte b1, GLubyte r2, GLubyte g2, GLubyte b2);

void drawShoulder(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);
void drawUpperArm(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);
void drawForearm(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);
void drawHand(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);
void drawArm(GLfloat x, GLfloat y, GLubyte r1, GLubyte g1, GLubyte b1, GLubyte r2, GLubyte g2, GLubyte b2, GLubyte colorOffset);

void drawEye(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);
void drawFace(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);
void drawHood(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);
void drawHead(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b);

void drawCape();

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

void drawLeg(GLfloat x, GLfloat y, GLubyte r1, GLubyte g1, GLubyte b1, GLubyte r2, GLubyte g2, GLubyte b2, GLubyte colorOffset) {
    GLfloat angle = 0.0;

    glPushMatrix();
    {
        glTranslatef(x, y, 0.0);

        angle = 10.0;
        glRotatef(angle, 0.0, 0.0, 1.0);
        drawThigh(2.5, 20.0, r1 + colorOffset, g1 + colorOffset, b1 + colorOffset);
        glRotatef(-angle, 0.0, 0.0, 1.0);

        angle = 2.0;
        glRotatef(angle, 0.0, 0.0, 1.0);
        drawCalf(0.5, 0.0, r1 + colorOffset, g1 + colorOffset, b1 + colorOffset);
        glRotatef(-angle, 0.0, 0.0, 1.0);

        angle = 2.0;
        glRotatef(angle, 0.0, 0.0, 1.0);
        drawKnee(0.5, 16.0, r2 + colorOffset, g2 + colorOffset, b2 + colorOffset);
        glRotatef(-angle, 0.0, 0.0, 1.0);

        drawFoot(0.0, 0.0, r2 + colorOffset, g2 + colorOffset, b2 + colorOffset);
    }
    glPopMatrix();
}

void drawTorso(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_QUADS);
    {
        glVertex2f(x + 0.0, y + 0.0);
        glVertex2f(x + 0.0, y + 30.0);
        glVertex2f(x + 15.0, y + 30.0);
        glVertex2f(x + 15.0, y + 0.0);
    }
    glEnd();
}

void drawStrap(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_POLYGON);
    {
        glVertex2f(x + 0.0, y + 0.0);
        glVertex2f(x + 0.0, y + 3.0);
        glVertex2f(x + 15.0, y + 20.0);
        glVertex2f(x + 15.0, y + 17.0);
    }
    glEnd();
}

void drawBelt(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_QUADS);
    {
        glVertex2f(x + 0.0, y + 0.0);
        glVertex2f(x + 0.0, y + 3.0);
        glVertex2f(x + 15.0, y + 3.0);
        glVertex2f(x + 15.0, y + 0.0);
    }
    glEnd();
}

void drawChest(GLfloat x, GLfloat y, GLubyte r1, GLubyte g1, GLubyte b1, GLubyte r2, GLubyte g2, GLubyte b2) {
    GLfloat angle = 0.0;

    glPushMatrix();
    {
        glTranslatef(x, y, 0.0);
        drawTorso(0.0, 0.0, r1, g1, b1);
        drawBelt(0.0, 4.0, r2, g2, b2);
        drawStrap(0.0, 8.0, r2, g2, b2);
    }
    glPopMatrix();
}

void drawShoulder(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_QUADS);
    {
        glVertex2f(x + 0.0, y + 0.0);
        glVertex2f(x + 0.0, y + 8.0);
        glVertex2f(x + 8.0, y + 8.0);
        glVertex2f(x + 8.0, y + 0.0);
    }
    glEnd();
}

void drawUpperArm(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_QUADS);
    {
        glVertex2f(x + 0.0, y + 0.0);
        glVertex2f(x + 0.0, y + 15.0);
        glVertex2f(x + 7.0, y + 15.0);
        glVertex2f(x + 7.0, y + 0.0);
    }
    glEnd();
}

void drawForearm(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_QUADS);
    {
        glVertex2f(x + 1.0, y + 0.0);
        glVertex2f(x + 0.0, y + 15.0);
        glVertex2f(x + 7.0, y + 15.0);
        glVertex2f(x + 6.0, y + 0.0);
    }
    glEnd();
}

void drawHand(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_QUADS);
    {
        glVertex2f(x + 0.0, y + 0.0);
        glVertex2f(x + 0.0, y + 6.0);
        glVertex2f(x + 6.0, y + 6.0);
        glVertex2f(x + 6.0, y + 0.0);
    }
    glEnd();
}

void drawArm(GLfloat x, GLfloat y, GLubyte r1, GLubyte g1, GLubyte b1, GLubyte r2, GLubyte g2, GLubyte b2, GLubyte colorOffset) {
    GLfloat angle = 0.0;

    glPushMatrix();
    {
        glTranslatef(x, y, 0.0);

        drawUpperArm(-0.5, 21.0, r1 + colorOffset, g1 + colorOffset, b1 + colorOffset);
        drawForearm(-0.5, 6.0, r1 + colorOffset, g1 + colorOffset, b1 + colorOffset);
        drawShoulder(-1.0, 31.0, r2 + colorOffset, g2 + colorOffset, b2 + colorOffset);
        drawHand(0.0, 0.0, r2 + colorOffset, g2 + colorOffset, b2 + colorOffset);
    }
    glPopMatrix();
}

void drawFace(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_POLYGON);
    {
        glVertex2f(x + 3.0, y + 1.0);
        glVertex2f(x + 2.0, y + 3.0);
        glVertex2f(x + 1.0, y + 5.0);
        glVertex2f(x + 0.0, y + 7.5);
        glVertex2f(x + 0.0, y + 9.0);
        glVertex2f(x + 0.0, y + 10.5);
        glVertex2f(x + 1.0, y + 13.0);
        glVertex2f(x + 2.0, y + 15.0);
        glVertex2f(x + 3.0, y + 17.0);
        glVertex2f(x + 4.0, y + 17.6);
        glVertex2f(x + 6.0, y + 18.0);
        glVertex2f(x + 8.0, y + 17.6);
        glVertex2f(x + 9.0, y + 17.0);
        glVertex2f(x + 10.0, y + 15.0);
        glVertex2f(x + 11.0, y + 13.0);
        glVertex2f(x + 12.0, y + 10.5);
        glVertex2f(x + 12.0, y + 9.0);
        glVertex2f(x + 12.0, y + 7.5);
        glVertex2f(x + 11.0, y + 5.0);
        glVertex2f(x + 10.0, y + 3.0);
        glVertex2f(x + 9.0, y + 1.0);
        glVertex2f(x + 8.0, y + 0.4);
        glVertex2f(x + 4.0, y + 0.4);
        glVertex2f(x + 6.0, y + 0.0);
    }
    glEnd();
}

void drawEye(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_QUADS);
    {
        glVertex2f(x + 0.0, y + 1.0);
        glVertex2f(x + 2.0, y + 2.0);
        glVertex2f(x + 4.0, y + 1.0);
        glVertex2f(x + 2.0, y + 0.0);
    }
    glEnd();
}

void drawHood(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    glColor3ub(r, g, b);

    glBegin(GL_POLYGON);
    {
        glVertex2f(x + 0.0, y + 5.2);
        glVertex2f(x + 1.0, y + 2.0);
        glVertex2f(x + 3.0, y + 1.0);
        glVertex2f(x + 6.0, y + 0.0);
        glVertex2f(x + 10.0, y + 0.0);
        glVertex2f(x + 17.0, y + 1.0);
        glVertex2f(x + 15.0, y + 1.0);
        glVertex2f(x + 14.0, y + 2.0);
        glVertex2f(x + 12.0, y + 3.0);
        glVertex2f(x + 11.0, y + 5.0);
        glVertex2f(x + 10.0, y + 8.0);
        glVertex2f(x + 10.0, y + 10.0);
        glVertex2f(x + 11.0, y + 13.0);
        glVertex2f(x + 12.0, y + 15.0);
        glVertex2f(x + 13.0, y + 17.0);
        glVertex2f(x + 14.0, y + 18.0);
        glVertex2f(x + 15.0, y + 19.0);
        glVertex2f(x + 16.0, y + 19.0);
        glVertex2f(x + 12.0, y + 20.0);
        glVertex2f(x + 8.0, y + 19.6);
        glVertex2f(x + 4.8, y + 17.6);
        glVertex2f(x + 3.2, y + 14.0);
        glVertex2f(x + 1.2, y + 10.8);
        glVertex2f(x + 0.4, y + 8.0);
    }
    glEnd();
}

void drawHead(GLfloat x, GLfloat y, GLubyte r, GLubyte g, GLubyte b) {
    GLfloat angle = 0.0;

    glPushMatrix();
    {
        glTranslatef(x, y, 0.0);

        drawFace(8.0, 1.0, 0, 0, 0);

        angle = -15.0;
        glRotatef(angle, 0.0, 0.0, 1.0);
        drawEye(7.0, 13.0, 255, 255, 255);
        glRotatef(-angle, 0.0, 0.0, 1.0);

        angle = 15.0;
        glRotatef(angle, 0.0, 0.0, 1.0);
        drawEye(18.0, 5.0, 255, 255, 255);
        glRotatef(-angle, 0.0, 0.0, 1.0);

        drawHood(0.0, 0.0, r, g, b);
    }
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawArm(71.0, 48.0, 60, 40, 80, 60, 60, 60, -20);
    drawLeg(70.0, 20.0, 60, 40, 80, 60, 60, 60, -15);
    drawChest(58.0, 54.0, 60, 40, 80, 60, 60, 60);
    drawLeg(60.0, 20.0, 60, 40, 80, 60, 60, 60, 15);
    drawHead(54.0, 82.5, 60, 40, 80);
    drawArm(56.0, 48.0, 60, 40, 80, 60, 60, 60, 20);

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    // Tamanho do monitor
    int displayWidth = glutGet(GLUT_SCREEN_WIDTH);
    int displayHeight = glutGet(GLUT_SCREEN_HEIGHT);

    // Tamanho da janela
    int windowWidth = displayHeight / 2;
    int windowHeight = displayHeight / 2;

    // Cria a janela
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((displayWidth - windowWidth) / 2, (displayHeight - windowHeight) / 2);
    glutCreateWindow("Spoiler");

    // Define fundo e espaço de desenho
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0.00, (double)windowWidth / 4.0, 0.00, (double)windowHeight / 4.0);

    // Exibe conteúdo
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
