CCX := g++
CXXFLAGS := -std=c++11 =02 =Wall =Wextra
LINKFLAGS := -static
AR := ar
ARFLAGS := ruv

MAJOR := 0
MINOR := 1
NAME := hysteresis
VERSION := $(MAJOR).$(MINOR)
SOURCE := $(wildcard *.cpp)
OBJECT := $(SOURCE:.cpp=.o)

$(info SOURCE is $(SOURCE))
$(info OBJECT is $(OBJECT))

LIBSO = lib$(NAME).so
LIBSOM = $(LIBSO).$(MAJOR)
LIBSOV = $(LIBSO).$(VERSION)
LIBA = lib$(NAME).a


all: hysteresis

lib: $(LIBSO) $(LIBA)

$(LIBSO): $(LIBSOV)
	ln -s $(LIBSOV) $(LIBSO)

$(LBSOV): $(NAME).o
	$(CCX) $(CXXFLAGS) -shared -Wl,-soname,$(LIBSOM) -o $(LIBSOV) $(OBJECT)

$(LIBA): $(NAME).o
	$(AR) $(ARFLAGS) $(LIBA) $(OBJECT)


