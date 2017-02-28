# Linux_Project
######--Thanks Prof.Li, I have learned lots of knowledge of Linux system.Final project is about producer and consumers  problem. 
##Problem ：
###there is a plate on table.it can contain two fruits. plate must be vistited by one person at same time. father put apple to plate,mother put orange to plate.there are two daughters waiting for apple in plate, and two sons waiting for orange in plate.
##Method : 
### Design a daemon process for parents, it used to put fruits in plate,it contains 2 thread called 'mother' and 'father' 
###Design a client process called 'children',it contains two subprocesss i.e. 'son' and 'daughter'.every subprocess has two thread for indicate two sons and two danghters.
###Design communication method between process and thread,Using Semaphore of System V standard.
##Trick：
### Using gdb to debug program. add '-g' when compile program, then you can using gdb. 
##### input 'gdb' change to debug mode. Then e.g.'file parents' load the execuable file to gdb. Or input 'gdb parents'
##### 'l'or 'list' : view the source code.
##### 'b n'or 'break n': set break point in nth line. e.g. break 12
##### 'd' delete all breakpoint s. 'd n' delete No.n break point. we can use info b see all the breakpoints.
##### 'n' next or 's' step running ,'c' continue
##### 'r' run program.
##### 'p val_name' see the value of val_name.
### using gcc to compile program.
##### '-c' means generate .o file. '-o' means generate executable file.
