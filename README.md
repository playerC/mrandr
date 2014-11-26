mrandr
======

设置 MAC OS X 系统屏幕分辨率的命令行工具

注意：
 这个程序只能在 MAC OS X 10.6 和 更新的系统上运行.

使用说明
--------

直接在finder 中双击打开mrandr 可执行文件，提示选择显示器,如下。

	mrandr v0.1 
	Copyright (c) 2014 playerc <playerc@msn.cn>
	!!!This program only run on mac os x 10.6 and later.
	Display List:
	    0 : 8547
	Choose a display:

中间 `Display List` 下面的内容不同的显示器显示的不同，输入开头的数字便选择了这个显示器。

选择完显示器后会提示选择显示模式，也就是显示分辨率了:

	 Mode List:
	      0 : 1280* 1024*33554439@ 60
	 *    1 : 1920* 1080* 3@ 60
	      2 : 1280* 1024* 3@ 75
	      3 : 1024*  768* 3@ 75
	      4 : 1024*  768* 3@ 70
	      5 : 1024*  768* 3@ 60
	      6 :  800*  600* 3@ 75
	      7 :  800*  600* 3@ 72
	      8 :  800*  600* 3@ 60
	      9 :  800*  600* 3@ 56
	     10 :  640*  480* 3@ 75
	     11 :  640*  480* 3@ 72
	     12 :  640*  480* 3@ 59
	     13 :  848*  480* 1@ 60
	     14 : 1280*  960* 1@ 60
	     15 : 1280*  960* 1@ 75
	     16 : 1360*  768* 1@ 60
	     17 : 1920* 1080* 1@ 60
	     18 :  640*  512* 3@ 60
	     19 :  800*  640* 3@ 60
	     20 : 1024*  820* 3@ 60
	choose a mode :

同样 `Mode List` 下得内容也是根据显示器的不同显示不同。开头带 `*` 号的是正在使用的模式。输入第一列的数字就选择了这个模式。

显示模式更改后，会一直在这个显示模式下工作，重启也是一样。