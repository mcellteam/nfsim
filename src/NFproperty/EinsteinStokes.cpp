#include "NFcore.hh"
#include "NFproperty.hh"
#include "NFutil.hh"

using namespace std;
using namespace NFcore;


void EinsteinStokes::getValue(string& value){
    value = "";
}

double EinsteinStokes::getDiffusionValue(){
    double kb = NFutil::convertToDouble(this->getProperty("kb")->getValue());
    double t =  NFutil::convertToDouble(this->getProperty("temperature")->getValue());
    double rs = NFutil::convertToDouble(this->getProperty("rs")->getValue());
    double viscosity = NFutil::convertToDouble(this->getProperty("viscosity")->getValue());
    double pi = 3.141592;
    int complexSize = dynamic_cast<Complex*>(this->getContainer())->getComplexSize();

    return kb*t/(6*pi*viscosity*rs*cbrt(complexSize));
    //KB*T/(6*PI*eta_EC*Rs)
    //KB*T*LOG((eta_PM*h/(Rc*(eta_EC+eta_CP)/2))-gamma)/(4*PI*eta_PM*h)
    return 0;
}
