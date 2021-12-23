#include <math.h>

#define e 2.718
#define PI 3.1415

float logisticUnitCircle(float v){
    return (4*PI)/( 1 + pow(e , (-v))) - (2*PI); // between -2p and p;
}