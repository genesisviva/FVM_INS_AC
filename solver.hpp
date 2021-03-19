#include "functions.hpp"





class solver {



    private:
        gridData mesh;


    public:
        solver();
        void getInputData();
        void getMeshData();
        void setInitial();
        void FVM_INSE();
        void setBound();
        void decomposition();
        void viscidFlux();
        void output(string);
        double calculateTimeStep(vector<vector<double>> &);





};




