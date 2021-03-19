#include "solver.hpp"


void solver::setBound(){
    int imax = mesh.getIMax();
	int jmax = mesh.getJMax();
	double rbValue = mesh.getRb_value();
	double lbValue = mesh.getLb_value();
	double tbValue = mesh.getTb_value();
	double bbValue = mesh.getBb_value();
	double density = mesh.getDensity();
	vector<vector <double>> x = mesh.getX();
	vector<vector <double>> y = mesh.getY();
	vector<vector <double>> xMiddle = mesh.getXmiddle();
	vector<vector <double>> yMiddle = mesh.getYmiddle();;
	vector<vector <double>> isFluid = mesh.getFlag();
	vector <vector <array<array<double,2>,2>>> faceVectors = mesh.getfaceVectors();

	for (int j = 1; j < jmax; j++)		//Левая и правая границы
	{
		if (mesh.getLb_type() == 0)
		{
			double xNormalVec, yNormalVec, len;
			isFluid[0][j] = 0;
			len = sqrt(pow(x[1][j + 1] - x[1][j], 2) + pow(y[1][j + 1] - y[1][j], 2));
			xNormalVec = lbValue * (x[1][j + 1] - x[1][j]) / len;
			yNormalVec = lbValue * (y[1][j + 1] - y[1][j]) / len;
			mesh.getU()[0][j] = 2 * xNormalVec - mesh.getU()[1][j];
			mesh.getV()[0][j] = 2 * yNormalVec - mesh.getV()[1][j];
			mesh.getP()[0][j] = mesh.getP()[1][j];
		}
		else if (mesh.getLb_type() == 1)
		{
			if (mesh.getLb_flux_type() == 0)
			{
				double xNormalVec, yNormalVec, len;
				len = sqrt(pow(x[1][j + 1] - x[1][j], 2) + pow(y[1][j + 1] - y[1][j], 2));
				xNormalVec = faceVectors[0][j][0][0] / len;		
				yNormalVec = faceVectors[0][j][0][1] / len;		
				mesh.getU()[0][j] =  lbValue   * xNormalVec;
				mesh.getV()[0][j] =  lbValue   * yNormalVec;
				mesh.getP()[0][j] = mesh.getP()[1][j];
			}
			else if (mesh.getLb_flux_type() == 1)
			{
				mesh.getU()[0][j] = mesh.getU()[1][j];
				mesh.getV()[0][j] = mesh.getV()[1][j];
				mesh.getP()[0][j] = lbValue - 0.5 * density * (pow(mesh.getU()[0][j], 2) + pow(mesh.getV()[0][j], 2));
			}
		}

		else if (mesh.getLb_type() == 2)
		{
			mesh.getU()[0][j] = mesh.getU()[1][j];
			mesh.getV()[0][j] = mesh.getV()[1][j];
			mesh.getP()[0][j] = lbValue;
		}


		if (mesh.getRb_type() == 0)
		{
			double xNormalVec, yNormalVec, len;
			isFluid[imax - 1][j] = 0;
			len = sqrt(pow(x[imax][j + 1] - x[imax][j], 2) + pow(y[imax][j + 1] - y[imax][j], 2));
			xNormalVec = rbValue * (x[imax][j + 1] - x[imax][j]) / len;
			yNormalVec = rbValue * (y[imax][j + 1] - y[imax][j]) / len;
			mesh.getU()[imax][j] = 2 * xNormalVec - mesh.getU()[imax - 1][j];
			mesh.getV()[imax][j] = 2 * yNormalVec - mesh.getV()[imax - 1][j];
			mesh.getP()[imax][j] = mesh.getP()[imax - 1][j];
		}

		else if (mesh.getRb_type() == 1)
		{
			if (mesh.getRb_flux_type() == 0)
			{
				double xNormalVec, yNormalVec, len;
				len = sqrt(pow(faceVectors[imax - 1][j][0][0], 2) + pow(faceVectors[imax - 1][j][0][1], 2));
				xNormalVec = faceVectors[imax - 1][j][0][0] / len;
				yNormalVec = faceVectors[imax - 1][j][0][1] / len;
				mesh.getU()[imax][j] =  rbValue  * xNormalVec;
				mesh.getV()[imax][j] =  rbValue  * yNormalVec;
				mesh.getP()[imax][j] = mesh.getP()[imax - 1][j];
			}
			else if (mesh.getRb_flux_type() == 1)
			{
				mesh.getU()[imax][j] = mesh.getU()[imax - 1][j];
				mesh.getV()[imax][j] = mesh.getV()[imax - 1][j];
				mesh.getP()[imax][j] = rbValue - 0.5 * density * (pow(mesh.getU()[imax - 1][j], 2) + pow(mesh.getV()[imax - 1][j], 2));
			}
		}

		else if (mesh.getRb_type() == 2)
		{
			mesh.getU()[imax][j] = mesh.getU()[imax - 1][j];
			mesh.getV()[imax][j] = mesh.getV()[imax - 1][j];
			mesh.getP()[imax][j] = rbValue;
		}

	}


	for (int i = 1; i < imax; i++) 	//Нижняя и верхняя границы
	{

		if (mesh.getBb_type() == 0)
		{
			double xNormalVec, yNormalVec, len;
			isFluid[i][0] = 0;
			len = sqrt(pow(x[i + 1][1] - x[i][1], 2) + pow(y[i + 1][1] - y[i][1], 2));
			xNormalVec = bbValue * (x[i + 1][1] - x[i][1]) / len;
			yNormalVec = bbValue * (y[i + 1][1] - y[i][1]) / len;
			mesh.getU()[i][0] = 2 * xNormalVec - mesh.getU()[i][1];
			mesh.getV()[i][0] = 2 * yNormalVec - mesh.getV()[i][1];
			mesh.getP()[i][0] = mesh.getP()[i][1];
		}
		else if (mesh.getBb_type() == 1)
		{
			if (mesh.getBb_flux_type() == 0)
			{
				double xNormalVec, yNormalVec, len;
				len = sqrt(pow(x[i + 1][1] - x[i][1], 2) + pow(y[i + 1][1] - y[i][1], 2));
				xNormalVec = faceVectors[i][0][1][0] / len;
				yNormalVec = faceVectors[i][0][1][1] / len;
				mesh.getU()[i][0] =  bbValue * xNormalVec;
				mesh.getV()[i][0] =  bbValue * yNormalVec;
				mesh.getP()[i][0] = mesh.getP()[i][1];
			}
			else if (mesh.getBb_flux_type() == 1)
			{
				mesh.getU()[i][0] = mesh.getU()[i][1];
				mesh.getV()[i][0] = mesh.getV()[i][1];
				mesh.getP()[i][0] = bbValue - 0.5 * density * (pow(mesh.getU()[i][0], 2) + pow(mesh.getV()[i][0], 2));
			}
		}

		else if (mesh.getBb_type() == 2)
		{
			mesh.getU()[i][0] = mesh.getU()[i][1];
			mesh.getV()[i][0] = mesh.getV()[i][1];
			mesh.getP()[i][0] = bbValue;
		}


		if (mesh.getTb_type() == 0)
		{
			double xNormalVec, yNormalVec, len;
			isFluid[i][jmax - 1] = 0;
			len = sqrt(pow(x[i + 1][jmax] - x[i][jmax], 2) + pow(y[i + 1][jmax] - y[i][jmax], 2));
			xNormalVec = tbValue * (x[i + 1][jmax] - x[i][jmax]) / len;
			yNormalVec = tbValue * (y[i + 1][jmax] - y[i][jmax]) / len;
			mesh.getU()[i][jmax] = 2 * xNormalVec - mesh.getU()[i][jmax - 1];
			mesh.getV()[i][jmax] = 2 * yNormalVec - mesh.getV()[i][jmax - 1];
			mesh.getP()[i][jmax] = mesh.getP()[i][jmax - 1];
		}

		else if (mesh.getTb_type() == 1)
		{
			if (mesh.getTb_flux_type() == 0)
			{
				double xNormalVec, yNormalVec, len;
				len = sqrt(pow(x[i + 1][jmax] - x[i][jmax], 2) + pow(y[i + 1][jmax] - y[i][jmax], 2));
				xNormalVec = faceVectors[i][jmax - 1][1][0] / len;
				yNormalVec = faceVectors[i][jmax - 1][1][1] / len;
				mesh.getU()[i][jmax] = tbValue  * xNormalVec;
				mesh.getV()[i][jmax] = tbValue  * yNormalVec;
				mesh.getP()[i][jmax] = mesh.getP()[i][jmax - 1];
			}
			else if (mesh.getTb_flux_type() == 1)
			{
				mesh.getU()[i][jmax] = mesh.getU()[i][jmax - 1];
				mesh.getV()[i][jmax] = mesh.getV()[i][jmax - 1];
				mesh.getP()[i][jmax] = tbValue - 0.5 * density * (pow(mesh.getU()[i][jmax], 2) + pow(mesh.getV()[i][jmax], 2));
			}
		}

		else if (mesh.getTb_type() == 2)
		{
			mesh.getU()[i][jmax] = mesh.getU()[i][jmax - 1];
			mesh.getV()[i][jmax] = mesh.getV()[i][jmax - 1];
			mesh.getP()[i][jmax] = tbValue;
		}
	}
}