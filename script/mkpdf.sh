#!/bin/sh

#/* This file is part of The Firekylin Operating System.
# *
# * Copyright (c) 2016, Liuxiaofeng
# * All rights reserved.
# *
# * This program is free software; you can distribute it and/or modify
# * it under the terms of The BSD License, see LICENSE.
# */

enscript -p -  README LICENSE > append.ps  2> /dev/null 

cnt=0
for file in `git ls-files | grep ^kernel  `
do
	php -r '
	echo "\t/*****************   ", $argv[1] , "   *****************/\n";
	$fp=fopen($argv[1],"r");
	$cnt=$argv[2];
	while($line=fgets($fp)){
		printf("%05d\t%s",$cnt,$line);
		$cnt++;
	}
	fclose($fp);
	' $file  $cnt | enscript -p - >> append.ps 2> /dev/null
	cnt=$(($cnt + $(wc -l $file | cut -d ' ' -f 1 )))
	cnt=$(( ($cnt + 99 )/100 *100 ))
done

ps2pdf  append.ps  firekylin-source.pdf 2>&1 > /dev/null

rm -f append.ps
