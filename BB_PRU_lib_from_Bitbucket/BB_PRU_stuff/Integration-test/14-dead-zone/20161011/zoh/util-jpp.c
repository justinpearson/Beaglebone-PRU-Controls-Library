#include "util-jpp.h"

#include <math.h> // fmod
#include <stdbool.h> // true/false
#include <stdio.h> // printf
#include <stdlib.h> // exit

#define BILLION  (1000000000LL)

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





// https://gist.github.com/diabloneo/9619917
void timespec_diff(struct timespec *start, struct timespec *stop,
                   struct timespec *result)
{
  if ((stop->tv_nsec - start->tv_nsec) < 0) {
    result->tv_sec = stop->tv_sec - start->tv_sec - 1;
    result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000L;
  } else {
    result->tv_sec = stop->tv_sec - start->tv_sec;
    result->tv_nsec = stop->tv_nsec - start->tv_nsec;
  }
  return;
}


double ts_to_sec( struct timespec ts ) {
  return( ts.tv_sec + ts.tv_nsec / (double)BILLION );
}

void toc(double* sec_since_start, double* sec_since_last ) {
  static struct timespec t0;
  static struct timespec tprev;
  static bool firstTime = true;
  char* errinfo = NULL;
  errinfo = (char *) malloc (sizeof (char) * 200);

  if( firstTime ) {
    firstTime = false;

    if( clock_gettime(CLOCK_REALTIME,&t0) == -1 ) {
      sprintf(errinfo, "%s %s %d: clock_gettime\n", __FUNCTION__, __FILE__, __LINE__ );
      perror(errinfo);
      exit( EXIT_FAILURE );
    }


    if( clock_gettime(CLOCK_REALTIME,&tprev) == -1 ) {
      sprintf(errinfo, "%s %s %d: clock_gettime\n", __FUNCTION__, __FILE__, __LINE__ );
      perror(errinfo);
      exit( EXIT_FAILURE );
    }

  }
  struct timespec tnow;
  if( clock_gettime(CLOCK_REALTIME,&tnow) == -1 ) {
    sprintf(errinfo, "%s %s %d: clock_gettime\n", __FUNCTION__, __FILE__, __LINE__ );
    perror(errinfo);
    exit( EXIT_FAILURE );
  }
  struct timespec tdiff;
  struct timespec tdiff2;
  timespec_diff(&t0, &tnow, &tdiff);
  timespec_diff(&tprev, &tnow, &tdiff2);
  double d = ts_to_sec(tdiff);
  double d2 = ts_to_sec(tdiff2);
  //  printf("Main CPU time: sec: %lu\tnsec: %lu\n",tdiff.tv_sec, tdiff.tv_nsec);
  //  fprintf(fp,"Main CPU time: %15.9lf (since last call: %15.9lf) \n",d,d2);
  tprev.tv_sec = tnow.tv_sec; // new becomes old for next time.
  tprev.tv_nsec = tnow.tv_nsec;
  
  *sec_since_start = d;
  *sec_since_last = d2;
}
