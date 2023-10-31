#WINDOW_ID=$(xdotool getactivewindow)
#xdotool windowsize $WINDOW_ID 100% 100%

LINES=$(tput cols)
ROWS=$(tput lines)
gdb --tui --args ./build/bouncing_ball $LINES $ROWS
