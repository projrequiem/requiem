CCX := g++
CXXFLAGS := -std=c++11 =02 =Wall =Wextra -fPIC
LINKFLAGS := -static
AR := ar
ARFLAGS := ruv
OBJDIR := obj

MAJOR := 0
MINOR := 1
NAME := matrix
VERSION := $(MAJOR).$(MINOR)
SOURCE := $(wildcard *.hpp)
OBJECT := $(SOURCE:.hpp=.o)

$(info SOURCE is $(SOURCE))
$(info OBJECT is $(OBJECT))

LIBSO = lib$(NAME).so
LIBSOM = $(LIBSO).$(MAJOR)
LIBSOV = $(LIBSO).$(VERSION)
LIBA = lib$(NAME).a


lib: $(OBJECT) $(LIBSO) $(LIBA)

$(LIBSO): $(LIBSOV)
	ln -s $(LIBSOV) $(LIBSO)

$(LIBSOV): $(OBJECT)
	$(CCX) $(CXXFLAGS) -shared -Wl,-soname,$(LIBSOM) -o $(LIBSOV) $(OBJECT)

$(LIBA): $(OBJECT)
	$(AR) $(ARFLAGS) $(LIBA) $(OBJECT)

$(OBJECT): $(SOURCE)
	$(CXX) -c $(CXXFLAGS) $(SOURCE)

clean:
	rm *.o *.so*
