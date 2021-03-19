#include "solver.hpp"

void solver::getMeshData(){
    int imax, jmax;
    string line;
    ifstream fin;
    fin.open(mesh.getMeshName());
    fin>>imax>>jmax;
    getline(fin,line);

    
    vector<vector <double>> x(imax+2, vector<double> (jmax+2));
    vector<vector <double>> y(imax+2, vector<double> (jmax+2));

    for(int j=1;j<jmax+1;j++)
        for(int i=1;i<imax+1;i++)
            fin>>x[i][j]>>y[i][j];

    for(int j=1; j<jmax+1;j++){   
        x[0][j]=2*x[1][j]-x[2][j];
        y[0][j]=2*y[1][j]-y[2][j];
        x[imax+1][j]=2*x[imax][j]-x[imax-1][j];
        y[imax+1][j]=2*y[imax][j]-y[imax-1][j];
    }

    for(int i=1; i<imax+1;i++){
        x[i][0]=2*x[i][1]-x[i][2];
        y[i][0]=2*y[i][1]-y[i][2];
        x[i][jmax+1]=2*x[i][jmax]-x[i][jmax-1];
        y[i][jmax+1]=2*y[i][jmax]-y[i][jmax-1];
    }
    x[0][0]=2*x[1][0]-x[2][0];
    y[0][0]=2*y[0][1]-y[0][2];
    x[imax+1][0]=2*x[imax][0]-x[imax-1][0];
    y[imax+1][0]=2*y[imax+1][1]-y[imax+1][2];
    x[0][jmax+1]=2*x[1][jmax+1]-x[2][jmax+1];
    y[0][jmax+1]=2*y[0][jmax]-y[0][jmax-1];
    x[imax+1][jmax+1]=2*x[imax][jmax+1]-x[imax-1][jmax+1];
    y[imax+1][jmax+1]=2*y[imax+1][jmax]-y[imax+1][jmax-1];

   vector <vector <array<array<double,2>,2>>> faceVectors;
   faceVectors.resize(imax+1);
   for (auto &i : faceVectors){
       i = vector <array<array<double,2>,2>> (jmax+1);
   }


    for(int j=0;j<jmax+1; j++)
        for(int i=0;i<imax+1; i++)
        {
            faceVectors[i][j][0][0]=y[i+1][j+1]-y[i+1][j];
            faceVectors[i][j][0][1]=-x[i+1][j+1]+x[i+1][j];
            faceVectors[i][j][1][0]=y[i][j+1]-y[i+1][j+1];
            faceVectors[i][j][1][1]=-x[i][j+1]+x[i+1][j+1];


        }
    mesh.setfaceVectors(faceVectors);
   
    
    vector<vector <double>> vol;
    vol.resize(imax+1);

    for (int i=0; i < imax+1; i++) 
        vol[i].resize(jmax+1);
   
    vol.resize(imax+1);

    vector<vector <double>> xc;
    xc.resize(imax+1);
    for (int i=0; i < imax+1; i++) 
        xc[i].resize(jmax+1);

    vector<vector <double>> yc;
    yc.resize(imax+1);

    for (int i=0; i < imax+1; i++) 
        yc[i].resize(jmax+1);

    

    for(int i=0; i<imax+1; i++){
        for(int j=0; j<jmax+1; j++)
        {           
            vol[i][j]=triangle_area(x[i+1][j+1],y[i+1][j+1],x[i][j+1],y[i][j+1],x[i][j],y[i][j]);
            vol[i][j]=vol[i][j]+triangle_area(x[i+1][j+1],y[i+1][j+1],x[i][j],y[i][j],x[i+1][j],y[i+1][j]);
            xc[i][j]=0.25*(x[i][j]+x[i+1][j]+x[i+1][j+1]+x[i][j+1]);
            yc[i][j]=0.25*(y[i][j]+y[i+1][j]+y[i+1][j+1]+y[i][j+1]);
        }
    }





mesh.setX(x);
mesh.setY(y);
mesh.setVol(vol);
mesh.setMeshReadingsBasic(imax, jmax);
mesh.setXmiddle(xc);
mesh.setYmiddle(yc);



fin.close();
}
