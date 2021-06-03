#define GL_SILENCE_DEPRECATION // to ignore warning messages that occured by mac os
#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <GLUT/glut.h>
#include <cmath>
#include <cctype>
#define TEXTURE GLU_FILL
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700
#define CAMERA_NEAR 1
#define CAMERA_FAR 1000
#define PI 3.141592

// Mesh 생성용 포인터 변수
GLUquadricObj  *qobj;
// 색상 코드 배열
GLfloat brown[3] = {0.53, 0.36, 0.29};
GLfloat deep_brown[3] = {0.26, 0.24, 0.22};
GLfloat grey[3] = {0.83, 0.84, 0.85};
GLfloat black[3] = {0.0, 0.0, 0.0};

// 마우스 & 키보드 인터랙션 변수
int preX, preY;
float cameraX, cameraY, cameraZ;
float cameraRadius = 600.0;
float alpha = 0.0, theta = 0.0;
float fieldOfVision, aspect;
bool isStart = true;

void updateCameraPosition()
{
    float upX = 0.0, upY = 1.0, upZ = 0.0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fieldOfVision, aspect, CAMERA_NEAR, CAMERA_FAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 관측자 위치 세팅
    cameraX = sin(alpha) * cos(theta) * cameraRadius;
    cameraY = sin(theta) * cameraRadius;
    cameraZ = cos(alpha) * cos(theta) * cameraRadius;
    
    if(theta >= PI / 2.0 && theta < 3.0 * PI / 2.0)
        upY = -1.0;
    else
        upY = 1.0;

    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, upX, upY, upZ);
}

void drawHead()
{
    qobj = gluNewQuadric();

    gluQuadricDrawStyle(qobj, TEXTURE);
    gluSphere(qobj, 50, 20, 20);
}

void drawEar()
{
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, TEXTURE);

    gluSphere(qobj, 18, 10, 10);
}

void drawEarCycle()
{
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, TEXTURE);

    gluSphere(qobj, 14, 10, 10);
}

void drawEye()
{
    qobj = gluNewQuadric();

    gluQuadricDrawStyle(qobj, TEXTURE);
    gluSphere(qobj, 5, 20, 20);
}

void drawMouth()
{
    qobj = gluNewQuadric();

    gluQuadricDrawStyle(qobj, TEXTURE);
    gluSphere(qobj, 10, 20, 20);
}

void drawLip()
{
    glutSolidCube(10);
}

void drawNose()
{
    qobj = gluNewQuadric();

    gluQuadricDrawStyle(qobj, TEXTURE);
    gluSphere(qobj, 3, 20, 20);
}

void drawBody()
{
    qobj = gluNewQuadric();

    gluQuadricDrawStyle(qobj, TEXTURE);
    gluCylinder(qobj, 50, 50, 80, 20, 20);
}

void drawHip()
{
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, TEXTURE);

    gluSphere(qobj, 50, 20, 20);
}

void drawTail()
{
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, TEXTURE);

    gluSphere(qobj, 10, 10, 10);
}

void drawArm()
{
    qobj = gluNewQuadric();

    gluQuadricDrawStyle(qobj, TEXTURE);
    gluCylinder(qobj, 18, 18, 82, 10, 10);
}

void drawHand()
{
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, TEXTURE);

    gluSphere(qobj, 22, 15, 15);
}

void drawLeg()
{
    qobj = gluNewQuadric();

    gluQuadricDrawStyle(qobj, TEXTURE);
    gluCylinder(qobj, 22, 21, 58, 20, 20);
}

void drawFoot()
{
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, TEXTURE);

    gluSphere(qobj, 18, 20, 20);
}

void drawSun()
{
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, TEXTURE);

    gluSphere(qobj, 40, 20, 20);
}

void renderBrown(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    updateCameraPosition();
    
    // 오른쪽 눈 그리기
    glPushMatrix();
    glColor3fv(black);
    glRotatef(-100, 0.0, 1.0, 0.0);
    glTranslated(68, 100, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(0.5, 1.5, 1.5);
    drawEye();
    glPopMatrix();
    
    // 왼쪽 눈 그리기
    glPushMatrix();
    glColor3fv(black);
    glRotatef(-80, 0.0, 1.0, 0.0);
    glTranslated(68, 100, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(0.5, 1.5, 1.5);
    drawEye();
    glPopMatrix();
    
    // 코 그리기
    glPushMatrix();
    glColor3fv(black);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glRotatef(-10, 0.0, 0.0, 1.0);
    glTranslated(56, 95, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(0.5, 1.5, 1.5);
    drawNose();
    glPopMatrix();
    
    // 입 그리기
    glPushMatrix();
    glColor3fv(grey);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glRotatef(-20, 0.0, 0.0, 1.0);
    glTranslated(25, 95, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1.5, 1.8, 2);
    drawMouth();
    glPopMatrix();
    
    glPushMatrix();
    glColor3fv(black);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glRotatef(-18.5, 0.0, 0.0, 1.0);
    glTranslated(37.8, 95, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1.0, 0.4, 1.0);
    drawLip();
    glPopMatrix();
    
    glPushMatrix();
    glColor3fv(black);
    glRotatef(-92.5f, 0.0, 1.0, 0.0);
    glRotatef(-25, 0.0, 0.0, 1.0);
    glTranslated(28, 95, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(-45, 1.0, 0.0, 0.0);
    glScalef(1.0, 0.4, 1.0);
    drawLip();
    glPopMatrix();
    
    glPushMatrix();
    glColor3fv(black);
    glRotatef(-87.5f, 0.0, 1.0, 0.0);
    glRotatef(-25, 0.0, 0.0, 1.0);
    glTranslated(28, 95, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(45, 1.0, 0.0, 0.0);
    glScalef(1.0, 0.4, 1.0);
    drawLip();
    glPopMatrix();
    
    // 머리 그리기
    glPushMatrix();
    glColor3fv(brown);
    glTranslated(0, 100, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1.5, 1.40, 1.35);
    drawHead();
    glPopMatrix();
    
    // 오른쪽 귀 그리기
    glPushMatrix();
    glTranslated(-50, 150, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1.0, 0.8, 1.0);
    drawEar();
    glPopMatrix();
    
    // 왼쪽 귀 그리기
    glPushMatrix();
    glTranslated(50, 150, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1.0, 0.8, 1.0);
    drawEar();
    glPopMatrix();
    
    // 오른쪽 귀 내부 그리기
    glPushMatrix();
    glColor3fv(deep_brown);
    glTranslated(50, 150, 6.5);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1.0, 0.75, 1.0);
    drawEarCycle();
    glPopMatrix();
    
    // 왼쪽 귀 내부 그리기
    glPushMatrix();
    glTranslated(-50, 150, 6.5);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1.0, 0.75, 1.0);
    drawEarCycle();
    glPopMatrix();
    
    // 몸통 그리기
    glPushMatrix();
    glColor3fv(brown);
    glTranslated(0, 50, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1, 0.8, 1);
    drawBody();
    glPopMatrix();
    
    // 엉덩이 그리기
    glPushMatrix();
    glTranslated(0, -30, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glScalef(1, 0.8, 0.4);
    drawHip();
    glPopMatrix();
    
    // 꼬리 그리기
    glPushMatrix();
    glTranslated(0, -20, -45.5);
    glRotatef(90, 1.0, 0.0, 0.0);
    drawTail();
    glPopMatrix();
    
    // 오른팔 그리기
    glPushMatrix();
    glTranslated(-30, 60, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(-30, 0.0, 1.0, 1.0);
    drawArm();
    glPopMatrix();
    
    // 왼팔 그리기
    glPushMatrix();
    glTranslated(30, 60, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(30, 0.0, 1.0, 1.0);
    drawArm();
    glPopMatrix();
    
    // 오른손 그리기
    glPushMatrix();
    glRotatef(-5, 0.0, 0.0, 1.0);
    glTranslated(-55, -10, 5);
    drawHand();
    glPopMatrix();
    
    // 왼손 그리기
    glPushMatrix();
    glRotatef(5, 0.0, 0.0, 1.0);
    glTranslated(55, -10, 5);
    drawHand();
    glPopMatrix();
    
    // 오른다리 그리기
    glPushMatrix();
    glTranslated(-24, -30, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    drawLeg();
    glPopMatrix();
    
    // 왼다리 그리기
    glPushMatrix();
    glTranslated(24, -30, 0);
    glRotatef(90, 1.0, 0.0, 0.0);
    drawLeg();
    glPopMatrix();
    
    // 오른발 그리기
    glPushMatrix();
    glTranslated(-30, -88,5);
    glScalef(1.55, 1, 1.55);
    glRotatef(-45, 0.0, 1.0, 0.0);
    drawFoot();
    glPopMatrix();
    
    // 왼발 그리기
    glPushMatrix();
    glTranslated(30, -88,5);
    glScalef(1.55, 1, 1.55);
    glRotatef(45, 0.0, 1.0, 0.0);
    drawFoot();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y)
{
    // 키 입력
    key = tolower(key);
    
    switch(key) {
        case 'a': // 줌 인
            cameraRadius -= 10.0f;
            break;
        case 'z': // 줌 아웃
            cameraRadius += 10.0f;
            break;
    }
    
    glutPostRedisplay(); // rerender
}

void initializeLighting() {

    GLfloat lightAmbient[4] = {0.3, 0.3, 0.3, 1.0};
    GLfloat lightDiffuse[4] = {0.4, 0.4, 0.4, 1.0};
    GLfloat lightSpecular[4] = {0.4, 0.4, 0.4, 1.0};
    GLfloat lightpos[] = {-600.0, 600.0, 0.0, 1.0};

    glClearColor(0.7f, 0.71f, 0.6f, 0.0f);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmbient);
    glShadeModel(GL_SMOOTH);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    fieldOfVision = 45.0;
}

void mouseMoved(int x, int y)
{
    if(isStart) { // 첫 클릭 시 이동하지 않고 기준점 저장
        preX = x;
        preY = y;
        isStart = false;
    }
    else {
        if(x > preX)
            alpha -= 0.075;
        else if(x < preX)
            alpha += 0.075;

        if(y > preY)
            theta += 0.075;
        else if(y < preY)
            theta -= 0.075;

        if(theta > 2 * PI)
            theta = theta - 2 * PI;
        else if(theta < 0.0)
            theta = 2 * PI - theta;

        if(alpha > 2 * PI)
            alpha = alpha - 2 * PI;
        else if(alpha < 0.0)
            alpha = 2 * PI - alpha;

        isStart = true;

        glutPostRedisplay();
    }
}

void resizeWindow(GLsizei w, GLsizei h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    aspect = (GLfloat)w / (GLfloat)h;
    updateCameraPosition();
}

int main(int argc , char** argv)
{
    glutInit(&argc, argv);

    // 윈도우 세팅
    int screenWidth  = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    int x = (screenWidth - WINDOW_WIDTH) / 2;
    int y = (screenHeight - WINDOW_HEIGHT) / 2;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(x, y);
    glutCreateWindow("LINE Friends BROWN");
    
    // 콜백 등록
    glutDisplayFunc(renderBrown);
    glutKeyboardFunc(keyPressed);
    glutMotionFunc(mouseMoved);
    glutReshapeFunc(resizeWindow);
    initializeLighting();

    glutMainLoop();
    return 0;
}
