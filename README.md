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
##### 'l' : view the source code.
##### 'break n': set break point in nth line. e.g. break 12
##### 'n' step running 
##### 'r' run program.
