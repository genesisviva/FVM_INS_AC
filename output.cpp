#include "solver.hpp"


void solver::output(string time){
    int imax = mesh.getIMax();
    int jmax = mesh.getJMax();
    fstream fout;
    string outputPath = "../output/";
    outputPath+=getNumber(mesh.getMeshName());
    outputPath=outputPath+".plt";
    fout.open(outputPath.c_str(), ios::out | ios::trunc);
    fout<<"TITLE = \"INSE_FVM_AC\""<<endl;
    fout<<"Variables = x, y, uX, uY, U, p"<<endl;
    fout<<"ZONE I = "<<imax<<" J = "<<jmax<<endl;
    double uNode,vNode,pNode;
    for(int j=1;j<jmax+1;j++){
        for(int i=1;i<imax+1;i++)
        {
            uNode=0.25*(mesh.getU()[i][j]+mesh.getU()[i-1	][j]+mesh.getU()[i-1][j-1]+mesh.getU()[i][j-1]);
            vNode=0.25*(mesh.getV()[i][j]+mesh.getV()[i-1][j]+mesh.getV()[i-1][j-1]+mesh.getV()[i][j-1]);
            pNode=0.25*(mesh.getP()[i][j]+mesh.getP()[i-1][j]+mesh.getP()[i-1][j-1]+mesh.getP()[i][j-1]);
            fout<<mesh.getX()[i][j]<<" "<<mesh.getY()[i][j]<<" "<<uNode<<" "<<vNode<<" "<<sqrt(pow(uNode,2)+pow(vNode,2))<<" "<<pNode<<endl;
        }  
    }
    fout.close();
}