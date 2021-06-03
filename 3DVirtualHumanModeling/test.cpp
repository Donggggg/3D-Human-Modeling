#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <GLUT/glut.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <cctype>

#define SLICES  100
#define STACKS  100

#define PI      3.141592

#define WINDOW_WIDTH    700
#define WINDOW_HEIGHT   500

#define CAMERA_NEAR     1
#define CAMERA_FAR      1000

using namespace std;

typedef struct {
    float x, y, z;
} Coordinate;

float fieldOfVision, aspect;

// Coordenadas da câmera
float cameraX, cameraY, cameraZ;

// Coordenadas da fonte de iluminação
float lightX, lightY, lightZ;

// Distância da câmera até o centro do objeto observado
float cameraRadius = 600.0f;

// 'theta' controla o ângulo entre o vetor da câmera (cameraX, cameraY, cameraZ)
float theta = 0.0f;

// 'alpha' controla o ângulo entre a projeção do vetor da câmera (cameraX, cameraY, cameraZ)
float alpha = 0.0f;

// Juntas do pescoço
float neckJointXAxis = 0.0;
float neckJointYAxis = 0.0;
float neckJointZAxis = 0.0;

// Juntas do braço esquerdo
float leftShoulderJointXAxis = 0.0;
float leftShoulderJointZAxis = 0.0;

float leftElbowJointZAxis = 0.0;

// Juntas do braço direito
float rightShoulderJointXAxis = 0.0;
float rightShoulderJointZAxis = 0.0;

float rightElbowJointZAxis = 0.0;

// Juntas da perna esquerda
float leftHipJointXAxis = 0.0;
float leftHipJointZAxis = 0.0;

float leftKneeJointXAxis = 0.0;

// Juntas da perna direita
float rightHipJointXAxis = 0.0;
float rightHipJointZAxis = 0.0;

float rightKneeJointXAxis = 0.0;

float *xRotation, *zRotation, *yRotation;

int previousX;
int previousY;

bool firstClick = true;

// Desenha cabeça e pescoço
void drawHead(float headRadius) {

    float neckLength    = headRadius * 0.6;
    float neckRadius    = headRadius * 0.5;

    float eyeRadius     = 3.0;

    // Desenha junta do pescoço
    glutSolidSphere(neckRadius * 0.8, SLICES, STACKS);

    glPushMatrix();

        glTranslatef(0.0, headRadius + neckLength, 0.0);

        // Desenha cabeça
        glPushMatrix();
            // Aplica uma pequena deformação da esfera para deixá-la um pouco oval
            glScalef(1.05, 1.2, 1.0);
            glutSolidSphere(headRadius, SLICES, STACKS);
        glPopMatrix();

        // Especifica Cor dos Olhos
        glColor3f(0.0, 0.0, 0.0);

        // Desenha olho direito
        glPushMatrix();
            glTranslatef(-headRadius * 0.5, 0.0, headRadius - eyeRadius);
            glutSolidSphere(eyeRadius, SLICES, STACKS);
        glPopMatrix();

        // Desenha olho esquerdo
        glPushMatrix();
            glTranslatef(headRadius * 0.5, 0.0, headRadius - eyeRadius);
            glutSolidSphere(eyeRadius, SLICES, STACKS);
        glPopMatrix();

    glPopMatrix();
}

void updateLightPosition() {

    // Determina a proporção do vetor da câmera que será utilizada
    // como coordenada da fonte de luz, por defaul é 1.0 mas pode ser
    // alterada para que a fonte de luz fique mais próxima ou mais distante
    // do objeto observado
    float proportion = 1.0;

    lightX = cameraX * proportion;
    lightY = cameraY * proportion;
    lightZ = cameraZ * proportion;

    // Especifica a posição da fonte de luz
    GLfloat lightPosition[4] = {lightX, lightY, lightZ, 1.0};

    // Posiciona a fonte de luz
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

}

// Função usada para especificar o volume de visualização
void updateCameraPosition() {

    float upX, upY, upZ;

    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);

    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva
    gluPerspective(fieldOfVision, aspect, CAMERA_NEAR, CAMERA_FAR);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);

    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    // Calcula as coordenadas da câmera de forma que esta se
    // movimenta em uma trajetória esférica
    cameraX = sin(alpha) * cos(theta) * cameraRadius;

    cameraY = sin(theta) * cameraRadius;

    cameraZ = cos(alpha) * cos(theta) * cameraRadius;

    upX = 0.0;
    upY = 1.0;
    upZ = 0.0;

    // Tratamento para manter o vetor UP da câmera de acordo
    // com a cena
    if(theta >= PI / 2.0 && theta < 3.0 * PI / 2.0)
        upY = -1.0;
    else
        upY = 1.0;

    // Especifica posição da câmera e do alvo
    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, upX, upY, upZ);

    updateLightPosition();
}

// Callback que desenha o corpo humano em 3D
void draw() {

    float headRadius            = 22.0;

    float upperArmUpperRadius   = 15.0;
    float upperArmLowerRadius   = 10.0;
    float upperArmLength        = 70.0;

    float lowerArmUpperRadius   = 13.0;
    float lowerArmLowerRadius   = 9.0;
    float lowerArmLength        = 60.0;

    float upperLegUpperRadius   = 20.0;
    float upperLegLowerRadius   = 16.0;
    float upperLegLength        = 60.0;

    float lowerLegUpperRadius   = 17.0;
    float lowerLegLowerRadius   = 13.0;
    float lowerLegLength        = 80.0;

    float shouldersWidth    = 85.0;
    float thoraxWidth       = 70.0;
    float thoraxHeight      = 70.0;

    float waistWidth    = thoraxWidth * 0.7;
    float waistHeight   = thoraxHeight * 0.9;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    updateCameraPosition();

    // Define a cor do tórax
    glColor3f(1.0, 0.0, 0.0);

    glPushMatrix();

        glTranslatef(0.0, thoraxWidth, 0.0);

        // Define cor da cabeça e do pescoço
        glColor3f(0.0, 0.0, 1.0);

        // Posiciona e desenha cabeça
        glPushMatrix();

            // Graus de liberdade da cabeça
            glRotatef(neckJointXAxis, 1.0, 0.0, 0.0);
            glRotatef(neckJointYAxis, 0.0, 1.0, 0.0);
            glRotatef(neckJointZAxis, 0.0, 0.0, 1.0);

            drawHead(headRadius);

        glPopMatrix();

    glutSwapBuffers();
}

// Inicializa parâmetros de iluminação
void initializeLighting() {

    GLfloat lightAmbient[4]     = {0.3, 0.3, 0.3, 1.0};
    GLfloat lightDiffuse[4]     = {0.4, 0.4, 0.4, 1.0};
    GLfloat lightSpecular[4]    = {0.4, 0.4, 0.4, 1.0};

    // Capacidade de brilho do material
    GLfloat materialSpecular[4] = {0.3, 0.3, 0.3, 1.0};

    GLint materialShininess = 60;

    // Especifica que a cor de fundo da janela será PRETA
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmbient);

    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);

    // Define a refletância do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

    // Define a concentração do brilho
    glMateriali(GL_FRONT, GL_SHININESS, materialShininess);

    // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);

    //Habilita o uso de iluminação
    glEnable(GL_LIGHTING);

    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);

    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);

    // Define o 'ângulo de abertura da câmera'
    fieldOfVision = 45.0;
}

// Função callback chamada quando o tamanho da janela é alterado
void resizeWindow(GLsizei w, GLsizei h) {

    // Para previnir uma divisão por zero
    if ( h == 0 ) h = 1;

    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);

    // Calcula a correção de aspecto
    aspect = (GLfloat) w / (GLfloat) h;

    updateCameraPosition();
}

// Callback que trata os eventos de teclado para caracteres com código ASCII
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

// Callback que trata os eventos de mouse quando o mesmo está pressionado
void mousePressed(int x, int y) {

    if(firstClick) {

        previousX = x;
        previousY = y;

        firstClick = false;

    } else {

        // Incrementa ou decrementa os ângulos de rotação da câmera
        // baseado na variação das coordenadas x e de y do mouse

        if(x > previousX)
            alpha -= 0.05;
        else if(x < previousX)
            alpha += 0.05;

        if(y > previousY)
            theta += 0.05;
        else if(y < previousY)
            theta -= 0.05;

        // Mantém os valores dos ângulos da câmera entre 0.0 e 2 * PI
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

// Programa Principal
int main(int argc, char *argv[]) {

    glutInit(&argc, argv);

    // Por default a junta do braço superior direito é selecionada
    xRotation = &rightShoulderJointXAxis;
    yRotation = &rightShoulderJointZAxis;
    zRotation = &rightShoulderJointZAxis;

    // Obtém as dimensões da tela
    int screenWidth  = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    // Coordenadas para posicionar a janela no centro da tela
    int x = (screenWidth - WINDOW_WIDTH) / 2;
    int y = (screenHeight - WINDOW_HEIGHT) / 2;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(x, y);
    glutCreateWindow("Corpo Humando 3D");

    glutDisplayFunc(draw);
    glutKeyboardFunc(keyPressed);
    glutMotionFunc(mousePressed);

    glutReshapeFunc(resizeWindow);

    initializeLighting();

    glutMainLoop();
    return EXIT_SUCCESS;
}