###########################################################################
##### Config
###########################################################################
APP 		:= maze
C			:= gcc
SRCDIR		:= src
OBJDIR		:= obj
INCDIR		:= -I$(SRCDIR)/includes
CFLAGS 		:= -Wall -pedantic 
RFLAGS		:= -lopengl32 -lgdi32 -lwinmm
MKDIR		:= mkdir -p

ifeq ($(OS),Windows_NT)
	LIBSDIR =$(SRCDIR)/libs/windows
else
	UNAMEOS = $(shell uname)
	ifeq ($(UNAMEOS),Linux)
		RFLAGS = -lGL -lm -lpthread -ldl -lrt -lX11 
		LIBSDIR =$(SRCDIR)/libs/linux 	
	endif
	ifeq ($(UNAMEOS),Darwin)
		RFLAGS = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
		LIBSDIR = ./$(SRCDIR)/libs
    endif
endif

LIBS		:= $(LIBSDIR)/libraylib.a

ifdef RELEASE
	CFLAGS += -O3
else
	CFLAGS += -g
endif

CFILES 		:= $(shell find $(SRCDIR)/ -type f -iname *.c)
OBJFILES	:= $(patsubst %.c,%.o,$(patsubst $(SRCDIR)%,$(OBJDIR)%,$(CFILES)))
SUBDIR		:= $(shell find $(SRCDIR)/ -type d)
OBJSUBDIRS	:= $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SUBDIR))

.PHONY: info clean cleanall

$(APP): $(OBJSUBDIRS) $(OBJFILES)
	$(C) $(OBJFILES) -o $(APP) $(CFLAGS) -L src/libs $(LIBS) $(RFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(C) -c $^ -o $(patsubst $(SRCDIR)%,%(OBJDIR),$@) $(INCDIR) $(CFLAGS)

$(OBJSUBDIRS):
	$(MKDIR) $(OBJSUBDIRS)

info:
	$(info $(CFILES))
	$(info $(OBJFILES))
	$(info $(OBJSUBDIR))

clean:
	rm -r $(OBJDIR)

cleanall:
	rm  $(APP)
	rm -rf $(OBJDIR)
