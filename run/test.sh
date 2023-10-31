#WINDOW_ID=$(xdotool getactivewindow)
#xdotool windowsize $WINDOW_ID 100% 100%

COLS=$(tput cols)
ROWS=$(tput lines)
./build/test
