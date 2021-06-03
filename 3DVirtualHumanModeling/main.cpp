#define GL_SILENCE_DEPRECATION // to ignore warning messages that occured by mac os
#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <GLUT/glut.h>
#include <cmath>
#include <cctype>
#define STANDARD 100
#define SIZE 600
#define TEXTURE GLU_FILL
#define PI      3.141592
#define WINDOW_WIDTH    700
#define WINDOW_HEIGHT   500

#define CAMERA_NEAR     1
#define CAMERA_FAR      1000


// 포인터변수필요
GLUquadricObj  *qobj;
int ViewX = 0, ViewY = 0;
float brown_color[3] = {0.53, 0.36, 0.29};

// 모션 추가
float XAxis = 0.0;
float ZAxis = 0.0;
float *xRotation, *zRotation, *yRotation;
float cameraX, cameraY, cameraZ;
float lightX, lightY, lightZ;
float cameraRadius = 600.0f;
float theta = 0.0f;
float alpha = 0.0f;
float fieldOfVision, aspect;
bool firstClick = true;

int previousX;
int previousY;


void updateLightPosition() {

    float proportion = 1.0;

    lightX = cameraX * proportion;
    lightY = cameraY * proportion;
    lightZ = cameraZ * proportion;

    GLfloat lightPosition[4] = {lightX, lightY, lightZ, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

}

void updateCameraPosition() {

    float upX, upY, upZ;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fieldOfVision, aspect, CAMERA_NEAR, CAMERA_FAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    cameraX = sin(alpha) * cos(theta) * cameraRadius;
    cameraY = sin(theta) * cameraRadius;
    cameraZ = cos(alpha) * cos(theta) * cameraRadius;

    upX = 0.0;
    upY = 1.0;
    upZ = 0.0;

    if(theta >= PI / 2.0 && theta < 3.0 * PI / 2.0)
        upY = -1.0;
    else
        upY = 1.0;

    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, upX, upY, upZ);

    printf("c: %f %f %f\n", cameraX, cameraY, cameraZ);
    printf("u: %f %f %f\n", upX, upY, upZ);
    updateLightPosition();
}

void draw_head()
{
    qobj = gluNewQuadric();

    gluQuadricDrawStyle(qobj, TEXTURE);
    gluSphere(qobj, 150, 20, 20);
}

void draw_body()
{
    qobj = gluNewQuadric();

    gluQuadricDrawStyle(qobj, TEXTURE);
    gluCylinder(qobj, 125, 125, 350, 20, 20);
}

void draw_hip()
{
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, TEXTURE);

    gluSphere(qobj, 125, 10, 10);
}

void draw_ear()
{
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, TEXTURE);

    gluSphere(qobj, 50, 10, 10);
}

void draw_arm()
{
    qobj = gluNewQuadric();

    gluQuadricDrawStyle(qobj, TEXTURE);
    gluCylinder(qobj, 50, 50, 250, 10, 10);
}

void draw_hand()
{
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, TEXTURE);

    gluSphere(qobj, 60, 15, 15);
}

void draw_leg()
{
    qobj = gluNewQuadric();

    gluQuadricDrawStyle(qobj, TEXTURE);
    gluCylinder(qobj, 50, 50, 225, 10, 10);
}

void draw_foot()
{
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, TEXTURE);

    gluSphere(qobj, 50, 20, 20);
}

void render_brown(void)
{
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    updateCameraPosition();

//    gluLookAt(00, 000, 00,
//        X, Y, 1.0,
//        0, 1, 0);
    
    // 머리 그리기
    glPushMatrix();
    glRotatef(90, 0.0, 1.0, 0.0);
    glColor3fv(brown_color);
    glTranslated(0, 250 + STANDARD, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1.5, 1.5, 1.35);
    draw_head();
    glPopMatrix();
    
    // 왼귀 그리기
    glPushMatrix();
    glTranslated(-150, 420 + STANDARD, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    draw_ear();
    glPopMatrix();
    
    // 오른귀 그리기
    glPushMatrix();
    glTranslated(150, 420 + STANDARD, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    draw_ear();
    glPopMatrix();
    
    // 몸통 그리기
    glPushMatrix();
    glTranslated(0, 150 + STANDARD, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    draw_body();
    glPopMatrix();
    
    // 엉덩이 그리기
    glPushMatrix();
    glTranslated(0, -STANDARD, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1, 1, 0.3);
    draw_hip();
    glPopMatrix();
    
    // 왼팔 그리기
    glPushMatrix();
    glTranslated(-80, 60 + STANDARD, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(-45, 0.0, 1.0, 1.0);
    draw_arm();
    glPopMatrix();
    
    // 오른팔 그리기
    glPushMatrix();
    glTranslated(80, 60 + STANDARD, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(45, 0.0, 1.0, 1.0);
    draw_arm();
    glPopMatrix();
    
    // 왼손 그리기
    glPushMatrix();
    glRotatef(45, 0.0, 1.0, 0.0);
    glTranslated(-180, 30 - STANDARD, -120);
    draw_hand();
    glPopMatrix();
    
    // 오른손 그리기
    glPushMatrix();
    glRotatef(-45, 0.0, 1.0, 0.0);
    glTranslated(180, 30 - STANDARD, -120);
    draw_hand();
    glPopMatrix();
    
    // 왼다리 그리기
    glPushMatrix();
    glTranslated(-75, - STANDARD, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    draw_leg();
    glPopMatrix();
    
    // 오른다리 그리기
    glPushMatrix();
    glTranslated(75, - STANDARD, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    draw_leg();
    glPopMatrix();
    
    // 오른발 그리기
    glPushMatrix();
    glTranslated(-95, -205 - STANDARD, 20);
    glScalef(1.5, 1, 1.5);
    glRotatef(-45, 0.0, 1.0, 0.0);
    draw_foot();
    glPopMatrix();
    
    // 왼발 그리기
    glPushMatrix();
    glTranslated(95, -205 - STANDARD, 20);
    glScalef(1.5, 1, 1.5);
    glRotatef(45, 0.0, 1.0, 0.0);
    draw_foot();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void MyMouseMove(GLint X, GLint Y) {
    ViewX = X;
    ViewY = Y;
    glutPostRedisplay();
}

void keyPressed(unsigned char key, int x, int y) {
    key = tolower(key);
    if(xRotation != NULL && yRotation != NULL && zRotation != NULL) {
        switch(key) {
            case 'a':
                cameraRadius -= 10.0f;
                break;
            case 'z':
                cameraRadius += 10.0f;
                break;
        }
        glutPostRedisplay();
    }
}

void initializeLighting() {

    GLfloat lightAmbient[4]     = {0.3, 0.3, 0.3, 1.0};
    GLfloat lightDiffuse[4]     = {0.4, 0.4, 0.4, 1.0};
    GLfloat lightSpecular[4]    = {0.4, 0.4, 0.4, 1.0};
    GLfloat materialSpecular[4] = {0.3, 0.3, 0.3, 1.0};
    GLint materialShininess = 60;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmbient);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMateriali(GL_FRONT, GL_SHININESS, materialShininess);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    fieldOfVision = 45.0;
}

void resizeWindow(GLsizei w, GLsizei h) {
    if ( h == 0 ) h = 1;

    glViewport(0, 0, w, h);
    aspect = (GLfloat) w / (GLfloat) h;
    updateCameraPosition();
}


void mousePressed(int x, int y) {

    if(firstClick) {

        previousX = x;
        previousY = y;

        firstClick = false;

    } else {

        if(x > previousX)
            alpha -= 0.05;
        else if(x < previousX)
            alpha += 0.05;

        if(y > previousY)
            theta += 0.05;
        else if(y < previousY)
            theta -= 0.05;

        if(theta > 2 * PI)
            theta = theta - 2 * PI;
        else if(theta < 0.0)
            theta = 2 * PI - theta;

        if(alpha > 2 * PI)
            alpha = alpha - 2 * PI;
        else if(alpha < 0.0)
            alpha = 2 * PI - alpha;

        firstClick = true;

        glutPostRedisplay();
    }
}

int main(int argc , char** argv)
{
    glutInit(&argc, argv);
    
    xRotation = &XAxis;
    yRotation = &ZAxis;
    zRotation = &ZAxis;
    
    int screenWidth  = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    int x = (screenWidth - WINDOW_WIDTH) / 2;
    int y = (screenHeight - WINDOW_HEIGHT) / 2;

    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(x, y);
    glutCreateWindow("LINE Friends BROWN");
    
//    init();
    glutDisplayFunc(render_brown);
    glutKeyboardFunc(keyPressed);
    glutMotionFunc(MyMouseMove);
    glutReshapeFunc(resizeWindow);
    initializeLighting();

    glutMainLoop();
    return 0;
}
//
//
//void init(void)
//{
//    glEnable(GL_DEPTH_TEST);
//
//    glClearColor(1.0,1.0,1.0,0.0);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-500.0, 700.0, -500.0, 700.0, -1000.0, 1000.0);
//
////    gluLookAt(00, 000, 400,
////        0, 0, 0,
////        0, 1, 0);
//}
