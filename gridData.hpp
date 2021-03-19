#include <vector>
#include <array>

using namespace std;

class gridData{
    private:

        string mshName;
        int imax, jmax, rb_type, tb_type, lb_type, bb_type, rb_flux_type, tb_flux_type, lb_flux_type, bb_flux_type, nMax;
        double density, rb_value, tb_value, lb_value, bb_value, tType;
        double mErr, cErr, uReference, length, visc, CFLN;
        vector<vector <double>> x, y, vol, xMiddle, yMiddle, dt, isFluid;
        vector <vector <array<double,3>>> residue;
        vector <vector <array<array<double,2>,2>>> faceVectors;
        double **u, **v, **p;

    public:

        void setInitialConditions();

        void setMeshName(string);
        string getMeshName();
        int getIMax();
        int getJMax();
        int getDensity();
        void setDensity(double);
        void setMeshReadingsBasic(int, int);

        int getRb_type();
        void setRb_type(int);
        int getTb_type();
        void setTb_type(int);
        int getLb_type();
        void setLb_type(int);
        int getBb_type();
        void setBb_type(int);

        int getRb_flux_type();
        void setRb_flux_type(int);
        int getTb_flux_type();
        void setTb_flux_type(int);
        int getLb_flux_type();
        void setLb_flux_type(int);
        int getBb_flux_type();
        void setBb_flux_type(int);

        double getRb_value();
        void setRb_value(double);
        double getTb_value();
        void setTb_value(double);
        double getLb_value();
        void setLb_value(double);
        double getBb_value();
        void setBb_value(double);

        int getNMax();
        void setNMax(int);
        double getMErr();
        void setMErr(double);
        double getCErr();
        void setCErr(double);
        double getUReference();
        void setUReference(double);
        double getLength();
        void setLength(double);
        double getVisc();
        void setVisc(double);
        double getCFLN();
        void setCFLN(double);
        double gettType();
        void settType(double);

        double ** getU();
        double ** getV();
        double ** getP();


        vector<vector <double>> & getX();
        void setX(vector<vector <double>> &);
        vector<vector <double>> & getY();
        void setY(vector<vector <double>> &);
        vector<vector <double>> & getVol();
        void setVol(vector<vector <double>> &);
        vector<vector <double>> & getXmiddle();
        void setXmiddle(vector<vector <double>> &);
        vector<vector <double>> & getYmiddle();
        void setYmiddle(vector<vector <double>> &);        
        vector<vector <double>> & getdT();   
        vector<vector <double>> & getFlag(); 
        vector <vector <array<double,3>>> & getResidue();        
        void setResidue(vector <vector <array<double,3>>> &);     
        vector <vector <array<array<double,2>,2>>> & getfaceVectors();
        void setfaceVectors(vector <vector <array<array<double,2>,2>>> &);
        







};