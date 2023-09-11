This is microchip studio project file.

For Low current signal, you need to write bianry and set FUSE bits to AVR Attiny13A.

*Attention!!*

This project use Attiny13A Reset pin to GPIO.
It must be written in the following order.

1. Write main firmware(8ichlc.hex) to AVR.
2. Wrtie Low FUSE bit to 0x7A.
3. Write High FUSE bit to 0xFE.(Reset pin is disable)

And it cannot be re-written without AVR high voltage programmer.