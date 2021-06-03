#define GL_SILENCE_DEPRECATION // to ignore warning messages that occured by mac os
#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <GLUT/glut.h>
#define STANDARD 100
#define TEXTURE GLU_FILL


// 포인터변수필요
GLUquadricObj  *qobj;
float brown_color[3] = {0.53, 0.36, 0.29};

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

void init(void)
{
    glEnable(GL_DEPTH_TEST);
   
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-500.0, 700.0, -500.0, 700.0, 0.0, 1000.0);
    gluLookAt(00, 000, 400,
        0, 0, 0,
        0, 1, 0);
}

int main(int argc , char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(300,300);
    glutCreateWindow("LINE Friends BROWN");
    init();
    glutDisplayFunc(render_brown);
    glutMainLoop();
    return 0;
}
