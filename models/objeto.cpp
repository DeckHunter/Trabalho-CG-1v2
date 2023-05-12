#include <iostream>
using namespace std;
#include <gui.h>
#include <objeto.h>

//============| Gets |============
//Rotação
Vetor3D Objeto::returnRotacaoXyz(){
    Vetor3D xyz = Vetor3D(Objeto::objetoRx,Objeto::objetoRy,Objeto::objetoRz);
    return xyz;
}
//Translação
Vetor3D Objeto::returnTranslacaoXyz(){
    Vetor3D xyz = Vetor3D(Objeto::objetoTx,Objeto::objetoTy,Objeto::objetoTz);
    return xyz;
}
//Escala
Vetor3D Objeto::returnScaleXyz(){
    Vetor3D xyz = Vetor3D(Objeto::objetoSx,Objeto::objetoSy,Objeto::objetoSz);
    return xyz;
}
//============| Sets |============
//Rotação
void Objeto::setRotacaoX(float x, float y, float z){
    Objeto::objetoRx = x;
    Objeto::objetoRy = y;
    Objeto::objetoRz = z;
}
//Translação
void Objeto::setTranslacaoX(float x, float y, float z){
    Objeto::objetoTx = x ;
    Objeto::objetoTy = y ;
    Objeto::objetoTz = z ;
}
//Escala
void Objeto::setScaleX(float x, float y, float z){
    Objeto::objetoSx = x ;
    Objeto::objetoSy = y ;
    Objeto::objetoSz = z ;
}
//info
string Objeto::getNome(){
    return Objeto::nome;
}
long Objeto::getId(){
    return Objeto::id;
}
vector<int> Objeto::getColorRGB(){
    return Objeto::colorRGB;
}
bool Objeto::getSelect(){
    return Objeto::select;
}
