#include "solver.hpp"




double solver::calculateTimeStep(vector<vector<double>> &betaSquared){
    	double dtMin = 1e10;	
		array <double, 2> areaXAverage;		
		array <double, 2> areaYAverage;	
        double areaXAverageValue, areaYAverageValue, xVelocity, yVelocity ,eigenValueX, eigenValueY, curVelocity;
		for (int j = 1; j < mesh.getJMax(); j++)
		{
			for (int i = 1; i < mesh.getIMax(); i++)
			{
				areaXAverage[0] = 0.5 * (mesh.getfaceVectors()[i][j][0][0] + mesh.getfaceVectors()[i - 1][j][0][0]);
				areaXAverage[1] = 0.5 * (mesh.getfaceVectors()[i][j][0][1] + mesh.getfaceVectors()[i - 1][j][0][1]);
				areaYAverage[0] = 0.5 * (mesh.getfaceVectors()[i][j][1][0] + mesh.getfaceVectors()[i][j - 1][1][0]);
				areaYAverage[1] = 0.5 * (mesh.getfaceVectors()[i][j][1][1] + mesh.getfaceVectors()[i][j - 1][1][1]);
				areaXAverageValue = sqrt(pow(areaXAverage[0], 2) + pow(areaXAverage[1], 2));
				areaYAverageValue = sqrt(pow(areaYAverage[0], 2) + pow(areaYAverage[1], 2));
				xVelocity = (mesh.getU()[i][j] * areaXAverage[0] + mesh.getV()[i][j] * areaXAverage[1]) / areaXAverageValue;
				yVelocity = (mesh.getU()[i][j] * areaYAverage[0] + mesh.getV()[i][j] * areaYAverage[1]) / areaYAverageValue;
				eigenValueX = 0.5 * areaXAverageValue * (abs(xVelocity) + sqrt(pow(xVelocity, 2) + 4.0 * betaSquared[i][j]));
				eigenValueY = 0.5 * areaYAverageValue * (abs(yVelocity) + sqrt(pow(yVelocity, 2) + 4.0 * betaSquared[i][j]));
				curVelocity = eigenValueX + eigenValueY;
				mesh.getdT()[i][j] = mesh.getCFLN() * mesh.getVol()[i][j] / curVelocity;
				dtMin = min(dtMin, mesh.getdT()[i][j]);
			}
		}
        return dtMin;

}