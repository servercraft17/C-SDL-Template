CC = gcc
PROJ_NAME=PROJECT_NAME
SDLPATH = libs/SDL/x86_64-w64-mingw32

CFLAGS := \

inc := -I src \
	-I libs/stb \
	-I $(SDLPATH)/include \

# OS agnostics
ifeq ($(OS),Windows_NT)
fixcmd=$(subst /,\,$1)
EXECNAME=$(PROJ_NAME).exe
CLEANCMD=del build\$(EXECNAME) build\*.o
else # Linux
fixcmd=$1
EXECNAME=$(PROJ_NAME)
CLEANCMD=rm -f build/$(EXECNAME) build/*.o
endif

# Usefull helper "functions"
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
rdwildcard=$(sort $(dir $(call rwildcard,$1,$2)))
rsubsuffix=$(sort $(filter-out $(addprefix %,$1),$(foreach s,$1,$(patsubst $(addprefix %,$s),$(addprefix %,$2),$3))))

OBJS = $(call rsubsuffix,.c,.o,$(subst src,build,$(call rwildcard,src,*.c)))
COMPILE = $(CC) -c $< -o $@ $(inc) $(CFLAGS)

build/$(EXECNAME): $(OBJS)
	$(CC) $^ -o $@ $(SDLPATH)/lib/libSDL3.dll.a

.PHONY: clean
clean:
	$(CLEANCMD)

.PHONY: run
run: build/$(EXECNAME)
	$(call fixcmd,./$<)

# ################
# # OBJECT FILES #
# ################

build/main.o : src/main.c ; $(COMPILE)
build/utils.o : src/utils.c ; $(COMPILE)