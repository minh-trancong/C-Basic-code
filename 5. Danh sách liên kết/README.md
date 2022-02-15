# Danh sách liên kết đơn

`gsl_t list = gsl_create(gtype_free_s);` Tạo một danh sách liên kết đơn với kiểu free là `gtype_free_s`

`gsl_free(list);` free list

`gsl_push_back(list, gtype_s(strdup(line)));` Thêm con trỏ kiểu xâu của strdup line.

Tại sao thêm dấu ngoặc vào 2 đầu biểu thức đúng trong if sẽ bỏ warning?![image-20220215013017492](/Users/minh/Library/Application Support/typora-user-images/image-20220215013017492.png)

1. <u>**Bài tập 5.1**</u>
    Danh sách bài hát được lưu trong [songs.txt](songs.txt)
    Tên bài hát\*#*path

  Viết chương trình đọc và **hiển thị danh sách** tên bài hát từ tệp songs.txt, khi người dùng **chọn 1 bài hát** thì hiển thị **đường dẫn** đến tệp tương ứng. Chương trình cấp phát bộ nhớ động để lưu tên và đường dẫn bài hát, hạn chế dư thừa.

