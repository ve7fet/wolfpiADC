CXX=g++
AR=ar
CXXFLAGS=-W -Wall
LDFLAGS=

SRC=ADS1X15_TLA2024.cpp
OUT=libads1x15_tla2024.a
OBJ=$(SRC:.cpp=.o)

all: examples

lib: $(OUT)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	$(AR) rcs $(OUT) $(OBJ)

examples: $(OUT)
	@(cd wolfpi && $(MAKE))

help:
	@echo "Usage: all, wolfpi, lib, clean, mrproper"

clean:
	rm -f $(OBJ)
	@(cd wolfpi && $(MAKE) $@)

mrproper: clean
	rm -f $(OUT)
	@(cd wolfpi && $(MAKE) $@)
