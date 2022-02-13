# Cách sử dụng cgen trong Xcode

Thêm vào `main.c` thư viện `#include "cgen.h"`

Thêm đường link tìm kiếm thư viện cgen trong `Header Search Paths`

![Pic1](pic/Pic1.png)

Vào `Build Phrases` thêm `all.c` của cgen

![Pic2](pic/Pic2.png)

Để dùng relative link trong `fopen("songs.txt","r");` cần phải set lại working directory

![Pic3](pic/Pic3.png)

