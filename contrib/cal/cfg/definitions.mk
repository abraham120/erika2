# definitions.mk - Common definitions of actors-make makefiles
# Overridden by any variable set on the command line
#
# Modified in order to integrate it in the Erika tree
# Author: Antonio Marcello Catinella
# Date:	  2011

export SHELL=/bin/sh

#
# directories
#

export ACTORS_INCLUDE=$(EEBASE)/contrib/cal/inc
export ACTORS_LIB=
export ACTORS_BIN=$(CAL_BASE)/bin
export ACTORS_MAKE=$(CAL_BASE)/share/actors-make
export ACTORS_JAR=$(CAL_BASE)/share/java
export ACTORS_XSL=$(CAL_BASE)/share/xsl

#
# ACTORS-specific tools
#

export ELABORATOR=$(ACTORS_BIN)/elaborator
export SAXON8=$(ACTORS_BIN)/saxon8
export SSAGENERATOR=$(ACTORS_BIN)/ssagenerator
export XLIM2C=$(ACTORS_BIN)/xlim2c
export XDF2PAR=$(ACTORS_BIN)/xdf2par
export MODELCOMPILER=$(ACTORS_BIN)/modelcompiler

export XDF2DEPEND_XSL=$(ACTORS_XSL)/generateDepend.xsl
export GENERATECONFIG_XSL=$(ACTORS_XSL)/generateConfig.xsl

#
# gcc and binutils
#

export target
export CC       =$(target)gcc
export AR       =$(target)ar
export LD       =$(target)ld
export STRIPTOOL=$(target)strip
export STRIP    =$(STRIPTOOL) --remove-section=.note --remove-section=.comment
