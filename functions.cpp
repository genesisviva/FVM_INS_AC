#include <unistd.h>
#include <stdio.h>
#include <string>

double min(double a, double b){
    if(a<b) 
        return(a);
    else 
        return(b);
}

double max(double a, double b){     
    if(a>b) 
        return(a);
    else 
        return(b);
}
double triangle_area(double x1,double y1,double x2,double y2,double x3, double y3){ //Площадь треугольника с соотвествующими координатами
    double area;
    area=x1*(y2-y3)+y1*(x3-x2)+(x2*y3-x3*y2);
    area=0.5*area;
    if(area<0.0) 
        area=-area;
    return(area);
}

std::string getNumber(std::string s){           //Вспомогательная для имени файлов
    auto const posF=s.find_last_of('/');
    auto const posL=s.rfind(".txt");
    std::string ss = s.substr(posF+1, posL-posF-1);
    return ss;
}

int sign(double x){
    if (x>0)
        return 1;
    if (x<0)
        return -1;
    else   
        return 0;
}
