#include <iostream>
#include <cstdlib>
#include <fstream>>
using namespace std;

#include<gui.h>
#include<objeto.h>
#include<models/arvore.cpp>
#include<models/bandeira.cpp>
#include<models/casa2.cpp>
#include<models/poste.cpp>
#include<models/piramide.cpp>

#include <algorithm>
#include <vector>

ofstream dbMapa;
ifstream dbMapaE;
string linha;
vector<string> dbObjetoAtual;

float x = 0.0;

float px;
float py;
float pz;
float raio = 0.5;

float rx;
float ry;
float rz;

float sx = 0.5;
float sy = 0.5;
float sz = 0.5;

float theta;
float thetaG;

int posCameraAtual = 0;
int posAtual = 0;
int posAtualNaLista = 0;
int posAtualCoresPrimarias = 0;
int posAtualCoresSecundarias = 0;
string objSelecionado;
bool executar = false;
bool editarFilho = false;
bool abrirSelecionarNovoObj = false;
bool abrirSelecionarCameraObj = false;
bool abrirSelecionarObjEmCena = false;
bool abrirSelecionarCorP = false;
bool abrirSelecionarCorS = false;

string action = "null";

//====================| Index |====================
int indexC = 0;
int indexA = 0;
int indexP = 0;
int indexB = 0;
int indexPI = 0;

//====================| Lista De Objetos |====================

vector<Casa2*> casas;
vector<Arvore*> arvores;
vector<Poste*> postes;
vector<Bandeira*> bandeiras;
vector<Piramide*> piramides;
vector<Objeto> idsObjetos;

vector<int> objetosEscolhas = {0,1,2,3,4};
vector<int> cameras {0,1,2,3,4,5,6};

//====================| Objetos |====================

Casa2 casaObj;
Bandeira bandeiraObj;
Arvore arvoreObj;
Poste posteObj;
Piramide piramideObj;
//====================| Objetos Aux|====================

Casa2 casaObjAux;
Bandeira bandeiraObjAux;
Arvore arvoreObjAux;
Poste posteObjAux;
Piramide piramideObjAux;

void configs(){

    GUI::setLight(0, 0,2,0, true, false);
    GUI::setColor(0.4,0.6,0);
    GUI::drawFloor(15,15);
    GUI::drawOrigin(0.5);
    glDisable(GL_CULL_FACE);

}

void desenharTodosObjetosEmCena(){
    for (int i = 0; i < casas.size(); i++) {
        if(casas[i]->getSelect() == true){
            casaObjAux = *casas[i];
            casaObjAux.rgbT = casaObjAux.getColorRGB();
            casaObjAux.rgbB = casaObjAux.getColorRGB();
            casaObjAux.DesenharCasinha();
        }else{
            casaObjAux = *casas[i];
            casaObjAux.DesenharCasinha();
        }
    }
    for (int i = 0; i < piramides.size(); i++) {
        if(piramides[i]->getSelect() == true){
            piramideObjAux = *piramides[i];
            piramideObjAux.rgbT = piramideObjAux.getColorRGB();
            piramideObjAux.rgbF = piramideObjAux.getColorRGB();
            piramideObjAux.DesenharPiramide();
        }else{
            piramideObjAux = *piramides[i];
            piramideObjAux.DesenharPiramide();
        }
    }
    for (int i = 0; i < postes.size(); i++) {
        if(postes[i]->getSelect() == true){
            posteObjAux = *postes[i];
            posteObjAux.rgbM = posteObjAux.getColorRGB();
            posteObjAux.rgbL = posteObjAux.getColorRGB();
            posteObjAux.DesenharPoste();
        }else{
            posteObjAux = *postes[i];
            posteObjAux.DesenharPoste();
        }
    }
    for (int i = 0; i < bandeiras.size(); i++) {
        if(bandeiras[i]->getSelect() == true){
            bandeiraObjAux = *bandeiras[i];
            bandeiraObjAux.rgbM = bandeiraObjAux.getColorRGB();
            bandeiraObjAux.rgbB = bandeiraObjAux.getColorRGB();
            bandeiraObjAux.DesenharBandeira();
        }else{
            bandeiraObjAux = *bandeiras[i];
            bandeiraObjAux.DesenharBandeira();
        }
    }
    for (int i = 0; i < arvores.size(); i++) {
        if(arvores[i]->getSelect() == true){
            arvoreObjAux = *arvores[i];
            arvoreObjAux.rgbT = arvoreObjAux.getColorRGB();
            arvoreObjAux.rgbF = arvoreObjAux.getColorRGB();
            arvoreObjAux.DesenharArvore();
        }else{
            arvoreObjAux = *arvores[i];
            arvoreObjAux.DesenharArvore();
        }
    }
}

void mudarCorP(string obj){
    if(obj == "Casa"){
        for (int i = 0; i < casas.size(); i++) {
            if(casas[i]->getSelect() == true){
                casas[i]->rgbB = casas[i]->rgbBases[posAtualCoresPrimarias];
            }
        }
    }
    if(obj == "Piramide"){
        for (int i = 0; i < piramides.size(); i++) {
            if(piramides[i]->getSelect() == true){
                piramides[i]->rgbT = piramides[i]->rgbBases[posAtualCoresPrimarias];
            }
        }
    }
    if(obj == "Poste"){
        for (int i = 0; i < postes.size(); i++) {
            if(postes[i]->getSelect() == true){
                postes[i]->rgbM = postes[i]->rgbMastros[posAtualCoresPrimarias];
            }
        }
    }
    if(obj == "Bandeira"){
        for (int i = 0; i < bandeiras.size(); i++) {
            if(bandeiras[i]->getSelect() == true){
                bandeiras[i]->rgbM = bandeiras[i]->rgbMastros[posAtualCoresPrimarias];
            }
        }
    }
    if(obj == "Arvore"){
        for (int i = 0; i < arvores.size(); i++) {
            if(arvores[i]->getSelect() == true){
                arvores[i]->rgbT = arvores[i]->rgbTroncos[posAtualCoresPrimarias];
            }
        }
    }
}

void mudarCorS(string obj){
    if(obj == "Casa"){
        for (int i = 0; i < casas.size(); i++) {
            if(casas[i]->getSelect() == true){
                casas[i]->rgbT = casas[i]->rgbTelhados[posAtualCoresSecundarias];
            }
        }
    }
    if(obj == "Poste"){
        for (int i = 0; i < postes.size(); i++) {
            if(postes[i]->getSelect() == true){
                postes[i]->rgbL = postes[i]->rgbLuzes[posAtualCoresSecundarias];
            }
        }
    }
    if(obj == "Piramide"){
        for (int i = 0; i < piramides.size(); i++) {
            if(piramides[i]->getSelect() == true){
                piramides[i]->rgbF = piramides[i]->rgbTelhados[posAtualCoresPrimarias];
            }
        }
    }
    if(obj == "Bandeira"){
        for (int i = 0; i < bandeiras.size(); i++) {
            if(bandeiras[i]->getSelect() == true){
                bandeiras[i]->rgbB = bandeiras[i]->rgbBandeiras[posAtualCoresSecundarias];
            }
        }
    }
    if(obj == "Arvore"){
        for (int i = 0; i < arvores.size(); i++) {
            if(arvores[i]->getSelect() == true){
                arvores[i]->rgbF = arvores[i]->rgbFolhas[posAtualCoresSecundarias];
            }
        }
    }
}
void desenha() {
    GUI::displayInit();

    switch (posCameraAtual) {
        case 0:
            CameraJogo();
            break;
        case 1:
            gluLookAt(0,5,8 ,  0,0,0 , 0,1,0);
            break;
        case 2:
            gluLookAt(10,5,8 ,  0,0,0 , 0,1,0);
            break;
        case 3:
            gluLookAt(-10,5,8 ,  0,0,0 , 0,1,0);
            break;
        case 4:
            gluLookAt(0,5,-10 ,  0,0,0 , 0,1,0);
            break;
        case 5:
            gluLookAt(0,1,5 ,  0,2,0 , 0,1,0);
            break;
        case 6:
            gluLookAt(6,8,0 ,  0,0,0 , 0,1,0);
            break;
    }
    configs();

    theta += 1 * glutGUI::daz;
    x += 10;

    px += 1.5*glutGUI::dtx;
    py += 1.5*glutGUI::dty;
    pz += 3*glutGUI::dtz;

    rx += 10.5*glutGUI::dax;
    ry += 10.5*glutGUI::day;
    rz += 10*glutGUI::daz;

    sx += 1.5*glutGUI::dsx;
    sy += 1.5*glutGUI::dsy;
    sz += 1.5*glutGUI::dsz;

    if(executar){
        glutGUI::trans_obj = true;
    }else{
        glutGUI::trans_obj = false;
    }

    desenharTodosObjetosEmCena();

    if(action == "translação"){
        if(objSelecionado == "Casa"){
            casas[indexC]->tx = px;
            casas[indexC]->ty = py;
            casas[indexC]->tz = pz;
        }
        if(objSelecionado == "Piramide"){
            piramides[indexPI]->tx = px;
            piramides[indexPI]->ty = py;
            piramides[indexPI]->tz = pz;
        }
        if(objSelecionado == "Poste"){
            postes[indexP]->tx = px;
            postes[indexP]->ty = py;
            postes[indexP]->tz = pz;
        }
        if(objSelecionado == "Arvore"){
            arvores[indexA]->tx = px;
            arvores[indexA]->ty = py;
            arvores[indexA]->tz = pz;
        }
        if(objSelecionado == "Bandeira"){
            bandeiras[indexB]->tx = px;
            bandeiras[indexB]->ty = py;
            bandeiras[indexB]->tz = pz;
        }
    }
    if(action == "rotação"){

        if(objSelecionado == "Casa"){
            casas[indexC]->rx = rx;
            casas[indexC]->ry = ry;
            casas[indexC]->rz = rz;
        }
        if(objSelecionado == "Piramide"){
            piramides[indexPI]->rx = rx;
            piramides[indexPI]->ry = ry;
            piramides[indexPI]->rz = rz;
        }
        if(objSelecionado == "Poste"){
            postes[indexP]->rx = rx;
            postes[indexP]->ry = ry;
            postes[indexP]->rz = rz;
        }
        if(objSelecionado == "Arvore"){
            arvores[indexA]->rx = rx;
            arvores[indexA]->ry = ry;
            arvores[indexA]->rz = rz;
        }
        if(objSelecionado == "Bandeira"){
            if(!editarFilho){
                bandeiras[indexB]->ryF = 0;
                bandeiras[indexB]->rx = rx;
                bandeiras[indexB]->ry = ry;
                bandeiras[indexB]->rz = rz;
            }else{
                 bandeiras[indexB]->ryF = ry;
            }
        }
    }
    if(action == "scala"){
        if(objSelecionado == "Casa"){
            casas[indexC]->sx = sx;
            casas[indexC]->sy = sy;
            casas[indexC]->sz = sz;
        }
        if(objSelecionado == "Piramide"){
            piramides[indexPI]->sx = sx;
            piramides[indexPI]->sy = sy;
            piramides[indexPI]->sz = sz;
        }
        if(objSelecionado == "Poste"){
            if(!editarFilho){
                postes[indexP]->sxF = 0;
                postes[indexP]->sx = sx;
                postes[indexP]->sy = sy;
                postes[indexP]->sz = sz;
            }else{
                postes[indexP]->sxF = sx;
            }
        }
        if(objSelecionado == "Arvore"){
            arvores[indexA]->sx = sx;
            arvores[indexA]->sy = sy;
            arvores[indexA]->sz = sz;
        }
        if(objSelecionado == "Bandeira"){
            bandeiras[indexB]->sx = sx;
            bandeiras[indexB]->sy = sy;
            bandeiras[indexB]->sz = sz;
        }
    }

    if(abrirSelecionarNovoObj){
        if(objetosEscolhas[posAtualNaLista] == 0){
            casaObj.rgbB = casaObj.getColorRGB();
            casaObj.rgbT = casaObj.getColorRGB();
            casaObj.DesenharCasinha();
        }
        if(objetosEscolhas[posAtualNaLista] == 1){
            arvoreObj.rgbT = arvoreObj.getColorRGB();
            arvoreObj.rgbF = arvoreObj.getColorRGB();
            arvoreObj.DesenharArvore();
        }
        if(objetosEscolhas[posAtualNaLista] == 2){
            posteObj.rgbM = posteObj.getColorRGB();
            posteObj.rgbL = posteObj.getColorRGB();
            posteObj.DesenharPoste();
        }
        if(objetosEscolhas[posAtualNaLista] == 3){
            arvoreObj.rgbT = arvoreObj.getColorRGB();
            arvoreObj.rgbF = arvoreObj.getColorRGB();
            bandeiraObj.DesenharBandeira();
        }
        if(objetosEscolhas[posAtualNaLista] == 4){
            piramideObj.rgbT = piramideObj.getColorRGB();
            piramideObj.rgbF = piramideObj.getColorRGB();
            piramideObj.DesenharPiramide();
        }
    }
    GUI::displayEnd();
}
void addArvore(int x, int y, int z){
    Arvore* arvore1 = new Arvore();

    arvore1->nome = "Arvore";
    arvore1->id = rand();
    arvore1->colorRGB = {1,2,3};
    arvore1->tx = x;
    arvore1->ty = y;
    arvore1->tz = z;

    arvores.push_back(arvore1);

    Objeto ob;
    ob.nome = arvore1->nome;
    ob.id = arvore1->id;

    idsObjetos.push_back(ob);
}
void addPiramide(int x, int y, int z){
    Piramide* pir = new Piramide();

    pir->nome = "Piramide";
    pir->id = rand();
    pir->colorRGB = {1,2,3};
    pir->tx = x;
    pir->ty = y;
    pir->tz = z;

    piramides.push_back(pir);

    Objeto ob;
    ob.nome = pir->nome;
    ob.id = pir->id;

    idsObjetos.push_back(ob);
}
void addPoste(int x, int y, int z){
    Poste* poste = new Poste();

    poste->nome = "Poste";
    poste->id = rand();
    poste->colorRGB = {1,2,3};
    poste->tx = x;
    poste->ty = y;
    poste->tz = z;

    postes.push_back(poste);

    Objeto ob;
    ob.nome = poste->nome;
    ob.id = poste->id;

    idsObjetos.push_back(ob);
}
void addBandeira(int x, int y, int z){
    Bandeira* bandeira = new Bandeira();

    bandeira->nome = "Bandeira";
    bandeira->id = rand();
    bandeira->colorRGB = {1,2,3};
    bandeira->tx = x;
    bandeira->ty = y;
    bandeira->tz = z;

    bandeiras.push_back(bandeira);

    Objeto ob;
    ob.nome = bandeira->nome;
    ob.id = bandeira->id;

    idsObjetos.push_back(ob);
}
void addCasa(int x, int y, int z){
    Casa2* casa = new Casa2();

    casa->nome = "Casa";
    casa->id = rand();
    casa->colorRGB = {1,2,3};
    casa->tx = x;
    casa->ty = y;
    casa->tz = z;

    casas.push_back(casa);

    Objeto ob;
    ob.nome = casa->nome;
    ob.id = casa->id;

    idsObjetos.push_back(ob);
}
void moverVetorEmCena(int i){

    posAtual += i;

    if(posAtual >= idsObjetos.size() && posAtual > 0){
        posAtual = 0;
    }
    if(posAtual < 0){
        posAtual = (idsObjetos.size() -1);
    }
}
void moverVetorNaLista(int i){

    posAtualNaLista += i;

    if(posAtualNaLista >= objetosEscolhas.size() && posAtualNaLista > 0){
        posAtualNaLista = 0;
    }
    if(posAtualNaLista < 0){
        posAtualNaLista = (objetosEscolhas.size() -1);
    }
}
void moverVetorNaListaCoresP(int i){

    posAtualCoresPrimarias += i;

    if(posAtualCoresPrimarias >= 3 && posAtualCoresPrimarias > 0){
        posAtualCoresPrimarias = 0;
    }
    if(posAtualCoresPrimarias < 0){
        posAtualCoresPrimarias = (3-1);
    }
}
void moverVetorNaListaCoresS(int i){

    posAtualCoresSecundarias += i;

    if(posAtualCoresSecundarias >= 3 && posAtualCoresSecundarias > 0){
        posAtualCoresSecundarias = 0;
    }
    if(posAtualCoresSecundarias < 0){
        posAtualCoresSecundarias = (3-1);
    }
}

void isSelect(int id, string t){

    objSelecionado = t;
    for (int y = 0; y < casas.size(); y++) {
        if(casas[y]->getId() == id){
            casas[y]->select = true;
            casas[y]->colorRGB = {0,0,1};
        }else{
            casas[y]->select = false;
            casas[y]->colorRGB = {1,2,3};
        }
    }
    for (int y = 0; y < piramides.size(); y++) {
        if(piramides[y]->getId() == id){
            piramides[y]->select = true;
            piramides[y]->colorRGB = {0,0,1};
        }else{
            piramides[y]->select = false;
            piramides[y]->colorRGB = {1,2,3};
        }
    }
    for (int y = 0; y < postes.size(); y++) {
        if(postes[y]->getId() == id){
            postes[y]->select = true;
            postes[y]->colorRGB = {0,0,1};
        }else{
            postes[y]->select = false;
            postes[y]->colorRGB = {1,2,3};
        }
    }
    for (int y = 0; y < arvores.size(); y++) {
        if(arvores[y]->getId() == id){
            arvores[y]->select = true;
            arvores[y]->colorRGB = {0,0,1};
        }else{
            arvores[y]->select = false;
            arvores[y]->colorRGB = {1,2,3};
        }
    }
    for (int y = 0; y < bandeiras.size(); y++) {
        if(bandeiras[y]->getId() == id){
            bandeiras[y]->select = true;
            bandeiras[y]->colorRGB = {0,0,1};
        }else{
            bandeiras[y]->select = false;
            bandeiras[y]->colorRGB = {1,2,3};
        }
    }
}
void selecionarObjeto(int id, string tipo){

    if(tipo == "Casa"){
        for (int y = 0; y < casas.size(); y++) {
            if(casas[y]->getId() == id){
                indexC = y;
                isSelect(casas[indexC]->getId(),"Casa");
            }
        }
    }
    if(tipo == "Piramide"){
        for (int y = 0; y < piramides.size(); y++) {
            if(piramides[y]->getId() == id){
                indexPI = y;
                isSelect(piramides[indexPI]->getId(),"Piramide");
            }
        }
    }
    if(tipo == "Poste"){
        for (int y = 0; y < postes.size(); y++) {
            if(postes[y]->getId() == id){
                indexP = y;
                isSelect(postes[indexP]->getId(),"Poste");
            }
        }
    }
    if(tipo == "Arvore"){
        for (int y = 0; y < arvores.size(); y++) {
            if(arvores[y]->getId() == id){
                indexA = y;
                isSelect(arvores[indexA]->getId(),"Arvore");
            }
        }
    }
    if(tipo == "Bandeira"){
        for (int y = 0; y < bandeiras.size(); y++) {
            if(bandeiras[y]->getId() == id){
                indexB = y;
                isSelect(bandeiras[indexB]->getId(),"Bandeira");
            }
        }
    }
}
void Guardar(){
    dbMapa.open("dbMapa.txt");
        for (int i = 0; i < casas.size(); i++) {
            dbMapa << casas[i]->getNome() << endl;
            dbMapa << casas[i]->tx << endl;
            dbMapa << casas[i]->ty << endl;
            dbMapa << casas[i]->tz << endl;
            dbMapa << casas[i]->rx << endl;
            dbMapa << casas[i]->ry << endl;
            dbMapa << casas[i]->rz << endl;
            dbMapa << casas[i]->sx << endl;
            dbMapa << casas[i]->sy << endl;
            dbMapa << casas[i]->sz << endl;
            dbMapa << casas[i]->rgbB[0] << casas[i]->rgbB[1] << casas[i]->rgbB[2] << endl;
            dbMapa << casas[i]->rgbT[0] << casas[i]->rgbT[1] << casas[i]->rgbT[2] << endl;
            dbMapa << "=" << endl;
        }
        for (int i = 0; i < piramides.size(); i++) {
            dbMapa << piramides[i]->getNome() << endl;
            dbMapa << piramides[i]->tx << endl;
            dbMapa << piramides[i]->ty << endl;
            dbMapa << piramides[i]->tz << endl;
            dbMapa << piramides[i]->rx << endl;
            dbMapa << piramides[i]->ry << endl;
            dbMapa << piramides[i]->rz << endl;
            dbMapa << piramides[i]->sx << endl;
            dbMapa << piramides[i]->sy << endl;
            dbMapa << piramides[i]->sz << endl;
            dbMapa << piramides[i]->rgbT[0] << piramides[i]->rgbT[1] << piramides[i]->rgbT[2] << endl;
            dbMapa << piramides[i]->rgbF[0] << piramides[i]->rgbF[1] << piramides[i]->rgbF[2] << endl;
            dbMapa << "=" << endl;
        }
        for (int i = 0; i < arvores.size(); i++) {
            dbMapa << arvores[i]->getNome() << endl;
            dbMapa << arvores[i]->tx << endl;
            dbMapa << arvores[i]->ty << endl;
            dbMapa << arvores[i]->tz << endl;
            dbMapa << arvores[i]->rx << endl;
            dbMapa << arvores[i]->ry << endl;
            dbMapa << arvores[i]->rz << endl;
            dbMapa << arvores[i]->sx << endl;
            dbMapa << arvores[i]->sy << endl;
            dbMapa << arvores[i]->sz << endl;
            dbMapa << arvores[i]->rgbT[0] << arvores[i]->rgbT[1] << arvores[i]->rgbT[2] << endl;
            dbMapa << arvores[i]->rgbF[0] << arvores[i]->rgbF[1] << arvores[i]->rgbF[2] << endl;
            dbMapa << "=" << endl;
        }
        for (int i = 0; i < postes.size(); i++) {
            dbMapa << postes[i]->getNome() << endl;
            dbMapa << postes[i]->tx << endl;
            dbMapa << postes[i]->ty << endl;
            dbMapa << postes[i]->tz << endl;
            dbMapa << postes[i]->rx << endl;
            dbMapa << postes[i]->ry << endl;
            dbMapa << postes[i]->rz << endl;
            dbMapa << postes[i]->sx << endl;
            dbMapa << postes[i]->sy << endl;
            dbMapa << postes[i]->sz << endl;
            dbMapa << postes[i]->sxF << endl;
            dbMapa << postes[i]->rgbM[0] << postes[i]->rgbM[1] << postes[i]->rgbM[2] << endl;
            dbMapa << postes[i]->rgbL[0] << postes[i]->rgbL[1] << postes[i]->rgbL[2] << endl;
            dbMapa << "=" << endl;
        }
        for (int i = 0; i < bandeiras.size(); i++) {
            dbMapa << bandeiras[i]->getNome() << endl;
            dbMapa << bandeiras[i]->tx << endl;
            dbMapa << bandeiras[i]->ty << endl;
            dbMapa << bandeiras[i]->tz << endl;
            dbMapa << bandeiras[i]->rx << endl;
            dbMapa << bandeiras[i]->ry << endl;
            dbMapa << bandeiras[i]->rz << endl;
            dbMapa << bandeiras[i]->sx << endl;
            dbMapa << bandeiras[i]->sy << endl;
            dbMapa << bandeiras[i]->sz << endl;
            dbMapa << bandeiras[i]->ryF << endl;
            dbMapa << bandeiras[i]->rgbM[0] << bandeiras[i]->rgbM[1] << bandeiras[i]->rgbM[2] << endl;
            dbMapa << bandeiras[i]->rgbB[0] << bandeiras[i]->rgbB[1] << bandeiras[i]->rgbB[2] << endl;
            dbMapa << "=" << endl;
        }
    dbMapa.close();
}

void Carregar(){
    dbMapaE.open("dbMapa.txt");

    while(getline(dbMapaE, linha) ){
        if(linha[0] == '='){
            if(dbObjetoAtual[0] == "Casa"){
                Casa2* c = new Casa2();
                c->nome = "Casa";
                c->id = rand();

                c->tx = stof(dbObjetoAtual[1]);
                c->ty = stof(dbObjetoAtual[2]);
                c->tz = stof(dbObjetoAtual[3]);

                c->rx = stof(dbObjetoAtual[4]);
                c->ry = stof(dbObjetoAtual[5]);
                c->rz = stof(dbObjetoAtual[6]);

                c->sx = stof(dbObjetoAtual[7]);
                c->sy = stof(dbObjetoAtual[8]);
                c->sz = stof(dbObjetoAtual[9]);

                vector<int> cp;
                vector<int> cs;

                cp.push_back((dbObjetoAtual[10][0] - '0'));
                cp.push_back(int(dbObjetoAtual[10][1] - '0'));
                cp.push_back(int(dbObjetoAtual[10][2] - '0'));

                cs.push_back(int(dbObjetoAtual[11][0] - '0'));
                cs.push_back(int(dbObjetoAtual[11][1] - '0'));
                cs.push_back(int(dbObjetoAtual[11][2] - '0'));

                c->rgbB = cp;
                c->rgbT = cs;

                Objeto ob;
                ob.nome = c->nome;
                ob.id = c->id;

                casas.push_back(c);
                idsObjetos.push_back(ob);
            }
            if(dbObjetoAtual[0] == "Piramide"){
                Piramide* p = new Piramide();
                p->nome = "Piramide";
                p->id = rand();

                p->tx = stof(dbObjetoAtual[1]);
                p->ty = stof(dbObjetoAtual[2]);
                p->tz = stof(dbObjetoAtual[3]);

                p->rx = stof(dbObjetoAtual[4]);
                p->ry = stof(dbObjetoAtual[5]);
                p->rz = stof(dbObjetoAtual[6]);

                p->sx = stof(dbObjetoAtual[7]);
                p->sy = stof(dbObjetoAtual[8]);
                p->sz = stof(dbObjetoAtual[9]);

                vector<int> cp;
                vector<int> cs;

                cp.push_back((dbObjetoAtual[10][0] - '0'));
                cp.push_back(int(dbObjetoAtual[10][1] - '0'));
                cp.push_back(int(dbObjetoAtual[10][2] - '0'));

                cs.push_back(int(dbObjetoAtual[11][0] - '0'));
                cs.push_back(int(dbObjetoAtual[11][1] - '0'));
                cs.push_back(int(dbObjetoAtual[11][2] - '0'));

                p->rgbT = cp;
                p->rgbF = cs;

                Objeto ob;
                ob.nome = p->nome;
                ob.id = p->id;

                piramides.push_back(p);
                idsObjetos.push_back(ob);
            }
            if(dbObjetoAtual[0] == "Bandeira"){
                Bandeira* c = new Bandeira();
                c->nome = "Bandeira";
                c->id = rand();

                c->tx = stof(dbObjetoAtual[1]);
                c->ty = stof(dbObjetoAtual[2]);
                c->tz = stof(dbObjetoAtual[3]);

                c->rx = stof(dbObjetoAtual[4]);
                c->ry = stof(dbObjetoAtual[5]);
                c->rz = stof(dbObjetoAtual[6]);

                c->sx = stof(dbObjetoAtual[7]);
                c->sy = stof(dbObjetoAtual[8]);
                c->sz = stof(dbObjetoAtual[9]);

                c->ryF = stof(dbObjetoAtual[10]);

                vector<int> cp;
                vector<int> cs;

                cp.push_back((dbObjetoAtual[11][0] - '0'));
                cp.push_back(int(dbObjetoAtual[11][1] - '0'));
                cp.push_back(int(dbObjetoAtual[11][2] - '0'));

                cs.push_back(int(dbObjetoAtual[12][0] - '0'));
                cs.push_back(int(dbObjetoAtual[12][1] - '0'));
                cs.push_back(int(dbObjetoAtual[12][2] - '0'));

                c->rgbB = cs;
                c->rgbM = cp;

                Objeto ob;
                ob.nome = c->nome;
                ob.id = c->id;

                bandeiras.push_back(c);
                idsObjetos.push_back(ob);
            }
            if(dbObjetoAtual[0] == "Poste"){
                Poste* c = new Poste();
                c->nome = "Poste";
                c->id = rand();

                c->tx = stof(dbObjetoAtual[1]);
                c->ty = stof(dbObjetoAtual[2]);
                c->tz = stof(dbObjetoAtual[3]);

                c->rx = stof(dbObjetoAtual[4]);
                c->ry = stof(dbObjetoAtual[5]);
                c->rz = stof(dbObjetoAtual[6]);

                c->sx = stof(dbObjetoAtual[7]);
                c->sy = stof(dbObjetoAtual[8]);
                c->sz = stof(dbObjetoAtual[9]);

                c->sxF = stof(dbObjetoAtual[10]);

                vector<int> cp;
                vector<int> cs;

                cp.push_back((dbObjetoAtual[11][0] - '0'));
                cp.push_back(int(dbObjetoAtual[11][1] - '0'));
                cp.push_back(int(dbObjetoAtual[11][2] - '0'));

                cs.push_back(int(dbObjetoAtual[12][0] - '0'));
                cs.push_back(int(dbObjetoAtual[12][1] - '0'));
                cs.push_back(int(dbObjetoAtual[12][2] - '0'));

                c->rgbL = cs;
                c->rgbM = cp;

                Objeto ob;
                ob.nome = c->nome;
                ob.id = c->id;

                postes.push_back(c);
                idsObjetos.push_back(ob);
            }
            if(dbObjetoAtual[0] == "Arvore"){
                Arvore* c = new Arvore();
                c->nome = "Arvore";
                c->id = rand();

                c->tx = stof(dbObjetoAtual[1]);
                c->ty = stof(dbObjetoAtual[2]);
                c->tz = stof(dbObjetoAtual[3]);

                c->rx = stof(dbObjetoAtual[4]);
                c->ry = stof(dbObjetoAtual[5]);
                c->rz = stof(dbObjetoAtual[6]);

                c->sx = stof(dbObjetoAtual[7]);
                c->sy = stof(dbObjetoAtual[8]);
                c->sz = stof(dbObjetoAtual[9]);

                vector<int> cp;
                vector<int> cs;

                cp.push_back((dbObjetoAtual[10][0] - '0'));
                cp.push_back(int(dbObjetoAtual[10][1] - '0'));
                cp.push_back(int(dbObjetoAtual[10][2] - '0'));

                cs.push_back(int(dbObjetoAtual[11][0] - '0'));
                cs.push_back(int(dbObjetoAtual[11][1] - '0'));
                cs.push_back(int(dbObjetoAtual[11][2] - '0'));

                c->rgbF = cs;
                c->rgbT = cp;

                Objeto ob;
                ob.nome = c->nome;
                ob.id = c->id;

                arvores.push_back(c);
                idsObjetos.push_back(ob);
            }

            dbObjetoAtual.clear();
        }else{
            dbObjetoAtual.push_back(linha);
        }
    }

    dbMapaE.close();
}
void deletarObj(int id, string tipo){
    if(tipo == "Casa"){
        for (int y = 0; y < casas.size(); y++) {
            if(casas[y]->getId() == id){
                casas.erase(casas.begin()+y);
            }
        }
    }
    if(tipo == "Piramide"){
        for (int y = 0; y < piramides.size(); y++) {
            if(piramides[y]->getId() == id){
                piramides.erase(piramides.begin()+y);
            }
        }
    }
    if(tipo == "Poste"){
        for (int y = 0; y < postes.size(); y++) {
            if(postes[y]->getId() == id){
                postes.erase(postes.begin()+y);
            }
        }
    }
    if(tipo == "Arvore"){
        for (int y = 0; y < arvores.size(); y++) {
            if(arvores[y]->getId() == id){
                arvores.erase(arvores.begin()+y);
            }
        }
    }
    if(tipo == "Bandeira"){
        for (int y = 0; y < bandeiras.size(); y++) {
            if(bandeiras[y]->getId() == id){
                bandeiras.erase(bandeiras.begin()+y);
            }
        }
    }
}
void deletarObjSelecionado(string tipo){
    if(tipo == "Casa"){
        casas.erase(casas.begin()+indexC);
    }
    if(tipo == "Poste"){
        postes.erase(postes.begin()+indexP);
    }
    if(tipo == "Piramide"){
        piramides.erase(piramides.begin()+indexPI);
    }
    if(tipo == "Arvore"){
        arvores.erase(arvores.begin()+indexA);
    }
    if(tipo == "Bandeira"){
        bandeiras.erase(bandeiras.begin()+indexB);
    }
}
void removerUltimoElemento(){
    deletarObj(idsObjetos[idsObjetos.size()-1].getId(),idsObjetos[idsObjetos.size()-1].getNome());
    idsObjetos.pop_back();
}

void setXYZ(string tipo){
    if(tipo == "Casa"){
        for (int y = 0; y < casas.size(); y++) {
            if(casas[y]->getId() == casas[indexC]->getId()){
                px = casas[y]->tx;
                py = casas[y]->ty;
                pz = casas[y]->tz;

                rx = casas[y]->rx;
                ry = casas[y]->rx;
                rz = casas[y]->rx;

                sx = casas[y]->sx;
                sy = casas[y]->sx;
                sz = casas[y]->sx;
            }
        }
    }
    if(tipo == "Piramide"){
        for (int y = 0; y < piramides.size(); y++) {
            if(piramides[y]->getId() == piramides[indexPI]->getId()){
                px = piramides[y]->tx;
                py = piramides[y]->ty;
                pz = piramides[y]->tz;

                rx = piramides[y]->rx;
                ry = piramides[y]->rx;
                rz = piramides[y]->rx;

                sx = piramides[y]->sx;
                sy = piramides[y]->sx;
                sz = piramides[y]->sx;
            }
        }
    }
    if(tipo == "Poste"){
        for (int y = 0; y < postes.size(); y++) {
            if(postes[y]->getId() == postes[indexP]->getId()){
                px = postes[y]->tx;
                py = postes[y]->ty;
                pz = postes[y]->tz;

                rx = postes[y]->rx;
                ry = postes[y]->rx;
                rz = postes[y]->rx;

                sx = postes[y]->sx;
                sy = postes[y]->sx;
                sz = postes[y]->sx;
            }
        }
    }
    if(tipo == "Arvore"){
        for (int y = 0; y < arvores.size(); y++) {
            if(arvores[y]->getId() == arvores[indexA]->getId()){
                px = arvores[y]->tx;
                py = arvores[y]->ty;
                pz = arvores[y]->tz;

                rx = arvores[y]->rx;
                ry = arvores[y]->rx;
                rz = arvores[y]->rx;

                sx = arvores[y]->sx;
                sy = arvores[y]->sx;
                sz = arvores[y]->sx;
            }
        }
    }
    if(tipo == "Bandeira"){
        for (int y = 0; y < bandeiras.size(); y++) {
            if(bandeiras[y]->getId() == bandeiras[indexB]->getId()){
                px = bandeiras[y]->tx;
                py = bandeiras[y]->ty;
                pz = bandeiras[y]->tz;

                rx = bandeiras[y]->rx;
                ry = bandeiras[y]->rx;
                rz = bandeiras[y]->rx;

                sx = bandeiras[y]->sx;
                sy = bandeiras[y]->sx;
                sz = bandeiras[y]->sx;
            }
        }
    }
}
void  moverVetorCamera(int i){
    posCameraAtual += i;

    if(posCameraAtual >= cameras.size() && posCameraAtual > 0){
        posCameraAtual = 0;
    }
    if(posCameraAtual < 0){
        posCameraAtual = (cameras.size() -1);
    }
}
void teclado(unsigned char tecla, int mx, int my) {
    GUI::keyInit(tecla, mx,my);

    switch (tecla) {
        case '=':
            if(abrirSelecionarCameraObj){
                abrirSelecionarCameraObj = false;
            }else{
                abrirSelecionarCameraObj = true;
            }
            break;
        case '[':
            if(!abrirSelecionarNovoObj){
                abrirSelecionarNovoObj = true;
                abrirSelecionarObjEmCena = false;
                abrirSelecionarCorS = false;
                abrirSelecionarCorP = false;
                abrirSelecionarCameraObj = false;
            }else{
                abrirSelecionarNovoObj = false;
            }
            break;
        case ']':
            if(!abrirSelecionarObjEmCena){
                abrirSelecionarNovoObj = false;
                abrirSelecionarCorS = false;
                abrirSelecionarCorP = false;
                abrirSelecionarObjEmCena = true;
                abrirSelecionarCameraObj = false;
            }else{
                abrirSelecionarObjEmCena = false;
            }
            break;
        case ',':
            if(abrirSelecionarCameraObj){
                moverVetorCamera(-1);
            }
            if(abrirSelecionarObjEmCena){
                moverVetorEmCena(-1);
                selecionarObjeto(idsObjetos[posAtual].getId(),idsObjetos[posAtual].getNome());
                action = "null";

                posAtualCoresPrimarias = 0;
                posAtualCoresSecundarias = 0;

                rx = 0;
                ry = 0;
                rz = 0;

                sx = 0.5;
                sy = 0.5;
                sz = 0.5;
            }
            if(abrirSelecionarNovoObj){
                posAtualCoresPrimarias = 0;
                posAtualCoresSecundarias = 0;
                moverVetorNaLista(-1);;
            }
            if(abrirSelecionarCorP){
                moverVetorNaListaCoresP(-1);
                mudarCorP(objSelecionado);
            }
            if(abrirSelecionarCorS){
                moverVetorNaListaCoresS(-1);
                mudarCorS(objSelecionado);
            }
            break;
        case '.':
            if(abrirSelecionarCameraObj){
                moverVetorCamera(1);
            }
            if(abrirSelecionarObjEmCena){
                moverVetorEmCena(1);
                selecionarObjeto(idsObjetos[posAtual].getId(),idsObjetos[posAtual].getNome());
                action = "null";

                posAtualCoresPrimarias = 0;
                posAtualCoresSecundarias = 0;

                rx = 0;
                ry = 0;
                rz = 0;

                sx = 0.5;
                sy = 0.5;
                sz = 0.5;
            }
            if(abrirSelecionarNovoObj){
                posAtualCoresPrimarias = 0;
                posAtualCoresSecundarias = 0;
                moverVetorNaLista(1);
            }
            if(abrirSelecionarCorP){
                moverVetorNaListaCoresP(1);
                mudarCorP(objSelecionado);
            }
            if(abrirSelecionarCorS){
                moverVetorNaListaCoresS(1);
                mudarCorS(objSelecionado);
            }
            break;
        case '-':
            if(executar){
                executar = false;
                editarFilho = false;
            }else{
                executar = true;
                editarFilho = false;
            }
            break;
        case 't':
            glutGUI::trans_obj = !glutGUI::trans_obj;
            break;
        case 'l':
            glutGUI::trans_luz = !glutGUI::trans_luz;
            break;
        case 'a':
            action = "rotação";
            setXYZ(objSelecionado);
            break;
        case 'd':
            action = "translação";
            setXYZ(objSelecionado);
            break;
        case '3':
            if(editarFilho){
                editarFilho = false;

            }else{
                editarFilho = true;
            }

            break;
        case '1':
            abrirSelecionarCorP = true;
            abrirSelecionarCorS = false;
            abrirSelecionarNovoObj = false;
            abrirSelecionarObjEmCena = false;
            editarFilho = false;
            break;
        case '2':
            editarFilho = false;
            abrirSelecionarCorP = false;
            abrirSelecionarCorS = true;
            abrirSelecionarNovoObj = false;
            abrirSelecionarObjEmCena = false;
            break;
            case ';':
                if(abrirSelecionarNovoObj){
                    if(objetosEscolhas[posAtualNaLista] == 0){
                        addCasa(0,0,0);
                    }
                    if(objetosEscolhas[posAtualNaLista] == 1){
                        addArvore(0,0,0);
                    }
                    if(objetosEscolhas[posAtualNaLista] == 2){
                        addPoste(0,0,0);;
                    }
                    if(objetosEscolhas[posAtualNaLista] == 3){
                        addBandeira(0,0,0);
                    }
                    if(objetosEscolhas[posAtualNaLista] == 4){
                        addPiramide(0,0,0);
                    }
                }
                break;
        case 's':
            action = "scala";
            setXYZ(objSelecionado);
            break;
        case 'n':
            action = "null";
            break;
        case '7':
            Guardar();
            break;
        case '8':
            casas.clear();
            postes.clear();
            bandeiras.clear();
            arvores.clear();
            piramides.clear();
            idsObjetos.clear();

            rx = 0;
            ry = 0;
            rz = 0;

            sx = 0.5;
            sy = 0.5;
            sz = 0.5;

            px = 0;
            py = 0;
            pz = 0;
            Carregar();
            break;
        case 'u':
            removerUltimoElemento();
            break;
        case 'k':
            if(abrirSelecionarObjEmCena){
                deletarObjSelecionado(objSelecionado);
            }
            break;
        default:
            break;
        }
    }

int main()
{
    Carregar();
    GUI gui = GUI(800,600,desenha,teclado);
}
