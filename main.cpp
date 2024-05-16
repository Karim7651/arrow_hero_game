#ifdef APPLE
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

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


void init2D() {
    //background
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

//draw smallRedCircle
void smallRedCircle(float cx,float cy,float r, int num_segments){
    //smallRedCircle(50,50,2,50);
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
    //drawSquare(50,50,3);
  glColor3f(227.0f / 255.0f, 170.0f / 255.0f, 204.0f / 255.0f);

  glLineWidth(3.0f);

  glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x, y + size);
  glEnd();
}
void drawTriangle(float x, float y,float size) {
    //drawTriangle(50,50,3);
    // Set the color
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
//text
void printSome(char *str, int x, int y) {

    glColor3f(1, 1, 1);
    glRasterPos2d(x, y);
    for (int i = 0; i < strlen(str); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
    glFlush();
}
void scoreTime(){
    printSome("Score : ",2,95);
    printSome("Time : ",90,95);
}
void drawPatternBackground(){
    int counter = 0;
    for(int i = 7 ; i < logHeight - 10 ; i+=20){
        for(int j = 7 ; j < logWidth - 10 ; j += 20){
            if(j>=40 && j <=65 && i>=55 && i <=90){
                counter++;
                continue;
            }
            if(counter ==0){
                counter++;
                //draw circle
                smallRedCircle(j,i,2,50);
            }else if(counter == 1){
                counter++;
                //draw x
                drawX(j,i,3,30);
            }else if(counter == 2){
                //draw triangle
                counter++;
                drawTriangle(j,i,3);
            }else{
                //draw square
                drawSquare(j,i,3);
                counter = 0;
            }
        }
    }
}
void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPatternBackground();
    DrawColoredCircle(50,75,15,1500);
    scoreTime();
    glutSwapBuffers();
    glFlush();
}
int main(int argc, char *argv[])
{   glutInit( &argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition( 100, 100);
    glutInitWindowSize(phyWidth, phyHeight);
    glutCreateWindow("phase 1");
    init2D();
    glutDisplayFunc(Display);
    glutMainLoop();
}
