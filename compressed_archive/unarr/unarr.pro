INCLUDEPATH += $$PWD/unarr-master/
DEPENDPATH += $$PWD/unarr-master/

unix:QMAKE_CFLAGS_RELEASE -= "-O2"
unix:QMAKE_CFLAGS_RELEASE += "-O3"
unix:QMAKE_CFLAGS_RELEASE += "-DNDEBUG"
unix:QMAKE_CFLAGS += "-D_FILE_OFFSET_BITS=64"

win32:QMAKE_CFLAGS_RELEASE += "/DNDEBUG"

HEADERS+=$$PWD/unarr-master/common/allocator.h\
		 $$PWD/unarr-master/common/unarr-imp.h\
		 $$PWD/unarr-master/lzmasdk/7zTypes.h\
		 $$PWD/unarr-master/lzmasdk/CpuArch.h\
		 $$PWD/unarr-master/lzmasdk/Ppmd7.h\
		 $$PWD/unarr-master/lzmasdk/Ppmd.h\
		 $$PWD/unarr-master/lzmasdk/LzmaDec.h\
		 $$PWD/unarr-master/lzmasdk/Ppmd8.h\
		 $$PWD/unarr-master/tar/tar.h\
		 $$PWD/unarr-master/_7z/_7z.h\
		 $$PWD/unarr-master/unarr.h

SOURCES+=$$PWD/unarr-master/common/conv.c\
		$$PWD/unarr-master/common/custalloc.c\
		$$PWD/unarr-master/common/unarr.c\
		$$PWD/unarr-master/common/crc32.c\
		$$PWD/unarr-master/common/stream.c\
		$$PWD/unarr-master/lzmasdk/CpuArch.c\
		$$PWD/unarr-master/lzmasdk/Ppmd7.c\
		$$PWD/unarr-master/lzmasdk/Ppmd8.c\
		$$PWD/unarr-master/lzmasdk/LzmaDec.c\
		$$PWD/unarr-master/lzmasdk/Ppmd7Dec.c\
		$$PWD/unarr-master/lzmasdk/Ppmd8Dec.c\
		$$PWD/unarr-master/zip/inflate.c\
		$$PWD/unarr-master/zip/parse-zip.c\
		$$PWD/unarr-master/zip/uncompress-zip.c\
		$$PWD/unarr-master/zip/zip.c\
		$$PWD/unarr-master/rar/filter-rar.c\
		$$PWD/unarr-master/rar/parse-rar.c\
		$$PWD/unarr-master/rar/rarvm.c\
		$$PWD/unarr-master/rar/huffman-rar.c\
		$$PWD/unarr-master/rar/rar.c\
		$$PWD/unarr-master/rar/uncompress-rar.c\
		$$PWD/unarr-master/tar/parse-tar.c\
		$$PWD/unarr-master/tar/tar.c\
		$$PWD/unarr-master/_7z/_7z.c