#!/bin/bash
function getdir(){
    for element in `ls $1`
    do  
        dir_or_file=$1"/"$element
        if [ -d $dir_or_file ]
        then
	    chmod 755 $dir_or_file
            getdir $dir_or_file
        else
	    chmod 664 $dir_or_file
            echo $dir_or_file
        fi  
    done
}

root_dir=$1
getdir $root_dir
