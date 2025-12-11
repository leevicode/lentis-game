flags = -Iinclude -Llib -lm -lraylib -Wl,-rpath=lib -O0 -ggdb

main:
	gcc src/main.c -o build/main $(flags)



clean:
	 rm -rf build/*