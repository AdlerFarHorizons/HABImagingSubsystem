# CustomImageEx makefile

CC = g++
OUTPUTNAME = ImageEventEx${D}
INCLUDE = -I../../include -I/usr/include/flycapture
LIBS = -L../../lib -lflycapture${D}

OUTDIR = ../../bin

OBJS = ImageEventEx.o

${OUTPUTNAME}: ${OBJS}
	${CC} -o ${OUTPUTNAME} ${OBJS} ${LIBS} ${COMMON_LIBS} 
	mv ${OUTPUTNAME} ${OUTDIR}

%.o: %.cpp
	${CC} ${CFLAGS} ${INCLUDE} -Wall -c $*.cpp
	
clean_obj:
	rm -f ${OBJS}	@echo "all cleaned up!"

clean:
	rm -f ${OUTDIR}/${OUTPUTNAME} ${OBJS}	@echo "all cleaned up!"
