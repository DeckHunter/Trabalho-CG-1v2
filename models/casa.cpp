#include <iostream>
using namespace std;
#include <gui.h>
#include <objeto.h>

class Casa:public Objeto{
    public:
        void DesenharCasa(float px, float py);
};

void Casa::DesenharCasa(float px, float py){

    glutGUI::trans_obj = true;
    glPushMatrix();
        glTranslatef(px,py,0);
        glScalef(0.5f,0.5f,0.5f);
        //=================| Base |=================//
        GUI::setColor(0.5,0.5,0, 1,true);
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
            GUI::setColor(1,0,0, 1,true);
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
