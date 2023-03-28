#!/bin/bash

function shutdown() {
  tput cnorm # reset cursor
}
trap shutdown EXIT

function cursorBack() {
  echo -en "\033[$1D"
}

function spinner() {
	local LC_CTYPE=C

	local pid=$1
	local spin='[-][\][|][/]'
	local charwidth=3

	local i=0
	tput civis
	while kill -0 $pid 2>/dev/null; do
	local i=$(((i + $charwidth) % ${#spin}))
	printf "\033[1;33m%s" "${spin:$i:$charwidth}"

	cursorBack 3
	sleep .1
	done
	tput cnorm
	wait $pid
	return $?
}

("$@") &

spinner $!