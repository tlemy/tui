.PHONY: test

bouncing_ball:
	clang ./src/bouncing_ball.c ./src/Screen.c ./src/Logger.c ./src/Rect.c -g -o ./build/bouncing_balli
move_ball:
	clang ./src/move_ball.c ./src/Screen.c ./src/Logger.c ./src/Rect.c ./src/Control.c -lncurses -g -o ./build/move_ball
test:
	clang ./src/test.c ./src/Screen.c ./src/Logger.c ./src/Rect.c -g -lcunit -o ./build/test

