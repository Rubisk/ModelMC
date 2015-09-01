#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include ModelMaker-Makefile.mk

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/json/json.o \
	${OBJECTDIR}/src/json/object_value.o \
	${OBJECTDIR}/src/json/simple_values.o \
	${OBJECTDIR}/src/json/util.o \
	${OBJECTDIR}/src/json/vector_value.o \
	${OBJECTDIR}/src/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# C Compiler Flags
CFLAGS=`cppunit-config --cflags` 

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L.

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${TESTDIR}/TestFiles/f3.exe

${TESTDIR}/TestFiles/f3.exe: ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f3 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/json/json.o: src/json/json.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/json.o src/json/json.cpp

${OBJECTDIR}/src/json/object_value.o: src/json/object_value.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/object_value.o src/json/object_value.cpp

${OBJECTDIR}/src/json/simple_values.o: src/json/simple_values.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/simple_values.o src/json/simple_values.cpp

${OBJECTDIR}/src/json/util.o: src/json/util.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/util.o src/json/util.cpp

${OBJECTDIR}/src/json/vector_value.o: src/json/vector_value.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/vector_value.o src/json/vector_value.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: E:/CLib/raw/nvwa/debug_new.cpp

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/json_load_test.o ${TESTDIR}/tests/json_object_test.o ${TESTDIR}/tests/json_save_test.o ${TESTDIR}/tests/json_simple_values_test.o ${TESTDIR}/tests/json_test.o ${TESTDIR}/tests/json_util_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -L/E\CLib\raw\cppunit-1.13.2\src\cppunit\.libs -lcppunit-1-13-0 


${TESTDIR}/tests/json_load_test.o: tests/json_load_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/json_load_test.o tests/json_load_test.cpp


${TESTDIR}/tests/json_object_test.o: tests/json_object_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/json_object_test.o tests/json_object_test.cpp


${TESTDIR}/tests/json_save_test.o: tests/json_save_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/json_save_test.o tests/json_save_test.cpp


${TESTDIR}/tests/json_simple_values_test.o: tests/json_simple_values_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/json_simple_values_test.o tests/json_simple_values_test.cpp


${TESTDIR}/tests/json_test.o: tests/json_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/json_test.o tests/json_test.cpp


${TESTDIR}/tests/json_util_test.o: tests/json_util_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/json_util_test.o tests/json_util_test.cpp


${OBJECTDIR}/src/json/json_nomain.o: ${OBJECTDIR}/src/json/json.o src/json/json.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/json/json.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/json_nomain.o src/json/json.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/json/json.o ${OBJECTDIR}/src/json/json_nomain.o;\
	fi

${OBJECTDIR}/src/json/object_value_nomain.o: ${OBJECTDIR}/src/json/object_value.o src/json/object_value.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/json/object_value.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/object_value_nomain.o src/json/object_value.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/json/object_value.o ${OBJECTDIR}/src/json/object_value_nomain.o;\
	fi

${OBJECTDIR}/src/json/simple_values_nomain.o: ${OBJECTDIR}/src/json/simple_values.o src/json/simple_values.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/json/simple_values.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/simple_values_nomain.o src/json/simple_values.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/json/simple_values.o ${OBJECTDIR}/src/json/simple_values_nomain.o;\
	fi

${OBJECTDIR}/src/json/util_nomain.o: ${OBJECTDIR}/src/json/util.o src/json/util.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/json/util.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/util_nomain.o src/json/util.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/json/util.o ${OBJECTDIR}/src/json/util_nomain.o;\
	fi

${OBJECTDIR}/src/json/vector_value_nomain.o: ${OBJECTDIR}/src/json/vector_value.o src/json/vector_value.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/json/vector_value.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/vector_value_nomain.o src/json/vector_value.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/json/vector_value.o ${OBJECTDIR}/src/json/vector_value_nomain.o;\
	fi

${OBJECTDIR}/src/main_nomain.o: ${OBJECTDIR}/src/main.o src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -s -I. -I../../CLib/include -I/E/CLib/raw/nvwa -I. -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main_nomain.o src/main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${TESTDIR}/TestFiles/f3.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
