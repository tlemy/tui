

LINES=$(tput cols)
ROWS=$(tput lines)
gdb --tui --args ./build/move_ball $LINES $ROWS
