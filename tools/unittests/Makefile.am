if ENABLE_UNITTEST
TEST_SOURCES = DigraphTest.cpp \
	FileHandleTest.cpp \
	PassManagerTest.cpp \
	LivenessAnalysisTest.cpp \
  QuadrupleTest.cpp \
	StringRefTest.cpp \
	AnyTest.cpp \
	BinaryTreeTest.cpp \
	StringSwitchTest.cpp \
	StringMapTest.cpp \
	JsonValueTest.cpp \
	JsonObjectTest.cpp \
	ComputeIRTest.cpp \
	TensorSelTest.cpp \
	MemAllocTest.cpp \
	ComputeGraphTest.cpp \
	ONNXReaderTest.cpp
endif

if ENABLE_REGRESSION
MORE_TEST_SOURCES =
endif

ONNC_INCLUDES = -I${abs_top_srcdir}/tools/unittests \
	@LIBONNC_INCLUDES@ @SKYPAT_INCLUDES@ @ONNX_INCLUDES@

ANDROID_CPPFLAGS=-Waddress -Wchar-subscripts -Wcomment -Wformat -Wparentheses -Wreorder -Wreturn-type -Wsequence-point -Wstrict-aliasing -Wstrict-overflow=1 -Wswitch -Wtrigraphs -Wuninitialized -Wunknown-pragmas -Wunused-function -Wunused-label -Wunused-value -Wunused-variable -Wvolatile-register-var -Wno-return-stack-address

ONNC_CPPFLAGS = -O0 -g3 \
	-DUNITTEST=1 \
	-DTOPDIR=\"${abs_top_srcdir}\" \
	-DBUILDDIR=\"${abs_top_builddir}\"

if ENABLE_WERROR
ONNC_CPPFLAGS += -Werror
endif

AM_CPPFLAGS = ${ONNC_INCLUDES} ${ONNC_CPPFLAGS} ${ANDROID_CPPFLAGS}

bin_PROGRAMS = unittests

unittests_LDFLAGS = @LIBONNC_LDFLAGS@

unittests_LDADD = @LIBONNC_LIBS@ @SKYPAT_LIBS@

nodist_unittests_SOURCES = main.cpp ${TEST_SOURCES} ${MORE_TEST_SOURCES}

if HAVE_PTHREADS
unittests_LDADD += -lpthread
endif

