
xset r rate 1 25

LINES=$(tput cols)
ROWS=$(tput lines)
gdb --tui --args ./build/bouncing_ball $LINES $ROWS

xset r rate
