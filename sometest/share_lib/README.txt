编译动态库： gcc func.c -fPIC -shared -o libfunc.so 
编译main函数: gcc main.c -L. -lfunc
这个文件夹的主要目的是建立一个动态库，学习动态库的编译和使用！以及路径的配置。
编译时候用的动态库的位置和运行时的位置可以不同，比如编译时
gcc main.c -L/home/hanb/lib -lfunc 表示编译使用/home/hanb/lib下的libfunc.so文件，运行时则需要在所配置的DL_LIBRARY_PATH所配置的路径寻找库或者在/etc/ld.so.conf所配置的路径中寻找库，当然系统会默认在/lib /usr/lib 或者/usr/local/lib下去寻找动态库文件（运行时）。
