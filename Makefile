
# quick

QK_DIR=$(shell pwd)
QK_BIN=$(QK_DIR)/bin
QK_OBJ=$(QK_DIR)/obj
QK_INC=$(QK_DIR)/inc
QK_SRC=$(QK_DIR)/src
QK_TEST=$(QK_DIR)/test
QK_MD5=$(QK_DIR)/md5-1.3.0

QK_CC=g++
GE_OL=-O3
QK_PARAMS=$(GE_OL) -Wall -fPIC -std=c++11
GE_MACROS=
QK_MACROS=$(GE_MACROS)
QK_INCS=-I$(QK_INC)
QK_LNKS=-L$(QK_BIN) -lquick
QK_MAKE=$(QK_CC) $(QK_PARAMS) $(QK_MACROS) $(QK_INCS)

# $(1): input src file
# $(2): output obj file
define make_obj
	$(QK_MAKE) -c $(1) -o $(2)
endef

# $(1): input src file
# $(2): output prog file
define make_prog
	$(QK_MAKE) $(1) -o $(2) $(QK_LNKS)
endef

# $(1): message
define success
	@printf "\033[;1m quick:\033[1;32m $(1)\033[0m\n"
endef

# $(1): message
define warn
	@printf "\033[;1m quick:\033[1;33m $(1)\033[0m\n"
endef

# $(1): message
define message
	@printf "\033[;1m quick: $(1)\033[0m\n"
endef

# $(1): suffix of src file
define object
	$(call message,make object: {SRC}/$(1).cc --> {OBJ}/$(1).o)
	$(call make_obj,$(QK_SRC)/$(1).cc,$(QK_OBJ)/$(1).o)
endef

# $(1): subdir of src file
# $(2): suffix of src file
define program
	$(call message,make program: {DIR}/$(1)/$(2).cc --> {BIN}/$(2))
	$(call make_prog,$(QK_DIR)/$(1)/$(2).cc,$(QK_BIN)/$(2))
endef

all: clean init md5 library progs
	$(call success,all success)
	
d:
	$(call warn,for debug)
	make "GE_OL=-g" "GE_MACROS=$(GE_MACROS) -D_DEBUG_"
	
xcode:
	make "GE_MACROS=$(GE_MACROS) -D_XCODE_" d

o1:
	make "GE_OL=-O1"
	
o2:
	make "GE_OL=-O2"
	
md5:
	$(call message,make 3rd code: md5)
	cd $(QK_MD5); ./configure; make clean; make
	$(call success,make md5 code success)
	cp $(QK_MD5)/md5.o $(QK_OBJ)/
  
library:
	$(call object,types)
	$(call object,crash)
	$(call object,mymd5)
	$(call object,strs)
	$(call object,time)
	$(call object,mem)
	$(call object,kvmap)
	$(call object,file)
	$(call object,dir)
	$(call object,log)
	ar -crv $(QK_BIN)/libquick.a $(QK_OBJ)/*.o
	$(call success,make library success)
	
progs:
	$(call program,test,test)
	$(call success,make programs success)

init:
	mkdir -p $(QK_BIN)
	mkdir -p $(QK_OBJ)

clean:
	rm -rf $(QK_BIN)
	rm -rf $(QK_OBJ)
	$(call success,cleaned)

# END
