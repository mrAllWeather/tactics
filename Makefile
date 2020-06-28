TARGET	= tactics

CC		= g++
CFLAGS	= -Wall -std=c++17 -O2 -I.

LINKER	= g++
LFLAGS	= -Wall	-I. -lm -lpthread

SRCPATH = src
OBJPATH = obj
BINPATH = bin

SOURCES 	:= $(wildcard $(SRCPATH)/*.cpp)
INCLUDES 	:= $(wildcard $(SRCPATH)/*.h)
OBJECTS		:= $(SOURCES:$(SRCPATH)/%.cpp=$(OBJPATH)/%.o)
rm			= rm -f

$(BINPATH)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJPATH)/%.o : $(SRCPATH)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINPATH)/$(TARGET)
	@echo "Executable removed!"