reset
SOURCE_NAME=libtcpnative.cpp
LIBRARY_NAME=libtcpnative.so
g++ -fpermissive -fPIC -shared -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" /usr/local/lib/libuv.a -o $(pwd)/$LIBRARY_NAME $SOURCE_NAME -luv -lpthread

# uncomment this for first run, then comment again, as symlink is created already
#sudo ln -sf $(pwd)/$LIBRARY_NAME /usr/local/lib/$LIBRARY_NAME
#sudo ln -sf $(pwd)/$LIBRARY_NAME /usr/local/lib/$LIBRARY_NAME
#sudo ln -sf $(pwd)/$LIBRARY_NAME /usr/lib/$LIBRARY_NAME
#sudo ln -sf $(pwd)/$LIBRARY_NAME /usr/lib/$LIBRARY_NAME
#sudo ldconfig
