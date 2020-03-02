# fill disk image to fit specified size
dd if=/dev/zero of=floppya.img bs=512 count=2880

# write bootloader to disk image
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc

# compile C kernel code
bcc -ansi -c -o kernel.o kernel.c

# link kernel output file to assembly code
ld86 -o kernel -d kernel.o kasm.o

# compile C shell code
bcc -ansi -c -o Shell.o Shell.c

# link shell output file
ld86 -o Shell -d Shell.o basm.o

# copy kernel program to disk image
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=259

# copy shell program to disk image
dd if=Shell of=floppya.img bs=512 conv=notrunc seek=30

# add config file to disk image
dd if=config of=floppya.img bs=512 count=1 seek=258 conv=notrunc
