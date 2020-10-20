:x
C:\Users\slava\AppData\Local\nasm\nasm bootloader\bootloader.asm -f bin -o .\boot.bin 

.\utilities\VC152\CL.EXE /I .\lib /AT /G2 /Gs /Gx /c /Zl kernel\kernel.c lib\*.c
.\utilities\VC152\ML.EXE /AT /c kernel\StartPoint.asm 



move /Y *.obj bin\
move /Y *.bin bin\
cd bin
..\utilities\VC152\LINK.EXE /T /NOD StartPoint.obj kernel.obj stdio.obj string.obj 
move /Y StartPoint.com Boot\

cd ../




rm .\out.iso
fsutil file createnew .\out.iso 4096




.\utilities\dd.exe if=.\bin\boot.bin of=.\out.iso
.\utilities\dd.exe if=bin\Boot\StartPoint.com of=.\out.iso seek=1

"C:\Program Files\qemu\qemu-system-i386.exe" .\out.iso

pause
cls
goto x
