COMMON:=	$(ROOT)/common

CC:=		g++
CFLAGS:=	-g -I$(COMMON)
CPPFLAGS:=	-std=c++11
RM:=		rm -fr

SOURCES:=	$(wildcard *.cpp)
OBJECTS:=	$(SOURCES:.cpp=.o)

.cpp.o:
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $<

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

$(OBJECTS): $(COMMON)/cxx_test.h

check: $(TARGET)
	@./$(TARGET)

run: $(TARGET)
	./$(TARGET) $(RUN_ARGS)

clean:
	$(RM) $(OBJECTS)

distclean: clean
	$(RM) $(TARGET)

# vim:set noet sw=8 ts=8: