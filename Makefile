# To use this Makefile, you type:
#
#        make 
#                  
# Libraries are assumed to be in the default search paths
# as are any required include files

# last-modified: Mon Oct  5 20:34:59 2020

# Assumes the following file exists in the proper place.
include /home/ben/devl/graphics/examples/Makefile.defs

# First target in the makefile will be used if you simply type make
# with no arguments. 
# animate is the executable to be created.
animate: game.cc i.o o.o t.o j.o l.o s.o z.o tetromino.o
	$(CC) game.cc  $(InitShader) i.o o.o t.o j.o l.o s.o z.o tetromino.o $(OPTIONS) $(LDLIBS) -o tetris

# One pattern for each other file to be compiled.  These will be
# object files (i.e. .o files) Notice that only the options arguments
# are passed, not the LDLIBS as there will be no linking done for the
# .o files.
i.o: i.h i.cc tetromino.h
	$(CC) i.cc -c $(OPTIONS)

# circle.o: circle.h circle.cc object.h
# 	$(CC) circle.cc -c $(OPTIONS)

o.o: o.h o.cc tetromino.h
	$(CC) o.cc -c $(OPTIONS)

t.o: t.h t.cc tetromino.h
	$(CC) t.cc -c $(OPTIONS)

j.o: j.h j.cc tetromino.h
	$(CC) j.cc -c $(OPTIONS)

l.o: l.h l.cc tetromino.h
	$(CC) l.cc -c $(OPTIONS)	

s.o: s.h s.cc tetromino.h
	$(CC) s.cc -c $(OPTIONS)

z.o: z.h z.cc tetromino.h
	$(CC) z.cc -c $(OPTIONS)

tetromino.o: tetromino.h tetromino.cc
	$(CC) tetromino.cc -c $(OPTIONS)

# clean up after yourself
clean: 
	rm -f tetris i.o o.o t.o j.o l.o s.o z.o tetromino.o
