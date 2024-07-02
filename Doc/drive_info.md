# Drive pin assign info

All odd pins are assigned to GND.

| Pin Number | FD1165A          | YD-180 1601               |  YD-180 1600               | 
| ---------- | ---------------- | ------------------------- | -------------------------  | 
| 2          | LOW CURRENT(i)      | LOW CURRENT/SWITCH FILTER | Ready 3(o)|
| 4          | UNSAFE RESET(i)     | Alternate I/O             | Ready 2(o)|
| 6          | FILE UNSAFE(o)      | Alternate I/O             | Ready 1(o)|
| 8          | -                | Alternate I/O             |  SWITCH FILTER(i)|
| 10         | TWO SIDED(o)        | TWO SIDED                 | DRIVE SELECT 3(i)|
| 12         | DISK CHANGE(o)      | DISK CHANGE(optional)     | DRIVE SELECT 2(i)|
| 14         | SIDE SELECT(i)      | SIDE SELECT               | DRIVE SELECT 1(i)|
| 16         | IN USE(i)           | IN USE(optional)          | DRIVE SELECT 0(i)|
| 18         | HEAD LOAD(i)        | HEAD LOAD(optional)       | HEAD LOAD(i)|
| 20         | INDEX(o)            | INDEX                     | DIRECTION(i)|
| 22         | READY(o)            | READY                     | STEP(i)|
| 24         | VFO SYNC(for VFO)   | Alternate I/O             | LOW CURRENT(i)|
| 26         | DRIVE SELECT 1(i)   | DRIVE SELECT 1            | UNSAFE RESET(i)|
| 28         | DRIVE SELECT 2(i)   | DRIVE SELECT 2            | TRACK 00(o)|
| 30         | DRIVE SELECT 3(i)   | DRIVE SELECT 3            | WRITE PROTECT(o)|
| 32         | DRIVE SELECT 4(i)   | DRIVE SELECT 4            | FILE UNSAFE(o)|
| 34         | DIRECTION SELECT(i) | DIRECTION                 | WRITE GATE(i)|
| 36         | STEP(i)             | STEP                      |DRIVE SENCE(o)|
| 38         | WRITE DATA(i)       | WRITE DATA                |  WRITE DATA(i)|
| 40         | WRITE GATE(i)       | WRITE GATE                | INDEX(o)|
| 42         | TRACK 00 (o)        | TRACK 00                  | DISK2 SENSE(o)|
| 44         | WRITE PROTECT(o)    | WRITE PROTECT             | READY 0(o)|
| 46         | READ DATA  (o)      | READ DATA                 |READ DATA(o)|
| 48         | MFM (for VFO)      | -                         |  IN USE(i)|
| 50         | WINDOWS (for VFO)  | -                         |  HEAD SELECT(i)|

ドライブのピンアサインをまとめました。
奇数ピンはいずれのドライブもすべてGNDです。
カッコ内のiもしくはoはドライブ側からみた場合の信号入力、出力を意味しています。