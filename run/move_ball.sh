
xset r rate 1 25

LINES=$(tput cols)
ROWS=$(tput lines)
./build/move_ball $LINES $ROWS

xset r rate
