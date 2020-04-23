#include <NFapiAux.hh>
#include <NFinput/NFinput.hh>


using namespace std;

string calculateOriginalCompartment(string referenceSpecies, map<string, string> originalCompartments){
    map<int, vector<shared_ptr<NFinput::componentStruct>>> componentList;
    //a list containing an id-> molecule name equivalence list
    map<int, string> moleculeIndex; 
    map<int, string> moleculeCompartment;
    //stores molecule and component information
    vector<shared_ptr<NFinput::componentStruct>> componentIndex;
    vector<pair<int, int>> bondNumbers;

    map<string, string> speciesCompartmentMap;

    NFinput::transformComplexString(referenceSpecies, componentList, moleculeIndex, moleculeCompartment, 
                           componentIndex, bondNumbers);


    string speciesCompartment;
    // For now removing this section to use the nauty string as the source  
    // for compartment information 
    
    // for(auto it: moleculeIndex){
    //     speciesCompartment = originalCompartments[it.second];
    // }

    // This section for now will be used to return the compartment
    for (auto it: moleculeCompartment){
        // std::cout << "NFapiAux, it.first:" << it.first << " it.second " << it.second << std::endl;
        // std::cout << "NFapiAux, comparment:" << moleculeCompartment[it.second] << std::endl;
	speciesCompartment = it.second;
    }

    // std::cout << "NFapiAux, string: " <<  referenceSpecies << " returning compartment info: " << speciesCompartment << std::endl;
    return speciesCompartment;
}
