

LINES=$(tput cols)
ROWS=$(tput lines)
gdb --tui --args ./build/snake $LINES $ROWS
