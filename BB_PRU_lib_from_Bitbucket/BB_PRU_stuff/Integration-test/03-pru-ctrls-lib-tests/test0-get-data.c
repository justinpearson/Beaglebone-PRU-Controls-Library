#include <unistd.h> // for unsigned int sleep(unsigned int seconds);
#include "jpp-pru-lib.h"

int main() {

  start_pru( );

  DataBuffer d;

  get_data_buf( &d );
  print_data_buf(d);

  return(0);

}
