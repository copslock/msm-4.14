#
# Copyright 2015-2016, Silicon Labs
#
# $Id: Makefile 6196 2016-12-15 00:40:37Z nizajerk $
#
# User will need to set ARCH, CROSS_COMPILE, KDIR, & PROSLIC_API_DIR (ABS PATH)
# In addition, PROSLIC_CHIPSET & PROSLIC_CONVERTER needs to be set for each chipset used.
#
# Example: 
#   export ARCH=arm
#   export CROSS_COMPILE=armv7-linux-
#   export PROSLIC_API_DIR=/home/silabs_usr/silabs_prj/proslic_api
#   export KDIR=/usr/src/linux 
#
# Tested with ProSLIC API 8.2.0
#

#
# Since we can't really use vpath to define paths to search code,
# prefix the _SRC listing to include the actual path of the code.
# This assumes symbolic links are created to src, patch_files, config_src.
#
# The alternative is to copy EVERYTHING into 1 directory, which
# would make it later to compare the Silicon Labs release code to
# what is being used on the current platform.
#

SRC := 	proslic_linux.c proslic_chardev.c\
				$(addprefix src/, $(PROSLIC_CHIPSET_SRC)) \
				$(addprefix src/, $(PROSLIC_SRC_CORE)) \
				$(addprefix patch_files/, $(PROSLIC_PATCH_SRC)) \
				$(addprefix custom/, $(PROSLIC_CFG_SRC))

PROSLIC_API_CUSTOM := $(PROSLIC_API_DIR)/custom

PROSLIC_INCDIRS := -I$(PROSLIC_API_DIR)/inc -I$(PROSLIC_API_CUSTOM) \
								  -I$(PROSLIC_API_DIR)/proslic_sys \

EXTRA_CFLAGS := $(PROSLIC_CFLAGS) $(PROSLIC_INCDIRS) -DPROSLIC_LINUX_KERNEL=1 
obj-$(CONFIG_PROSLIC) += proslic_core.o
proslic_core-objs:= $(SRC:.c=.o)

