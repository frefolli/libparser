EXE=./builddir/main.exe

@all: ${EXE}

${EXE}:
	meson setup builddir
	ninja -C builddir

run: ${EXE}
	${EXE}

clean:
	ninja -C builddir clean

depclean:
	rm -rf builddir
	rm -rf subprojects/*.git
