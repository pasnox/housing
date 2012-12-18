#!/bin/bash

# Update external git repositories needed to build the project
git submodule update --init --recursive

# Download oxygen theme for Windows & Mac OS X
OS=`uname -s | tr '[:upper:]' '[:lower:]'`

if [ "$OS" == "darwin" ] || [ "$OS" == *"_NT-"* ] || [ "$OS" == *"CYGWIN"* ] || [ "$OS" == *"MINGW"* ] || [ "$OS" == *"UWIN"* ]; then
    ICONS_THEME="oxygen-theme"
    ICONS_THEME_GIT="oxygen-icons-png.git"

    if [ ! -d "$ICONS_THEME" ]; then
        git clone https://github.com/pasnox/oxygen-icons-png.git "$ICONS_THEME_GIT"
        mv "$ICONS_THEME_GIT\oxygen" "$ICONS_THEME"
        rm -fr "$ICONS_THEME_GIT"
    fi
fi
