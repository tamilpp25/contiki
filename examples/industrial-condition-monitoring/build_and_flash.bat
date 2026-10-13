make -f Makefile.coord
make -f Makefile.node
@REM  Needs the programmer to be added to the path
JN51xxProgrammer.exe -Y -V 10 -I 38400 -P 1000000 -f .\coord.jn516x.bin -s COM4
JN51xxProgrammer.exe -Y -V 10 -I 38400 -P 1000000 -f .\node.jn516x.bin -s COM6
JN51xxProgrammer.exe -Y -V 10 -I 38400 -P 1000000 -f .\node.jn516x.bin -s COM7
