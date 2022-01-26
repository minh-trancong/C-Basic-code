# Nhập xuất dữ liệu

1.  *`fscanf`* có thể nhập dữ liệu theo nhiều định dạng
▪ *fscanf(..., “%c", ...)* và *fgetc(...)* đều cho phép nhập một ký
tự, nhưng có sự khác biệt về phong cách - kết quả đọc của *fscanf* được lưu trong biến, còn *fgetc* cung cấp thông qua giá trị được trả về.
▪ *fscanf(..., “%[^\n]", ...)*, **fscanf(..., “%N[^\n]", ...)** - (N là số nguyên dương) và *fgets(...)* đều cho phép nhập chuỗi ký tự có chứa khoảng trắng nhưng **fgets** và **fscanf(..., “%N[^\n]", ...)** an toàn hơn (vì có giới hạn số lượng ký tự giúp tránh được lỗi tràn mảng), tuy nhiên cú pháp của **fgets** có thể đơn giản nhất.
