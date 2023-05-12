#include <iostream>
using namespace std;
#include <gui.h>
#include <objeto.h>
#include <vector>

class Casa2:public Objeto{ 
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

        vector<int> rgbB = {2,1,0};
        vector<int> rgbT = {0,1,0};

        vector<vector<int>> rgbBases = {{2,1,0},{1,2,0},{1,1,1}};
        vector<vector<int>> rgbTelhados = {{0,1,0},{1,1,0},{0,1,1}};

    public:
        void DesenharCasinha();
};

void Casa2::DesenharCasinha(){

    glPushMatrix();

        glTranslatef(tx,ty,tz);
        glScalef(sx,sy,sz);
        glRotated(rx,1,0,0);
        glRotated(ry,0,1,0);
        glRotated(rz,0,0,1);
        //=================| Base |=================//
        GUI::setColor(rgbB[0],rgbB[1],rgbB[0], 1,true);
        glBegin ( GL_QUADS );
            // Frente
            glVertex3f(-1.0f, 0.0f,  1.0f);
            glVertex3f( 1.0f, 0.0f,  1.0f);
            glVertex3f( 1.0f,  1.0f,  1.0f);
            glVertex3f(-1.0f,  1.0f,  1.0f);
            // Tras
            glVertex3f(-1.0f, 0.0f, -1.0f);
            glVertex3f(-1.0f,  1.0f, -1.0f);
            glVertex3f( 1.0f,  1.0f, -1.0f);
            glVertex3f( 1.0f, 0.0f, -1.0f);
            // Superior
            glVertex3f(-1.0f,  1.0f, -1.0f);
            glVertex3f(-1.0f,  1.0f,  1.0f);
            glVertex3f( 1.0f,  1.0f,  1.0f);
            glVertex3f( 1.0f,  1.0f, -1.0f);
            // Inferior
            glVertex3f(-1.0f, 0.0f, -1.0f);
            glVertex3f( 1.0f, 0.0f, -1.0f);
            glVertex3f( 1.0f, 0.0f,  1.0f);
            glVertex3f(-1.0f, 0.0f,  1.0f);
            // Lateral Direita
            glVertex3f( 1.0f, 0.0f, -1.0f);
            glVertex3f( 1.0f,  1.0f, -1.0f);
            glVertex3f( 1.0f,  1.0f,  1.0f);
            glVertex3f( 1.0f, 0.0f,  1.0f);
            // Lateral Esquerda
            glVertex3f(-1.0f, 0.0f, -1.0f);
            glVertex3f(-1.0f, 0.0f,  1.0f);
            glVertex3f(-1.0f,  1.0f,  1.0f);
            glVertex3f(-1.0f,  1.0f, -1.0f);
        glEnd();
        //==========================================//
        //================| Telhado |===============//
            GUI::setColor(rgbT[1],rgbT[0],rgbT[2], 1,true);
            //Frontal
            glBegin(GL_POLYGON);
                glNormal3f(0,1,1);
                glVertex3f(1,1,1);
                glVertex3f(0,2,0);
                glVertex3f(-1,1,1);
            glEnd();

            //Trazeira
            glBegin(GL_POLYGON);
                glNormal3f(0,2,-1);
                glVertex3f(-1,1,-1);
                glVertex3f(0,2,0);
                glVertex3f(1,1,-1);
            glEnd();
            //Lateral Esquerda
            glBegin(GL_POLYGON);
                glNormal3f(-1,2,0);
                glVertex3f(-1,1,1);
                glVertex3f(0,2,0);
                glVertex3f(-1,1,-1);
            glEnd();

            //Lateral Direita
            glBegin(GL_POLYGON);
                glNormal3f(1,2,0);
                glVertex3f(1,1,1);
                glVertex3f(1,1,-1);
                glVertex3f(0,2,0);
            glEnd();

            //Inferior
            glBegin(GL_POLYGON);
                glNormal3f(0,0,0);
                glVertex3f(1,1,1);
                glVertex3f(-1,1,1);
                glVertex3f(-1,1,-1);
                glVertex3f(1,1,-1);
            glEnd();
        //==========================================//
        //=================| Porta |================//
            GUI::setColor(1,0.7,0, 1,true);
            glBegin(GL_QUADS);
                glVertex3f(0.8f, 0.0f, 1.001f);
                glVertex3f(0.4f, 0.0f, 1.001f);
                glVertex3f(0.4f, 0.7f, 1.001f);
                glVertex3f(0.8f,0.7f, 1.001f);
            glEnd();
        //==========================================//
    glPopMatrix();

}
