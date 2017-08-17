objects = wpthread.o

wpthread: $(objects)
	gcc   $(objects) -o   wpthread_test -lpthread
	
wpthread.o: wpthread.c


.PHONY: clean

clean:
	-rm wpthread_test $(objects)