###
### Makefile for Gerp Project
###
### Author:  Justin Projansky (jproj01) and Joon Heo (jheo03)


## Vars:
CXX      = clang++
CXXFLAGS = -g3 -O2 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 


## Gerp program:
gerp: main.o Gerp.o HashTable.o FSTree.o DirNode.o
	${CXX} ${CXXFLAGS} -o $@ $^

main.o: main.cpp Gerp.h

Gerp.o: Gerp.cpp Gerp.h HashTable.cpp HashTable.h IndexingStructs.h FSTree.h \
	DirNode.h

HashTable.o: HashTable.cpp HashTable.h IndexingStructs.h FSTree.h DirNode.h

IndexingStructs.o: IndexingStructs.h

## Processing:
processing.o: processing.h processing.cpp

## Unit test:
unit_test: unit_test_driver.o processing.o Gerp.o HashTable.o FSTree.o \
	DirNode.o
	$(CXX) $(CXXFLAGS) $^

unit_test_driver.o: unit_test_driver.cpp


##
## Here is a special rule that removes all .o files besides the provided ones 
## (DirNode.o and FSTree.o), all temporary files (ending with ~), and 
## a.out produced by running unit_test. First, we find all .o files 
## that are not provided files, then we run rm -f on each found file 
## using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
		-name '*.o' ! -name 'FSTree.o' ! -name 'DirNode.o' \
		\) -exec rm -f {} \;
	@rm -f *~ a.out

