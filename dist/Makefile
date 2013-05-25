################## SWF Config
APP_ID = $(EXT_ID).test
NAME = Kontagent
COMPANY = company
VERSION = 1.0
KONTAGENT_API_KEY = 52765fc5331c4efc82b92e31e39d0c7e
KONTAGENT_TEST_MODE = true
WIKI_GIT_URL = git@github.com:jlopez/ane-kontagent.wiki.git

SRCDIR = $(ROOT)/src/test
SRC_MAIN = $(SRCDIR)/test.mxml
APP_XML_IN = $(SRCDIR)/app.xml.in
ANES = $(ANE) ../lib/ane/dist/nativelibrary.ane
OTHER_RESOURCES =

################## ANE Config
EXT_ID = com.jesusla.kontagent
ANE_AS3DIR = ../src/as3 ../src/lib/kontagent/src
ANE_IOS_LIB_SOURCES = $(call findcfiles,../src/ios) ../src/ios/kontagent/libKontagent.a ../src/ios/kontagent/libKontagent_ODIN.a
ANE_IOS_LIB_CFLAGS = -I../lib/ane/src/ios -I ../src/ios/kontagent

NATIVE_LIBRARY_LIB = libNativeLibrary.a
NATIVE_LIBRARY_LIB_SOURCES = $(call findcfiles,../lib/ane/src/ios)
NATIVE_LIBRARY_LIB_CFLAGS = -I$(FLEX_SDK)/include

ANE_ANDROID_JAR_SOURCES = ../src/android
ANE_ANDROID_JAR_CLASSPATH = $(NATIVE_LIBRARY_JAR)

NATIVE_LIBRARY_JAR = nativeLibrary.jar
NATIVE_LIBRARY_JAR_SOURCES = ../lib/ane/src/android

include mk/ane.mk
