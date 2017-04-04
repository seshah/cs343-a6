CXX = u++							# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -Wno-maybe-uninitialized -MMD -O2
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS1 = Config.o Student.o WATCardOffice.o Bank.o Parent.o GroupOff.o VendingMachine.o NameServer.o BottlingPlant.o Truck.o Printer.o Main.o  # files requird
EXEC1 = soda

OBJECT = ${OBJECTS1}				# all object files
DEPEND = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXECS = ${EXEC1}					# all executables

#############################################################

.PHONY : all clean

all : ${EXECS}						# build all executables

${EXEC1} : ${OBJECTS1}				# link step 1st executable
	${CXX} ${CXXFLAGS} $^ -o $@
	
#############################################################

${OBJECT} : ${MAKEFILE_NAME}

-include ${DEPENDS}

clean :
	rm -f *.d *.o ${EXECS}