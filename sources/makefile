# Makefile Generique

#cpp
EXT = cc
CXX = g++


EXEC = exe
 
CXXFLAGS = -std=c++14 -Wall -Wno-deprecated-declarations
LDFLAGS =  -lGL -lGLU -lglut -lm
 
 
OBJDIR = obj
SRC = $(wildcard *.$(EXT))
OBJ = $(SRC:.$(EXT)=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))
 
all: $(EXEC)
 
$(EXEC): $(OBJ)
	@$(CXX) -o $@ $^ $(LDFLAGS)
 
$(OBJDIR)/%.o: %.$(EXT)
	@$(CXX) -o $@ -c $< $(CXXFLAGS)
 
clean:
	@rm -rf $(OBJDIR)/*.o
	@rm -f $(EXEC)
