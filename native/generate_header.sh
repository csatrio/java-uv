classname=com.csatrio.libuv.UvBridge
output_file=libtcpnativejni.h

cd ../bin
rm -rf *.h
javah $classname
echo $(ls)
rm -rf ../native/$output_file
echo $(pwd)
mv *.h ../native/$output_file
cd ../native