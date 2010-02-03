sources = $(wildcard *.c)
objects = $(sources:%.c=%.o)
libclient_objects = $(sources:%.c=libclient_%.o)
deps = $(sources:%.c=%.d)

all: sexp.a libclient_sexp.a

clean:
	rm -f $(objects) $(libclient_objects) $(deps) sexp.a libclient_sexp.a

%.d: %.c
	@set -e; rm -f $@; \
	(dirname $< | tr '\n' '/'; $(CC) -MM $(CPPFLAGS) $<) > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

libclient_%.o: override CFLAGS += -fPIC
libclient_%.o: %.c %.d
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

.PHONY: clean all

libclient_sexp.a: ${libclient_objects}
	ar cr $@ $^
	ranlib $@

sexp.a: ${objects}
	ar cr $@ $^
	ranlib $@

-include $(deps)

