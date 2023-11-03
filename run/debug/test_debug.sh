
COLS=$(tput cols)
ROWS=$(tput lines)
gdb --tui --args ./build/test $ROWS $COLS
