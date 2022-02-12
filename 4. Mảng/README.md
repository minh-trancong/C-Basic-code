# Kiểu mảng

### Dùng `cgen/base/Arr.h`

`arr_decl(a, 0, int)` khai báo mảng a, có 0 phần tử, kiểu int

`arr_free(a)` giải phóng bộ nhớ mảng a

`arr_append(a, element)` thêm giá trị vào mảng, kết hợp for hoặc scanf.

`arr_size(a)` số lượng phần tử của a → chỉ số phần tử cuối là `arr_size(a)-1`

`ARR(a)[i]` truy cập vào phần tử thứ i của a

`arr_set_size(a, num)` thay đổi kích thước mảng hiện tại thành mảng `num` phần tử

