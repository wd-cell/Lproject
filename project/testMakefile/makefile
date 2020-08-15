TARGET = test
LINKFILE += test.o
LINKFILE += hello.o
LINKFILE += bye.o
${TARGET} : ${LINKFILE}
	g++ $^ -o $@
	echo "******$^     ****** $@"
	echo "********** execute TARGET***********"
	./${TARGET}
	echo "********** execute TARGET***********"

clean:
	rm -rf *.o
	rm -rf test
	rm -rf a.out