

#include "jpp-pru-lib.h"
#include "util-jpp.h"
#include <math.h>

// To get usleep:
#define _POSIX_C_SOURCE199309L  // dammit, weird posix stuff. usleep specified in some versions of posix, not in others, and it's obsolete in favor of nanosleep, which takes shitty timespec arguments.
// warning: implicit declaration of function ‘usleep’ [-Wimplicit-function-declaration]
// see https://ubuntuforums.org/showthread.php?t=1146543
// note: changing to nanosleep not a great option
#include <time.h> // usleep, clock_gettime


/* WHEN USING NEWLY GENERATED CODE, UPDATE THIS FUNCTION AS FOLLOWS:   */ 
/* 	1) Find all functions that being with 'tmpC_TS_20160916_164531_354725_classname' and replace with the new classname.   
	2) Check to make sure the following are updated to the correct values.
			a) 	#define HORIZON_L 5
				#define HORIZON_T 10 
			
			b) 	double Ts = .005;
				double switchTol = .99;
                double omegaRef=1.8*3.141592653589793;
			
			c)	double Vsupply[] = {7};
		  		double Vswitches[] = {1};
				double Vdiodes[] = {1.2};

				double RM = 2.35;
				double LM = .001;
				double inv_LM[] =
				double JM =
				double inv_JM[] = 
				double bM[] = 
				double Kb[] = 
				double KM[] = 

			d)  double refWeight[] = {1};
  				double uWeight[] = {1.0e-5};
  				double nWeight[] = {100000};
  				double dWeight[] = {1000};

  	3) Remember to set mu0 to something sensible and adjust if necessary.		   	

*/




// shitty function that writes an array to a file.
void ughprint(FILE* fp, double* a, int len);

void ughprint(FILE* fp, double* a, int len) {
      for( int i=0; i<len; i++ ) {
          fprintf(fp,"%lg ",a[i]);
      }


  // fprintf(fp,"\n");
}

// void ughprint2(double (*) a_buffer[], int tstep, double* a, int len);

// void ughprint2(double (*) a_buffer[], int tstep, double* a, int len) {
// for( int i=0; i< len; i++ ) {
// 	a_buffer[tstep][i] = a[i];
// }
// }

// void ughwrite(FILE* fp, double* a_buffer[], int len, int MAX_TSTEPS);

// void ughwrite(FILE* fp, double* a_buffer[], int len, int MAX_TSTEPS)  {
// 	for( int i=0; i<MAX_TSTEPS; i++ ) {
// 		ughprint(fp, a_buffer[i], len);
// 	}
// }



// sign() or sgn() function. This may be slow (comparisons)...? 
double sign(double x) 
{
    if(x > 0) return 1;
    if(x < 0) return -1;
    return 0;
}



int main(int argc, char* argv[]) {


    double pid_gain = argc > 1 ? atof(argv[1]) : .50 ;
    double pid_Ki   = argc > 2 ? atof(argv[2]) : .4  ;
    printf("\nPID gain: %lf Ki: %lf\n",pid_gain, pid_Ki);
    double sum_angle_error = 0.0;



  ////////////////////
  // Begin hw setup

  start_pru();



    // Stop motor.
    printf("Stopping motor...\n");
    send_single_voltage( 0 );



  

  // Horizon Lengths:
#define HORIZON_L 3
#define HORIZON_T 5
#define HORIZON_S 1
#define PI 3.141592653589793


  int fid = 1; //stdout? jpp: hopefully this will just dump output to cmd line...

  // jpp: file to hold results, ugh
  FILE* fp;
FILE* flog;

    fp = fopen("mpc-data.txt", "w");
    fprintf(stderr,"NOTE: Writing results to file: mpc-data.txt\n");
    flog = fopen("runlog.txt","w");
    fprintf(stderr,"NOTE: Writing log to file: runlog.txt\n");


  
  ////////////////////////////////////////////////////
  // Set parameters (fixed over all iters)
    
  /* define and set parameters */
  double Vsupply[] = {MAX_MOTOR_VOLTAGE};
  tmpC_TS_20160928_153333_055989_classname_set_Vsupply(Vsupply);


  double RM[] = {2.62}; // with 1 inductor from Amazon
  tmpC_TS_20160928_153333_055989_classname_set_RM(RM);
  
  double LM = .0259; // with 1 inductor from Amazon
  double inv_LM[] = {1.0/LM};
  tmpC_TS_20160928_153333_055989_classname_set_inv_LM(inv_LM); 
  
  double JM = 3.75e-6; // 5e-6; // 2.2e-6;
  double inv_JM[] = {1.0/JM};
  tmpC_TS_20160928_153333_055989_classname_set_inv_JM(inv_JM); 
  
  double bM[] = {1.3e-5}; // {3e-6}; // {5e-8};
  tmpC_TS_20160928_153333_055989_classname_set_bM(bM);
   
  double Kb[] = {.01}; // {.013}; //{.01}; 
  tmpC_TS_20160928_153333_055989_classname_set_Kb(Kb);

  double KM[1*1] = {.01}; // {.013}; // {.01}; 
  tmpC_TS_20160928_153333_055989_classname_set_KM(KM);
    

  double Ts = .020;  // ms

  
  double uMax = Vsupply[0]; // max voltage that we'll apply to the motor // Old: Vsupply[0] - Vswitches[0];
           
    

  /* define weights */
  double refWeight[] = {1000};
  double uWeight[] = {1e-6};
  double nWeight[] = {1.0e12};
  double dWeight[] = {1.0e7};

  /* set weights */
  tmpC_TS_20160928_153333_055989_classname_set_refWeight(refWeight);
  tmpC_TS_20160928_153333_055989_classname_set_uWeight(uWeight);
  tmpC_TS_20160928_153333_055989_classname_set_nWeight(nWeight);
  tmpC_TS_20160928_153333_055989_classname_set_dWeight(dWeight);


  ///////////////////////////////////////////////////////////
  // Init variables that will change each iter

	
  /* define past data */
  double upast[1*HORIZON_L] = {};
  double ypast[1*(HORIZON_L+1)] = {};
  double uapply[1*HORIZON_S] = {};
  tmpC_TS_20160928_153333_055989_classname_set_upast(upast);
  tmpC_TS_20160928_153333_055989_classname_set_ypast(ypast);
  tmpC_TS_20160928_153333_055989_classname_set_uapply(uapply);


  double initU[1*(HORIZON_T-HORIZON_S)] = {}; 
  tmpC_TS_20160928_153333_055989_classname_set_u(initU);
    

  //////////Pick something reasonable for first iteration, then use output of optimization //////////////
  // States: current, shaft ang vel, shaft angle
  double x0[] = {0,0,0}; // jpp: uh, dunno: .01*randn(n,1) in mpc_dcmotor.m
  // start at the new value of x0 from the prev iter.
  tmpC_TS_20160928_153333_055989_classname_set_x0(x0);

  double initD[1*HORIZON_L+HORIZON_T] = {};
  tmpC_TS_20160928_153333_055989_classname_set_d(initD);

  double initX[3*(HORIZON_T+HORIZON_L-1)] = {};
  tmpC_TS_20160928_153333_055989_classname_set_x(initX);
           
  double P1lambda1_[1*(HORIZON_T-HORIZON_S)] = {};
  tmpC_TS_20160928_153333_055989_classname_set_P1lambda1_(P1lambda1_);
            
  double P1lambda2_[1*(HORIZON_T-HORIZON_S)] = {};
  tmpC_TS_20160928_153333_055989_classname_set_P1lambda2_(P1lambda2_);
             
  double P2lambda1_[1*HORIZON_L+HORIZON_T] = {};
  tmpC_TS_20160928_153333_055989_classname_set_P2lambda1_(P2lambda1_);
             
  double P2lambda2_[1*HORIZON_L+HORIZON_T] = {};
  tmpC_TS_20160928_153333_055989_classname_set_P2lambda2_(P2lambda2_);
            
  double P1nux1_[3*(HORIZON_L+HORIZON_T-1)] = {};
  tmpC_TS_20160928_153333_055989_classname_set_P1nux1_(P1nux1_);

  double P2nux1_[3*(HORIZON_L+HORIZON_T-1)] = {};
  tmpC_TS_20160928_153333_055989_classname_set_P2nux1_(P2nux1_);
             
  /*======================================================================================*/

  // optimization parameters
  double mu0[] = {10};
  int32_t maxIter[] = {20};
  int32_t saveIter[] = {-1};


  // Vars that the getOutputs function will write to about how the optimization is going:
  int32_t *status;
  int32_t *iter;

  double  *time;
  if ((status=malloc(sizeof(int32_t)*(1)))==NULL) exit(1);
  if ((iter=malloc(sizeof(int32_t)*(1)))==NULL) exit(1);
  if ((time=malloc(sizeof(double)*(1)))==NULL) exit(1);
    

  // Vars to store the outputs, i.e.,
  // (tmpC_TS_20160719_150909_311901_classname_getOutputs(y1,y2,y3,y4,y5,y6,y7,y8,y9,y10,y11,y12,y13);)

  // [optJ,optU,optD,optX,optX0,optIM,optOmega,optTheta,optEnergy,optNoise,opt_bM,opt_KM,opt_Kb_by_LM]=getOutputs(obj);

  double *optJ;
  double *optU;
  double *optD;
  double *optX;
  double *optX0;
  double *optIM;
  double *optOmega;
  double *optTheta;
  double *optEnergy;
  double *optNoise;
    
    
  /* allocate memory for outputs */
  if ((optJ          = malloc(sizeof(double)))==NULL) exit(1);
  if ((optU          = malloc(sizeof(double)*(1*HORIZON_T-HORIZON_S)))==NULL) exit(1);
  if ((optD          = malloc(sizeof(double)*(1*(HORIZON_T+HORIZON_L))))==NULL) exit(1);
  if ((optX          = malloc(sizeof(double)*(3*(HORIZON_T+HORIZON_L-1))))==NULL) exit(1);
  if ((optX0         = malloc(sizeof(double)*(3*1)))==NULL) exit(1);
  if ((optIM         = malloc(sizeof(double)*(1*(HORIZON_T+HORIZON_L))))==NULL) exit(1);
  if ((optOmega      = malloc(sizeof(double)*(1*(HORIZON_T+HORIZON_L))))==NULL) exit(1);
  if ((optTheta      = malloc(sizeof(double)*(1*(HORIZON_T+HORIZON_L))))==NULL) exit(1);
  if ((optEnergy     = malloc(sizeof(double)))==NULL) exit(1);
  if ((optNoise      = malloc(sizeof(double)*(1*(HORIZON_L+1))))==NULL) exit(1);

  
  double *z;
  double *nu;
  double *lambda;
  double *dZ_s;
  double *dNu_s;
  double *dLambda_s;
  double *G;
  double *F;
  double *primaAlpha_s;
  double *dualAlpha_s;
  double *finalAlpha;

  // copied from server code tmpC_DCmotor_server.c
  if ((z=malloc(sizeof(double)*(36*201)))==NULL) exit(1);
  if ((nu=malloc(sizeof(double)*(42*201)))==NULL) exit(1);
  if ((lambda=malloc(sizeof(double)*(24*201)))==NULL) exit(1);
  if ((dZ_s=malloc(sizeof(double)*(36*200)))==NULL) exit(1);
  if ((dNu_s=malloc(sizeof(double)*(42*200)))==NULL) exit(1);
  if ((dLambda_s=malloc(sizeof(double)*(24*200)))==NULL) exit(1);
  if ((G=malloc(sizeof(double)*(21*201)))==NULL) exit(1);
  if ((F=malloc(sizeof(double)*(24*201)))==NULL) exit(1);
  if ((primaAlpha_s=malloc(sizeof(double)*(201)))==NULL) exit(1);
  if ((dualAlpha_s=malloc(sizeof(double)*(201)))==NULL) exit(1);
  if ((finalAlpha=malloc(sizeof(double)*(201)))==NULL) exit(1);


  /* if ((z=malloc(sizeof(double)*((HORIZON_T+(HORIZON_L+HORIZON_T)+(3*(HORIZON_L+HORIZON_T)))*201)))==NULL) exit(1);    		  // primal variables: u,d,x,x0    HORIZON_T+(HORIZON_L+HORIZON_T)+(3*(HORIZON_L+HORIZON_T)) */

  /* if ((nu=malloc(sizeof(double)*((2*(3*(HORIZON_T-HORIZON_S+HORIZON_L-1)))*201)))==NULL) exit(1);   		 */
  /* // 2*(3*(HORIZON_T+HORIZON_L-1)) */

  /* if ((lambda=malloc(sizeof(double)*(((2*HORIZON_T+2*(HORIZON_L+HORIZON_T))*201))))==NULL) exit(1);	       */
  /* // dual variables: u,d   (2*HORIZON_T+2*(HORIZON_L+HORIZON_T) */

  /* if ((dZ_s=malloc(sizeof(double)*((HORIZON_T+(HORIZON_L+HORIZON_T)+(3*(HORIZON_L+HORIZON_T)))*200)))==NULL) exit(1);		  // (HORIZON_T)+(HORIZON_L+HORIZON_T)+(3*(HORIZON_L+HORIZON_T)) */

  /* if ((dNu_s=malloc(sizeof(double)*((2*(3*(HORIZON_T+HORIZON_L-1)))*200)))==NULL) exit(1);		 */
  /* //	2*(3*(HORIZON_T+HORIZON_L-1)) */
  /* if ((dLambda_s=malloc(sizeof(double)*(((2*HORIZON_T+2*(HORIZON_L+HORIZON_T))*200))))==NULL) exit(1);	 */
  /* // (2*HORIZON_T+2*(HORIZON_L+HORIZON_T) */
  /* if ((G=malloc(sizeof(double)*((3*(HORIZON_T+HORIZON_L-1))*201)))==NULL) exit(1);			 */
  /* // equality constraints: 3*(HORIZON_T+HORIZON_L-1) */
  /* if ((F=malloc(sizeof(double)*(((2*HORIZON_T+2*(HORIZON_L+HORIZON_T))*201))))==NULL) exit(1);			 */
  /* // inequality constraints: (2*HORIZON_T+2*(HORIZON_L+HORIZON_T) */
  /* if ((primaAlpha_s=malloc(sizeof(double)*(201)))==NULL) exit(1);	//  */
  /* if ((dualAlpha_s=malloc(sizeof(double)*(201)))==NULL) exit(1);	// */
  /* if ((finalAlpha=malloc(sizeof(double)*(201)))==NULL) exit(1);		// */


    
  /////////////////////////////////////////////////////////////
  // Main FOR loop (timesteps)
  const int MAX_TSTEPS = argc > 3 ? atoi(argv[3]) : 200  ;



  double cputime[MAX_TSTEPS];
  double cputimediff[MAX_TSTEPS];
  unsigned int sns[MAX_TSTEPS];



  double optU_buffer[MAX_TSTEPS][1*(1*HORIZON_T-HORIZON_S)];
  double optD_buffer[MAX_TSTEPS][1*(1*(HORIZON_T+HORIZON_L))];
  double optX_buffer[MAX_TSTEPS][1*(3*(HORIZON_T+HORIZON_L-1))];
  double optX0_buffer[MAX_TSTEPS][1*(3*1)];
  double optIM_buffer[MAX_TSTEPS][1*(1*(HORIZON_T+HORIZON_L))];
  double optOmega_buffer[MAX_TSTEPS][1*(1*(HORIZON_T+HORIZON_L))];
  double optTheta_buffer[MAX_TSTEPS][1*(1*(HORIZON_T+HORIZON_L))];
  double optNoise_buffer[MAX_TSTEPS][1*(1*(HORIZON_L+1))];
  double optJ_buffer[MAX_TSTEPS][1];
  double optEnergy_buffer[MAX_TSTEPS][1];

  double t_buffer[MAX_TSTEPS][1*(1)];

  double status_buffer[MAX_TSTEPS][1*(1)];
  double iter_buffer[MAX_TSTEPS][1*(1)];
  double time_buffer[MAX_TSTEPS][1*(1)];
  

  double ref_buffer [MAX_TSTEPS][1*(1*(HORIZON_T-1))];

  DataBuffer db_buffer[MAX_TSTEPS];
  CommandBuffer cb_buffer[MAX_TSTEPS];
   CommandBuffer cb_rx[MAX_TSTEPS];

   for( int i=0; i<MAX_TSTEPS; i++ ) {
     init_data_buf( db_buffer[i] );
   }
   for( int i=0; i<MAX_TSTEPS; i++ ) {
     init_cmd_buf( cb_buffer[i] );
   }
   for( int i=0; i<MAX_TSTEPS; i++ ) {
     init_cmd_buf( cb_rx[i] );
   }


 // read fake data into buffer

 /* const char* filename_fake_upasts = "past_inputs.txt"; */
 /* const char* filename_fake_ypasts = "measurements.txt"; */
 /* const char* filename_fake_optUs  = "opt_inputs.txt"; */
 /* const char* filename_fake_refs  = "reference.txt"; */

 /* FILE* file_fake_upasts = fopen(filename_fake_upasts,"r"); */
 /* FILE* file_fake_ypasts = fopen(filename_fake_ypasts,"r"); */
 /* FILE* file_fake_optUs  = fopen(filename_fake_optUs,"r"); */
 /* FILE* file_fake_refs  = fopen(filename_fake_refs,"r"); */

 /* if( file_fake_upasts == NULL ||  file_fake_ypasts == NULL ||  file_fake_optUs == NULL ||  file_fake_refs == NULL) { */
 /*   printf("File not found!!\n"); */
 /* } */

 /* fprintf(stderr,"NOTE: FAKING OUT FROM %s, %s, %s, %s\n",filename_fake_upasts, filename_fake_ypasts, filename_fake_optUs, filename_fake_refs); */



 /* double fake_upasts[MAX_TSTEPS][1*HORIZON_L]; */
 /* for( int i=0; i<MAX_TSTEPS; i++) { */
 /*   for( int j=0; j<1*HORIZON_L; j++ ) { */
 /*     if( fscanf(file_fake_upasts, "%lf", &(fake_upasts[i][j])) <= 0 ) {  */
 /*       printf("!!!!!!!!!!!!!!!!!!!End of file %s i=%d, j=%d, were you expecting this??.\n", filename_fake_upasts,i,j);  */
 /*     break;  */
 /*   } */
 /*   } */
 /* } */
 /* double fake_ypasts[MAX_TSTEPS][1*(HORIZON_L+1)]; */
 /* for( int i=0; i<MAX_TSTEPS; i++) { */
 /*   for( int j=0; j<1*(HORIZON_L+1); j++ ) { */
 /*     if( fscanf(file_fake_ypasts, "%lf", &(fake_ypasts[i][j])) <= 0 ) {  */
 /*       printf("!!!!!!!!!!!!!!!!!!!End of file %s i=%d, j=%d, were you expecting this??.\n", filename_fake_ypasts,i,j);  */
 /*     break;  */
 /*   } */
 /*   } */
 /* } */
 /* double fake_optUs[MAX_TSTEPS][1*(1*HORIZON_T)]; */
 /* for( int i=0; i<MAX_TSTEPS; i++) { */
 /*   for( int j=0; j<1*(HORIZON_T); j++ ) { */
 /*     if( fscanf(file_fake_optUs, "%lf", &(fake_optUs[i][j])) <= 0 ) {  */
 /*       printf("!!!!!!!!!!!!!!!!!!!End of file %s i=%d, j=%d, were you expecting this??.\n", filename_fake_optUs,i,j);  */
 /*     break;  */
 /*   } */
 /*   } */
 /* } */
 /* double fake_refs[MAX_TSTEPS][1*(1*HORIZON_T-1)]; */
 /* for( int i=0; i<MAX_TSTEPS; i++) { */
 /*   for( int j=0; j<1*(HORIZON_T-1); j++ ) { */
 /*     if( fscanf(file_fake_refs, "%lf", &(fake_refs[i][j])) <= 0 ) {  */
 /*       printf("!!!!!!!!!!!!!!!!!!!End of file %s i=%d, j=%d, were you expecting this??.\n", filename_fake_refs,i,j);  */
 /*     break;  */
 /*   } */
 /*   } */
 /* } */

 double pru_time_sec = 0;
 double pru_time_sec_old = 0;
 

 //////////////////////////////
 // Main loop

  for(int tstep=0; tstep<MAX_TSTEPS; tstep++ ) {
    if( tstep % 1 == 0 ) {
      fprintf(flog,"\n======================\ntop of tstep=%d\n",tstep);
    }


    toc(&(cputime[tstep]), &(cputimediff[tstep]) );

    unsigned int cc_top = get_cycle_count();
    printf("top. tstep: %u cputime: %lf cputimediff: %lf cc: %u\n",tstep, cputime[tstep], cputimediff[tstep], cc_top);

      
    /* if( tstep == 14 ) { */
    /*   fprintf(flog,"\n\noh my!!!\n\n"); */
    /* } */

      /* fprintf(flog,"\nFake upasts:\n"); */
      /* for( int j=0; j<1*HORIZON_L; j++ ) { */
      /* 	fprintf(flog,"%lf ", fake_upasts[tstep][j]); */
      /* } */

      /* fprintf(flog,"\nFake ypasts:\n"); */
      /* for( int j=0; j<1*(HORIZON_L+1); j++ ) { */
      /* 	fprintf(flog,"%lf ", fake_ypasts[tstep][j]); */
      /* } */

      /* fprintf(flog,"\nFake optUs:\n"); */
      /* for( int j=0; j<1*(HORIZON_T); j++ ) { */
      /* 	fprintf(flog,"%lf ", fake_optUs[tstep][j]); */
      /* } */
      
      /* fprintf(flog,"\nFake refs:\n"); */
      /* for( int j=0; j<1*(HORIZON_T-1); j++ ) { */
      /* 	fprintf(flog,"%lf ", fake_refs[tstep][j]); */
      /* } */
      /* fprintf(flog,"\n"); */


    DataBuffer db;
    get_data_cmd_bufs( &(db_buffer[tstep]), &(cb_rx[tstep]) ); // write it to the huge history of buffers for writing the data file later,

    printf("got data. samp num of last: %u cc of last: %u\n", db_buffer[tstep][PKTS_PER_DATA_BUFFER-1].sample_num,  db_buffer[tstep][PKTS_PER_DATA_BUFFER-1].cycle_count);

    /* fprintf(stderr, "\nData pkt:\n"); */
    /* fprintf_data_buf_nl( stderr, db_buffer[tstep] ); */
    /* fprintf(stderr, "\nCmd pkt:\n"); */
    /* fprintf_cmd_buf_nl(stderr, cb_rx[tstep] ); */

    // and also give it a shorter name. copy into db
    for( int k=0; k<PKTS_PER_DATA_BUFFER; k++ ) {

      db[k].cycle_count = db_buffer[tstep][k].cycle_count;
      db[k].sample_num = db_buffer[tstep][k].sample_num;
      db[k].adc = db_buffer[tstep][k].adc;
      db[k].eqep = db_buffer[tstep][k].eqep;
      db[k].gpio = db_buffer[tstep][k].gpio;
      db[k].duty = db_buffer[tstep][k].duty;
      db[k].last_data_req = db_buffer[tstep][k].last_data_req;
      db[k].last_cmd_sch = db_buffer[tstep][k].last_cmd_sch;

    }

    // Sample number that our Vm's should start at:
    unsigned int sn = db[PKTS_PER_DATA_BUFFER-1].sample_num;
    unsigned int sample_num = sn + 1; // db[PKTS_PER_DATA_BUFFER-1].sample_num+1;
    sns[tstep] = sn;

      fprintf(flog, "Time: %15.9lf diff: %15.9lf getsampnum: %5u ",cputime[tstep], cputimediff[tstep], sns[tstep]);


    // Compute pru time, time vector (t), and reference (ref):

  // Grab the current cycle time; that's pretty much the current time.
  // CPU needs to know the current time for computing the reference.

  /* setP_t(obj,t); */
  pru_time_sec = (db[PKTS_PER_DATA_BUFFER-1].cycle_count)/(double)PRU_TICKS_PER_SEC;
  fprintf(flog,"pru time: %f (delta: %f) status: %d iter: %d time: %lf\n",pru_time_sec,pru_time_sec-pru_time_sec_old,status[0],iter[0],time[0]);
  pru_time_sec_old = pru_time_sec;

  //  pru_time_sec = Ts * tstep; // !!!!!!!!!!!!!!!!! hijacking pru time for testing.


  double t[HORIZON_L+HORIZON_T] = {};
  for(int j=0; j<HORIZON_T+HORIZON_L; j++ ) {
    t[j] = pru_time_sec + Ts*(j-HORIZON_L); // units: sec
  }

  tmpC_TS_20160928_153333_055989_classname_set_t(t);


  double ref[1*(HORIZON_T-1)] = {};
  double omegaRef= 2*PI; // 0.01*PI; // units: rad/sec

  for(int j=0; j<(HORIZON_T-1); j++) {
    ref[j] = PI/2.0; // 2*PI * sign(sin(omegaRef*t[j+HORIZON_L+1])); // PI/2; // 0.0*PI/2.0*sign(sin(omegaRef*t[j+HORIZON_L+1])); 
    // ref[j] = fake_refs[tstep][j]; // !!!
  }
  tmpC_TS_20160928_153333_055989_classname_set_ref(ref);

    // Most up-to-date values are the last data packets in the buffer:
    // double current = adc_to_amps(db[PKTS_PER_DATA_BUFFER-1].adc);
    // double shaft_angle = eqep_to_angle( db[PKTS_PER_DATA_BUFFER-1].eqep );
    

    // If timestep is not the first one,
    //    Populate from prev tstep's output.
    if( tstep>0) {
      
      // upast is HORIZON_L long: 
      // double upast[1*HORIZON_L] = {};


      // upast[0] is chronologically oldest motor voltage.
      // upast[HORIZON_L-1] is the newest motor voltage.
      // ypast is 2*HORIZON_L+2 long because there are 2 sensors: current and shaft angle;
      //
      // double ypast[2*(HORIZON_L+1)] = {};
      // ypast is ordered so that ypast[0] is the oldest current, ypast[1] is the oldest angle,
      //    ypast[2] is the second-to-oldest current, ypast[3] is the second-to-oldest angle,
      //    ...
      //    ypast[2*HORIZON_L] is the newest current
      //    ypast[2*HORIZON_L+1] is the newest angle.

      fprintf(flog, "upast: ");
      for( int i=0; i<HORIZON_L; i++ ) {
	upast[i] = gpio_duty_to_motor_voltage_cmd(
			  db[PKTS_PER_DATA_BUFFER-HORIZON_L+i-1].gpio,
			  db[PKTS_PER_DATA_BUFFER-HORIZON_L+i-1].duty
			  );
	//	upast[i] = fake_upasts[tstep][i]; // !!! Correct indexing? Or need to go backwards like above?
	fprintf(flog, "%lf ", upast[i]);
      }

      //  double ypast[2*(HORIZON_L+1)] = {};
      fprintf(flog, "\n\nypast: ");
      for( int i=0; i<HORIZON_L+1; i++ ) {  // i: this many sample pairs (current,angle) 
	//	ypast[2*i]   = adc_to_amps(  db[PKTS_PER_DATA_BUFFER-HORIZON_L+i-1].adc  );  // !!!!!!!!!!!!!!!!!
	ypast[i] = eqep_to_angle(   db[PKTS_PER_DATA_BUFFER-HORIZON_L+i-1].eqep );
	//	ypast[i] =  fake_ypasts[tstep][i]; // !!! Correct indexing? Or need to go backwards like above?
	fprintf(flog, "%lf ", ypast[i]);
      }

      
      
      /* % Set parameters */
      //////////////////////
      
      /* setP_upast(obj,thisUpast); */
      /* for( int j=0; j<HORIZON_L-1; j++ ) { */
      /* 	upast[j] = upast[j+1]; */
      /* } */
      /* upast[HORIZON_L-1] = optU[0]; // TODO: jpp ask david! */
      tmpC_TS_20160928_153333_055989_classname_set_upast(upast);    // Where is upast defined? Grabbed from the db? Yupperoo

      
      /* setP_ypast(obj,thisYpast); */
      /* for( int j=0; j<(2*(HORIZON_L+1))-1; j++ ) { */
      /* 	ypast[j] = ypast[j+1]; */
      /* } */
      /* ypast[2*(HORIZON_L+1)-2] = current; */
      /* ypast[2*(HORIZON_L+1)-1] = shaft_angle; */
      tmpC_TS_20160928_153333_055989_classname_set_ypast(ypast);      

      
      // WARNING: assuming S=1 here. If S>1 do a for loop here.
      uapply[0] =  gpio_duty_to_motor_voltage_cmd(
			  db[PKTS_PER_DATA_BUFFER-1].gpio,
			  db[PKTS_PER_DATA_BUFFER-1].duty
			  );

	fprintf(flog, "uapply[0]: %lf ", uapply[0]);

      tmpC_TS_20160928_153333_055989_classname_set_uapply(uapply);

      /* % Initialize primal variables */
    ////////////////////////////////////////////////////////////////

      // Warm-start optX0 by taking L+1 elem of optX 
    {      
	/*
	double cur = optX[3*(HORIZON_L+1)+0];   
	double w   = optX[3*(HORIZON_L+1)+1];
	double th  = optX[3*(HORIZON_L+1)+2];	

	double newcur = cur;
	double newW = w;
	double newTh = th;
	
	x0[0] = newcur;
	x0[1] = newW;
	x0[2] = newTh;
	*/

	// cold start
	x0[0] = 0; // optX0[0];
	x0[1] = 0; // optX0[1];
	x0[2] = 0; // optX0[2];
         
    tmpC_TS_20160928_153333_055989_classname_set_x0(x0);

    }


      // cold start
      for( int j=0; j<3*(HORIZON_T+HORIZON_L-1); j++ ) {
      	initX[j] = 0; //optX[j];
      }


   tmpC_TS_20160928_153333_055989_classname_set_x(initX);
      
      /* setV_u(obj,initU); */
      //   double initU[1*HORIZON_T] = {}; 
      for( int j=0; j<HORIZON_T-HORIZON_S; j++ ) {
	initU[j] = 0; // optU[j+1];
      }
      tmpC_TS_20160928_153333_055989_classname_set_u( initU );

      /* setV_d(obj,initD); */
      for( int j=0; j<HORIZON_T + HORIZON_L; j++) {
	initD[j] = 0; // optD[j+1];
      }
      //      initD[HORIZON_T + HORIZON_L-1] = 0.0;
      tmpC_TS_20160928_153333_055989_classname_set_d( initD );
      

	   
    } // if tstep>0
    
    // Solve
    /*     ipmPDeq_CSsolver(mu0, */
    /* 		     maxIter, */
    /* 		     saveIter, */
    /* 		     status, */
    /* 		     iter, */
    /* 		     time, */
    /* 		     z, */
    /* 		     nu, */
    /* 		     lambda, */
    /* 		     dZ_s, */
    /* 		     dNu_s, */
    /* 		     dLambda_s, */
    /* 		     G, */
    /* 		     F, */
    /* 		     primaAlpha_s, */
    /* 		     dualAlpha_s, */
    /* 		     finalAlpha); */


    /* tmpC_TS_20160928_153333_055989_classname_getOutputs(optJ, */
    /* 							optU, */
    /* 							optD, */
    /* 							optX, */
    /* 							optX0, */
    /* 							optIM, */
    /* 							optOmega, */
    /* 							optTheta, */
    /* 							optEnergy, */
    /* 							optNoise); */


    // compare optU with 
    //    for( int k=0; k<1*(1*HORIZON_T); k++ ) { fprintf(flog,"tstep: %d, optU matlab: %lg, BB: %lg\n",tstep,fake_optUs[tstep][k], optU[k]); }

	// Send actual optU now that we can send PWM
    motor_voltage_schedule_to_cmd_buf(  optU, HORIZON_T-HORIZON_S, sample_num, &(cb_buffer[tstep]) ); 

    //    set_cmd_buf( cb_buffer[tstep] );    

    // Here's where we hijack the cmd signal with a plain old PID signal.
    // Note: if des_angle - angle > 0, then angle needs to move up. 
    // Our sys should have the property that pos voltage -> pos angle movement,
    // therefore gain should be pos. If not, we may have a sign error somewhere.
    double sim_time = cputime[tstep] - cputime[0];
    double sim_time_diff = cputimediff[tstep];
    double ref_freq = .5; // hz
    double desired_angle = PI / 2.0 * sin(2.0 * M_PI * ref_freq * sim_time) ; // PI/2.0; // PI / 2.0 * sin(2.0 * M_PI * ref_freq * sim_time) ;
    double angle = eqep_to_angle( db[PKTS_PER_DATA_BUFFER-1].eqep );
    double angle_error = (desired_angle - angle);
    sum_angle_error += pid_Ki * angle_error * sim_time_diff;
    if( sum_angle_error > MAX_MOTOR_VOLTAGE ) {sum_angle_error = MAX_MOTOR_VOLTAGE;}
    if( sum_angle_error < -MAX_MOTOR_VOLTAGE ) {sum_angle_error = -MAX_MOTOR_VOLTAGE;}
    double pid_voltage = pid_gain * angle_error + sum_angle_error;
    if( pid_voltage > MAX_MOTOR_VOLTAGE ) {pid_voltage = MAX_MOTOR_VOLTAGE;}
    if( pid_voltage < -MAX_MOTOR_VOLTAGE ) {pid_voltage = -MAX_MOTOR_VOLTAGE;}
    printf("post-write. tstep: %4d time: %5.4lf dtime: %5.4lf gain: %5.4lf freq: %5.4lf des_ang: %5.4lf ang: %5.4lf err: %5.4lf int_term: %5.4lf volt: %5.4lf\n", tstep,
	   sim_time, sim_time_diff, pid_gain, ref_freq, desired_angle, angle, angle_error, sum_angle_error, pid_voltage);
    send_single_voltage( pid_voltage );






    /* write outputs */


    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optJ [%lg...]\n",(long unsigned int)sizeof(double),(double)optJ[0]);
    //ughprint(fp,optJ,1);
    fprintf(flog,"\noptJ:\n");
    for( int k=0; k<1; k++ ) { fprintf(flog,"%lg ",optJ_buffer[tstep][k] = optJ[k]); }
    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optU [%lg...]\n",(long unsigned int)sizeof(double)*(1*HORIZON_T),(double)optU[0]);
    //ughprint(fp,optU,1*(1*HORIZON_T));
    fprintf(flog,"\noptU:\n");
    for( int k=0; k<1*(1*HORIZON_T-HORIZON_S); k++ ) { fprintf(flog,"%lg ",optU_buffer[tstep][k] = optU[k]); }
    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optD [%lg...]\n",(long unsigned int)sizeof(double)*(1*(HORIZON_L+HORIZON_T)),(double)optD[0]);
    //ughprint(fp,optD,1*(1*(HORIZON_L+HORIZON_T)));
    fprintf(flog,"\noptD:\n");
    for( int k=0; k<1*(1*(HORIZON_L+HORIZON_T)); k++ ) { fprintf(flog,"%lg ",optD_buffer[tstep][k] = optD[k]); }
    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optX [%lg...]\n",(long unsigned int)sizeof(double)*(3*(HORIZON_T+HORIZON_L-1)),(double)optX[0]);
    // write(fid,optX,sizeof(double)*(3*14));
    //ughprint(fp,optX,1*(3*(HORIZON_T+HORIZON_L-1)));
    for( int k=0; k<1*(3*(HORIZON_T+HORIZON_L-1)); k++ ) { optX_buffer[tstep][k] = optX[k]; }
    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optX0 [%lg...]\n",(long unsigned int)sizeof(double)*(3*1),(double)optX0[0]);
    //ughprint(fp,optX0,1*(3*1));
    for( int k=0; k<1*(3*1); k++ ) { optX0_buffer[tstep][k] = optX0[k]; }
    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optIM [%lg...]\n",(long unsigned int)sizeof(double)*(1*(HORIZON_T+HORIZON_L-1)),(double)optIM[0]);
    //ughprint(fp,optIM,1*(1*(HORIZON_T+HORIZON_L-1)));
    for( int k=0; k<1*(1*(HORIZON_T+HORIZON_L-1)); k++ ) { optIM_buffer[tstep][k] = optIM[k]; }
    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optOmega [%lg...]\n",(long unsigned int)sizeof(double)*(1*(HORIZON_T+HORIZON_L-1)),(double)optOmega[0]);
    //ughprint(fp,optOmega,1*(1*(HORIZON_T+HORIZON_L-1)));
    for( int k=0; k<1*(1*(HORIZON_T+HORIZON_L-1)); k++ ) { optOmega_buffer[tstep][k] = optOmega[k]; }
    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optTheta [%lg...]\n",(long unsigned int)sizeof(double)*(1*(HORIZON_T+HORIZON_L-1)),(double)optTheta[0]);
    //ughprint(fp,optTheta,1*(1*(HORIZON_T+HORIZON_L-1)));
    for( int k=0; k<1*(1*(HORIZON_T+HORIZON_L-1)); k++ ) { optTheta_buffer[tstep][k] = optTheta[k]; }
    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optEnergy [%lg...]\n",(long unsigned int)sizeof(double),(double)optEnergy[0]);
    //ughprint(fp,optEnergy,1);
    fprintf(flog,"\noptEnergy:\n");
    for( int k=0; k<1; k++ ) { fprintf(flog,"%lg ",optEnergy_buffer[tstep][k] = optEnergy[k]); }
    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optNoise [%lg...]\n",(long unsigned int)sizeof(double)*(2*(HORIZON_L+1)),(double)optNoise[0]);
    //ughprint(fp,optNoise,1*(2*(HORIZON_L+1)));
    fprintf(flog,"\noptNoise:\n");
    for( int k=0; k<1*(1*(HORIZON_L+1)); k++ ) { fprintf(flog,"%lg ",optNoise_buffer[tstep][k] = optNoise[k]); }


    
/*	time_vect
	full_reference 
	u 
	status 
	iter 
	compute_time */


    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to t [%lg...]\n",(long unsigned int)sizeof(double)*(1*(HORIZON_L+HORIZON_T)),(double)t[0]);
    // write(fid,t,sizeof(double)*(1*(HORIZON_L+HORIZON_T)));
	for( int k=0; k<1*(1*(HORIZON_L+HORIZON_T)); k++) { t_buffer[tstep][k]=t[k];    }
	//fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to ref [%lg...]\n",(long unsigned int)sizeof(double)*(1*(HORIZON_T-1)),(double)ref[0]);
    // write(fid,ref,sizeof(double)*(1*(HORIZON_T-1)));
	fprintf(flog,"\nref:\n");
	for( int k=0; k<1*(1*(HORIZON_T-1)); k++) { fprintf(flog,"%lg ",ref_buffer[tstep][k]=ref[k]);    } 

	//	fprintf(flog,"\nref Matlab:\n");
	//	for( int k=0; k<1*(1*(HORIZON_T-1)); k++) { fprintf(flog,"%lg ",fake_refs[tstep][k]); }

	//fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to voltage_cmd [%lg...]\n",(long unsigned int)sizeof(double)*(1*1),(double)voltage_cmd[0]);
    // write(fid,voltage_cmd,sizeof(double)*(1*1));
	//	voltage_cmd_buffer[tstep][0] = voltage_cmd[0];
	//fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to status [%lg...]\n",(long unsigned int)sizeof(double)*(1*1),(double)status[0]);
    // write(fid,status,sizeof(double)*(1*1));
	status_buffer[tstep][0] = status[0];
	//fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to iter [%lg...]\n",(long unsigned int)sizeof(double)*(1*1),(double)iter[0]);
    // write(fid,iter,sizeof(double)*(1*1));

	iter_buffer[tstep][0] = iter[0];
//	ughprint2(&iter_save_buffer,tstep,iter_save,1*(1*1));    // Is it as simple as udghprint(fp,(double)iter,1*(1*1)); ???
	//fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to time [%lg...]\n",(long unsigned int)sizeof(double)*(1*1),(double)time[0]);
    // write(fid,time,sizeof(double)*(1*1));

    time_buffer[tstep][0] = time[0];

    
    // break;}
    // } // switch ()
    // close(fid);
    // } // while ()

//    fprintf(fp,"\n"); // from fp = fopen("mpc-data.txt", "w");





    // put in a little sleep, just to let the scheduler run.
    //    usleep(0L); // microseconds


    // sleep until the next sample time.
    unsigned int cycle_count = get_cycle_count();
    printf("bottom. cyc count: %u ",cycle_count);
    unsigned int cc_at_next_sample_time = (/* relying on int floor here*/ cycle_count/PRU_TICKS_PER_SAMPLE + 1) * PRU_TICKS_PER_SAMPLE;
    printf("cc at next samp time: %u ", cc_at_next_sample_time);
    unsigned int pru_ticks_to_sleep = cc_at_next_sample_time - cycle_count;
    printf("ticks to sleep: %u ", pru_ticks_to_sleep);
    double usec_to_sleep = (double) pru_ticks_to_sleep * USEC_PER_SEC / PRU_TICKS_PER_SEC;
    printf("Sleeping for %lf usec...\n",usec_to_sleep);
    usleep((unsigned long int) usec_to_sleep);


      
    /* if( tstep == 14 ) { */
    /*   fprintf(flog,"oh my (tstep=14, the firsrt time optU differs from Matlab)!!!"); */
    /* } */


  } // for loop -- timesteps

  printf("sleping for .1 sec...\n");  
  usleep(100000);
  printf("stopping motor...\n");
 send_single_voltage( 0 );
printf("Write mpc-data.txt or whatever...\n");
  
// Header row
/////////////////////
 for( int k=0; k<1*(1*HORIZON_T-HORIZON_S); k++) { fprintf(fp,"optU_%u ",k); }   
   for( int k=0; k<1*(1*(HORIZON_T+HORIZON_L)); k++) { fprintf(fp,"optD_%u ",k); }      
   for( int k=0; k<1*(3*(HORIZON_T+HORIZON_L-1)); k++) { fprintf(fp,"optX_%u_%u_%u ",k,k/3,k%3); }    
   for( int k=0; k<1*(3*1); k++) { fprintf(fp,"optX0_%u ",k); }
   for( int k=0; k<1*(1*(HORIZON_T+HORIZON_L)); k++) { fprintf(fp,"optIM_%u ",k); }     
   for( int k=0; k<1*(1*(HORIZON_T+HORIZON_L)); k++) { fprintf(fp,"optOmega_%u ",k); }  
   for( int k=0; k<1*(1*(HORIZON_T+HORIZON_L)); k++) { fprintf(fp,"optTheta_%u ",k); }  
   for( int k=0; k<1*(1*(HORIZON_L+1)); k++) { fprintf(fp,"optNoise_%u ",k); }
   
   for( int k=0; k<1; k++) { fprintf(fp,"optJ_%u ",k); }                                
   for( int k=0; k<1; k++) { fprintf(fp,"optEnergy_%u ",k); }                           
   for( int k=0; k<1*(1*(HORIZON_L+HORIZON_T)); k++) { fprintf(fp,"t_%u ",k); }
   for( int k=0; k<1*(1*(HORIZON_T-1)); k++) { fprintf(fp,"ref_%u ",k); }
   //	for( int k=0; k<1; k++) { fprintf(fp,"%lg ",voltage_cmd_buffer[tstep][k]); }
   for( int k=0; k<1; k++) { fprintf(fp,"status_%u ",k); }
   for( int k=0; k<1; k++) { fprintf(fp,"iter_%u ",k); }
   for( int k=0; k<1; k++) { fprintf(fp,"time_%u ",k); }

   fprintf_data_buf_header( fp );
   fprintf_cmd_buf_header( fp );
   fprintf_cmd_buf_header( fp ); // for cmd bufs from get_data_cmd_bufs
   fprintf(fp,"\n");



// Data rows
///////////////////
 for( int tstep=0; tstep<MAX_TSTEPS; tstep++ ) {
   for( int k=0; k<1*(1*HORIZON_T-HORIZON_S); k++) { fprintf(fp,"%lg ",optU_buffer[tstep][k]); }   
   for( int k=0; k<1*(1*(HORIZON_T+HORIZON_L)); k++) { fprintf(fp,"%lg ",optD_buffer[tstep][k]); }      
   for( int k=0; k<1*(3*(HORIZON_T+HORIZON_L-1)); k++) { fprintf(fp,"%lg ",optX_buffer[tstep][k]); }    
   for( int k=0; k<1*(3*1); k++) { fprintf(fp,"%lg ",optX0_buffer[tstep][k]); }                        
   for( int k=0; k<1*(1*(HORIZON_T+HORIZON_L)); k++) { fprintf(fp,"%lg ",optIM_buffer[tstep][k]); }     
   for( int k=0; k<1*(1*(HORIZON_T+HORIZON_L)); k++) { fprintf(fp,"%lg ",optOmega_buffer[tstep][k]); }  
   for( int k=0; k<1*(1*(HORIZON_T+HORIZON_L)); k++) { fprintf(fp,"%lg ",optTheta_buffer[tstep][k]); }  
   for( int k=0; k<1*(1*(HORIZON_L+1)); k++) { fprintf(fp,"%lg ",optNoise_buffer[tstep][k]); }
   
   for( int k=0; k<1; k++) { fprintf(fp,"%lg ",optJ_buffer[tstep][k]); }                                
   for( int k=0; k<1; k++) { fprintf(fp,"%lg ",optEnergy_buffer[tstep][k]); }                           
   for( int k=0; k<1*(1*(HORIZON_L+HORIZON_T)); k++) { fprintf(fp,"%lg ",t_buffer[tstep][k]); }
   for( int k=0; k<1*(1*(HORIZON_T-1)); k++) { fprintf(fp,"%lg ",ref_buffer[tstep][k]); }
   //	for( int k=0; k<1; k++) { fprintf(fp,"%lg ",voltage_cmd_buffer[tstep][k]); }
   for( int k=0; k<1; k++) { fprintf(fp,"%lg ",status_buffer[tstep][k]); }
   for( int k=0; k<1; k++) { fprintf(fp,"%lg ",iter_buffer[tstep][k]); }
   for( int k=0; k<1; k++) { fprintf(fp,"%lg ",time_buffer[tstep][k]); }



   // Print data buffer:
   fprintf_data_buf( fp, db_buffer[tstep] );
    /* for( int k=0; k<PKTS_PER_DATA_BUFFER; k++ ) { */
    /*   DataPacket p = db_buffer[tstep][k]; */
    /*   double v; */
    /*   gpio_duty_to_motor_voltage_cmd( p.gpio, */
    /* 				      p.duty, */
    /* 				      MAX_MOTOR_VOLTAGE, */
    /* 				      &v ); */

    /*   //      fprintf(fp,"cycle: %u sample: %d adc: %d eqep: %d gpio: %x duty: %d last-data-req: %u last-cmd: %u amps: %f angle: %f volts: %f\n", */
    /*   fprintf(fp,"%u %d %d %d %u %d %u %u %f %f %f ", */
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
    /* } */

    // Print cmd buffer
    fprintf_cmd_buf(fp, cb_buffer[tstep] );

    /* for( int k=0; k<PKTS_PER_CMD_BUFFER; k++ ) { */
    /*   CommandPacket p = cb_buffer[tstep][k]; */

    /*   double v; */
    /*   gpio_duty_to_motor_voltage_cmd( p.gpio, */
    /* 				      p.duty, */
    /* 				      MAX_MOTOR_VOLTAGE, */
    /* 				      &v ); */

    /*   //      fprintf(fp,"cycle: %u sample: %d adc: %d eqep: %d gpio: %x duty: %d last-data-req: %u last-cmd: %u amps: %f angle: %f volts: %f\n", */
    /*   fprintf(fp,"%u %d %u %d %f ", */
    /* 	     p.cycle_count, */
    /* 	     p.sample_num, */
    /* 	     p.gpio, */
    /* 	     p.duty, */
    /* 	     v */
    /* 	     ); */
    /* } */

    fprintf_cmd_buf(fp, cb_rx[tstep] );



   fprintf(fp,"\n");

 }


printf("Done writing data file. Closing...\n");

 fclose(fp);




  // Hardware cleanup
  //////////////////////////////////////////


    ///////////////////////
  // Cleanup



 //  adc_cleanup();
  


  /* { */
  /*   // Stop motor. */
  /*   printf("Stopping motor...\n"); */
  /*   CommandBuffer cb_stop; */
  /*   make_const_cmd_buf( &cb_stop, 0, 0, MOTOR_STBY, 0 ); */
  /*   DataBuffer db; */
  /*   get_data_buf( &db ); */
  /*   //    print_data_buf( db ); */
  /*   unsigned int sample_num = db[PKTS_PER_DATA_BUFFER-1].sample_num;  */
  /*   cb_stop[0].sample_num = sample_num;  */
  /*   printf("Sending STBY cmd...\n"); */
  /*   set_cmd_buf( cb_stop ); */
  /* } */





  /* PWM.stop(MY_PWM_PIN) */

  //  pwm_disable(key);

  /* GPIO.output(MY_PWM_STBY, GPIO.LOW) */
  /* GPIO.output(MY_PWM_DIR_PIN_1, GPIO.LOW)	 */
  /* GPIO.output(MY_PWM_DIR_PIN_2, GPIO.LOW) */

  /* gpio_set_value(pin1, LOW); */
  /* gpio_set_value(pin2, LOW); */
  /* gpio_set_value(stby, LOW); */



  //  printf("Cleaning up...\n");





  /* GPIO.cleanup() */

  //  event_cleanup();

  /* PWM.cleanup() */

  //  pwm_cleanup();




} // main(
