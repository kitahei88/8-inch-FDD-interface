# AVR source and binary

This is microchip studio project file.
For Low current signal, you need to write bianry and set FUSE bits to AVR Attiny13A.

*Attention!!*

This project use Attiny13A Reset pin to GPIO.
It must be written in the following order.

1. Write main firmware(8ichlc.hex) to AVR.
2. Wrtie Low FUSE bit to 0x7A.
3. Write High FUSE bit to 0xFE.(Reset pin is disable)

And it cannot be re-written without AVR high voltage programmer.

AVRのソースとバイナリです。
Attiny13Aを使っています。（秋月などで購入）
ピンが少なく、リセットピンをI/Oとして使っていますので、書き込み方法に注意してください。

1. ファームウェア(8ichlc.hex) をAVRに書き込む
2. Low FUSE を 0x7Aで書き込む
3. High FUSE を0xFEで書き込む.(リセットが出来なくなり、ISPで書き込めなくなります。)

消去や書き込みをする場合は　高電圧印加によるリセットが必要になります。