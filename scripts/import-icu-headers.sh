#!/bin/sh
icupath="$1"
if test "x$icupath" = x ; then
    echo syntax: import-icu-headers /path/to/icu
    exit 1
fi

cd ../src/icu
touch .has_more_files
while test -f .has_more_files ; do
    rm -f .has_more_files
    has_more_files=0
    grep -rh '^# *include ".*"' * | sed -e 's/# *include "\(.*\)".*/\1/' | sort | uniq | while read filename ; do
        if ! test -f "include/$filename" ; then
            subpath="$icupath/source/common"
            if test -f "$subpath/$filename" ; then
                echo "$subpath/$filename"
                mkdir -p "`dirname "include/$filename"`"
                cp "$subpath/$filename" "include/$filename"
                has_more_files=1
                touch .has_more_files
            fi
            subpath="$icupath/source/i18n"
            if test -f "$subpath/$filename" ; then
                echo "$subpath/$filename"
                mkdir -p "`dirname "include/$filename"`"
                cp "$subpath/$filename" "include/$filename"
                has_more_files=1
                touch .has_more_files
            fi
        fi
    done
done
