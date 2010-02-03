JAVAFILES=$(shell ls *.java 2> /dev/null)

all: ../c/libclient.so Main.class

run: all
	LD_LIBRARY_PATH=../c/ java -cp jna.jar:. Main

../c/libclient.so: 
	$(MAKE) -C ../c/ libclient.so

Main.class: $(JAVAFILES) ../c/libclient.so
	javac -cp jna.jar:. $(JAVAFILES)

clean:
	rm -f *.class
	rm -f ../c/libclient.so
