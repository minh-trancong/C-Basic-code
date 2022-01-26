# Nhập xuất tệp

**Nhập dữ liệu từ tệp văn bản:**

1. `fscanf` có thể nhập dữ liệu theo nhiều định dạng
2. `fscanf(..., “%c", ...)` và `fgetc(...)` đều cho phép nhập một ký tự, nhưng có sự khác biệt về phong cách - kết quả đọc của `fscanf` được lưu trong biến, còn `fgetc` cung cấp thông qua giá trị được trả về.
3. `fscanf(..., “%[^\n]", ...)`, `fscanf(..., “%N[^\n]", ...)` - (**N** là số nguyên dương) và `fgets(...)` đều cho phép nhập chuỗi ký tự có chứa khoảng trắng nhưng fgets và **`fscanf(..., “%N[^\n]",...`**) an toàn hơn (vì có giới hạn số lượng ký tự giúp tránh được lỗi tràn mảng), tuy nhiên cú pháp của **`fgets`** có thể đơn giản nhất.

**Xuất dữ liệu vào tệp văn bản:**

1. `fprintf(..., “%c", ...)` tương đương với `fputc(...)` 
2. `fprintf(..., “%s", ....)` tương đương với `<u>fputs(...)</u>`

<h1 style="color:RED;text-align:center;">Bài tập</h1>