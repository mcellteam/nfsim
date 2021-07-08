#include "NFcore.hh"
#include "NFproperty.hh"
#include "NFutil.hh"

using namespace std;
using namespace NFcore;


void DerivedDiffusion::getValue(string& value){
    value = "";
}

double DerivedDiffusion::getDiffusionValue(){
    // For large complex aggregates (1 um) diffusing on 2D surface:
    //D_2D = KB*T*LOG((eta_PM*h/(Rc*(eta_EC+eta_CP)/2))-gamma)/(4*PI*eta_PM*h) (Saffman Delbruck)
    //  combining rule for this case is not elaborated here.

    // For small complexes diffusing on 2D surface:
    //D_2D = ~1/Rc  (ref?)
    //  combining rule for this case is the squareroot of the sum of the squares

    // For complexes diffusing in 3D:
    //D_3D = KB*T/(6*PI*eta_EC*Rs) (Einstein Stokes)
    //  combining rule for this case is the cuberoot of the sum of the cubes

    vector<double> subunits2D;
    vector<double> subunits3D;
    double acc =0;
    Complex* complex = dynamic_cast<Complex*>(this->getContainer());
    for(auto it: complex->getComplexMembers()){
        string dimensionality = "";
        it->getProperty("dimensionality")->getValue(dimensionality);
        shared_ptr<DiffusionClass> diffusion = dynamic_pointer_cast<DiffusionClass>(it->getProperty("diffusion_function"));
        if(dimensionality == "2")
            subunits2D.push_back(diffusion->getDiffusionValue());
        else
            subunits3D.push_back(diffusion->getDiffusionValue());
    }

<<<<<<< HEAD
    // cout<<endl<<endl<<"##### In DerivedDiffusion #####"<<endl<<endl;
=======
    //cout<<endl<<endl<<"##### In DerivedDiffusion #####"<<endl<<endl;
>>>>>>> mcell4_dev
    
    // If complex contains any 2D subunits then the whole complex is considered to be a surface complex.
    //   In this case combine only the 2D subunits to derive the 2D diffusion constant
    if (subunits2D.size() > 0){
        // 2D combining rule:
        // Compute squareroot of the sum of the squares:
        for(auto it:subunits2D){
            // Note: if diffusion constant of any 2D member is zero (i.e. is immobile) then whole complex should be immobile
            if (it == 0) {
              return 0;
            }
            acc += pow(it, -2);
        }
        acc =  pow(acc,-(0.5));
    }
    // Only if there are no 2D subunits should the complex be considered to be a volume complex.
    //   In this case combine all the 3D subunits to derive the 3D diffusion constant
    else{
        // 3D combining rule:
        // Compute cuberoot of the sum of the cubes:
        for(auto it:subunits3D){
            // Note: if diffusion constant of any 3D member is zero (i.e. is immobile) then whole complex should be immobile
            if (it == 0) {
              return 0;
            }
            acc += pow(it, -3);
        }
        acc = pow(acc,-(0.3333333333333));
    }
    
    return acc;
}

