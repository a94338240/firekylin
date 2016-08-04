#!/bin/sh
#/*  This file is part of The Firekylin Operating System.
# *
# *  Copyright 2016 Liuxiaofeng
# *
# *  Licensed under the Apache License, Version 2.0 (the "License");
# *  you may not use this file except in compliance with the License.
# *  You may obtain a copy of the License at
# *
# *      http://www.apache.org/licenses/LICENSE-2.0
# *
# *  Unless required by applicable law or agreed to in writing, software
# *  distributed under the License is distributed on an "AS IS" BASIS,
# *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# *  See the License for the specific language governing permissions and
# *  limitations under the License.
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
