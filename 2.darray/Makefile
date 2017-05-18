CFILES= main.c darray.c
all:
	#gcc -g typedef.h darray.c darray.h main.c  -o darray.exe
	gcc -g -shared -lpthread $(CFILES) -o libdarray.so
	gcc -g -D DARRAY_TEST -lpthread $(CFILES)  -o darray_test
clean:
	rm -f *.exe
