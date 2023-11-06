.PHONY: test

bouncing_ball:
	clang ./examples/bouncing_ball.c ./src/Screen.c ./src/Logger.c ./src/Rect.c -g -o ./build/bouncing_balli
move_ball:
	clang ./examples/move_ball.c ./src/Screen.c ./src/Logger.c ./src/Rect.c ./src/Control.c -lncurses -g -o ./build/move_ball
snake: 
	clang ./examples/snake.c ./src/Screen.c ./src/Logger.c ./src/Rect.c ./src/Control.c ./src/Snake.c ./src/Random.c -lncurses -g -o ./build/snake
test:
	clang ./tests/test.c ./src/Screen.c ./src/Logger.c ./src/Rect.c -g -lcunit -o ./build/test

