
PROJECT_DIRECTORY = $(shell pwd)

IFLAGS = -I$(PROJECT_DIRECTORY)/src

INCLUDE = -ljansson

SOURCE   = src/main.c


TARGET             = employee_finder
CC                 = gcc
ACU_CROSS_PLATFORM =
WARN_OPTION        = -Wall
BUILD_DIRECTORY    = build
OBJ_DIRECTORY      = obj
OBJECTS            = $(patsubst %.c,$(OBJ_DIRECTORY)/%.o,$(SOURCE))

vpath $(TARGET) $(BUILD_DIRECTORY)
vpath %.o $(OBJ_DIRECTORY)

$(TARGET):$(OBJECTS)
	@echo
	@echo "  \033[1;33mCreating executable file : $@\033[0m"
	$(CC) $(WARN_OPTION) $(OBJECTS) -o $(BUILD_DIRECTORY)/$@ $(INCLUDE) $(IFLAGS)
	@cp $(BUILD_DIRECTORY)/$@ .
	@echo "\033[1;33m-------------------------FINISH-------------------------- \033[0m"

$(OBJ_DIRECTORY)/%.o:%.c
	@echo
	@echo "  \033[1;32mCompiling: $<\033[0m"
	$(call init_proc);
	$(CC) $(WARN_OPTION) -c $< -o $@ $(INCLUDE) $(IFLAGS)

clean:
	@rm -fv `find . -type f -name '*.o'`
	@rm -fv ./$(BUILD_DIRECTORY)/$(TARGET)

define init_proc
	@mkdir -p $(OBJ_DIRECTORY)
	@mkdir -p $(BUILD_DIRECTORY)
	@find . -type f -name '*.c' -printf '%h\n' |sort -u | grep -v '$(BUILD_DIRECTORY)' | grep -v '$(OBJ_DIRECTORY)' > dir.struct
	@cd $(OBJ_DIRECTORY) && xargs mkdir -p < ../dir.struct
endef