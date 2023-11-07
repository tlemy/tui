
xset r rate 1 

LINES=$(tput cols)
ROWS=$(tput lines)
./build/snake $LINES $ROWS

xset r rate
reset
