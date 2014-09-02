# xinitrc for testing rigue

urxvtd -q -f -o
setxkbmap hu
xrdb -merge $HOME/.Xresources
compton -b -c -C
#xclock &
#sleep 2 && xterm &
feh --randomize --bg-fill ~/img/wallpapers &
./scripts/status.sh &

xbindkeys
exec ./rigue
