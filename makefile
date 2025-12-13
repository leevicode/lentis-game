flags = -Iinclude -Llib -lm -lraylib -Wl,-rpath=lib -O0 -ggdb
needed = src/main.c src/input.c
main:
	gcc $(needed) -o build/main $(flags)

clean:
	 rm -rf build/*