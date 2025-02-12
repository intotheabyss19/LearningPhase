#! usr/bin/bash

read -p "Enter the path: " path
mkdir -v -p $path
echo "Created path at $path"

read -p "Enter the number of files to be created: " n

for i in $n
do
	read -p "Enter the "$i"th file name: " f_name
	touch $path/$f_name
done

echo ""
echo "Succesful"
