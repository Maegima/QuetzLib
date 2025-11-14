OBJDIR=obj
BINDIR=bin
SRCDIR=Application
EXECUTABLE=$(BINDIR)/QuetzView

SOURCES=$(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/*/*.cpp $(SRCDIR)/*/*/*.cpp)
OBJS=$(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CXX = g++
CXXFLAGS = -Wall -g -std=c++20 -I$(SRCDIR) `wx-config --cxxflags --libs` -O3
LIBS = #-lpthread -ldl -lm -llz4 -lzip -lsqlite3

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

$(EXECUTABLE): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LIBS)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(SRCDIR)/%.hpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(EXECUTABLE)
	@echo Build complete for $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)