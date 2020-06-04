# Author: Darshan Sen (RaisinTen)

# meta

TARGET := vpp
VERSION := 1.0.0

# dirs

SRC := ./src
INCLUDE := ./include

# files

CPPFILES = $(filter-out $(wildcard $(SRC)/Vector2d.cpp $(SRC)/vppMath.cpp), $(wildcard $(SRC)/*.cpp))
OBJECTS := $(patsubst $(SRC)/%, %, $(CPPFILES:.cpp=.o))
DEPS := $(OBJECTS:.o=.d)
.PHONY := all clean

# colours

PRE := \033[
NC := $(PRE)0m
GREEN := $(PRE)1;32m
YELLOW := $(PRE)1;33m
BLUE := $(PRE)1;36m
RED := $(PRE)1;31m

# tools

CPP := g++
RM := rm

# flags util

COMPILE := -c
STD := -std=c++17
SANITIZE := -fsanitize=address -fno-omit-frame-pointer
ARCH := $(shell getconf LONG_BIT)
MODE := -m$(ARCH)
DEBUG := -g
WARNINGS := -Wall
INCLUDE_FLAG := -I $(INCLUDE)
MAKE_DEPS := -MMD -MP
DEFINES := -D TARGET=\"$(TARGET)\" -D VERSION=\"$(VERSION)\"

# flags

CPPFLAGS := $(COMPILE) $(STD) $(SANITIZE) $(MODE) $(DEBUG) $(WARNINGS) $(INCLUDE_FLAG) $(MAKE_DEPS) $(DEFINES)
RMFLAGS := -f

# recipes

all: $(TARGET)
	@echo "$(GREEN)Build complete!$(NC)"

$(TARGET): $(OBJECTS)
	@echo "$(BLUE)... making $(YELLOW)$@ $(BLUE)...$(NC)\n"
	$(CPP) -o $(TARGET) $(SANITIZE) $^
	@echo ""

%.o: $(SRC)/%.cpp
	@echo "$(BLUE)... making $(YELLOW)$@ $(BLUE)...$(NC)\n"
	$(CPP) $(CPPFLAGS) $<
	@echo ""

clean:
	@echo "$(RED)... cleaning up ...$(NC)\n"
	$(RM) $(RMFLAGS) $(OBJECTS) $(DEPS) $(TARGET)
	@echo ""
	@echo "$(RED)Cleaning complete!$(NC)"

# from the generated dependency files

-include $(DEPS)
