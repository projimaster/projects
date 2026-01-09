###
### Makefile for CalcYouLater Project
###
### Author:  Justin Projansky (jproja01)

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# This rule builds the executable for CalcYouLater
CalcYouLater: main.o RPNCalc.o DatumStack.o Datum.o parser.o
	$(CXX) $(LDFLAGS) -o CalcYouLater main.o RPNCalc.o DatumStack.o \
		Datum.o parser.o

# This rule builds main.o
main.o: main.cpp RPNCalc.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# This rule builds RPNCalc.o
RPNCalc.o: RPNCalc.cpp RPNCalc.h Datum.o DatumStack.o parser.o
	$(CXX) $(CXXFLAGS) -c RPNCalc.cpp

# This rule builds DatumStack.o
DatumStack.o: DatumStack.cpp DatumStack.h Datum.h
	$(CXX) $(CXXFLAGS) -c DatumStack.cpp

# This rule builds parser.o
parser.o: parser.cpp parser.h
	$(CXX) $(CXXFLAGS) -c parser.cpp

# The below rule will be used by unit_test.
unit_test: unit_test_driver.o parser.o DatumStack.o Datum.o RPNCalc.o
	$(CXX) $(CXXFLAGS) $^

## Rules for building an executable from Datum+vector_example.cpp
## This is useful in seeing the behavior of Datum::toString()
Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^

##
## Here is a special rule that removes all .o files besides the provided one
## (Datum.o), all temporary files (ending with ~), and 
## a.out produced by running unit_test. First, we find all .o files 
## that are not provided files, then we run rm -f on each found file 
## using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
	-name '*.o' ! -name 'Datum.o' \
	\) -exec rm -f {} \;
	@rm -f *~ a.out

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
