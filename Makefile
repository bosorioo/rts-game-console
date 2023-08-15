SRC_PATH = src/
# INC_PATH = include/
INC_PATH = src/
LIB_PATH = lib/
OBJ_PATH = obj/
OUTPUT_PATH = ./
OUTPUT_NAME = rts-game

CC = gcc
LFLAGS = -lncurses
CFLAGS = -Wall -I$(INC_PATH) -g

ifdef SystemRoot
	REM = del /Q
	FixPath = $(subst /,\,$1)
	CFLAGS = $(CFLAGS) -L$(LIB_PATH)
else
	REM = rm -f
	FixPath = $1
endif

all: init exec

SRC_FILES = $(notdir $(wildcard $(SRC_PATH)*.c))
SCREENS_FILES = $(patsubst src/screens/%.c, screens/%.c, $(wildcard $(SRC_PATH)screens/*.c))
FILES = $(SRC_FILES) $(SCREENS_FILES)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo Compiling "$(notdir $@)" $^ $(CC) $(CFLAGS)...
	@$(CC) -O2 -c $^ -o $@ $(CFLAGS)

init:
	if [ ! -d "$(OBJ_PATH)" ]; then mkdir $(OBJ_PATH); fi
	if [ ! -d "$(OBJ_PATH)screens" ]; then mkdir $(OBJ_PATH)screens; fi

exec: $(patsubst %.c, $(OBJ_PATH)%.o, $(FILES))
	@echo Generating output on "$(OUTPUT_PATH)$(OUTPUT_NAME)".
	@$(CC) $^ -o $(OUTPUT_PATH)$(OUTPUT_NAME) $(CFLAGS) $(LFLAGS)

gcov:
	gcov -oobj attacktype.o clock.o color_manager.o engine.o \
map.o menu.o player.o position.o screen.o unit.o unitlist.o unitloader.o \
unittype.o

print:
	@echo $(FILES) $(REM)

docker:
	docker build -t rts-game .
	docker run -it rts-game

clean:
	@$(REM) $(call FixPath, $(OBJ_PATH)*.o $(OBJ_PATH)*.gcda \
	$(OBJ_PATH)*.gcno $(CUNIT_PATH)*.o $(OBJ_PATH)tests/*.gcno \
	$(OBJ_PATH)tests/*.gcda $(OBJ_PATH)tests/*.o $(OBJ_PATH)screens/*.o \
	$(OBJ_PATH)screens/*.gcno $(OBJ_PATH)screens/*.gcda *.gcov)

.PRECIOUS: $(OBJ_PATH)%.o
.PHONY: gcov clean
