#include <iostream>
using namespace std;
#include <gui.h>
#include <objeto.h>

class Arvore: public Objeto{
    public:
        float tx = 0;
        float ty = 0;
        float tz = 0;

        float sx = 0.5;
        float sy = 0.5;
        float sz = 0.5;

        float rx = 0;
        float ry = 0;
        float rz = 0;

        vector<int> rgbT = {2,1,0};
        vector<int> rgbF = {0,1,0};

        vector<vector<int>> rgbTroncos = {{2,1,0},{1,2,0},{1,1,1}};
        vector<vector<int>> rgbFolhas = {{0,1,0},{1,1,0},{0,1,1}};
    public:
        void DesenharArvore();
};

void Arvore::DesenharArvore(){

    //================| Tronco |================//
        GUI::setColor(rgbT[0],rgbT[1],rgbT[2], 1,true);
        float raio = 0.1f;
        float altura = 0.6;
        int slices = 20;

        glPushMatrix();
            glRotatef(-90, 1.0f, 0.0f, 0.0f);
            glScalef(sx,sy,sz);
            glTranslatef(tx, ty, tz);
            glRotated(rx,1,0,0);
            glRotated(ry,0,1,0);
            glRotated(rz,0,0,1);

            gluCylinder(gluNewQuadric(), raio, raio, 1, slices, 1);
            gluDisk(gluNewQuadric(), 0.0f, raio, slices, 1);
            glTranslatef(0.0f, 0.0f, altura);
            gluDeleteQuadric(gluNewQuadric());
            glPushMatrix();
            //================| Folhas |================//
                glRotatef(90, 1.0f, 0.0f, 0.0f);
                GUI::setColor(rgbF[0],rgbF[1],rgbF[2],true);
                glutGUI:: slices = 5;
                float raioSphere = 0.2f;
                //Base 1
                    GUI::drawSphere(0.0f, 1.0f,0.0f,raioSphere);
                //Base 2
                    GUI::drawSphere(0.2f, 0.8f,0.0f,raioSphere);
                    GUI::drawSphere(-0.2f, 0.8f,0.0f,raioSphere);
                    GUI::drawSphere(0.0f, 0.8f,0.2f,raioSphere);
                    GUI::drawSphere(0.0f, 0.8f,-0.2f,raioSphere);
                //Base 3
                    GUI::drawSphere(0.4f, 0.5f,0.0f,raioSphere);
                    GUI::drawSphere(0.2f, 0.5f,0.2f,raioSphere);
                    GUI::drawSphere(-0.4f, 0.5f,0.0f,raioSphere);
                    GUI::drawSphere(-0.2f, 0.5f,-0.2f,raioSphere);
                    GUI::drawSphere(0.0f, 0.5f,0.4f,raioSphere);
                    GUI::drawSphere(-0.2f, 0.5f,0.2f,raioSphere);
                    GUI::drawSphere(0.0f, 0.5f,-0.4f,raioSphere);
                    GUI::drawSphere(0.2f, 0.5f,-0.2f,raioSphere);
                //Base 4
                //==========================================//
            glPopMatrix();
        glPopMatrix();
    //==========================================//
}
