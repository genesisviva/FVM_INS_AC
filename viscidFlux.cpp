#include "solver.hpp"

void solver::viscidFlux(){


	double volAverage,area2;
	int ijmax =max(mesh.getIMax(),mesh.getJMax());
	vector <double> xVars(ijmax);
	vector <double> yVars(ijmax);

	for(int j=1; j<mesh.getJMax(); j++){
		for(int i=0; i<mesh.getIMax();i++){
			area2=pow(mesh.getfaceVectors()[i][j][0][0],2)+pow(mesh.getfaceVectors()[i][j][0][1],2);	
			volAverage=0.5*(mesh.getVol()[i+1][j]+mesh.getVol()[i][j]);
			xVars[i] = mesh.getVisc()*(mesh.getU()[i+1][j]-mesh.getU()[i][j])*area2/volAverage;
			yVars[i] = mesh.getVisc()*(mesh.getV()[i+1][j]-mesh.getV()[i][j])*area2/volAverage;
		}	
		for(int i=1;i<mesh.getIMax();i++){
			mesh.getResidue()[i][j][1]=mesh.getResidue()[i][j][1]-(xVars[i]-xVars[i-1]);
			mesh.getResidue()[i][j][2]=mesh.getResidue()[i][j][2]-(yVars[i]-yVars[i-1]);
		}
	}

	for(int i=1; i<mesh.getIMax(); i++){
		for(int j=0; j<mesh.getJMax();j++){
			area2=pow(mesh.getfaceVectors()[i][j][1][0],2)+pow(mesh.getfaceVectors()[i][j][1][1],2);	
			volAverage=0.5*(mesh.getVol()[i][j+1]+mesh.getVol()[i][j]);
			xVars[j] = mesh.getVisc()*(mesh.getU()[i][j+1]-mesh.getU()[i][j])*area2/volAverage;
			yVars[j] = mesh.getVisc()*(mesh.getV()[i][j+1]-mesh.getV()[i][j])*area2/volAverage;
		}
		for(int j=1;j<mesh.getJMax();j++){
			mesh.getResidue()[i][j][1]=mesh.getResidue()[i][j][1]-(xVars[j]-xVars[j-1]);
			mesh.getResidue()[i][j][2]=mesh.getResidue()[i][j][2]-(yVars[j]-yVars[j-1]);
		}
	}

}


