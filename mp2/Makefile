EXENAME = testimage
OBJS = image.o png.o rgbapixel.o testimage.o
EXENAME2 = testscene
OBJS2 = image.o png.o rgbapixel.o scene.o testscene.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all: $(EXENAME) $(EXENAME2)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

$(EXENAME2) : $(OBJS2)
	$(LD) $(OBJS2) $(LDFLAGS) -o $(EXENAME2)

image.o : image.cpp image.h png.h
	$(CXX) $(CXXFLAGS) image.cpp

scene.o : scene.cpp scene.h image.h png.h
	$(CXX) $(CXXFLAGS) scene.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

testimage.o : testimage.cpp image.h
	$(CXX) $(CXXFLAGS) testimage.cpp

testscene.o : testscene.cpp scene.h image.h
	$(CXX) $(CXXFLAGS) testscene.cpp

clean :
	-rm -f *.o $(EXENAME)
