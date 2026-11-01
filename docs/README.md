# Quản lý nhiệm vụ nhóm học lập trình

Dự án cuối khóa của nhóm 6, viết bằng ngôn ngữ C và chạy trên Console. Chương trình dùng `struct` và mảng một chiều để quản lý tối đa 100 nhiệm vụ.

## Thành viên và phân công

| Thành viên | MSSV | Phần phụ trách |
|---|---|---|
| Hà Lê Quốc An | 26708711 | Menu, hiển thị danh sách, tổng hợp tài liệu và phối hợp ghép code. |
| Tín | 26667471 | Thêm nhiệm vụ, kiểm tra dữ liệu nhập và tìm mã tránh trùng. |

Hai thành viên cùng kiểm tra chương trình và chuẩn bị báo cáo.

## Chức năng

1. Thêm nhiệm vụ.
2. Hiển thị danh sách dạng bảng.
3. Cập nhật tên, người phụ trách, điểm và trạng thái theo mã.
4. Xóa nhiệm vụ theo mã, có xác nhận trước khi xóa.
5. Tìm kiếm nhiệm vụ theo mã.
6. Thống kê số nhiệm vụ theo trạng thái và tính điểm trung bình.
7. Lọc nhiệm vụ theo trạng thái.

Chọn `0` để thoát chương trình.

Mỗi nhiệm vụ gồm mã, tên, người phụ trách, trạng thái và thông tin chấm điểm. Trạng thái gồm chưa làm, đang làm và hoàn thành. Điểm nằm trong khoảng 0–10; nhiệm vụ chưa chấm không được tính vào điểm trung bình.

Chương trình kiểm tra mã trùng, thông tin rỗng, chuỗi quá dài, số nhập sai và giới hạn mảng.

## Các tệp trong dự án

| Tệp | Nội dung |
|---|---|
| `main_qa.c` | Mã nguồn chính. |
| `build_and_run_windows.bat` | Biên dịch và chạy chương trình trên Windows. |
| `demo_windows.bat` | Biên dịch và chạy với dữ liệu demo có sẵn. |
| `docs/demo-input.txt` | Dữ liệu nhập cho demo. |
| `docs/demo-output.txt` | Bản ghi kết quả chạy demo. |
| `.gitignore` | Bỏ qua các tệp không cần đưa lên GitHub. |

## Biên dịch và chạy

### Windows

Cần cài GCC và thêm thư mục chứa GCC vào `PATH`. Mở PowerShell tại thư mục dự án rồi chạy:

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic main_qa.c -o nhiemvu.exe
.\nhiemvu.exe
```

Hoặc mở `build_and_run_windows.bat` để biên dịch và chạy.

Nếu dùng Dev-C++, mở `main_qa.c`, chọn biên dịch theo ngôn ngữ C và chuẩn C11 hoặc C99, sau đó Compile & Run.

### Linux

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic main_qa.c -o nhiemvu
./nhiemvu
```

## Demo

Trên Windows, mở `demo_windows.bat` để chạy chương trình với dữ liệu trong [demo-input.txt](docs/demo-input.txt).

Có thể xem bản ghi kết quả tại [demo-output.txt](docs/demo-output.txt).

## Lưu ý

- Dữ liệu được lưu trong RAM và mất khi thoát chương trình.
- Mã nhiệm vụ không được trùng hoặc chứa khoảng trắng; tìm mã có phân biệt chữ hoa và chữ thường.
- Khi nhập điểm thập phân, dùng dấu chấm, ví dụ `8.5`.
- Dùng terminal hỗ trợ UTF-8 nếu nhập tiếng Việt có dấu; mở rộng cửa sổ khi tên nhiệm vụ dài.
