#include <stdio.h>
#include <stdlib.h>

void main() {
  unsigned int ui_zero = 0;
  unsigned int ui_minusone = ui_zero-1;
  int i_minusone_equals = ui_minusone;
  int i_minusone_pointer = *( (int *) &(ui_minusone) );
  printf("ui_minusone: %u %d %x\ni_minusone_equals: %u %d %x\ni_minusone_pointer: %u %d %x\n",
	 ui_minusone,
	 ui_minusone,
	 ui_minusone,
	 i_minusone_equals,
	 i_minusone_equals,
	 i_minusone_equals,
	 i_minusone_pointer,
	 i_minusone_pointer,
	 i_minusone_pointer);



  printf("for loop\n");
  ui_minusone = 4;

  for( int i=0; i<10; i++ ) {
    ui_minusone--;
  i_minusone_equals = ui_minusone;
   i_minusone_pointer = *( (int *) &(ui_minusone) );
  printf("ui_minusone: %u %d %x\ni_minusone_equals: %u %d %x\ni_minusone_pointer: %u %d %x\n",
	 ui_minusone,
	 ui_minusone,
	 ui_minusone,
	 i_minusone_equals,
	 i_minusone_equals,
	 i_minusone_equals,
	 i_minusone_pointer,
	 i_minusone_pointer,
	 i_minusone_pointer);
  }

}
