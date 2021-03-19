#include "gridData.hpp"


void gridData::setMeshName(string x){
    mshName = x;
}

string gridData::getMeshName(){
    return mshName;
}

int gridData::getIMax(){
    return imax;
}

int gridData::getJMax(){
    return jmax;
}

int gridData::getDensity(){
    return density;
}

void gridData::setDensity(double x){
    density = x;
}

void gridData::setMeshReadingsBasic(int a, int b){
    imax = a;
    jmax = b;
}

int gridData::getRb_type(){
    return rb_type;
}

void gridData::setRb_type(int x){
    rb_type = x;
}

int gridData::getTb_type(){
    return tb_type;
}

void gridData::setTb_type(int x){
    tb_type = x;
}

int gridData::getLb_type(){
    return lb_type;
}

void gridData::setLb_type(int x){
    lb_type = x;
}

int gridData::getBb_type(){
    return bb_type;
}

void gridData::setBb_type(int x){
    bb_type = x;
}

int gridData::getRb_flux_type(){
    return rb_flux_type;
}

void gridData::setRb_flux_type(int x){
    rb_flux_type = x;
}

int gridData::getTb_flux_type(){
    return tb_flux_type;
}

void gridData::setTb_flux_type(int x){
    tb_flux_type = x;
}

int gridData::getLb_flux_type(){
    return lb_flux_type;
}

void gridData::setLb_flux_type(int x){
    lb_flux_type = x;
}

int gridData::getBb_flux_type(){
    return bb_flux_type;
}

void gridData::setBb_flux_type(int x){
    bb_flux_type = x;
}

int gridData::getNMax(){
    return nMax;
}

void gridData::setNMax(int x){
    nMax = x;
}

double gridData::getRb_value(){
    return rb_value;
}

void gridData::setRb_value(double x){
    rb_value = x;
}

double gridData::getTb_value(){
    return tb_value;
}

void gridData::setTb_value(double x){
    tb_value = x;
}

double gridData::getLb_value(){
    return lb_value;
}

void gridData::setLb_value(double x){
    lb_value = x;
}

double gridData::getBb_value(){
    return bb_value;
}

void gridData::setBb_value(double x){
    bb_value = x;
}

double gridData::getMErr(){
    return mErr;
}

void gridData::setMErr(double x){
    mErr = x;
}

double gridData::getCErr(){
    return cErr;
}

void gridData::setCErr(double x){
    cErr = x;
}

double gridData::getUReference(){
    return uReference;
}

void gridData::setUReference(double x){
    uReference = x;
}

double gridData::getLength(){
    return length;
}

void gridData::setLength(double x){
    length = x;
}

double gridData::getVisc(){
    return visc;
}

void gridData::setVisc(double x){
    visc = x;
}

double gridData::getCFLN(){
    return CFLN;
}

void gridData::setCFLN(double x){
    CFLN = x;
}

vector<vector <double>> & gridData::getX(){
    return x;
}

void gridData::setX(vector<vector <double>> &_x){
    x = _x;
}

vector<vector <double>> & gridData::getY(){
    return y;
}

void gridData::setY(vector<vector <double>> &_y){
    y = _y;
}

vector<vector <double>> & gridData::getVol(){
    return vol;
}

void gridData::setVol(vector<vector <double>> &_vol){
    vol = _vol;
}

vector<vector <double>> & gridData::getXmiddle(){
    return xMiddle;
}

void gridData::setXmiddle(vector<vector <double>> &_xMiddle){
    xMiddle = _xMiddle;
}

vector<vector <double>> & gridData::getYmiddle(){
    return yMiddle;
}

void gridData::setYmiddle(vector<vector <double>> &_yMiddle){
    yMiddle = _yMiddle;
}

vector<vector <double>> & gridData::getdT(){
    return dt;
}

vector<vector <double>> & gridData::getFlag(){
    return isFluid;
}

vector <vector <array<double,3>>> & gridData::getResidue(){
    return residue;
}

void gridData::setResidue(vector <vector <array<double,3>>> & _residue){
    residue = _residue;
}

vector <vector <array<array<double,2>,2>>> & gridData::getfaceVectors(){
    return faceVectors;
}

void gridData::setfaceVectors(vector <vector <array<array<double,2>,2>>> & _del){
    faceVectors = _del;
}

double gridData::gettType(){
    return tType;
}

void gridData::settType(double x){
    tType = x;
}

double ** gridData::getU(){
    return u;
}

double ** gridData::getP(){
    return p;
}

double ** gridData::getV(){
    return v;
}