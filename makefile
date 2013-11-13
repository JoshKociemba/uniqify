CC = icc
CFLAGS = -Wall -std=c99 -openmp -O3 -g -I.

#overkill on the flags, but that doesn't hurt anything
LDFLAGS = -lrt -lpthread -lm

#replace this if you want to change the output name
CTARGET = uniqify

#any headers go here
INCLUDES = 

#any .c or .cpp files go here
CSOURCE = ${CTARGET}.c

#default is to compile
default: compile

#depends on all of you source and header files
compile: ${CSOURCE} ${INCLUDES}
	
#this assumes you actually are linking all of the source files together
	${CC} ${CFLAGS} ${CSOURCE} -o ${CTARGET} ${LDFLAGS}

#to debug use this
debug: ${CSOURCE} ${INCLUDES}
	${CC} ${CFLAGS} ${CSOURCE} -o ${CTARGET} ${LDFLAGS} -DDEBUG

###########
# TeX Portion of the makefile
# Author Josh Kociemba
###########

TEX_TARGET = writeup

TEX_SOURCE = ${TEX_TARGET}.tex

default: pdf

dvi: ${TEX_SOURCE}
	latex ${TEX_SOURCE}
	latex $(TEX_SOURCE)

ps: dvi
	dvips -R -Poutline -t letter ${TEX_TARGET}.dvi -o ${TEX_TARGET}.ps

pdf: ps
	ps2pdf ${TEX_TARGET}.ps
	rm ${TEX_TARGET}.aux
	rm ${TEX_TARGET}.ps
	rm ${TEX_TARGET}.out
	rm ${TEX_TARGET}.dvi
	rm ${TEX_TARGET}.log
	
