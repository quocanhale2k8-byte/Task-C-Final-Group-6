# Quản lý nhiệm vụ nhóm học lập trình

Ứng dụng Console viết bằng C, dùng struct và mảng tĩnh để quản lý tối đa 100 nhiệm vụ. Dữ liệu lưu trong RAM và mất khi thoát chương trình.

## Thành viên và phân công

| Thành viên | Phần phụ trách |
|---|---|
| Hà Lê Quốc An | Menu, hiển thị danh sách, thiết lập repo và tài liệu, phối hợp ghép code. |
| Tín | Thêm nhiệm vụ, kiểm tra dữ liệu đầu vào, tìm mã để tránh trùng. |
| Cả hai | Kiểm tra, sửa lỗi và báo cáo tiến độ. |

## Chức năng tuần 1

- Thêm nhiệm vụ: mã, tên, người phụ trách, trạng thái và điểm.
- Hiển thị danh sách dạng bảng, trạng thái bằng chữ.
- Phân biệt chưa chấm điểm và được 0 điểm.
- Kiểm tra thông tin rỗng, mã trùng, khoảng trắng trong mã, chuỗi quá dài, số không hợp lệ và mảng đầy.
- Hủy thao tác thêm nếu đầu vào kết thúc hoặc đọc lỗi trước khi đủ thông tin.
- Menu lặp bằng `do-while` và `switch-case`, chọn 0 để thoát.

Các chức năng tìm kiếm từ menu, cập nhật, xóa, thống kê tiến độ và lọc/sắp xếp sẽ triển khai ở tuần 2.

## Dữ liệu

| Trường | Kiểu | Quy ước |
|---|---|---|
| `ma` | `char[20]` | Tối đa 19 byte, không rỗng, không khoảng trắng, không trùng. |
| `ten` | `char[100]` | Tối đa 99 byte, không rỗng, cho phép dấu cách. |
| `nguoiPhuTrach` | `char[100]` | Tối đa 99 byte, không rỗng, cho phép dấu cách. |
| `trangThai` | `int` | 0: chưa làm; 1: đang làm; 2: hoàn thành. |
| `daChamDiem` | `int` | 0: chưa chấm; 1: đã chấm. |
| `diem` | `float` | 0–10; chỉ hiển thị điểm khi đã chấm. |

Bảng tự nới cột theo độ dài chuỗi. Dữ liệu không dấu căn cột chính xác hơn vì `strlen` đếm byte, không đếm độ rộng ký tự trên màn hình. Với tên dài, cần mở rộng Terminal. Điểm hiển thị một chữ số thập phân; dùng dấu chấm khi nhập điểm thập phân.

## Biên dịch và chạy

Cần GCC hoặc trình biên dịch hỗ trợ C11. Mở Terminal tại thư mục chứa `main.c`.

### Windows — PowerShell

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o nhiemvu.exe
.\nhiemvu.exe
```

### Linux / macOS có GCC

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o nhiemvu
./nhiemvu
```

## Cách dùng

1. Chọn 1 để thêm nhiệm vụ và nhập thông tin theo lời nhắc.
2. Chọn 2 để xem danh sách.
3. Chọn 0 để thoát.

Thông tin sai sẽ được yêu cầu nhập lại. Nếu kết thúc đầu vào khi đang thêm, nhiệm vụ chưa hoàn chỉnh sẽ không được lưu.

## Kiểm thử

Đã chạy 11 nhóm kiểm tra gồm dữ liệu hợp lệ, menu nhập sai, mã trùng, thông tin rỗng, giới hạn chuỗi, dòng quá dài, số vượt phạm vi, điểm không hữu hạn, kết thúc đầu vào và mảng đầy. Kết quả chi tiết trong `docs/kiem-thu.txt`.

## Demo

![Đầu ra chạy thử](docs/demo-output.png)

Ảnh minh họa được dựng từ đầu ra thực tế trong `docs/demo-output.txt`. Nhóm bổ sung ảnh chụp Terminal trên máy cá nhân trước khi nộp theo yêu cầu Screenshot.
