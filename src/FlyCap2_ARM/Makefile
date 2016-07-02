# A more complex Makefile

# Setting correct compiler and compiler flags
ifeq ($(PLATFORM),arm)
	CC = arm-linux-gnueabi-g++
	STRIP = arm-linux-gnueabi-strip
	CFLAGS += -mfloat-abi=softfp
	CFLAGS += -UMACHINE_ARCH_X32 -UMACHINE_ARCH_X64 -DMACHINE_ARCH_ARM
else
	ifeq ($(PLATFORM),armhf)
		CC = arm-linux-gnueabihf-g++
		STRIP = arm-linux-gnueabihf-strip
		CFLAGS += -mfloat-abi=hard
		CFLAGS += -UMACHINE_ARCH_X32 -UMACHINE_ARCH_X64 -DMACHINE_ARCH_ARM
	else
		CC = g++
		STRIP = strip
	endif
endif

SOFTWARELIB = /softwarelib

# GTK dependencies
ifeq ($(PLATFORM),arm)
	GTK_ROOT = $(SOFTWARELIB)/libgtk/precise/arm
	GTK_SUFFIX = arm-linux-gnueabi
else
	ifeq ($(PLATFORM),armhf)
		GTK_ROOT = $(SOFTWARELIB)/libgtk/precise/armhf
		GTK_SUFFIX = arm-linux-gnueabihf
	else
		ifeq ($(PLATFORM),amd64)
			GTK_ROOT = $(SOFTWARELIB)/libgtk/precise/amd64
			GTK_SUFFIX = x86_64-linux-gnu
		else
			GTK_ROOT = $(SOFTWARELIB)/libgtk/precise/i386
			GTK_SUFFIX = i386-linux-gnu
		endif
	endif
endif

ifeq ($(PLATFORM),)
GTK_INCLUDE = `pkg-config --cflags gtkmm-2.4` `pkg-config --cflags giomm-2.4` `pkg-config --cflags libglademm-2.4`
else
GTK_INCLUDE = -I${GTK_ROOT}/usr/include \
	-I${GTK_ROOT}/usr/include/atk-1.0 \
	-I${GTK_ROOT}/usr/include/atkmm-1.6 \
	-I${GTK_ROOT}/usr/include/cairo \
	-I${GTK_ROOT}/usr/include/cairomm-1.0 \
	-I${GTK_ROOT}/usr/include/fontconfig \
	-I${GTK_ROOT}/usr/include/freetype2 \
	-I${GTK_ROOT}/usr/include/gdkmm-2.4 \
	-I${GTK_ROOT}/usr/include/gdk-pixbuf-2.0 \
	-I${GTK_ROOT}/usr/include/giomm-2.4 \
	-I${GTK_ROOT}/usr/include/glib-2.0 \
	-I${GTK_ROOT}/usr/include/glibmm-2.4 \
	-I${GTK_ROOT}/usr/include/gtk-2.0 \
	-I${GTK_ROOT}/usr/include/gtk-2.0/gtk/gtk \
	-I${GTK_ROOT}/usr/include/gtkglext-1.0 \
	-I${GTK_ROOT}/usr/include/gtkglext-1.0/gdk \
	-I${GTK_ROOT}/usr/include/gtkglextmm-1.2 \
	-I${GTK_ROOT}/usr/include/gtkmm-2.4 \
	-I${GTK_ROOT}/usr/include/libglademm-2.4 \
	-I${GTK_ROOT}/usr/include/pango-1.0 \
	-I${GTK_ROOT}/usr/include/pangomm-1.4 \
	-I${GTK_ROOT}/usr/include/sigc++-2.0 \
	-I${GTK_ROOT}/usr/include/sigc++-2.0/sigc++ \
	-I${GTK_ROOT}/usr/lib/gtkglext-1.0/include \
	-I${GTK_ROOT}/usr/lib/gtkglextmm-1.2/include \
	-I${GTK_ROOT}/usr/lib/${GTK_SUFFIX}/cairomm-1.0/include \
	-I${GTK_ROOT}/usr/lib/${GTK_SUFFIX}/gdkmm-2.4/include \
	-I${GTK_ROOT}/usr/lib/${GTK_SUFFIX}/glib-2.0/include \
	-I${GTK_ROOT}/usr/lib/${GTK_SUFFIX}/glibmm-2.4/include \
	-I${GTK_ROOT}/usr/lib/${GTK_SUFFIX}/gtk-2.0/include \
	-I${GTK_ROOT}/usr/lib/${GTK_SUFFIX}/gtkmm-2.4/include \
	-I${GTK_ROOT}/usr/lib/${GTK_SUFFIX}/pangomm-1.4/include \
	-I${GTK_ROOT}/usr/lib/${GTK_SUFFIX}/sigc++-2.0/include
endif

ifeq ($(PLATFORM),)
GTK_LIBS = `pkg-config --libs gtkmm-2.4` `pkg-config --libs giomm-2.4` `pkg-config --libs libglademm-2.4` `pkg-config --libs gthread-2.0`
else
GTK_LIBS = -L${GTK_ROOT}/usr/lib -lglademm-2.4 -lgdkglext-x11-1.0 -lgdkglextmm-x11-1.2 -lgtkglext-x11-1.0 -lgtkglextmm-x11-1.2 \
	-L${GTK_ROOT}/usr/lib/${GTK_SUFFIX} -latk-1.0 -latkmm-1.6 -lcairo -lcairomm-1.0 -lexpat -lffi -lfontconfig -lfreetype -lgdk-x11-2.0 \
	-lgdk_pixbuf-2.0 -lglibmm-2.4 -lgobject-2.0 -lgtk-x11-2.0 -lgmodule-2.0 -lpango-1.0 -lpangocairo-1.0 -lpangoft2-1.0 -lpangomm-1.4 \
	-lpangox-1.0 -lpangoxft-1.0 -lpcre -lpixman-1 -lpng12 -lsigc-2.0 -lgiomm-2.4 -lglade-2.0 -lgthread-2.0 -lgio-2.0 -lgtk-x11-2.0 \
	-lgdkmm-2.4 -lgtkmm-2.4 -lglib-2.0 -lselinux -lxcb -lxcb-shm -lxcb-render -lX11 -lXau -lXext -lXrender -lXinerama -lXi -lXdmcp \
	-lXrandr -lXcursor -lXcomposite -lXdamage -lXfixes -lxml2 -lz
endif

GCHNAME = Precompiled.h.gch

GCH_INCLUDES = -I../../include ${GTK_INCLUDE}
INCLUDES = ${GCH_INCLUDES}

LIBS = -L../../lib -lflycapture${D} -lflycapturegui${D} ${GTK_LIBS}

NAME = FlyCap2${D}

XMLNAME = FlyCap2

OUTDIR = ../../bin

OBJS = main.o FlycapWindow.o FrameRateCounter.o ImageDrawingArea.o InformationPane.o HistogramWindow.o HistogramDrawingArea.o SaveImageFileChooserDialog.o

all: ${GCHNAME} ${NAME} glade

${GCHNAME}: Precompiled.h
	${CC} ${CFLAGS} ${GCH_INCLUDES} -Wall -c Precompiled.h

${NAME}: ${OBJS}
	${CC} -Wall -o ${NAME} ${OBJS} ${LIBS} -export-dynamic
ifneq (${D}, d)
	${STRIP} --strip-unneeded ${NAME}
endif
	mv ${NAME} ${OUTDIR}/${NAME}

%.o: %.cpp
	${CC} ${CFLAGS} ${INCLUDES} -Wall -c $*.cpp

glade:
	cp ${XMLNAME}.glade ${OUTDIR}/${XMLNAME}.glade

clean_obj:
	rm -f ${OBJS} Precompiled.h.gch

clean:
	rm -f ${OUTDIR}/${NAME} ${OBJS} Precompiled.h.gch
