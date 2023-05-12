#ifndef OBJETO_H
#define OBJETO_H

#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include "CameraDistante.h"
using namespace std;
#include <vector>


class Objeto{
    public:
        //Rotação
        float objetoRx;
        float objetoRy;
        float objetoRz;

        //Translação
        float objetoTx;
        float objetoTy;
        float objetoTz;

        //Escala
        float objetoSx;
        float objetoSy;
        float objetoSz;

        //Infi
        string nome;
        long id;
        vector<int> colorRGB = {1,2,3};
        bool select = false;
    public:
        //Gets
            //Rotação
            Vetor3D returnRotacaoXyz();
            //Translação
            Vetor3D returnTranslacaoXyz();
            //Escala
            Vetor3D returnScaleXyz();
        //Sets
            //Rotação
            void setRotacaoX(float x, float y, float z);
            //Translação
            void setTranslacaoX(float x, float y, float z);
            //Escala
            void setScaleX(float x, float y, float z);
        //Info
            string getNome();
            long getId();
            vector<int> getColorRGB();
            bool getSelect();
};

#endif // OBJETO_H
