INCLUDE=$(shell find include -type f)
SRC=$(shell find src -type f)
EXE=./builddir/main.exe

@all: ${EXE}

${EXE}: ${INCLUDE} ${SRC}
	meson setup builddir
	ninja -C builddir

run: ${EXE}
	${EXE}

clean:
	ninja -C builddir clean

depclean:
	rm -rf builddir
	rm -rf subprojects/*.git
