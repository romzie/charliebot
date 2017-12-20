
# Application name
TARGET=Controller

# Where to find user C code
USR_PATH=.

# -----------
# user C code
# -----------
USR_CFILES=\
	Controller.c \
	Controller_glue.c \
	Controller_ext.c \

# generic makefile ...
include $(MDL2LUS2OSEK)/generic.mak


# -----------
# mdl -> lustre -> c rules
# -----------

# c code is obtained by compiling Lustre code ...
# (note the "-ctx-static": it influences the way GLUE must be written)
Controller.c: Controller.lus
	lus2c Controller.lus Controller -ctx-static


# Lustre code is obtained from mdl
Controller.lus: robot.mdl
	mdl2lus -system Controller robot.mdl

clear: clean
	rm -f Controller.xml Controller.c Controller.h Controller.lus Controller.ec Controller.mws
