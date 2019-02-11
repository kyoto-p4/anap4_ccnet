#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cfortran.h"
#include <hbook.h>
#include <kernlib.h>

#include "kinema.h"
#include "anap4.h"

int anaevt(int evtlen,unsigned short *rawbuf,struct p4dat *dat){
  int i,ip,j;
  int segsize,ids,ips,ipsn,count;
  unsigned short qdc[N_QDC];
  unsigned short tdc[N_TDC];
  unsigned short sca[N_SCA];
  char tmpbuf[200];

  /************* Clear Event Buffer *****************/
  for(i=0;i<N_QDC;i++) {
    qdc[i]=0;
  }
  for(i=0;i<N_TDC;i++){
    tdc[i]=0;
  }
  for(i=0;i<N_SCA;i++){
    sca[i]=0;
  }
  /*  for(i=0;i<N_ADC;i++){
    adc[i]=0;
    adcc[i]=0.;
  }
  */
  count=0;

  /************* Clear Event Buffer *****************/

  /************* Decode Event Data Here *****************/
  ip=0;
  while(ip<evtlen){  
    int tmpdat,tmpch;

    /** Segment Header ************/
    segsize=rawbuf[ip++];
    ipsn=ip+segsize-1;
    ids=rawbuf[ip++];

#if _DEBUG
    ips=0;
    printf(" New Seg %d\n",ids);
#endif

    while(ip<ipsn){ /*** Segment loop ***/
      /*** 7166 ****/
#if _DEBUG
      pri ntf("  7166\n");
#endif
      for(i=0;i<N_QDC;i++) {
	tmpdat=rawbuf[ip++];
	tmpch=(tmpdat>>12)&0xf;
	qdc[i]=(tmpdat&0xfff);
#if _DEBUG
	sprintf(tmpbuf,"QDC:   %2d: %04x  ch:%02d  adc:%4d\n",i,tmpdat,tmpch,
		qdc[i]);
	dumpmsg(tmpbuf);
#endif
      }
      for(i=0;i<N_TDC;i++) {
	tmpdat=rawbuf[ip++];
	tmpch=(tmpdat>>12)&0xf;
	tdc[i]=(tmpdat&0xfff);
#if _DEBUG
	sprintf(tmpbuf,"TDC:   %2d: %04x  ch:%02d  adc:%4d\n",i,tmpdat,tmpch,
		tdc[i]);
	dumpmsg(tmpbuf);
#endif
      }
      for(i=0;i<N_SCA;i++) {
	tmpdat=rawbuf[ip++];
	tmpch=(tmpdat>>12)&0xf;
	sca[i]=(tmpdat&0xfff);
#if _DEBUG
	sprintf(tmpbuf,"SCA:   %2d: %04x  ch:%02d  adc:%4d\n",i,tmpdat,tmpch,
		sca[i]);
	dumpmsg(tmpbuf);
#endif
      }
      /*      for(i=0;i<N_ADC;i++) {
	tmpdat=rawbuf[ip++];
	tmpch=(tmpdat>>12)&0xf;
	adc[i]=(tmpdat&0xfff);
#if _DEBUG
	sprintf(tmpbuf,"ADC:   %2d: %04x  ch:%02d  adc:%4d\n",i,tmpdat,tmpch,
		adc[i]);
	dumpmsg(tmpbuf);
#endif
}*/
    }
  }
  /**** Decode Event Data Above***************/


  /**** Data Analysis Here ***************/

/* energy calibration */
  /*
    for(i=0;i<N_QDC;i++) {
    qdcc[i]=(qdc[i]-qpar[i][0])*qpar[i][1];
    qdcoff[i]=qdc[i]-qdcp0[i];
    }

  for(i=0;i<N_ADC;i++){
    adcc[i]=(double)adc[i];
  }
  for(i=0;i<N_QDC;i++){
    qdcc[i]=1.*qdc[i];
  }

  for(i=0;i<N_TDC;i++){
    tdcc[i]=1.*tdc[i];
  }
  */

  /**** Data Analysis Above ***************/

  
  /*********** Booking here **********/
  
  for(i=0;i<N_QDC;i++){
    HF1(10+i,qdc[i],1.0);
  }
  for(i=0;i<N_TDC;i++){
    HF1(30+i,tdc[i],1.0);
  }
  for(i=0;i<N_SCA;i++){
    HF1(50+i,sca[i],1.0);
  }

  HF2(70,qdc[0],tdc[0],1.0);
  HF2(71,qdc[0],tdc[1],1.0);

  if(tdc[0]>0){
    HF1(100,qdc[0],1.0);
  }
  if(tdc[0]<4096){
    HF1(101,qdc[0],1.0);
  }
  if(qdc[0]>0){
    HF1(110,tdc[0],1.0);
  }
  if(qdc[0]<4096){
    HF1(111,tdc[0],1.0);
  }
  
  /*********** Booking Above **********/
  return(ip);
}

