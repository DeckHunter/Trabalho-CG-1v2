#include <iostream>
using namespace std;
#include <gui.h>
#include <objeto.h>

class Poste: public Objeto{
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

        float sxF = 0;

        bool isShadowVisible = true;

        vector<int> rgbM = {2,1,0};
        vector<int> rgbL = {0,1,0};

        vector<vector<int>> rgbMastros= {{2,1,0},{1,2,0},{1,1,1}};
        vector<vector<int>> rgbLuzes = {{0,1,0},{1,1,0},{0,1,1}};
    public:
        void DesenharPoste();
        void mostrarSombra();
};
void Poste::mostrarSombra() {
    this->isShadowVisible = !this->isShadowVisible;
}
void Poste::DesenharPoste(){
    GUI::setColor(rgbM[0],rgbM[1],rgbM[2], 1,true);

    float raio = 0.03f;
    int slices = 20;


    //================| Cano - 1 |================//
    glPushMatrix();

        glTranslatef(tx, ty, tz);
        glScalef(sx,sy,sz);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);

        glRotated(rx,1,0,0);
        glRotated(ry,0,1,0);
        glRotated(rz,0,0,1);

        gluCylinder(gluNewQuadric(), raio, raio, 1, slices, 1);
        gluDisk(gluNewQuadric(), 0.0f, raio, slices, 1);
        gluDeleteQuadric(gluNewQuadric());
        //================| Cano - 2 |================//
        GUI::setColor(rgbM[0],rgbM[1],rgbM[2], 1,true);
        glPushMatrix();
            glRotatef(90, 1.0f, 0.0f, 0.0f);
            glTranslatef(0, 1, 0);
            glRotatef(rx, 0.0f, 1.0f, 0.0f);
            glScalef(1,1,1);

            gluCylinder(gluNewQuadric(), raio, raio, 1, slices, 1);
            gluDisk(gluNewQuadric(), 0.0f, raio, slices, 1);
            gluDeleteQuadric(gluNewQuadric());
            //================| Cano - 3 |================//
            glPushMatrix();
                GUI::setColor(rgbM[0],rgbM[1],rgbM[2], 1,true);
                glRotatef(90, 1.0f, 0.0f, 0.0f);
                glTranslatef(0, 1, 0);
                glScalef(sx,sy,sz);
                gluCylinder(gluNewQuadric(), raio, raio, 1, slices, 1);
                gluDisk(gluNewQuadric(), 0.0f, raio, slices, 1);
                gluDeleteQuadric(gluNewQuadric());
                //================| Luz |================//
                glPushMatrix();
                    glRotatef(90, 1.0f, 0.0f, 0.0f);
                    GUI::setColor(rgbL[0],rgbL[1],rgbL[2], 1,true);
                    glutGUI:: slices = 15;
                    float raioSphere = 0.2f;
                    GUI::drawSphere(0.0f, 1.0f,0.0f,(sx + sxF)*raioSphere);
                glPopMatrix();
                //=======================================//
            glPopMatrix();
            //============================================//
        glPopMatrix();
        //============================================//
    glPopMatrix();
   //==========================================//
}
