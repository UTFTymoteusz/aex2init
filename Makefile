BIN_NAME = aex2init

CXX = x86_64-aex2-elf-gcc
LD  = ld

MKDIR = mkdir -p

BIN  := bin/
DEP_DEST := $(BIN)dep/
OBJ_DEST := $(BIN)obj/

CXXFILES  := $(shell find . -type f -name '*.cpp')
HXXFILES  := $(shell find . -type f -name '*.hpp')
OBJS      := $(patsubst %.o, $(OBJ_DEST)%.o, $(CXXFILES:.cpp=.cpp.o))

BIN_OBJ = $(BIN)$(BIN_NAME).elf

GFLAGS = -O3 -Wall -Wextra -nostdlib -pipe

INCLUDES := -I. -I$(ARCH) -Iinclude/ -I../../kernel/include \
		    -I../../kernel/arch/x64/include

CXXFLAGS := $(GFLAGS)     \
	-std=c++17           \
	-fno-rtti            \
	-fno-exceptions      \
	-ffreestanding       \
	-masm=intel          \
	-mcmodel=kernel      \
	-fno-pic             \
	-fno-stack-protector \
	-mno-red-zone        \
	$(INCLUDES)

ASFLAGS := -felf64

LDFLAGS := $(GFLAGS)        \
	-ffreestanding          \
	-z max-page-size=0x1000 \
	-no-pie

format:
	@$(MKDIR) $(BIN)
	clang-format -style=file -i ${CXXFILES} ${HXXFILES}

all: $(OBJS)
	@$(MKDIR) $(BIN)
	@$(LD) -r -o $(BIN_OBJ) $(OBJS)

include $(shell find $(DEP_DEST) -type f -name *.d)

copy:
	@cp $(BIN_OBJ) "$(COPY_DIR)"

clean:
	rm -rf $(BIN)

$(OBJ_DEST)%.cpp.o : %.cpp
	@$(MKDIR) ${@D}
	@$(MKDIR) $(dir $(DEP_DEST)$*)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD -MT $@ -MF $(DEP_DEST)$*.cpp.d