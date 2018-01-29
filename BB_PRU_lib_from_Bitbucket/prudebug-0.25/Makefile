
# CC=arm-none-linux-gnueabi-gcc



SRCS=$(wildcard *.c)

OBJS=$(SRCS:.c=.o)

all: $(OBJS)


# objs = prudbg.o cmdinput.o cmd.o printhelp.o da.o uio.o

prudebug : ${objs}
	gcc -mfloat-abi=hard -mfpu=vfp ${objs} -o prudebug

