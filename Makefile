#Name: Ishaan Arya
#NetID: ixa160130
#CS 3377.502

#for backup
PROJECTNAME = Program6

#seting compiler and flags
CXX = g++
CFLAGS = -Wall -std=c++11 -Wsign-compare

#library flags
LDFLAGS = -L /scratch/perkins/lib
LDLIBS = -l cdk -l curses
INCLUDE = -I /scratch/perkins/include

#name of executable
EXECFILE = execFile

SRC = main.cc 

$(EXECFILE):$(SRC)
	$(CXX) $(LDFLAGS) $(CFLAGS) -o $@ $(SRC) $(LDLIBS) $(INCLUDE)

clean:
	@rm -f *~ $(EXECFILE)  \#*

#back up target given by Dr. Perkins
backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
	
