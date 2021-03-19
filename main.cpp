#include "solver.hpp"
#include <time.h>
#include <sys/time.h>



int main(){

solver temp;
temp.getInputData();
temp.getMeshData();
temp.setInitial();
temp.FVM_INSE();


return(0);

}



