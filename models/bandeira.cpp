#include <iostream>
using namespace std;
#include <gui.h>
#include <objeto.h>

class Bandeira:public Objeto{
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

        float ryF = 0;

        vector<int> rgbM = {2,1,0};
        vector<int> rgbB = {0,1,0};

        vector<vector<int>> rgbMastros= {{2,1,0},{1,2,0},{1,1,1}};
        vector<vector<int>> rgbBandeiras = {{0,1,0},{1,1,0},{0,1,1}};
    public:
        void DesenharBandeira();
};

void Bandeira::DesenharBandeira(){

        GUI::setColor(rgbM[0],rgbM[1],rgbM[2], 1,true);
        float raio = 0.03f;
        int slices = 20;

        //================| Cano |================//
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
            //================| Bandeira |================//
            GUI::setColor(rgbB[0],rgbB[1],rgbB[2], 1,true);
            glPushMatrix();
                glRotatef(90, 1.0f, 0.0f, 0.0f);
                glTranslatef(0, 0.5, 0);
                glRotatef((ry + ryF), 0.0f, 1.0f, 0.0f);
                glBegin(GL_QUADS);
                    glVertex3f( 0.5f, 0.5f, 0.0f);
                    glVertex3f( 0.0f, 0.5f, 0.0f);
                    glVertex3f( 0.0f, 0.0f, 0.0f);
                    glVertex3f( 0.5f, 0.0f, 0.0f);
                glEnd();
            glPopMatrix();
            //============================================//
        glPopMatrix();
       //==========================================//

}
