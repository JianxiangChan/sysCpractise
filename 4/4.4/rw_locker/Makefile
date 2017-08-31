CFILES=dlist.c locker_pthread.c locker_nest.h
all:
	gcc -g -shared $(CFILES) -o libdlist.so  -lpthread
	gcc -g -DDLIST_TEST $(CFILES)  -o dlist_test -lpthread 

clean:
	rm -f *test *.exe *.so
