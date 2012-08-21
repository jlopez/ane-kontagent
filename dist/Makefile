################## SWF Config
APP_ID = $(EXT_ID).test
NAME = Kontagent
COMPANY = company
VERSION = 1.0
KONTAGENT_API_KEY = 52765fc5331c4efc82b92e31e39d0c7e
WIKI_GIT_URL = git@github.com:jlopez/ane-kontagent.wiki.git

SRCDIR = $(ROOT)/src/test
SRC_MAIN = $(SRCDIR)/test.mxml
APP_XML_IN = $(SRCDIR)/app.xml.in
ANES = $(ANE)
OTHER_RESOURCES =

################## ANE Config
EXT_ID = com.jesusla.kontagent
ANE_AS3DIR = ../src/as3 ../src/lib/kontagent/src
ANE_IOS_LIB_SOURCES = $(call findcfiles,../src/ios) ../src/ios/kontagent/libKontagent.a ../src/ios/kontagent/libKontagent_UDID.a ../src/ios/kontagent/libKontagent_ODIN.a
ANE_IOS_LIB_CFLAGS = -I../src/ios/ane/src -I ../src/ios/kontagent
ANE_BUNDLED_LIBS = $(NATIVE_LIBRARY_LIB)

NATIVE_LIBRARY_LIB = libNativeLibrary.a
NATIVE_LIBRARY_LIB_SOURCES = $(call findcfiles,../src/ios/ane/src)
NATIVE_LIBRARY_LIB_CFLAGS = -I$(FLEX_SDK)/include

include mk/ane.mk
