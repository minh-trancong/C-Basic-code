# W10 - Tìm kiếm - P2 - Song

 [Ch10-Search-P2.pdf](Ch10-Search-P2.pdf) 

```c
enum {
  SONG_NULL, //0
  SONG_NAME, //1
  SONG_SINGER, //2
  SONG_MUSICIAN, //3
  SONG_YEAR, //4
  SONG_ELEMENTS //5
};
```

[Đọc thêm về enum](https://www.geeksforgeeks.org/enumeration-enum-c/)

 [w10-songs.c](w10-songs.c) - file bài làm, đã test thành công, giải phóng bộ nhớ theo [kichban9.txt](kichban9.txt)

Ý tưởng: dùng gvec_t để nhập, sắp xếp,...