# Nhập xuất tệp

**Nhập dữ liệu từ tệp văn bản:**

1. `fscanf` có thể nhập dữ liệu theo nhiều định dạng
2. `fscanf(..., “%c", ...)` và `fgetc(...)` đều cho phép nhập một ký tự, nhưng có sự khác biệt về phong cách - kết quả đọc của `fscanf` được lưu trong biến, còn `fgetc` cung cấp thông qua giá trị được trả về.
   - `fscanf` → trả về số giá trị nhận được (như scanf).
   - `fgetc` → trả về `EOF` hoặc là giá trị tiếp theo ngay sau con trỏ.
3. `fscanf(..., “%[^\n]", ...)`, `fscanf(..., “%N[^\n]", ...)` - (**N** là số nguyên dương) và `fgets(...)` đều cho phép nhập chuỗi ký tự có chứa khoảng trắng nhưng fgets và **`fscanf(..., “%N[^\n]",...`**) an toàn hơn (vì có giới hạn số lượng ký tự giúp tránh được lỗi tràn mảng), tuy nhiên cú pháp của **`fgets`** có thể đơn giản nhất.
   - kí hiệu `[^ ]` cho phép các kí tự có trong ngoặc [Đọc thêm n1256 (C99) p.360]

**Xuất dữ liệu vào tệp văn bản:**

1. `fprintf(..., “%c", ...)` tương đương với `fputc(...)` 

2. `fprintf(..., “%s", ....)` tương đương với `fputs(...)`

   [alrie](file1.c)

   [hello](file:///Users/minh/GithubMinh/C-Basic-code/1. Nhập dữ liệu/file1.c)

   [link]([chamburr/glance: 🔎 All-in-one Quick Look plugin (github.com)](https://github.com/chamburr/glance#installation))

   

<h1 style="color:green;text-align:center;">Bài tập</h1>

| Tên bài tập                                       | Algorithm | Source Code        | Sub-Files | Execute |      |
| ------------------------------------------------- | --------- | ------------------ | --------- | ------- | ---- |
| [Tạo danh sách sản phẩm](#Tạo-danh-sách-sản-phẩm) | fscanf    | [product](file1.c) |           |         |      |
|                                                   |           |                    |           |         |      |
|                                                   |           |                    |           |         |      |
|                                                   |           |                    |           |         |      |

### ![Screen Shot 2022-01-27 at 18.47.49](1.png)Tạo danh sách sản phẩm

Tạo một tệp văn bản có tên **product.txt**, mỗi dòng trong đó chứa thông tin về một sản phẩm: ID (kiểu int), Product Name (xâu ký tự không chứa ký tự trắng), Price (kiểu double). Các trường dữ liệu trên được phân tách với nhau bởi một dấu cách.

- Ví dụ **product.txt**

```ABAP
 1 Samsung_Television_4K 20000000
 2 Apple_MacBook_2020 18560000
```

- Viết chương trình đọc tệp **product.txt** vào một mảng cấu trúc và sau đó in danh sách sản phẩm ra màn hình theo định dạng:

```ABAP
No Product Name          Price
1  Samsung_Television_4K 20000000 
2  Apple_MacBook_2020    18560000
```

> *Gợi ý:* `fscanf(inp, “%d%s%lf", ...) != 3` 