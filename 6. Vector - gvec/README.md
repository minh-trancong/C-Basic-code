# Cách dùng gvec

`gcc file.c all.c -I cgen`

`gvec_t` kiểu con trỏ **gvec**

`gvec_create(10, NULL)` Tạo một mảng gvec có 10 phần tử, kiểu free theo gtype

`gvec_append(v, gtype_s(...));` Thêm phần tử dạng gtype vào trong gvec

`gvec_tranverse(cur, v)` cur kiểu gtype, v là gvec

`gvec_qsort(v, gtype_qsort_l)` → kiểu qsort gtype

`gvec_free(v)` → free gvec

`gvec_elem(v,i)` → truy cập phần tử thứ i của gvec

`gvec_elem_idx(v, elem)` → chỉ số phần tử elem trong gvec

`gvec_remove(v, idx)` → bỏ phần tử gvec mang chỉ số idx

`gvec_set_capacity(v, cap)` → thiết lập capacity gvec

`gvec_size(v)` số lượng phần tử của v → chỉ số phần tử cuối là `gvec_size(v)-1`
