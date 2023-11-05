
xset r rate 1 1000

LINES=$(tput cols)
ROWS=$(tput lines)
./build/snake $LINES $ROWS

xset r rate
reset
