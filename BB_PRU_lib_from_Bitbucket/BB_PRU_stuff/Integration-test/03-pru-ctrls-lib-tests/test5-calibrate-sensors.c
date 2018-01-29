#include "jpp-pru-lib.h"
#include <stdio.h> // printf
#include <stdlib.h> // exit
#include <string.h> //  memcpy
#include <unistd.h> // usleep
#include <math.h> // fmod

// Note: run this prog with real-time priority:
// chrt 20 ./test4-sysid

// Note: would be good to reset the eqep counter before each run.
// Todo: do this programatically in main().
// Can do manually from terminal like this.
/* root@beaglebone:/sys/devices/ocp.3/48302000.epwmss/48302180.eqep# ls */
/* driver	enabled  modalias  mode  period  position  power  subsystem  uevent */
/* root@beaglebone:/sys/devices/ocp.3/48302000.epwmss/48302180.eqep# cat position  */
/* -55051167 */
/* root@beaglebone:/sys/devices/ocp.3/48302000.epwmss/48302180.eqep# echo 0 > position */
/* root@beaglebone:/sys/devices/ocp.3/48302000.epwmss/48302180.eqep# cat position  */
/* 0 */
/* root@beaglebone:/sys/devices/ocp.3/48302000.epwmss/48302180.eqep# dmesg | tail */
/* [ 1795.722900] bone-capemgr bone_capemgr.9: slot #11: Applied #3 overlays. */
/* [ 1809.293041] bone-capemgr bone_capemgr.9: part_number 'bone_eqep1', version 'N/A' */
/* [ 1809.293226] bone-capemgr bone_capemgr.9: slot #12: generic override */
/* [ 1809.293273] bone-capemgr bone_capemgr.9: bone: Using override eeprom data at slot 12 */
/* [ 1809.293322] bone-capemgr bone_capemgr.9: slot #12: 'Override Board Name,00A0,Override Manuf,bone_eqep1' */
/* [ 1809.293585] bone-capemgr bone_capemgr.9: slot #12: Requesting part number/version based 'bone_eqep1-00A0.dtbo */
/* [ 1809.293632] bone-capemgr bone_capemgr.9: slot #12: Requesting firmware 'bone_eqep1-00A0.dtbo' for board-name 'Override Board Name', version '00A0' */
/* [ 1809.293696] bone-capemgr bone_capemgr.9: slot #12: dtbo 'bone_eqep1-00A0.dtbo' loaded; converting to live tree */
/* [ 1809.294218] bone-capemgr bone_capemgr.9: slot #12: #3 overlays */
/* [ 1809.308396] bone-capemgr bone_capemgr.9: slot #12: Applied #3 overlays. */




void make_cmd_buf_from_gpio( CommandBuffer*, unsigned int );
void make_cmd_buf_from_gpio( CommandBuffer* pb, unsigned int gpio ) {

  for( int i=0; i<PKTS_PER_CMD_BUFFER; i++ ) {
    (*pb)[i].cycle_count = 0x11111111;
    (*pb)[i].sample_num  = 0x22222222;
    (*pb)[i].gpio        = gpio;
    (*pb)[i].duty        = 0x33333333;
  }
  

}


double adc_to_amps( unsigned int raw_adc ) {
  // From 'raw' adc counts to [0,1] (which is what I calibrated our current with, instead of volts, was 
  //easiest thing to do at the time):                                                                          
  double normalized_adc = raw_adc / 4096.0;

  // From 'noramlized adc' to current (amps)                                                             
  // See (MPC MHE DC motor project dropbox):/Dropbox/DC_motor/Notes/notes.md                             
  // plot                                                                                                
  // ![](Images/2016-07-06-14-40-17.png "Optional title")                                                
  // amps = 7.48 - 14.778 * adc_from_0_to_1                                                              
  //july 6: double amps = 7.48 - 14.778 * normalized_adc;                                                
  // july 22:                                                                                            
  //    double amps = 7.901 - 15.0682 * normalized_adc;                                                  
  // july 27:                                                                                            
  double volts = 1.8 * normalized_adc;
  double amps = 2.73454 - 3.03192 * volts; // hall-effect sensor 2 (w/ no filter capacitor)              
  return amps;
}


// http://stackoverflow.com/a/29871193                                                                     
// http://pastebin.com/vqxHyH18                                                                            
/* wrap x -> [0,max) */
double wrapMax(double x, double max)
{
  /* integer math: `(max + x % max) % max` */
  return fmod(max + fmod(x, max), max);
}
/* wrap x -> [min,max) */
double wrapMinMax(double x, double min, double max)
{
  return min + wrapMax(x - min, max - min);
}


//http://stackoverflow.com/a/4633233                                                                       
/* if( angle_rad > 0 ) { */
/*   wrapped_angle = fmod( angle_rad + M_PI, 2.0 * M_PI) - M_PI; */
/* } */
/* else { */
/*   wrapped_angle = fmod( angle_rad - M_PI, 2.0 * M_PI) + M_PI; */
/* } */




double eqep_to_angle( unsigned int eqep )  {

  // read eqep encoder of motor shaft                                                                    

  //    printf("Shaft: %d\n", eqep1.get_position());                                                       

  // returns "# of stripes observed on the encoder"                                                        
  // - There are 4096 stripes per revolution.                                                              
  // - we also need to wrap the angle to -pi to pi.                                                        

  //  return wrapMinMax( eqep / 4096.0, -M_PI, M_PI );
  // some weird wrapping problem around 0 eqep.
  
  return -(double)(int)eqep/4096.0*2*M_PI;

}



int main() {

  start_pru();



const  unsigned int stby = 0;
const  unsigned int ain1 = 1;
const  unsigned int ain2 = 2;
const  unsigned int pwm  = 5;
const  unsigned int lo = 0;
const  unsigned int hi = 1;

  const unsigned int gpio_mask = (hi << stby) | (hi << ain1) | (hi << ain2) | (hi << pwm);

const  unsigned int STBY = (lo << stby) | (lo << ain1) | (lo << ain2) | (lo << pwm);
const  unsigned int BRAKE= (hi << stby) | (lo << ain1) | (hi << ain2) | (lo << pwm);
const  unsigned int CW   = (hi << stby) | (hi << ain1) | (lo << ain2) | (hi << pwm);
const  unsigned int CCW  = (hi << stby) | (lo << ain1) | (hi << ain2) | (hi << pwm);


  printf("0x%x\t0x%x\t0x%x\t0x%x\n",STBY,BRAKE,CW,CCW);


  unsigned int cmds[]={
    STBY,
    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    CCW,    BRAKE,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CW,    CCW,    BRAKE,    CCW,    CCW,    CCW,    BRAKE,    CCW,    BRAKE,    CCW,    CW,    CCW,    BRAKE,    CCW,    CW,    CCW,    BRAKE,    CCW,    BRAKE,    CCW,    CW,    CCW,    CW,    CCW,    BRAKE,    CCW,    BRAKE,    CCW,    BRAKE,    CCW,    CW,    CCW,    BRAKE,    CCW,    CW,    CCW,    BRAKE,    CCW,    BRAKE,    CCW,    CW,    CCW,    CW,    CCW,    BRAKE,    CCW,    BRAKE,    CCW,    CW,    CCW,    BRAKE,    CCW,    CW,    CCW,    BRAKE,    CCW,    CW,    CCW,    CW,    CCW,    BRAKE,    CCW,    BRAKE,    CCW,    CW,    BRAKE,    CCW,    CW,    CCW,    BRAKE,    CCW,    CW,    CCW,    CW,    CCW,    CW,    CCW,    BRAKE,    CCW,    CW,    CCW,    CW,    CCW,    CW,    CCW,    CW,    CCW,    CW,    CCW,    CW,    CCW,    BRAKE,    CCW,    CW,    BRAKE,    CW,    CCW,    CW,    CCW,    CW,    CCW,    CW,    CCW,    CW,    CCW,    CW,    CCW,    CW,    BRAKE,    CW,    CCW,    CW,    CCW,    CW,    CCW,    CW,    BRAKE,    CW,    CCW,    CW,    BRAKE,    CW,    CCW,    CW,    CCW,    CW,    CCW,    CW,    BRAKE,    CW,    BRAKE,    CW,    CCW,    CW,    BRAKE,    CW,    CCW,    CW, STBY };

  const int num_cmds = 20;

  //  CommandBuffer b;
  DataBuffer data_buf[num_cmds];

  for( int i=0; i<num_cmds; i++ ) {
    
    //    unsigned int cmd = cmds[i];

    get_data_buf( &(data_buf[i]) );

    //    make_cmd_buf_from_gpio(&b, cmd);

    //    set_cmd_buf( b );

    usleep(160000);  // wait until new cmd buffer

  }


  // There's 194 data buffers, each with 32 data packets. Many buffers overlap. Just write them all.


  //  FILE * fp;
  //  fp = fopen ("sysid-data.txt", "w+");

  double N = num_cmds*PKTS_PER_DATA_BUFFER;
  double ave_adc = 0;

  for( int i=0; i<num_cmds; i++ ) {

    for( int j=0; j<PKTS_PER_DATA_BUFFER; j++ ) {

      DataPacket p = data_buf[i][j];

      unsigned int gpio_cmd = p.gpio & gpio_mask;

      //      float v;

      /* if( gpio_cmd == CW )                        v = 4.0; */
      /* else if( gpio_cmd == CCW )                  v = -4.0; */
      /* else if( gpio_cmd == BRAKE || gpio_cmd == STBY ) v = 0.0; */
      /* else                                   v = 9999; */

      /* fprintf(fp,"cycle: %u sample: %d adc: %d eqep: %d gpio: %x duty: %d last-data-req: %u last-cmd: %u amps: %f angle: %f volts: %f\n", */
      /* 	     p.cycle_count, */
      /* 	     p.sample_num, */
      /* 	     p.adc, */
      /* 	     p.eqep, */
      /* 	     p.gpio, */
      /* 	     p.duty, */
      /* 	     p.last_data_req, */
      /* 	     p.last_cmd_sch, */
      /* 	     adc_to_amps(p.adc), */
      /* 	     eqep_to_angle(p.eqep),	  */
      /* 	     v */
      /* 	     ); */

      printf("%d ",p.adc);
      ave_adc += p.adc/N;
    }
    printf("\n");
  }

  printf("\nAve adc: %lf\n",ave_adc);



  //  fclose(fp);


  //////////////

  return(0);
}
