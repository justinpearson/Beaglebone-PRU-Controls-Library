#include "jpp-pru-lib.h"
#include "util-jpp.h"
#include <math.h>
#include <stdbool.h>

// #define WARM_START

  // Horizon Lengths:
#define HORIZON_L 10
#define HORIZON_T 20
#define HORIZON_S 5
#define PI 3.141592653589793

#define LEN_x0     (3)
#define LEN_xvecs  (HORIZON_L+HORIZON_T)
#define LEN_x      (3*LEN_xvecs)
#define LEN_ref    (HORIZON_T)
#define LEN_u      (HORIZON_T)
#define LEN_d      (HORIZON_L+HORIZON_T)
#define LEN_upast  (HORIZON_L)
#define LEN_uapply (HORIZON_S)
#define LEN_ypast  (HORIZON_L+1)
#define LEN_IM     (HORIZON_T+HORIZON_L)
#define LEN_omega  (HORIZON_T+HORIZON_L)
#define LEN_theta  (HORIZON_T+HORIZON_L)
#define LEN_noise  (HORIZON_L+1)
#define LEN_J      (1)
#define LEN_energy (1)
#define LEN_t      (HORIZON_T+HORIZON_L+1)
#define LEN_p1l1   (HORIZON_T)
#define LEN_p1l2   (HORIZON_T)
#define LEN_p1nu1  (HORIZON_S)
#define LEN_p2l1   (HORIZON_L+HORIZON_T)
#define LEN_p2l2   (HORIZON_L+HORIZON_T)
#define LEN_p1nux1 (LEN_x)
#define LEN_p2nux1 (LEN_x)



// To get usleep:
#define _POSIX_C_SOURCE199309L  // dammit, weird posix stuff. 
// usleep specified in some versions of posix, not in others, and it's
// obsolete in favor of nanosleep, which takes shitty timespec args.
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


  





// function that writes an array to a file.
void ughprint(FILE* fp, double* a, int len);
void ughprint(FILE* fp, double* a, int len) {
      for( int i=0; i<len; i++ ) {
          fprintf(fp,"%lf ",a[i]);
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

  // https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm
  time_t rawtime;
  struct tm *info;
  char buffer[80];
  time( &rawtime );
  info = localtime( &rawtime );
  printf("Current local time and date: %s", asctime(info));


  ////////////////////
  // Begin hw setup

  start_pru();
  send_single_voltage( 0 );



  int fid = 1; //stdout? jpp: hopefully this will just dump output to cmd line...

  // files to hold results
  FILE* fp;
  FILE* flog;

    fp = fopen("mpc-data.txt", "w");
    flog = fopen("runlog.txt","w");

    // Configure the data file and log file to be "fully buffered",
    // meaning that they won't write to disk until explicitly told (or closed).
    // https://www.chemie.fu-berlin.de/chemnet/use/info/libc/libc_7.html#SEC118
    #define fp_buf_size 999999
    #define flog_buf_size  999999
    char fp_buf[fp_buf_size] = {};
    char flog_buf[flog_buf_size] = {};
    int retval = 0;
    if( (retval = setvbuf( fp, fp_buf, _IOFBF, fp_buf_size )) != 0 ) {
      printf("BAD: setvbuf returned %d\n",retval);
    }
    if( (retval = setvbuf( flog, flog_buf, _IOFBF, flog_buf_size )) != 0 ) {
      printf("BAD: setvbuf returned %d\n",retval);
    }


    char stdout_buf[fp_buf_size] = {};
    if((retval=setvbuf(stdout, stdout_buf, _IOFBF, fp_buf_size))!=0) {
      printf("bad: setvbuf returned %d\n",retval);
      return EXIT_FAILURE;
    }

    char stderr_buf[fp_buf_size] = {};
    if((retval=setvbuf(stderr, stderr_buf, _IOFBF, fp_buf_size))!=0) {
      printf("bad: setvbuf returned %d\n",retval);
      return EXIT_FAILURE;
    }



    fprintf(stderr,"NOTE: Writing results to file: mpc-data.txt\n");
    fprintf(stderr,"NOTE: Writing log to file: runlog.txt\n");

    fprintf(flog,"Current local time and date: %s", asctime(info));

  
  ////////////////////////////////////////////////////
  // Set parameters (fixed over all iters)

    double Vsupply[] = {MAX_MOTOR_VOLTAGE};
    double RM[] = {2.62}; // with 1 inductor from Amazon
    double LM = .0259; // with 1 inductor from Amazon
    double inv_LM[] = {1.0/LM};
    double JM = 2.3e-6; // 3.75e-6; // 5e-6; // 2.2e-6;
    double inv_JM[] = {1.0/JM};
    double bM[] = {1.35e-5}; // {1.3e-5}; // {3e-6}; // {5e-8};
    double Kb[] = {.01}; // {.013}; //{.01}; 
    double KM[] = {.01}; // {.013}; // {.01}; 
  
  /* define and set parameters */
  tmpC_TS_20161011_155522_861392_classname_set_Vsupply(Vsupply);
  tmpC_TS_20161011_155522_861392_classname_set_RM(RM);
  tmpC_TS_20161011_155522_861392_classname_set_inv_LM(inv_LM); 
  tmpC_TS_20161011_155522_861392_classname_set_inv_JM(inv_JM); 
  tmpC_TS_20161011_155522_861392_classname_set_bM(bM);
  tmpC_TS_20161011_155522_861392_classname_set_Kb(Kb);
  tmpC_TS_20161011_155522_861392_classname_set_KM(KM);

  // Oct 10, 2016: model the crappy motor's voltage deadzone.
  //  double a_deadzone[] = {.6}; // {.5};
  //  double b_deadzone[] = {1.5};
  //  tmpC_TS_20161011_155522_861392_classname_set_a(a_deadzone);
  //  tmpC_TS_20161011_155522_861392_classname_set_b(b_deadzone);


  double Ts = .005;  // ms

  
  double uMax = Vsupply[0]; // max voltage that we'll apply to the motor // Old: Vsupply[0] - Vswitches[0];

  /* define weights */
  // Oct 6: .7 V min for friction vs .05 rads desired ref tracking => refweight = 10 * uweight
  double refWeight[] = {180};
  double uWeight[] = {150};
  double nWeight[] = {1.0e8};
  double dWeight[] = {50};

  /* set weights */
  tmpC_TS_20161011_155522_861392_classname_set_refWeight(refWeight);
  tmpC_TS_20161011_155522_861392_classname_set_uWeight(uWeight);
  tmpC_TS_20161011_155522_861392_classname_set_nWeight(nWeight);
  tmpC_TS_20161011_155522_861392_classname_set_dWeight(dWeight);


  ///////////////////////////////////////////////////////////
  // Init variables that will change each iter

	
  /* define past data */
  double upast[LEN_upast] = {};
  double ypast[LEN_ypast] = {};
  double uapply[LEN_uapply] = {};
  tmpC_TS_20161011_155522_861392_classname_set_upast(upast);
  tmpC_TS_20161011_155522_861392_classname_set_ypast(ypast);
  tmpC_TS_20161011_155522_861392_classname_set_uapply(uapply);


    

  //////////
  // Pick something reasonable for first iteration, then use output of optimization 

  double initU[LEN_u] = {}; 
  tmpC_TS_20161011_155522_861392_classname_set_u(initU);

  // States: current, shaft ang vel, shaft angle
  double initX0[LEN_x0] = {}; // jpp: uh, dunno: .01*randn(n,1) in mpc_dcmotor.m
  tmpC_TS_20161011_155522_861392_classname_set_x0(initX0);

  double initD[LEN_d] = {};
  tmpC_TS_20161011_155522_861392_classname_set_d(initD);

  double initX[LEN_x] = {};
  tmpC_TS_20161011_155522_861392_classname_set_x(initX);
           
  double P1lambda1_[LEN_p1l1] = {};
  tmpC_TS_20161011_155522_861392_classname_set_P1lambda1_(P1lambda1_);
            
  double P1lambda2_[LEN_p1l2] = {};
  tmpC_TS_20161011_155522_861392_classname_set_P1lambda2_(P1lambda2_);
             
  double P1nu1_[LEN_p1nu1] = {};           
  tmpC_TS_20161011_155522_861392_classname_set_P1nu1_(P1nu1_);

  double P2lambda1_[LEN_p2l1] = {};
  //double P2lambda1_[1*1] = {};
  tmpC_TS_20161011_155522_861392_classname_set_P2lambda1_(P2lambda1_);
             
  double P2lambda2_[LEN_p2l2] = {};
  tmpC_TS_20161011_155522_861392_classname_set_P2lambda2_(P2lambda2_);
            
  double P1nux1_[LEN_p1nux1] = {};
  tmpC_TS_20161011_155522_861392_classname_set_P1nux1_(P1nux1_);

  double P2nux1_[LEN_p2nux1] = {};
  tmpC_TS_20161011_155522_861392_classname_set_P2nux1_(P2nux1_);
             
  /*======================================================================================*/

  // optimization parameters
  double mu0[] = {10};
  int32_t maxIter[] = {35};
  int32_t saveIter[] = {-1};


  // Vars that the getOutputs function will write to about how the optimization is going:
  int32_t *status;
  int32_t *iter;
  double  *time;
  if ((status=malloc(sizeof(int32_t)*(1)))==NULL) exit(1);
  if ((iter=malloc(sizeof(int32_t)*(1)))==NULL) exit(1);
  if ((time=malloc(sizeof(double)*(1)))==NULL) exit(1);
    

  *status = 9999;
  *iter = 9999;

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
  if ((optU          = malloc(sizeof(double)*LEN_u))==NULL) exit(1);
  if ((optD          = malloc(sizeof(double)*LEN_d))==NULL) exit(1);
  if ((optX          = malloc(sizeof(double)*LEN_x))==NULL) exit(1);
  if ((optX0         = malloc(sizeof(double)*LEN_x0))==NULL) exit(1);
  if ((optIM         = malloc(sizeof(double)*LEN_IM))==NULL) exit(1);
  if ((optOmega      = malloc(sizeof(double)*LEN_omega))==NULL) exit(1);
  if ((optTheta      = malloc(sizeof(double)*LEN_theta))==NULL) exit(1);
  if ((optEnergy     = malloc(sizeof(double)*LEN_energy))==NULL) exit(1);
  if ((optNoise      = malloc(sizeof(double)*LEN_noise))==NULL) exit(1);

  
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
             if ((z=malloc(sizeof(double)*(143*201)))==NULL) exit(1);
             if ((nu=malloc(sizeof(double)*(185*201)))==NULL) exit(1);
             if ((lambda=malloc(sizeof(double)*(100*201)))==NULL) exit(1);
             if ((dZ_s=malloc(sizeof(double)*(143*200)))==NULL) exit(1);
             if ((dNu_s=malloc(sizeof(double)*(185*200)))==NULL) exit(1);
             if ((dLambda_s=malloc(sizeof(double)*(100*200)))==NULL) exit(1);
             if ((G=malloc(sizeof(double)*(95*201)))==NULL) exit(1);
             if ((F=malloc(sizeof(double)*(100*201)))==NULL) exit(1);
             if ((primaAlpha_s=malloc(sizeof(double)*(201)))==NULL) exit(1);
             if ((dualAlpha_s=malloc(sizeof(double)*(201)))==NULL) exit(1);
             if ((finalAlpha=malloc(sizeof(double)*(201)))==NULL) exit(1);

  // OLD
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
  //  const int MAX_TSTEPS = 48;
  const int MAX_TSTEPS = argc > 1 ? atoi(argv[1]) : 300  ;


  double cputime          [MAX_TSTEPS];
  double cputimediff      [MAX_TSTEPS];
  unsigned int sns        [MAX_TSTEPS];

  double optU_buffer      [MAX_TSTEPS][LEN_u];
  double optD_buffer      [MAX_TSTEPS][LEN_d];
  double optX_buffer      [MAX_TSTEPS][LEN_x];
  double optX0_buffer     [MAX_TSTEPS][LEN_x0];
  double optIM_buffer     [MAX_TSTEPS][LEN_IM];
  double optOmega_buffer  [MAX_TSTEPS][LEN_omega];
  double optTheta_buffer  [MAX_TSTEPS][LEN_theta];
  double optNoise_buffer  [MAX_TSTEPS][LEN_noise];
  double optJ_buffer      [MAX_TSTEPS][LEN_J];
  double optEnergy_buffer [MAX_TSTEPS][LEN_energy];
  double uapply_buffer    [MAX_TSTEPS][LEN_uapply];
  double t_buffer         [MAX_TSTEPS][LEN_t];
  double status_buffer    [MAX_TSTEPS][1];
  double iter_buffer      [MAX_TSTEPS][1];
  double time_buffer      [MAX_TSTEPS][1];
  double ref_buffer       [MAX_TSTEPS][LEN_ref];
  DataBuffer db_buffer    [MAX_TSTEPS];
  CommandBuffer cb_buffer [MAX_TSTEPS];
  CommandBuffer cb_rx     [MAX_TSTEPS];

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
 unsigned int sample_num_last_solve = 0; 

 //////////////////////////////
 // Main loop

  for(int tstep=0; tstep<MAX_TSTEPS; tstep++ ) {
    if( tstep % 1 == 0 ) {
      fprintf(flog,"\n======================\ntop of tstep=%d\n",tstep);
    }


    toc(&(cputime[tstep]), &(cputimediff[tstep]) );

    unsigned int cc_top = get_cycle_count();
    fprintf(flog,"top. tstep: %u cputime: %lf cputimediff: %lf cc: %u\n",tstep, cputime[tstep], cputimediff[tstep], cc_top);


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

    //    fprintf_data_buf_nl( flog, db_buffer[tstep] );
    //    fprintf_cmd_buf_nl(flog, cb_rx[tstep] );


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
    unsigned int sn = db[PKTS_PER_DATA_BUFFER-1].sample_num; // get_sample_num();
    unsigned int sample_num = sn; // db[PKTS_PER_DATA_BUFFER-1].sample_num+1;
    sns[tstep] = sn;
    int sample_num_diff = sample_num - sample_num_last_solve;

    fprintf(flog, "Time: %15.9lf diff: %15.9lf getsampnum: %5u sample_num_diff: %d",cputime[tstep], cputimediff[tstep], sns[tstep], sample_num_diff);

    if( sample_num_diff > HORIZON_T && tstep > 0) {
      fprintf(flog, "\n========================\nArg, pre-empted longer than %u, bailing...\n",HORIZON_T);
      break;
    }


    // Compute pru time, time vector (t), and reference (ref):

  // Grab the current cycle time; that's pretty much the current time.
  // CPU needs to know the current time for computing the reference.

  /* setP_t(obj,t); */
  pru_time_sec = (db[PKTS_PER_DATA_BUFFER-1].cycle_count)/(double)PRU_TICKS_PER_SEC;
  fprintf(flog,"pru time: %f (delta: %f)\n",pru_time_sec,pru_time_sec-pru_time_sec_old);
  pru_time_sec_old = pru_time_sec;

  //  pru_time_sec = Ts * tstep; // !!!!!!!!!!!!!!!!! hijacking pru time for testing.


  double t[LEN_t] = {};
  for(int j=0; j<LEN_t; j++ ) {
    t[j] = pru_time_sec + Ts*(j-HORIZON_L); // units: sec
  }


  /* for(int j=0; j<HORIZON_T+HORIZON_L; j++ ) { */
  /*   printf("tstep=%d, j=%d, t[j]=%lf",tstep,j,t[j]); */
  /* } */



  // Not needed bc using a discrete-time model now
  // Still compute t vec bc easier to keep the tbuffer code and for reference.
  //  tmpC_TS_20161011_155522_861392_classname_set_t(t);


  double ref[LEN_ref] = {};
  double omegaRef= 1.0*PI; // 2.0*PI; // 0.01*PI; // units: rad/sec

  for(int j=0; j<LEN_ref; j++) {
    ref[j] = 2.0 * PI * sign(sin(omegaRef*t[j+HORIZON_L+1])); // PI/2; // 0.0*PI/2.0*sign(sin(omegaRef*t[j+HORIZON_L+1])); 
    // ref[j] = fake_refs[tstep][j]; // !!!
  }
  tmpC_TS_20161011_155522_861392_classname_set_ref(ref);

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
      for( int i=0; i<LEN_upast; i++ ) {
	upast[i] = gpio_duty_to_motor_voltage_cmd(
			  db[PKTS_PER_DATA_BUFFER-HORIZON_L+i-1].gpio,
			  db[PKTS_PER_DATA_BUFFER-HORIZON_L+i-1].duty
			  );
	//	upast[i] = fake_upasts[tstep][i]; // !!! Correct indexing? Or need to go backwards like above?
	fprintf(flog, "%lf ", upast[i]);
      }

      //  double ypast[2*(HORIZON_L+1)] = {};
      fprintf(flog, "\n\nypast: ");
      for( int i=0; i<LEN_ypast; i++ ) {  // i: this many sample pairs (current,angle) 
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
      tmpC_TS_20161011_155522_861392_classname_set_upast(upast);    // Where is upast defined? Grabbed from the db? Yupperoo

      
      /* setP_ypast(obj,thisYpast); */
      /* for( int j=0; j<(2*(HORIZON_L+1))-1; j++ ) { */
      /* 	ypast[j] = ypast[j+1]; */
      /* } */
      /* ypast[2*(HORIZON_L+1)-2] = current; */
      /* ypast[2*(HORIZON_L+1)-1] = shaft_angle; */
      tmpC_TS_20161011_155522_861392_classname_set_ypast(ypast);      

      // Warning: assumes S=1.
      /* uapply[0] =  gpio_duty_to_motor_voltage_cmd( */
      /* 						  db[PKTS_PER_DATA_BUFFER-1].gpio, */
      /* 						  db[PKTS_PER_DATA_BUFFER-1].duty */
      /* 						  ); */

            
      for( int i=0; i<LEN_uapply; i++ ) {
      	// For each elem of uapply,
      	// Go thru the PRU cmd buffer looking for right sample num.
      	// If at end of PRU cmd buffer and didn't find it, panic.
      	bool foundit = false;
      	int jwin = 0;
      	for( int j=0; j<PKTS_PER_CMD_BUFFER; j++ ) {
      	  if( cb_rx[tstep][j].sample_num == sample_num + i ) {
      	    // Found it!
      	    foundit = true;
      	    jwin = j;
      	    break;
      	  }
      	}
      	if( foundit ) {
      	  uapply[i] =  gpio_duty_to_motor_voltage_cmd(
      			      cb_rx[tstep][jwin].gpio,
      			      cb_rx[tstep][jwin].duty
      			      );
      	} else {
      	  uapply[i] = 0;
      	  printf("%s (%s):%d: Can't find current sample num in PCB!\n",
      		__FILE__, __FUNCTION__, __LINE__);
      	}
      }

      /* for( int i=0; i<1*HORIZON_S; i++ ) { */
      /* 	fprintf(flog, "uapply[%d]: %lf \n", i,uapply[i]); */
      /* } */

      tmpC_TS_20161011_155522_861392_classname_set_uapply(uapply);

      /* % Initialize primal variables */
      ////////////////////////////////////////////////////////////////


#ifdef WARM_START

      if( 0 < sample_num_diff && sample_num_diff < HORIZON_T ) {
	
	// Get the optX from last iter that corresponds to the current sn.
	for( int i=0; i<LEN_x0; i++ ) {
	  initX0[i] = optX[3*(sample_num_diff-1)+i];
	}

	// Propagate that initX0 forward to form the initX guess.
	//   double initX[3*(HORIZON_T+HORIZON_L-1)] = {};
	for( int i=0; i<LEN_xvecs; i++ ) {

	  double* oldx;

	  if( i==0 ) { // use initX0 instead of initX
	    oldx = initX0;
	  } else {
	    oldx = &(initX[3*i-1]);
	  }
	  
	  double* oldu;
	  double ughzero = 0;
	  if( sample_num_diff +i < LEN_upast ) { // use upast; new sn is close to prev sn
	    oldu = &(upast[sample_num_diff+i]);
	  } else if( sample_num_diff + i >= LEN_upast && sample_num_diff + i < HORIZON_L + HORIZON_T ) { // TODO: replace L & T with LEN_??
	    // use optU; new sn is far from prev sn (past upast, and into optU)
	    oldu = &(optU[sample_num_diff - HORIZON_L + i]);
	  } else {
	    // idx is beyond what optU reached; use 0 for our input.
	    oldu = &(ughzero);
	  }

	  initX[3*i+0] = -RM[0] * inv_LM[0] * oldx[0] - Kb[0] * inv_LM[0] * oldx[1] + 0  + inv_LM[0] * oldu[0];
	  initX[3*i+1] =  KM[0] * inv_JM[0] * oldx[0] - bM[0] * inv_JM[0] * oldx[1] + 0;
	  initX[3*i+2] =  0 + 1.0 * oldx[1] + 0;

	  if( i >= HORIZON_L ) {
	    // fill in optU
	    initU[i-HORIZON_L] = *oldu;
	  }
	}
      }


      /* for( int j=0; j<3*(HORIZON_T+HORIZON_L-1); j++ ) { */
      /* 	initX[j] = optX[j]; */
      /* } */

      /* for( int j=0; j<HORIZON_T; j++ ) { */
      /* 	initU[j] = optU[j+1]; */
      /* } */

#else
      // Cold start
      initX0[0] = 0; // optX0[0];
      initX0[1] = 0; // optX0[1];
      initX0[2] = 0; // optX0[2];

      for( int j=0; j<LEN_x; j++ ) {
      	initX[j] = 0; //optX[j];
      }

      for( int j=0; j<LEN_u; j++ ) {
      	initU[j] = 0; // optU[j+1];
      }
      // end cold start

#endif

      tmpC_TS_20161011_155522_861392_classname_set_x0(initX0);
      tmpC_TS_20161011_155522_861392_classname_set_x(initX);
      tmpC_TS_20161011_155522_861392_classname_set_u( initU );

      /* setV_d(obj,initD); */
      for( int j=0; j<LEN_d; j++) {
      	initD[j] = 0; // optD[j+1];
      }
      //           initD[HORIZON_T + HORIZON_L-1] = 0.0; 
           tmpC_TS_20161011_155522_861392_classname_set_d( initD );

      
    } // if tstep>0



    
    // Solve
    ipmPDeq_CSsolver(mu0,
		     maxIter,
		     saveIter,
		     status,
		     iter,
		     time,
		     z,
		     nu,
		     lambda,
		     dZ_s,
		     dNu_s,
		     dLambda_s,
		     G,
		     F,
		     primaAlpha_s,
		     dualAlpha_s,
		     finalAlpha);


    tmpC_TS_20161011_155522_861392_classname_getOutputs(optJ,
							optU,
							optD,
							optX,
							optX0,
							optIM,
							optOmega,
							optTheta,
							optEnergy,
							optNoise);


    // compare optU 
    //    for( int k=0; k<1*(1*HORIZON_T); k++ ) { fprintf(flog,"tstep: %d, optU matlab: %lf, BB: %lf\n",tstep,fake_optUs[tstep][k], optU[k]); }

	// Send actual optU now that we can send PWM
    motor_voltage_schedule_to_cmd_buf(  optU, LEN_u, sample_num, &(cb_buffer[tstep]) ); 
    set_cmd_buf( cb_buffer[tstep] );    

    sample_num_last_solve = sample_num;

    /* write outputs */
  fprintf(flog,"\nstatus: %d iter: %d time: %lf\n",status[0],iter[0],time[0]);

    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optJ [%lf...]\n",(long unsigned int)sizeof(double),(double)optJ[0]);
    //ughprint(fp,optJ,1);
    fprintf(flog,"\noptJ:\n");
    for( int k=0; k<LEN_J; k++ ) { fprintf(flog,"%lf ",optJ_buffer[tstep][k] = optJ[k]); }
    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optU [%lf...]\n",(long unsigned int)sizeof(double)*(1*HORIZON_T),(double)optU[0]);
    //ughprint(fp,optU,1*(1*HORIZON_T));
    fprintf(flog,"\noptU:\n");
    for( int k=0; k<LEN_u; k++ ) { fprintf(flog,"%lf ",optU_buffer[tstep][k] = optU[k]); }

    fprintf(flog,"\nuapply:\n");
    for( int k=0; k<LEN_uapply; k++ ) { fprintf(flog,"%lf ",uapply_buffer[tstep][k] = uapply[k]); }


    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optD [%lf...]\n",(long unsigned int)sizeof(double)*(1*(HORIZON_L+HORIZON_T)),(double)optD[0]);
    //ughprint(fp,optD,1*(1*(HORIZON_L+HORIZON_T)));

       fprintf(flog,"\noptD:\n");
       for( int k=0; k<LEN_d; k++ ) { fprintf(flog,"%lf ",optD_buffer[tstep][k] = optD[k]); }


    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optX [%lf...]\n",(long unsigned int)sizeof(double)*(3*(HORIZON_T+HORIZON_L-1)),(double)optX[0]);
    // write(fid,optX,sizeof(double)*(3*14));
    //ughprint(fp,optX,1*(3*(HORIZON_T+HORIZON_L-1)));
    for( int k=0; k<LEN_x; k++ ) { optX_buffer[tstep][k] = optX[k]; }
    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optX0 [%lf...]\n",(long unsigned int)sizeof(double)*(3*1),(double)optX0[0]);
    //ughprint(fp,optX0,1*(3*1));
    for( int k=0; k<LEN_x0; k++ ) { optX0_buffer[tstep][k] = optX0[k]; }
    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optIM [%lf...]\n",(long unsigned int)sizeof(double)*(1*(HORIZON_T+HORIZON_L-1)),(double)optIM[0]);
    //ughprint(fp,optIM,1*(1*(HORIZON_T+HORIZON_L-1)));
    for( int k=0; k<LEN_IM; k++ ) { optIM_buffer[tstep][k] = optIM[k]; }
    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optOmega [%lf...]\n",(long unsigned int)sizeof(double)*(1*(HORIZON_T+HORIZON_L-1)),(double)optOmega[0]);
    //ughprint(fp,optOmega,1*(1*(HORIZON_T+HORIZON_L-1)));
    for( int k=0; k<LEN_omega; k++ ) { optOmega_buffer[tstep][k] = optOmega[k]; }
    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optTheta [%lf...]\n",(long unsigned int)sizeof(double)*(1*(HORIZON_T+HORIZON_L-1)),(double)optTheta[0]);
    //ughprint(fp,optTheta,1*(1*(HORIZON_T+HORIZON_L-1)));
    for( int k=0; k<LEN_theta; k++ ) { optTheta_buffer[tstep][k] = optTheta[k]; }
    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optEnergy [%lf...]\n",(long unsigned int)sizeof(double),(double)optEnergy[0]);
    //ughprint(fp,optEnergy,1);
    fprintf(flog,"\noptEnergy:\n");
    for( int k=0; k<LEN_energy; k++ ) { fprintf(flog,"%lf ",optEnergy_buffer[tstep][k] = optEnergy[k]); }
    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to optNoise [%lf...]\n",(long unsigned int)sizeof(double)*(2*(HORIZON_L+1)),(double)optNoise[0]);
    //ughprint(fp,optNoise,1*(2*(HORIZON_L+1)));
    fprintf(flog,"\noptNoise:\n");
    for( int k=0; k<LEN_noise; k++ ) { fprintf(flog,"%lf ",optNoise_buffer[tstep][k] = optNoise[k]); }


    //fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to t [%lf...]\n",(long unsigned int)sizeof(double)*(1*(HORIZON_L+HORIZON_T)),(double)t[0]);
    // write(fid,t,sizeof(double)*(1*(HORIZON_L+HORIZON_T)));
    fprintf(flog,"\ntime:\n");
    for( int k=0; k<LEN_t; k++) { fprintf(flog,"%lf ",t_buffer[tstep][k]=t[k]);    }
	//fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to ref [%lf...]\n",(long unsigned int)sizeof(double)*(1*(HORIZON_T-1)),(double)ref[0]);
    // write(fid,ref,sizeof(double)*(1*(HORIZON_T-1)));
	fprintf(flog,"\nref:\n");
	for( int k=0; k<LEN_ref; k++) { fprintf(flog,"%lf ",ref_buffer[tstep][k]=ref[k]);    } 

	//	fprintf(flog,"\nref Matlab:\n");
	//	for( int k=0; k<1*(1*(HORIZON_T-1)); k++) { fprintf(flog,"%lf ",fake_refs[tstep][k]); }

	//fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to voltage_cmd [%lf...]\n",(long unsigned int)sizeof(double)*(1*1),(double)voltage_cmd[0]);
    // write(fid,voltage_cmd,sizeof(double)*(1*1));
	//	voltage_cmd_buffer[tstep][0] = voltage_cmd[0];
	//fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to status [%lf...]\n",(long unsigned int)sizeof(double)*(1*1),(double)status[0]);
    // write(fid,status,sizeof(double)*(1*1));
	status_buffer[tstep][0] = status[0];
	//fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to iter [%lf...]\n",(long unsigned int)sizeof(double)*(1*1),(double)iter[0]);
    // write(fid,iter,sizeof(double)*(1*1));

	iter_buffer[tstep][0] = iter[0];
//	ughprint2(&iter_save_buffer,tstep,iter_save,1*(1*1));    // Is it as simple as udghprint(fp,(double)iter,1*(1*1)); ???
	//fprintf(stderr,"tmpC_DCmotor_server: writing %lu bytes to time [%lf...]\n",(long unsigned int)sizeof(double)*(1*1),(double)time[0]);
    // write(fid,time,sizeof(double)*(1*1));

    time_buffer[tstep][0] = time[0];

    
    // break;}
    // } // switch ()
    // close(fid);
    // } // while ()

//    fprintf(fp,"\n"); // from fp = fopen("mpc-data.txt", "w");



#if 1
    // put in a little sleep, just to let the scheduler run.
    usleep(0L); // microseconds
#else
    // sleep until the next sample time.
    //       unsigned int cycle_count = get_cycle_count();
    fprintf(flog,"\nbottom. cyc count: %u ",cycle_count);
    unsigned int cc_at_next_sample_time = (/* relying on int floor here*/ cycle_count/PRU_TICKS_PER_SAMPLE + 1) * PRU_TICKS_PER_SAMPLE;
    fprintf(flog,"cc at next samp time: %u ", cc_at_next_sample_time);
    unsigned int pru_ticks_to_sleep = cc_at_next_sample_time - cycle_count;
    fprintf(flog,"ticks to sleep: %u ", pru_ticks_to_sleep);
    double usec_to_sleep = (double) pru_ticks_to_sleep * USEC_PER_SEC / PRU_TICKS_PER_SEC;
    fprintf(flog, "Sleeping for %lf usec...\n",usec_to_sleep);
    usleep((unsigned long int) usec_to_sleep);
#endif

      
    /* if( tstep == 14 ) { */
    /*   fprintf(flog,"oh my (tstep=14, the firsrt time optU differs from Matlab)!!!"); */
    /* } */


  } // for loop -- timesteps

  printf("sleping for .1 sec...\n");  
  usleep(100000);
printf("Write mpc-data.txt or whatever...\n");

////////////////////////////////  
// Header row
////////////////////////////////

 /* struct BufferedVariable_s { */
 /*   char* name; */
 /*   double* var;  */
 /*   double** buf; */
 /*   int varsize; */
 /*   int bufsize; */
 /* }; */

 /* typedef struct BufferedVariable_s BufferedVariable; */

 /* const int NUM_BUFFERED_VARIABLES = 2; */

 /* BufferedVariable bufferedVariables[NUM_BUFFERED_VARIABLES] = { */
 /*   { "optU", optU, (double**)optU_buffer, LEN_u, MAX_TSTEPS },  */
 /*   { "uapply", uapply, (double**)uapply_buffer, LEN_uapply, MAX_TSTEPS } */
 /* }; */


 /* // Print header row */
 /* for( int k=0; k<NUM_BUFFERED_VARIABLES; k++ ) { */
 /*   BufferedVariable bv = bufferedVariables[k]; */
 /*   for( int l=0; l<bv.varsize; l++ ) { */
 /*     printf(fp, "ugh"); */
 /*   } */
 /* } */



 for( int k=0; k<LEN_u; k++) { fprintf(fp,"optU_%u ",k); }   

 for( int k=0; k<LEN_uapply; k++) { fprintf(fp,"uApply_%u ",k); }   


    for( int k=0; k<LEN_d; k++) { fprintf(fp,"optD_%u ",k); }      
   for( int k=0; k<LEN_x; k++) { fprintf(fp,"optX_%u_%u_%u ",k,k/3,k%3); }    
   for( int k=0; k<LEN_x0; k++) { fprintf(fp,"optX0_%u ",k); }
   for( int k=0; k<LEN_IM; k++) { fprintf(fp,"optIM_%u ",k); }     
   for( int k=0; k<LEN_omega; k++) { fprintf(fp,"optOmega_%u ",k); }  
   for( int k=0; k<LEN_theta; k++) { fprintf(fp,"optTheta_%u ",k); }  
   for( int k=0; k<LEN_noise; k++) { fprintf(fp,"optNoise_%u ",k); }
   
   for( int k=0; k<LEN_J; k++) { fprintf(fp,"optJ_%u ",k); }                                
   for( int k=0; k<LEN_energy; k++) { fprintf(fp,"optEnergy_%u ",k); }                           
   for( int k=0; k<LEN_t; k++) { fprintf(fp,"t%u ",k); }
   for( int k=0; k<LEN_ref; k++) { fprintf(fp,"ref%u ",k); }
   //	for( int k=0; k<1; k++) { fprintf(fp,"%lf ",voltage_cmd_buffer[tstep][k]); }
   for( int k=0; k<1; k++) { fprintf(fp,"status_%u ",k); }
   for( int k=0; k<1; k++) { fprintf(fp,"iter_%u ",k); }
   for( int k=0; k<1; k++) { fprintf(fp,"time_%u ",k); }

   // Print data buffer header
   fprintf_data_buf_header( fp ); // databuffer
   fprintf_cmd_buf_header_prefix( fp, "rx" ); // cb_rx
   fprintf_cmd_buf_header_prefix( fp, "tx" ); // cb_buffer

   fprintf(fp,"\n");

////////////////////////////////
// Data rows
////////////////////////////////

 for( int tstep=0; tstep<MAX_TSTEPS; tstep++ ) {
   for( int k=0; k<LEN_u; k++) { fprintf(fp,"%lf ",optU_buffer[tstep][k]); }

 for( int k=0; k<LEN_uapply; k++) { fprintf(fp,"%lf ",uapply_buffer[tstep][k]); }
   
    for( int k=0; k<LEN_d; k++) { fprintf(fp,"%lf ",optD_buffer[tstep][k]); }      
   for( int k=0; k<LEN_x; k++) { fprintf(fp,"%lf ",optX_buffer[tstep][k]); }    
   for( int k=0; k<LEN_x0; k++) { fprintf(fp,"%lf ",optX0_buffer[tstep][k]); }                        
   for( int k=0; k<LEN_IM; k++) { fprintf(fp,"%lf ",optIM_buffer[tstep][k]); }     
   for( int k=0; k<LEN_omega; k++) { fprintf(fp,"%lf ",optOmega_buffer[tstep][k]); }  
   for( int k=0; k<LEN_theta; k++) { fprintf(fp,"%lf ",optTheta_buffer[tstep][k]); }  
   for( int k=0; k<LEN_noise; k++) { fprintf(fp,"%lf ",optNoise_buffer[tstep][k]); }
   
   for( int k=0; k<LEN_J; k++) { fprintf(fp,"%lf ",optJ_buffer[tstep][k]); }                                
   for( int k=0; k<LEN_energy; k++) { fprintf(fp,"%lf ",optEnergy_buffer[tstep][k]); }                           
   for( int k=0; k<LEN_t; k++) { fprintf(fp,"%lf ",t_buffer[tstep][k]); }
   for( int k=0; k<LEN_ref; k++) { fprintf(fp,"%lf ",ref_buffer[tstep][k]); }
   //	for( int k=0; k<1; k++) { fprintf(fp,"%lf ",voltage_cmd_buffer[tstep][k]); }
   for( int k=0; k<1; k++) { fprintf(fp,"%lf ",status_buffer[tstep][k]); }
   for( int k=0; k<1; k++) { fprintf(fp,"%lf ",iter_buffer[tstep][k]); }
   for( int k=0; k<1; k++) { fprintf(fp,"%lf ",time_buffer[tstep][k]); }

   // Print data buffer:
   fprintf_data_buf( fp, db_buffer[tstep] );
    fprintf_cmd_buf(fp, cb_rx[tstep] );
    fprintf_cmd_buf(fp, cb_buffer[tstep] );



   fprintf(fp,"\n");

 }


printf("Done writing data file. Closing...\n");

 fclose(fp);




  // Hardware cleanup
  //////////////////////////////////////////


    ///////////////////////
  // Cleanup



 //  adc_cleanup();
  
  printf("Shutting down ...\n");

 send_single_voltage( 0 );


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
