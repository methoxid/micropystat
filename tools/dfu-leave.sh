dfu-util -v -d 0483:df11 -a 0 -s 0x08000000:leave -D ./build-NUSTAT10/firmware0.bin
./dfu-util -d 0483:df11 -a 0 -s 0x08000000:leave -U tmp.delete
