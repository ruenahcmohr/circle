#include <math.h>
#include <stdio.h>
#include "cmnCmdOptions2.h"

#define PI M_PI
#define radius       1
#define circumfrence 2
#define area         3
#define sphereArea   4
#define sphereVolume 5

void circ_R2C(float R, float * C) ;
void circ_R2A(float R, float * A) ;
void circ_A2R(float A, float * R) ;
void circ_C2R(float C, float * R) ;

void sph_SA2R(float SA, float * R) ;
void sph_SV2R(float SV, float * R) ;
void sph_R2SA(float R, float * SA) ;
void sph_R2SV(float R, float * SV) ;

void cyl_LA2V(float L, float A, float * V);
void cyl_VL2A(float V, float L, float * A) ;
void cyl_VA2L(float V, float A, float * L) ;


void setupParams(CLOSet_t ** options) ;
int SetA  (char * argv) ;
int SetR  (char * argv) ;
int SetD  (char * argv) ;
int SetC  (char * argv) ;
int Help  (char * argv) ;
int SetSA (char * argv) ;
int SetSV (char * argv) ;
int SetYL (char * argv) ;

unsigned char given, helpOnly;
unsigned char haveLen;
float R, C, A, SA, SV, L;

int main(int argc, char** argv) {
  CLOSet_t * options;
  
  options  = NULL;
  given    = 0;
  haveLen  = 0;
  helpOnly = 0;
  
  setupParams(&options); // define the arguments
  parseOptions(options, argc-1, &argv[1]);   // then parse the command line
  
  if (helpOnly)
    return 0;
  
  // from whatever we were given last, work out the radius
  
  switch(given) {
    case 0:
      printf("You need to know about the paramiter --help.\n");
      return 1;
    break;
  
    case area:
      circ_A2R(A, &R);
    break;
    
    case circumfrence:
      circ_C2R(C, &R);
    break;
    
    case sphereArea:
      sph_SA2R(SA, &R);
    break;
    
    case sphereVolume:
      sph_SV2R(SV, &R);
    break;
    
    
  }  
  
  circ_R2A(R, &A);
  circ_R2C(R, &C);
  sph_R2SA(R, &SA);
  sph_R2SV(R, &SV);
  
  printf("Radius is :       %f\n", R);
  printf("Diameter is:      %f\n", R*2.0);
  printf("Circumfrence is : %f\n", C);
  printf("Circular area is :%f\n", A);
  printf("Sphere area:      %f\n", SA);
  printf("Sphere volume:    %f\n", SV);
  
  cmdLineOptionFini(&options);
  return 0;

}

void setupParams(CLOSet_t ** options) {

  // this is outright ugly, but we have to because of limits to C
  static char* optsRadius[2] =       {"-r","--radius"};
  static char* optsDiameter[2] =     {"-d","--diameter"};
  static char* optsCircumfrence[2] = {"-c","--circumfrence"};
  static char* optsArea[2] =         {"-a","--area"};
  static char* optsHelp[2] =         {"-h","--help"};
  static char* optsSphereV[2] =      {"-v","--volume"};
  static char* optsSphereA[2] =      {"-A","--spherearea"};
  static char* optsCylL[2] =         {"-l","--length"};

  // first init 
  cmdLineOptionInit(options);
  // then add your options (note I ignore any errors (BAD! BAD!))
  addCmdLineOption(*options, optsRadius, 2, SetR);
  addCmdLineOption(*options, optsDiameter, 2, SetD);
  addCmdLineOption(*options, optsCircumfrence, 2, SetC);
  addCmdLineOption(*options, optsArea, 2, SetA);
  addCmdLineOption(*options, optsHelp, 2, Help);
  addCmdLineOption(*options, optsSphereV, 2, SetSV);
  addCmdLineOption(*options, optsSphereA, 2, SetSA);
  addCmdLineOption(*options, optsCylL, 2, SetYL);
}

int Help (char * argv) {
  printf("This program solves circle (and some sphere) stuff.\n\n");
  printf("-h --help            is the help your looking at\n");
  printf("-a --area N          set the area to N\n");
  printf("-c --circumfrence N  set the circumfrence to N\n");
  printf("-r --radius N        set the radius to N\n");
  printf("-d --diameter N      set the diameter to N\n");
  printf("-v --volume N        set sphere volume to N\n");
  printf("-A --spherearea N    set sphere area to N\n");
  printf("-l --length N        set cylinder length to N\n");
  
  helpOnly = 1;
  return 0;
}

int SetYL (char * argv) {
  L = atof(argv);
  haveLen = 1;
  return 1;
}

int SetR (char * argv) {
  R = atof(argv);
  given = radius;
  return 1;
}

int SetD (char * argv) {
  R = atof(argv)/2;
  given = radius;
  return 1;
}

int SetC (char * argv) {
  C = atof(argv);
  given = circumfrence;
  return 1;
}

int SetA (char * argv) {
  A = atof(argv);
  given = area;
  return 1;
}

int SetSA (char * argv) {
  SA = atof(argv);
  given = sphereArea;
  return 1;
}

int SetSV (char * argv) {
  SV = atof(argv);
  given = sphereVolume;
  return 1;
}


// ----=====| cylinder conversions |=====-----

void cyl_LA2V(float L, float A, float * V){
  *V = A * L;
} 

void cyl_VL2A (float V, float L, float * A) {
  *A = V / L;
}

void cyl_VA2L(float V, float A, float * L) {
  *L = A / V;
}


// ----=====| circle conversions |=====-----

void circ_R2C(float R, float * C) {
  *C = 2.0*PI*R;
}

void circ_R2A(float R, float * A) {
  *A = PI*R*R;
}

void circ_A2R(float A, float * R) {
  *R = sqrt(A/PI);
}

void circ_C2R(float C, float * R) {
  *R = C/(2.0*PI);
}


// ----=====| sphere conversions |=====-----

void sph_SA2R(float SA, float * R) {
  *R = sqrt(SA/(4*PI));
}

void sph_SV2R(float SV, float * R) {
  *R = cbrt(3*SV/(4*PI));
}

void sph_R2SA(float R, float * SA) {
  *SA = 4.0*PI*R*R;
}

void sph_R2SV(float R, float * SV) {
  *SV = (4.0/3.0)*PI*R*R*R;
}
