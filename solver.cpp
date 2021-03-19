#include "solver.hpp"



using namespace std;

solver::solver(){
    gridData grid;
    this->mesh = grid;
}

void solver::setInitial(){
    mesh.setInitialConditions();
}

void solver::getInputData(){
    string curStr;
    ifstream fin;
    fstream fout;
    fin.open("../input/input.txt",std::ios::in);

    if(fin.fail()){
        cout<<"Error while opening input file"<<endl;
        exit(1);
    }  
    fin>>curStr;
    mesh.setMeshName(curStr);
    cout<<"Mesh file name: "<<mesh.getMeshName()<<endl<<endl;
    getline(fin, curStr);
    fin>>curStr;
    mesh.settType(stod(curStr));
    cout<<"Time step type: "<<mesh.gettType()<<endl<<endl;
    getline(fin,curStr);
    fin>>curStr;
    mesh.setRb_type(stod(curStr));
    getline(fin,curStr);
    fin>>curStr;
    mesh.setRb_flux_type(stod(curStr));
    getline(fin,curStr);
    fin>>curStr;
    mesh.setRb_value(stod(curStr));


    switch (mesh.getRb_type()){
    case 0:
        cout<<"Right boundary type: "<<"solid"<<endl;
        break;
    case 1:
        cout<<"Right boundary type: "<<"solid with slip"<<endl;
        break;
    case 2:
        cout<<"Right boundary type: "<<"inflow"<<endl;
        break;
    case 3:
        cout<<"Right boundary type: "<<"outflow"<<endl;
        break;
    default:
        break;
    }
    switch (mesh.getRb_flux_type())
        {
        case 0:
            cout<<"Right boundary value type: velocity"<<endl;
            cout<<"Right boundary value: "<<mesh.getRb_value()<<endl<<endl;
            break;
        case 1:
            cout<<"Right boundary value type: pressure"<<endl;
            cout<<"Right boundary value: "<<mesh.getRb_value()<<endl<<endl;
            break;
        default:
            break;
        }

    getline(fin,curStr);
    fin>>curStr;
    mesh.setTb_type(stod(curStr));
    getline(fin,curStr);
    fin>>curStr;
    mesh.setTb_flux_type(stod(curStr));
    getline(fin,curStr);
    fin>>curStr;
    mesh.setTb_value(stod(curStr));

    switch (mesh.getTb_type()){
    case 0:
        cout<<"Top boundary type: "<<"solid"<<endl;
        break;
    case 1:
        cout<<"Top boundary type: "<<"solid with slip"<<endl;
        break;
    case 2:
        cout<<"Top boundary type: "<<"inflow"<<endl;
        break;
    case 3:
        cout<<"Top boundary type: "<<"outflow"<<endl;
        break;
    default:
        break;
    }

    switch (mesh.getTb_flux_type())
        {
        case 0:
            cout<<"Top boundary value type: velocity"<<endl;
            cout<<"Top boundary value: "<<mesh.getTb_value()<<endl<<endl;
            break;
        case 1:
            cout<<"Top boundary value type: pressure"<<endl;
            cout<<"Top boundary value: "<<mesh.getTb_value()<<endl<<endl;
            break;
        default:
            break;
        }

    getline(fin,curStr);
    fin>>curStr;
    mesh.setLb_type(stod(curStr));

    getline(fin,curStr);
    fin>>curStr;
    mesh.setLb_flux_type(stod(curStr));
    getline(fin,curStr);
    fin >>curStr;
    mesh.setLb_value(stod(curStr));

    switch (mesh.getLb_type()){
    case 0:
        cout<<"Left boundary type: "<<"solid"<<endl;
        break;
    case 1:
        cout<<"Left boundary type: "<<"solid with slip"<<endl;
        break;
    case 2:
        cout<<"Left boundary type: "<<"inflow"<<endl;
        break;
    case 3:
        cout<<"Left boundary type: "<<"outflow"<<endl;
        break;
    default:
        break;
    }
    switch (mesh.getLb_flux_type())
        {
        case 0:
            cout<<"Left boundary value type: velocity"<<endl;
            cout<<"Left boundary value: "<<mesh.getLb_value()<<endl<<endl;
            break;
        case 1:
            cout<<"Left boundary value type: pressure"<<endl;
            cout<<"Left boundary value: "<<mesh.getLb_value()<<endl<<endl;
            break;
        default:
            break;
        }


    getline(fin,curStr);
    fin>>curStr;
    mesh.setBb_type(stod(curStr));
    getline(fin,curStr);
    fin>>curStr;
    mesh.setBb_flux_type(stod(curStr));
    getline(fin,curStr);
    fin>>curStr;
    mesh.setBb_value(stod(curStr));



    switch (mesh.getBb_type()){
    case 0:
        cout<<"Bottom boundary type: "<<"solid"<<endl;
        break;
    case 1:
        cout<<"Bottom boundary type: "<<"solid with slip"<<endl;
        break;
    case 2:
        cout<<"Bottom boundary type: "<<"inflow"<<endl;
        break;
    case 3:
        cout<<"Bottom boundary type: "<<"outflow"<<endl;
        break;
    default:
        break;
    }

    switch (mesh.getBb_flux_type())
        {
        case 0:
            cout<<"Bottom boundary value type: velocity"<<endl<<endl;
            cout<<"Bottom boundary value: "<<mesh.getBb_value()<<endl<<endl;
            break;
        case 1:
            cout<<"Bottom boundary value type: pressure"<<endl<<endl;
            cout<<"Bottom boundary value: "<<mesh.getBb_value()<<endl<<endl;
            break;
        default:
            break;
        }


    getline(fin,curStr);
    fin>>curStr;
    mesh.setNMax(stod(curStr));
    cout<<"Maximum iterations: "<<mesh.getNMax()<<endl;

    getline(fin,curStr);
    fin>>curStr;
    mesh.setCErr(stod(curStr));
    cout<<"Continuous error: "<<mesh.getCErr()<<endl;

    getline(fin,curStr);
    fin>>curStr;
    mesh.setMErr(stod(curStr));
    cout<<"Moment error: "<<mesh.getMErr()<<endl;


    getline(fin,curStr);
    fin>>curStr; 
    mesh.setDensity(stod(curStr)); 
    cout<<"Density: "<<to_string(mesh.getDensity())<<endl;

    getline(fin,curStr);
    fin>>curStr;
    mesh.setVisc(stod(curStr));
    cout<<"Viscousity: "<<mesh.getVisc()<<endl;

    getline(fin,curStr);
    fin>>curStr;
    mesh.setCFLN(stod(curStr));
    cout<<"CFL number: "<<mesh.getCFLN()<<endl;


    mesh.setLength(1);
    mesh.setUReference(1);


    double RE=mesh.getDensity()*mesh.getUReference()*mesh.getLength()/(mesh.getVisc()+1e-16);
    cout<<"Re = "<<RE<<endl;
    
    cout<<"Press Enter to continue...";
    while(1){
        char c;
        c = getch();
        if (c == 13)
            break;
    }
    

fin.close();
}

