HDRS = ipc.h
OPTS = -g -Wall -c

# Define source and object files for each program
SUPPLIER_SRC = supplier.c
SUPPLIER_OBJ = supplier.o
# Add ipc.c to supplier's sources to force recompilation when it changes
# Avoid including ipc.o as a separate dependency to avoid double linking
# Also forces ipc.c to be compiled *with* supplier's source file and flags
# in case it needs the same -D or other options
SUPPLIER_ALL_SRC = $(SUPPLIER_SRC) ipc.c


SMOKER_TOBACCO_SRC = smoker_tobacco.c
SMOKER_TOBACCO_OBJ = smoker_tobacco.o
SMOKER_PAPER_SRC = smoker_paper.c
SMOKER_PAPER_OBJ = smoker_paper.o
SMOKER_GLUE_SRC = smoker_glue.c
SMOKER_GLUE_OBJ = smoker_glue.o
IPC_SRC=ipc.c
IPC_OBJ=ipc.o

TARGETS = supplier smoker_tobacco smoker_paper smoker_glue

all: $(TARGETS)
ipc.o: $(IPC_SRC) $(HDRS)
	gcc $(OPTS)  $(IPC_SRC) # Separate compilation for ipc.c

supplier: $(SUPPLIER_OBJ) $(IPC_OBJ)
	gcc  $(SUPPLIER_OBJ)  $(IPC_OBJ) -o supplier
$(SUPPLIER_OBJ): $(SUPPLIER_SRC) $(HDRS) # Changed here
	gcc $(OPTS) $(SUPPLIER_SRC)  #Compile supplier.c separately


smoker_tobacco: $(SMOKER_TOBACCO_OBJ)  $(IPC_OBJ)
	gcc $(SMOKER_TOBACCO_OBJ)  $(IPC_OBJ) -o smoker_tobacco
$(SMOKER_TOBACCO_OBJ): $(SMOKER_TOBACCO_SRC) $(HDRS)
	gcc $(OPTS) $(SMOKER_TOBACCO_SRC)

smoker_paper: $(SMOKER_PAPER_OBJ)  $(IPC_OBJ)
	gcc $(SMOKER_PAPER_OBJ)  $(IPC_OBJ) -o smoker_paper
$(SMOKER_PAPER_OBJ): $(SMOKER_PAPER_SRC) $(HDRS)
	gcc $(OPTS) $(SMOKER_PAPER_SRC)

smoker_glue: $(SMOKER_GLUE_OBJ)  $(IPC_OBJ)
	gcc $(SMOKER_GLUE_OBJ)  $(IPC_OBJ) -o smoker_glue
$(SMOKER_GLUE_OBJ): $(SMOKER_GLUE_SRC) $(HDRS)
	gcc $(OPTS) $(SMOKER_GLUE_SRC)
clean:
	rm -f $(TARGETS) *.o core

# Rule to clean IPC objects (optional, use with caution)
# You might need sudo for this if semaphores were created by another user
# or if you don't own them.
cleanipc:
	-ipcrm -s $(shell ipcs -s | grep '0x000001f4' | awk '{print $$2}')
	-ipcrm -s $(shell ipcs -s | grep '0x000001f5' | awk '{print $$2}')
	-ipcrm -s $(shell ipcs -s | grep '0x000001f6' | awk '{print $$2}')
	-ipcrm -s $(shell ipcs -s | grep '0x000001f7' | awk '{print $$2}')
	@echo "Attempted to remove semaphores with keys 500-503. Check with ipcs -s."

