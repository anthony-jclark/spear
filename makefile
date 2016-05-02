
SHELL := /bin/bash
RM    := rm -rf
MKDIR := mkdir -p

# <Debug|RelWithDebInfo|Release|MinSizeRel>
CMAKE       := cmake
CMAKE_FILE  := /Users/msu/usr/emsdk_portable/emscripten/incoming/cmake/Modules/Platform/Emscripten.cmake
CMAKE       += -DCMAKE_TOOLCHAIN_FILE=$(CMAKE_FILE)
CMAKE_BUILD := Debug
CMAKE       += -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD)
CMAKE_TARG  := "Unix Makefiles"
CMAKE       += -G $(CMAKE_TARG)

all: ./build/Makefile
	@ $(MAKE) -C build

./build/Makefile:
	@ ($(MKDIR) build > /dev/null)
	@ (cd build >/dev/null 2>&1 && $(CMAKE) ..)

distclean:
	@- (cd build >/dev/null 2>&1 && $(CMAKE) .. >/dev/null 2>&1)
	@- $(MAKE) --silent -C build clean || true
	@- $(RM) ./build/Makefile
	@- $(RM) ./build/src
	@- $(RM) ./build/test
	@- $(RM) ./build/CMake*
	@- $(RM) ./build/cmake.*
	@- $(RM) ./build/*.cmake
	@- $(RM) ./build/*.txt
	@- $(RM) ./docs/*.html
	@- $(RM) ./docs/*.css
	@- $(RM) ./docs/*.png
	@- $(RM) ./docs/*.jpg
	@- $(RM) ./docs/*.gif
	@- $(RM) ./docs/*.tiff
	@- $(RM) ./docs/*.php
	@- $(RM) ./docs/search
	@- $(RM) ./docs/installdox


ifeq ($(findstring distclean,$(MAKECMDGOALS)),)

$(MAKECMDGOALS): ./build/Makefile
	@ $(MAKE) -C build $(MAKECMDGOALS)

endif

