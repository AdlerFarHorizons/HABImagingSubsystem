# FlyCapture2Test_C makefile
# To compile the debug verison need to overwrite CXXFLAGS variable to include -ggdb

CC = gcc
OUTPUTNAME = FlyCapture2Test_C${D}
INCLUDE = -I../../include -I/usr/include/flycapture
LIBS = -L../../lib/C -lflycapture-c${D} -L../../lib -lflycapture${D}

OUTDIR = ../../bin/C

OBJS = FlyCapture2Test_C.o

${OUTPUTNAME}: ${OBJS}
	${CC} -o ${OUTPUTNAME} ${OBJS} ${LIBS} ${COMMON_LIBS} 
	mv ${OUTPUTNAME} ${OUTDIR}

%.o: %.c
	${CC} ${CFLAGS} ${INCLUDE} -c $*.c
	
clean_obj:
	rm -f ${OBJS}

clean:
	rm -f ${OUTDIR}/${OUTPUTNAME} ${OBJS}
