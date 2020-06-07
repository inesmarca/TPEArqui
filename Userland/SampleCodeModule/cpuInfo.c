
#include <libC.h>

extern int cpuModel();
extern char * cpuVendor();



int CPUFamily(int chipvalue);
int CPUModel(int chipvalue);

//https://software.intel.com/content/www/us/en/develop/download/intel-64-and-ia-32-architectures-sdm-combined-volumes-1-2a-2b-2c-2d-3a-3b-3c-3d-and-4.html

//la doc para descifrar que significan los numeros, el codigo es mio.

    

    


int CPUModel(int chipvalue){

    //The actual processor model is derived from the Model, Extended Model ID and Family ID fields. 
    //If the Family ID field is either 6 or 15, the model is equal to the sum of the Extended Model ID field shifted left by 4 bits and the Model field.
     //Otherwise, the model is equal to the value of the Model field.
   

    //consigo el numero compuesto 

    int FamilyID=chipvalue  & 0x00000F00;       //mask y corrimiento para conseguir los valores separados en distintas variables
    FamilyID=FamilyID>>8;

    int ModelID= chipvalue  & 0x000000F0;
    ModelID=ModelID>>4;

    int ExtendedModelID=chipvalue & 0x000F0000;
    ExtendedModelID=ExtendedModelID>>16;

    if (FamilyID==6||FamilyID==15)
    {
        ExtendedModelID=ExtendedModelID<<4;
        return ExtendedModelID + ModelID;
    }
    return ModelID; 


}
int CPUFamily(int chipvalue){

//The actual processor family is derived from the Family ID and Extended Family ID fields.
    // If the Family ID field is equal to 15, the family is equal to the sum of the Extended Family ID and the Family ID fields.
    // Otherwise, the family is equal to value of the Family ID field.

    //consigo el numero compuesto 

    int FamilyID=chipvalue  & 0x00000F00;       //mask y corrimiento para conseguir los valores separados en distintas variables
    FamilyID=FamilyID>>8;

    int ExtendedFamilyID=chipvalue & 0x0FF00000;
    ExtendedFamilyID=ExtendedFamilyID>>20;

    if (FamilyID==15){
        return ExtendedFamilyID + FamilyID;
    }
    return FamilyID;

}

void printCPUInfo(){
    int cpuval=cpuModel();
    int Family=CPUFamily(cpuval);
    int Model=CPUModel(cpuval);

    printf("CPU Vendor is: %s ,the procesor family ID is %d and the model ID is %d\n",cpuVendor(),Family,Model);
}

