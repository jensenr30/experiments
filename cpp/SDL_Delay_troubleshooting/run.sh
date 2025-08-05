#!/usr/bin/bash

make

s='sleep 0.5'

i3-msg "focus parent; focus parent; layout splith"
$s

# open a rectangular grid of i3 windows
for row in {1..5}; do
    for col in {1..5}; do
        i3-msg "layout splitv"
        $s
        i3-msg "exec alacritty --hold --working-directory $(pwd) -e ./main"
        $s
    done
    i3-msg "focus parent; focus parent; layout splith"
    $s
done
