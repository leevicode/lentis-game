flags = -Iinclude -Llib -lm -lraylib -Wl,-rpath=lib -O0 -ggdb
needed = src/main.c src/input.c src/player.c src/ball.c src/game.c src/renderBillboard.c
main:
	gcc $(needed) -o build/main $(flags)

clean:
	 rm -rf build/*