#include "gridData.hpp"


void gridData::setInitialConditions(){
    
    u=new double* [imax+1];
    v=new double* [imax+1];
    p=new double* [imax+1];

    for (int i=0; i < imax+1; i++)
        u[i]= new double[jmax+1];

    for (int i=0; i < imax+1; i++)
        v[i]= new double[jmax+1];

    for (int i=0; i < imax+1; i++)
        p[i]= new double[jmax+1];

    for(int i=0;i<imax+1;i++)
        for(int j=0;j<jmax+1;j++)
            u[i][j]=0;
    for(int i=0;i<imax+1;i++)
        for(int j=0;j<jmax+1;j++)
            v[i][j]=0;
    for(int i=0;i<imax+1;i++)
        for(int j=0;j<jmax+1;j++)
            p[i][j]=0;





   isFluid.resize(imax+1);
    for (auto &i : isFluid)
        i = vector <double> (jmax+1, 1);

}

