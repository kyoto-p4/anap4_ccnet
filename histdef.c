
#include <stdio.h>
#include "cfortran.h"
#include <kernlib.h>
#include <hbook.h>
#include "anap4.h"


int histdef(){
  int i;
  char hnam[100];

  for(i=0;i<N_QDC;i++){
    sprintf(hnam,"QDC %02d",i);
    HBOOK1(10+i,hnam,4096,0.,4096.,0);
  }
  for(i=0;i<N_TDC;i++){
    sprintf(hnam,"TDC %02d",i);
    HBOOK1(30+i,hnam,4096,0.,4096.,0);
  }
  for(i=0;i<N_SCA;i++){
    sprintf(hnam,"SCA %02d",i);
    HBOOK1(50+i,hnam,4096,0.,4096.,0);
  }
  /*
  for(i=0;i<N_ADC;i++){
    sprintf(hnam,"ADC %02d",i);
    HBOOK1(30+i,hnam,4096,0.,4096.,0);
  }*/


  HBOOK2(70,"QDC vs TDC0",512,0.,4096.,512,0.,4096.,0);
  HBOOK2(71,"QDC vs TDC1",512,0.,4096.,512,0.,4096.,0);

  HBOOK1(100,"QDC_n cut by TDC",4096,0.,4096.,0);
  HBOOK1(101,"QDC_gamma cut by TDC",4096,0.,4096.,0);
  HBOOK1(110,"TDC_n cut by QDC",4096,0.,4096.,0);
  HBOOK1(111,"TDC_gamma cut by QDC",4096,0.,4096.,0);

  return(1);
}
