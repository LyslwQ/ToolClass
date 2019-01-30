#########################################################################
# File Name: sentinel.sh
# Author: Ys
# Created Time: 2019年01月29日 星期二 13时53分49秒
#########################################################################
#!/bin/bash


des_dir="./des"
if [ ! -d $des_dir ];then
	sudo mkdir -p -m 755 $des_dir
fi


src_dir=/home/ciker/project/Sentinel

function ergodic(){
	ls -l $src_dir  | grep .nc$ 
	r=$?
	if [ $r == 0 ]; then
		for file in ` ls  $src_dir/*.nc`
		do
			cp $file $des_dir
		done
	elif [ $r == 1 ]; then
        echo "目标目录没有指定文件！！！"
	fi
}

ergodic
