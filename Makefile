.PHONY: test

bouncing_ball:
	clang ./src/bouncing_ball.c ./src/Screen.c ./src/Logger.c ./src/Rect.c -g -o ./build/bouncing_ball
test:
	clang ./src/test.c ./src/Screen.c ./src/Logger.c -g -lcunit -o ./build/test

