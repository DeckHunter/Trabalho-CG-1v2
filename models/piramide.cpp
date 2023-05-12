#include <iostream>
using namespace std;
#include <gui.h>
#include <objeto.h>

class Piramide: public Objeto{
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

        vector<vector<int>> rgbBases = {{2,1,0},{1,2,0},{1,1,1}};
        vector<vector<int>> rgbTelhados = {{0,1,0},{1,1,0},{0,1,1}};
    public:
        void DesenharPiramide();
};

void Piramide::DesenharPiramide(){

    glPushMatrix();
        glTranslatef(tx,ty,tz);
        glScalef(sx,sy,sz);
        glRotated(rx,1,0,0);
        glRotated(ry,0,1,0);
        glRotated(rz,0,0,1);
        //Frontal
        GUI::setColor(rgbT[1],rgbT[0],rgbT[2], 1,true);
        glBegin(GL_POLYGON);
            glNormal3f(0,1,1);
            glVertex3f(1,1,1);
            glVertex3f(0,2,0);
            glVertex3f(-1,1,1);
        glEnd();

        //Trazeira
        GUI::setColor(rgbT[1],rgbT[0],rgbT[2], 1,true);
        glBegin(GL_POLYGON);
            glNormal3f(0,2,-1);
            glVertex3f(-1,1,-1);
            glVertex3f(0,2,0);
            glVertex3f(1,1,-1);
        glEnd();
        //Lateral Esquerda
        GUI::setColor(rgbF[1],rgbF[0],rgbF[2], 1,true);
        glBegin(GL_POLYGON);
            glNormal3f(-1,2,0);
            glVertex3f(-1,1,1);
            glVertex3f(0,2,0);
            glVertex3f(-1,1,-1);
        glEnd();

        //Lateral Direita
        GUI::setColor(rgbF[1],rgbF[0],rgbF[2], 1,true);
        glBegin(GL_POLYGON);
            glNormal3f(1,2,0);
            glVertex3f(1,1,1);
            glVertex3f(1,1,-1);
            glVertex3f(0,2,0);
        glEnd();
        //Inferior
        GUI::setColor(rgbF[1],rgbF[0],rgbF[2], 1,true);
        glBegin(GL_POLYGON);
            glNormal3f(0,0,0);
            glVertex3f(1,1,1);
            glVertex3f(-1,1,1);
            glVertex3f(-1,1,-1);
            glVertex3f(1,1,-1);
        glEnd();
    glPopMatrix();
}
