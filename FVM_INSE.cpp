#include "solver.hpp"

void solver::FVM_INSE(){
    clock_t start = clock();
	int jmax = mesh.getJMax();
	int imax = mesh.getIMax();
	double density = mesh.getDensity();
	vector<vector <double>> x = mesh.getX();
	vector<vector <double>> y = mesh.getY();
	vector<vector <double>> vol = mesh.getVol();
	vector <vector <array<double,3>>> residue;
	vector <vector <array<array<double,2>,2>>> faceVectors = mesh.getfaceVectors();

	double areaXAverageValue, areaYAverageValue;
	double xVelocity, yVelocity, eigenValue, eigb, voldt;
	double velocityFaceValue, betaAverage = 0;
	vector<vector<double>> vars(max(imax, jmax), vector<double>(3));
	vector<vector<double>> betaSquared(mesh.getIMax() + 1, vector<double>(jmax + 1));
	vector <double> pressureDif(max(mesh.getIMax(), mesh.getJMax()), 0);



	residue.resize(mesh.getIMax());
	for (auto &i : residue)
		i = vector<array<double, 3>>(jmax, {0, 0, 0});
	mesh.setResidue(residue);

	vector<vector<double>> _dt(mesh.getIMax(), vector<double>(jmax));
	mesh.getdT() = _dt;
	time_t now = time(0);
    char* time_ = ctime(&now);				//Замер времени выполнения программы
    string time(time_);
	fstream resOutFile;						
	string pathToResidue = "../output/residue_"+ getNumber(mesh.getMeshName())+".txt";
	cout<<"\n\n\n\n"<<pathToResidue;
	resOutFile.open(pathToResidue.c_str(), ios::out | ios::trunc);
	resOutFile << "Iteration,     Velocity residue      Pressure residue" << endl;

	
	for (int iterationNumber = 0; iterationNumber < mesh.getNMax(); iterationNumber++)
	{
       	setBound();									//Граничные условия
		for (int i = 0; i < mesh.getIMax() + 1; i++){		//Расчет квадрата параметра искусственной сжимаемости
			for (int j = 0; j < jmax + 1; j++)	
			{
				double uValue = sqrt(pow(mesh.getU()[i][j], 2) + pow(mesh.getV()[i][j], 2));
				betaSquared[i][j] = max(mesh.getUReference(), uValue);						
				betaSquared[i][j] = pow(betaSquared[i][j], 2);
			}
		}


		for (int i = 0; i < mesh.getIMax(); i++)			//Обнуление значений разности для новой итерации
			for (int j = 0; j < jmax; j++)
				for (int k = 0; k < 3; k++)
					mesh.getResidue()[i][j][k] = 0;



		double uAverage2Cells = 0, vAverage2Cells = 0, pAverage2Cells = 0;
		double len = 0, xNormalVec = 0, yNormalVec = 0;
		double pDif = 0, pLeft = 0, pRight = 0;
		for (int j = 1; j < jmax; j++)		//Невязкие потоки, ось абсцисс
		{
				for (int i = 1; i < mesh.getIMax(); i++)		//Поиск разницы давления соседних ячеек
				{
					double rP = mesh.getP()[i + 1][j] - mesh.getP()[i][j];
					double lP = mesh.getP()[i][j] - mesh.getP()[i - 1][j];
					pressureDif[i] = 0.5 * (sign(rP) + sign(lP)) * min(abs(rP), abs(lP));
				}
				pressureDif[0] = pressureDif[1];
				pressureDif[mesh.getIMax()] = pressureDif[mesh.getIMax() - 1];
			

			for (int i = 0; i < mesh.getIMax(); i++)		
			{
				len = sqrt(pow(faceVectors[i][j][0][0], 2) + pow(faceVectors[i][j][0][1], 2));		//Вычисляем величину вектора нормали
				xNormalVec = faceVectors[i][j][0][0] / len;									//Составляющая вектора по икс
				yNormalVec = faceVectors[i][j][0][1] / len;									//Составляющая вектора по игрек
				uAverage2Cells = 0.5 * (mesh.getU()[i][j] + mesh.getU()[i + 1][j]);
				vAverage2Cells = 0.5 * (mesh.getV()[i][j] + mesh.getV()[i + 1][j]);
				pAverage2Cells = 0.5 * (mesh.getP()[i][j] + mesh.getP()[i + 1][j]);		//Средние значения переменных соседних ячеек
				velocityFaceValue = uAverage2Cells * xNormalVec + vAverage2Cells * yNormalVec;	//Величина скорости на грани
				betaAverage = 0.5 * (betaSquared[i][j] + betaSquared[i + 1][j]);			//Среднее значение параметра искусственной сжимаемости двух ячеек 
				eigenValue = 0.5 * (abs( velocityFaceValue) + sqrt(pow( velocityFaceValue, 2) + 4.0 * betaAverage));	//Соственное значение (для поправки)	


				pLeft = mesh.getP()[i][j] + 0.5 * pressureDif[i];
				pRight = mesh.getP()[i + 1][j] - 0.5 * pressureDif[i + 1];
				pDif = pLeft - pRight;					//TVD

				vars[i][0] = len * (density * velocityFaceValue * mesh.getFlag()[i][j] + 0.5 * eigenValue *pDif/betaAverage);
				vars[i][1] = len * (density *  velocityFaceValue * mesh.getFlag()[i][j] * uAverage2Cells + xNormalVec   * pAverage2Cells);
				vars[i][2] = len * (density *  velocityFaceValue * mesh.getFlag()[i][j] * vAverage2Cells + yNormalVec   * pAverage2Cells);
			}
			for (int i = 1; i < mesh.getIMax(); i++)
				for (int k = 0; k < 3; k++)
					mesh.getResidue()[i][j][k] = mesh.getResidue()[i][j][k] + vars[i][k] - vars[i - 1][k];
		}

		for (int i = 1; i < mesh.getIMax(); i++)		//Ось ординат
		{

				for (int j = 1; j < jmax; j++)
				{
					double rP = mesh.getP()[i][j + 1] - mesh.getP()[i][j];
					double lP = mesh.getP()[i][j] - mesh.getP()[i][j - 1];
					pressureDif[j] = 0.5 * (sign(rP) + sign(lP)) * min(abs(rP), abs(lP));
				}
				pressureDif[0] = pressureDif[1];
				pressureDif[jmax] = pressureDif[jmax - 1];

			for (int j = 0; j < jmax; j++)
			{
				len = sqrt(pow(faceVectors[i][j][1][0], 2) + pow(faceVectors[i][j][1][1], 2));
				xNormalVec = faceVectors[i][j][1][0] / len;
				yNormalVec = faceVectors[i][j][1][1] / len;
				uAverage2Cells = 0.5 * (mesh.getU()[i][j] + mesh.getU()[i][j + 1]);
				vAverage2Cells = 0.5 * (mesh.getV()[i][j] + mesh.getV()[i][j + 1]);
				pAverage2Cells = 0.5 * (mesh.getP()[i][j] + mesh.getP()[i][j + 1]);
				velocityFaceValue = uAverage2Cells * xNormalVec + vAverage2Cells * yNormalVec;
				betaAverage = 0.5 * (betaSquared[i][j] + betaSquared[i][j + 1]);
				eigenValue = 0.5 * (abs( velocityFaceValue) + sqrt(pow( velocityFaceValue, 2) + 4.0 * betaAverage));
				pLeft = mesh.getP()[i][j] + 0.5 * pressureDif[j];
				pRight = mesh.getP()[i][j + 1] - 0.5 * pressureDif[j + 1];
				pDif = pLeft - pRight;
				vars[j][0] = len * (density *  velocityFaceValue * mesh.getFlag()[i][j] + 0.5 * eigenValue * pDif / betaAverage);
				vars[j][1] = len * (density *  velocityFaceValue * mesh.getFlag()[i][j] * uAverage2Cells + xNormalVec  * pAverage2Cells);
				vars[j][2] = len * (density *  velocityFaceValue * mesh.getFlag()[i][j] * vAverage2Cells + yNormalVec  * pAverage2Cells);
			}
			for (int j = 1; j < jmax; j++)
				for (int k = 0; k < 3; k++)
					mesh.getResidue()[i][j][k] = mesh.getResidue()[i][j][k] + vars[j][k] - vars[j - 1][k];
		}


		viscidFlux();
		double dtMin = calculateTimeStep(betaSquared);	//Рассчитываем шаг по времени для каждой ячейки

		double pResFirst, vResFirst;		//Значение остатка на прошлой итерации (давление, величина скорости)
		double xVResSum = 0, yVResSum = 0;		//Сумма остатков скоростей по осям
		double pAverage, xVAverage, yVAverage;	//Среднее значение остатка в ячейке
		double vNormRes = 0, pResSum = 0;
		for (int j = 1; j < jmax; j++)			//Считаем сумму остатков для всех объемов
			for (int i = 1; i < mesh.getIMax(); i++)
			{
				pResSum = pResSum + mesh.getResidue()[i][j][0];					
				xVResSum = xVResSum + mesh.getResidue()[i][j][1] * mesh.getResidue()[i][j][1];
				yVResSum = yVResSum + mesh.getResidue()[i][j][2] * mesh.getResidue()[i][j][2];
			}
		pResSum = pResSum / mesh.getIMax() / jmax + 1e-30;	//Считаем средний остаток для ячейки давления и ниже величины (модуля) скорости
		xVResSum = xVResSum / mesh.getIMax() / jmax;
		yVResSum = yVResSum / mesh.getIMax() / jmax;
		vNormRes = sqrt(xVResSum + yVResSum) + 1e-30;
		if (iterationNumber == 0)
		{
			pResFirst = pResSum;
			vResFirst = vNormRes;
		}
		resOutFile << setw(7);
		resOutFile <<fixed <<setprecision(7);
		resOutFile << iterationNumber << "        " << abs(vNormRes / (vResFirst)) << "             " << abs(pResSum / (pResFirst)) << endl;
		cout << "Iteration: " << iterationNumber << endl;
		cout << "Relative velocity difference: " << abs(vNormRes / (vResFirst)) << endl;
		cout << "Relative pressure difference: " << abs(pResSum / (pResFirst)) << endl;

		if (abs(vNormRes / (vResFirst))<mesh.getMErr() && abs(pResSum / (pResFirst)) < mesh.getCErr())
		{
			break;
		}
		if (iterationNumber == mesh.getNMax() - 1)
		{
			cout << "Not solved with maximum number of iterations, N=" << mesh.getNMax() << endl;
			break;
		}


		double dtCur, dpCur, duCur, dvCur;
		for (int j = 1; j < jmax; j++)					//Изменяем текущие значения скорости и давления в ячейках
			for (int i = 1; i < mesh.getIMax(); i++)
			{
				if (!mesh.gettType()){
					dtCur = dtMin / vol[i][j];
				}
				else{
					dtCur = mesh.getdT()[i][j] / vol[i][j];
				}
				dpCur = -betaSquared[i][j] * dtCur * mesh.getResidue()[i][j][0];
				duCur = -dtCur * mesh.getResidue()[i][j][1] / density;
				dvCur = -dtCur * mesh.getResidue()[i][j][2] / density;
				mesh.getP()[i][j] = mesh.getP()[i][j] + dpCur;		
				mesh.getU()[i][j] = mesh.getU()[i][j] + duCur;
				mesh.getV()[i][j] = mesh.getV()[i][j] + dvCur;
			}

	}

	output(time);
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
  	printf("\n\nElapsed time: %f seconds\n", seconds);

	exit(0);

	resOutFile.close();
}


