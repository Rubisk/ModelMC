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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include ModelMaker-Makefile.mk

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/element.o \
	${OBJECTDIR}/src/json/extract.o \
	${OBJECTDIR}/src/json/json.o \
	${OBJECTDIR}/src/json/object_value.o \
	${OBJECTDIR}/src/json/simple_values.o \
	${OBJECTDIR}/src/json/util.o \
	${OBJECTDIR}/src/json/vector_value.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/util/status.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f8 \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f6 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f7

# C Compiler Flags
CFLAGS=`cppunit-config --cflags` 

# CC Compiler Flags
CCFLAGS=`cppunit-config --cflags` 
CXXFLAGS=`cppunit-config --cflags` 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`cppunit-config --libs` `cppunit-config --libs` `cppunit-config --libs` `cppunit-config --libs` `cppunit-config --libs` `cppunit-config --libs`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${TESTDIR}/TestFiles/f3.exe

${TESTDIR}/TestFiles/f3.exe: ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f3 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/element.o: src/element.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/element.o src/element.cpp

${OBJECTDIR}/src/json/extract.o: src/json/extract.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/extract.o src/json/extract.cpp

${OBJECTDIR}/src/json/json.o: src/json/json.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/json.o src/json/json.cpp

${OBJECTDIR}/src/json/object_value.o: src/json/object_value.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/object_value.o src/json/object_value.cpp

${OBJECTDIR}/src/json/simple_values.o: src/json/simple_values.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/simple_values.o src/json/simple_values.cpp

${OBJECTDIR}/src/json/util.o: src/json/util.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/util.o src/json/util.cpp

${OBJECTDIR}/src/json/vector_value.o: src/json/vector_value.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/vector_value.o src/json/vector_value.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/util/status.o: util/status.cpp 
	${MKDIR} -p ${OBJECTDIR}/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/util/status.o util/status.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/element_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   

${TESTDIR}/TestFiles/f8: ${TESTDIR}/tests/extract_json_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f8 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/json/object_values_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} `cppunit-config --libs` `cppunit-config --libs` `cppunit-config --libs` `cppunit-config --libs` `cppunit-config --libs`   

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/json/simple_values_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   

${TESTDIR}/TestFiles/f6: ${TESTDIR}/tests/json/json_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/json/util_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/json/vector_value_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   

${TESTDIR}/TestFiles/f7: ${TESTDIR}/tests/status_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f7 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   


${TESTDIR}/tests/element_test.o: tests/element_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/element_test.o tests/element_test.cpp


${TESTDIR}/tests/extract_json_test.o: tests/extract_json_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/extract_json_test.o tests/extract_json_test.cpp


${TESTDIR}/tests/json/object_values_test.o: tests/json/object_values_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests/json
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/json/object_values_test.o tests/json/object_values_test.cpp


${TESTDIR}/tests/json/simple_values_test.o: tests/json/simple_values_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests/json
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/json/simple_values_test.o tests/json/simple_values_test.cpp


${TESTDIR}/tests/json/json_test.o: tests/json/json_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests/json
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/json/json_test.o tests/json/json_test.cpp


${TESTDIR}/tests/json/util_test.o: tests/json/util_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests/json
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/json/util_test.o tests/json/util_test.cpp


${TESTDIR}/tests/json/vector_value_test.o: tests/json/vector_value_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests/json
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/json/vector_value_test.o tests/json/vector_value_test.cpp


${TESTDIR}/tests/status_test.o: tests/status_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/status_test.o tests/status_test.cpp


${OBJECTDIR}/src/element_nomain.o: ${OBJECTDIR}/src/element.o src/element.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/element.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/element_nomain.o src/element.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/element.o ${OBJECTDIR}/src/element_nomain.o;\
	fi

${OBJECTDIR}/src/json/extract_nomain.o: ${OBJECTDIR}/src/json/extract.o src/json/extract.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/json/extract.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/extract_nomain.o src/json/extract.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/json/extract.o ${OBJECTDIR}/src/json/extract_nomain.o;\
	fi

${OBJECTDIR}/src/json/json_nomain.o: ${OBJECTDIR}/src/json/json.o src/json/json.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/json
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/json/json.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/json_nomain.o src/json/json.cpp;\
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
	    $(COMPILE.cc) -O2 -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/object_value_nomain.o src/json/object_value.cpp;\
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
	    $(COMPILE.cc) -O2 -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/simple_values_nomain.o src/json/simple_values.cpp;\
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
	    $(COMPILE.cc) -O2 -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/util_nomain.o src/json/util.cpp;\
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
	    $(COMPILE.cc) -O2 -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/json/vector_value_nomain.o src/json/vector_value.cpp;\
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
	    $(COMPILE.cc) -O2 -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main_nomain.o src/main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/main_nomain.o;\
	fi

${OBJECTDIR}/util/status_nomain.o: ${OBJECTDIR}/util/status.o util/status.cpp 
	${MKDIR} -p ${OBJECTDIR}/util
	@NMOUTPUT=`${NM} ${OBJECTDIR}/util/status.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/util/status_nomain.o util/status.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/util/status.o ${OBJECTDIR}/util/status_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f8 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f6 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	    ${TESTDIR}/TestFiles/f7 || true; \
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
