
parents: parents.o lockit.o
	cc -o parents parents.o lockit.o -lpthread

parents.o:parents.c
	cc -c parents.c

lockit.o:lockit.c
	cc -c lockit.c

son: son.o lockit.o
	cc -o son son.o lockit.o -lpthread

son.o: son.c
	cc -c son.c

daughter:daughter.o lockit.o 
	cc -o daughter daughter.o lockit.o -lpthread

daughter.o:daughter.c
	cc -c daughter.c

children:children.c
	cc -o children.c
