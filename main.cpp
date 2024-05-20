
#ifdef APPLE

#else
#include <GL/glut.h>
#endif
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int phyWidth = 700;
int phyHeight = 700;
int logWidth = 100;
int logHeight = 100;
int centerX = logWidth / 2;
int centerY = logHeight / 2;
int score = 0;
float elapsedTime = 0.0f;
int timerInterval = 100; // 100 milliseconds

void init2D() {
    glClearColor(0.2, 0.2, 0.2, 1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, logWidth, 0.0, logHeight);
}

void DrawColoredCircle(float cx, float cy, float r, int num_segments) {
    glLineWidth(5.0f);
    glBegin(GL_LINE_LOOP);
    float segment_size = 2.0f * M_PI / float(num_segments);
    for (int i = 0; i < num_segments; i++) {
        float theta = segment_size * i;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        if (theta >= 0.0f && theta < M_PI / 2.0f) {
            glColor3f(1.0f, 0.0f, 0.0f); // Red
        } else if (theta >= M_PI / 2.0f && theta < M_PI) {
            glColor3f(0.0f, 0.0f, 1.0f); // Blue
        } else if (theta >= M_PI && theta < 3.0f * M_PI / 2.0f) {
            glColor3f(1.0f, 1.0f, 0.0f); // Yellow
        } else {
            glColor3f(0.0f, 1.0f, 0.0f); // Green
        }
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void smallRedCircle(float cx, float cy, float r, int num_segments) {
    glLineWidth(3.0f);
    glColor3f(0.9608f, 0.4863f, 0.4941f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawSquare(float x, float y, float size) {
    glColor3f(227.0f / 255.0f, 170.0f / 255.0f, 204.0f / 255.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x, y + size);
    glEnd();
}

void drawTriangle(float x, float y, float size) {
    glColor3f(96.0f / 255.0f, 190.0f / 255.0f, 184.0f / 255.0f);
    glLineWidth(2.5f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    const float rotationAngle = 5.0f;
    float topX = x + size / 2.0f;
    float topY = y + size * sqrt(3.0f) / 2.0f;
    float rotatedTopX = topX + cos(rotationAngle * M_PI / 180.0f) * (size / 6.0f);
    float rotatedTopY = topY + sin(rotationAngle * M_PI / 180.0f) * (size / 6.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(rotatedTopX, rotatedTopY);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawX(float x, float y, float size, float rotationAngle) {
    glLineWidth(3.0f);
    glColor3f(180.0f / 255.0f, 195.0f / 255.0f, 226.0f / 255.0f);
    float halfSize = size / 2.0f;
    float cosAngle = cos(rotationAngle * M_PI / 180.0f);
    float sinAngle = sin(rotationAngle * M_PI / 180.0f);
    glBegin(GL_LINES);
    glVertex2f(x + halfSize * cosAngle - halfSize * sinAngle, y + halfSize * sinAngle + halfSize * cosAngle);
    glVertex2f(x - halfSize * cosAngle + halfSize * sinAngle, y - halfSize * sinAngle - halfSize * cosAngle);
    glVertex2f(x + halfSize * cosAngle + halfSize * sinAngle, y + halfSize * sinAngle - halfSize * cosAngle);
    glVertex2f(x - halfSize * cosAngle - halfSize * sinAngle, y - halfSize * sinAngle + halfSize * cosAngle);
    glEnd();
}

void printSome(const char *str, int x, int y) {
    glColor3f(1, 1, 1);
    glRasterPos2d(x, y);
    for (int i = 0; i < strlen(str); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
    glFlush();
}

void scoreTime() {
    char scoreStr[50];
    sprintf(scoreStr, "Score %d", score); // Convert and concatenate the score
    printSome(scoreStr, 2, 95);

    char timeStr[50];
    sprintf(timeStr, "Time: %.1f", elapsedTime); // Convert and concatenate the elapsed time
    printSome(timeStr, 85, 95);
}

void drawPatternBackground() {
    int counter = 0;
    for (int i = 7; i < logHeight - 10; i += 20) {
        for (int j = 7; j < logWidth - 10; j += 20) {
            if (j >= 40 && j <= 65 && i >= 55 && i <= 90) {
                counter++;
                continue;
            }
            if (counter == 0) {
                counter++;
                smallRedCircle(j, i, 2, 50);
            } else if (counter == 1) {
                counter++;
                drawX(j, i, 3, 30);
            } else if (counter == 2) {
                counter++;
                drawTriangle(j, i, 3);
            } else {
                drawSquare(j, i, 3);
                counter = 0;
            }
        }
    }
}



void Timer(int value) {

    elapsedTime += 0.1f; // Increment elapsed time by 0.1 seconds (100 milliseconds)
    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(timerInterval, Timer, 0); // Register the timer callback again
}
void drawRedArrow(float x, float y, float width , float height ) {
    // Draw the shaft
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glBegin(GL_QUADS);
    glVertex2f(x, y - height / 4);
    glVertex2f(x, y + height / 4);
    glVertex2f(x + width - height / 2, y + height / 4);
    glVertex2f(x + width - height / 2, y - height / 4);
    glEnd();

    // Draw the head
    glBegin(GL_TRIANGLES);
    glVertex2f(x + width, y);
    glVertex2f(x + width - height / 2, y - height / 2);
    glVertex2f(x + width - height / 2, y + height / 2);
    glEnd();

    // Draw the stroke
    glColor3f(0.0f, 0.0f, 0.0f); // Black color
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y - height / 4);
    glVertex2f(x, y + height / 4);
    glVertex2f(x + width - height / 2, y + height / 4);
    glVertex2f(x + width - height / 2, y - height / 4);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(x + width, y);
    glVertex2f(x + width - height / 2, y - height / 2);
    glVertex2f(x + width - height / 2, y + height / 2);
    glEnd();
}

void drawYellowArrow(float x, float y, float width , float height ) {
    // Draw the shaft
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
    glBegin(GL_QUADS);
    glVertex2f(x + height / 2, y - height / 4);
    glVertex2f(x + height / 2, y + height / 4);
    glVertex2f(x + width, y + height / 4);
    glVertex2f(x + width, y - height / 4);
    glEnd();

    // Draw the head
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x + height / 2, y - height / 2);
    glVertex2f(x + height / 2, y + height / 2);
    glEnd();

    // Draw the stroke
    glColor3f(0.0f, 0.0f, 0.0f); // Black color
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x + height / 2, y - height / 4);
    glVertex2f(x + height / 2, y + height / 4);
    glVertex2f(x + width, y + height / 4);
    glVertex2f(x + width, y - height / 4);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + height / 2, y - height / 2);
    glVertex2f(x + height / 2, y + height / 2);
    glEnd();
}


void drawBlueArrow(float x, float y, float width, float height) {
    // Draw the shaft
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glBegin(GL_QUADS);
    glVertex2f(x - width / 4, y + height / 2);
    glVertex2f(x + width / 4, y + height / 2);
    glVertex2f(x + width / 4, y - height / 4);
    glVertex2f(x - width / 4, y - height / 4);
    glEnd();

    // Draw the head
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y - height / 2); // Bottom point of the arrowhead
    glVertex2f(x - width / 2, y); // Left point of the arrowhead
    glVertex2f(x + width / 2, y); // Right point of the arrowhead
    glEnd();

    // Draw the stroke
    glColor3f(0.0f, 0.0f, 0.0f); // Black color
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - width / 4, y + height / 2);
    glVertex2f(x + width / 4, y + height / 2);
    glVertex2f(x + width / 4, y - height / 100);
    glVertex2f(x - width / 4, y - height / 100);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y - height / 2);
    glVertex2f(x - width / 2, y);
    glVertex2f(x + width / 2, y);
    glEnd();
}

void drawGreenArrow(float x, float y, float width, float height ) {
    // Draw the shaft
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glBegin(GL_QUADS);
    glVertex2f(x - width / 4, y);
    glVertex2f(x + width / 4, y);
    glVertex2f(x + width / 4, y + height - width / 2);
    glVertex2f(x - width / 4, y + height - width / 2);
    glEnd();

    // Draw the head
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y + height);
    glVertex2f(x - width / 2, y + height - width / 2);
    glVertex2f(x + width / 2, y + height - width / 2);
    glEnd();

    // Draw the stroke
    glColor3f(0.0f, 0.0f, 0.0f); // Black color
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - width / 4, y);
    glVertex2f(x + width / 4, y);
    glVertex2f(x + width / 4, y + height - width / 2);
    glVertex2f(x - width / 4, y + height - width / 2);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y + height);
    glVertex2f(x - width / 2, y + height - width / 2);
    glVertex2f(x + width / 2, y + height - width / 2);
    glEnd();
}




void incrementScore() {
    score += 1; // Increment the score by 1
    glutPostRedisplay(); // Request a redraw to update the display
}

void startGame(){
    drawPatternBackground();
    DrawColoredCircle(50, 75, 15, 1500);
    scoreTime();
}
void handleKeypress(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        incrementScore();
    }

    if (key == GLUT_KEY_DOWN) {
        incrementScore();
    }

    if (key == GLUT_KEY_LEFT) {
        incrementScore();
    }

    if (key == GLUT_KEY_RIGHT) {
        incrementScore();
    }
}
void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    startGame();
    glutSwapBuffers();
    glFlush();
}
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(phyWidth, phyHeight);
    glutCreateWindow("Arrow Hero");
    init2D();
    glutDisplayFunc(Display);
    glutTimerFunc(timerInterval, Timer, 0);
    glutSpecialFunc(handleKeypress);
    glutMainLoop();
    return 0;
}
