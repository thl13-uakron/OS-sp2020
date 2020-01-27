# fill disk image
dd if=/dev/zero of=floppya.img bs=512 count=2880

# write bootloader to disk image
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc
