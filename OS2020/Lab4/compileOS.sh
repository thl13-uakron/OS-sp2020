# fill disk image to fit specified size
dd if=/dev/zero of=floppya.img bs=512 count=2880

# write bootloader to disk image
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc

# compile C kernel code
bcc -ansi -c -o kernel.o kernel.c

# link kernel output file to assembly code
ld86 -o kernel -d kernel.o kasm.o

# copy kernel program to disk image
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=259

# add file to disk containing config settings
dd if=config of=floppya.img bs=512 count=1 seek=258 conv=notrunc
