# Quản lý nhiệm vụ nhóm học lập trình — Tuần 1

Ứng dụng Console bằng C, lưu tối đa 100 nhiệm vụ trong mảng struct tĩnh. Dữ liệu chỉ tồn tại trong RAM và mất khi thoát chương trình.

## Thành viên và phân công

| Thành viên | Phần phụ trách |
|---|---|
| Hà Lê Quốc An | Menu, đọc lựa chọn menu, hiển thị bảng và trạng thái bằng chữ; thiết lập repo, `.gitignore`, bổ sung README; phối hợp ghép code. |
| Tín (Kuro trong chú thích code gốc) | Thêm nhiệm vụ; các hàm nhập và kiểm tra dữ liệu; tìm mã để chống trùng; hoàn thiện xử lý dòng dài và lỗi đọc khi thêm. |
| Cả hai | Kiểm tra chéo, tự commit phần mình, hiểu code và báo cáo tiến độ cho Mentor. |

Bảng trên là phân công, không thay thế lịch sử đóng góp thực tế. Bản bổ sung menu/hiển thị có hỗ trợ soạn và kiểm tra bằng AI; thành viên cần đọc hiểu và tự kiểm tra trước khi commit.

## Chức năng tuần 1

- Menu bằng `do-while` và `switch-case`: thêm, hiển thị, thoát.
- Thêm nhiệm vụ, chặn mã trùng, thông tin rỗng, mã có khoảng trắng và các giá trị số sai phạm vi thông thường.
- Bảng có STT, mã, tên, người phụ trách, trạng thái và điểm.
- Trạng thái hiển thị bằng chữ; phân biệt chưa chấm với được 0 điểm.
- Cột tự mở rộng theo chuỗi dài, không cắt dữ liệu. Điểm hiển thị một chữ số thập phân.
- Menu từ chối chữ, dòng rỗng, chuỗi như `0abc`, số ngoài 0–2 và dòng quá dài. Kết thúc đầu vào tại menu sẽ thoát.

Chưa triển khai các chức năng tuần 2: tìm kiếm từ menu, sửa, xóa, thống kê tiến độ, lọc/sắp xếp. `timTheoMa` hiện chỉ là hàm hỗ trợ kiểm tra mã trùng.

## Quy ước dữ liệu

| Trường | Kiểu | Quy ước |
|---|---|---|
| `ma` | `char[20]` | Tối đa 19 byte nội dung, không rỗng, không khoảng trắng, không trùng. Ví dụ NV001. |
| `ten` | `char[100]` | Tối đa 99 byte nội dung, không rỗng, cho phép dấu cách. |
| `nguoiPhuTrach` | `char[100]` | Tối đa 99 byte nội dung, không rỗng, cho phép dấu cách. |
| `trangThai` | `int` | 0: chưa làm; 1: đang làm; 2: hoàn thành. |
| `daChamDiem` | `int` | 0: chưa chấm; 1: đã chấm. |
| `diem` | `float` | 0–10 khi đã chấm; nếu chưa chấm thì lưu 0 nhưng in “Chua cham”. |

Giới hạn chuỗi tính bằng byte; tiếng Việt UTF-8 có thể dùng nhiều byte cho một ký tự. Bảng dùng `strlen` để tính độ rộng nên căn cột tốt nhất với dữ liệu không dấu. Với tên dài, mở rộng cửa sổ Terminal để tránh tự xuống dòng.

## Biên dịch và chạy

Cần trình biên dịch C hỗ trợ C11, ví dụ GCC. Trong Terminal, chuyển vào thư mục chứa `main.c`.

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

Chỉ biên dịch `main.c`. File `phan-quoc-an.c.txt` là đoạn code để đối chiếu/ghép, không phải file cần biên dịch thêm.

## Các hàm chính

| Hàm | Vai trò |
|---|---|
| `hienThiMenu` | In menu và lời nhắc. |
| `nhapLuaChon` | Đọc một dòng; trả 0–2 nếu hợp lệ, -1 nếu sai; trả 0 khi đầu vào kết thúc. |
| `tenTrangThai` | Đổi số trạng thái thành chuỗi. |
| `inDuongKe` | In đường viền bảng theo chiều rộng các cột. |
| `hienThiDanhSach` | Tính chiều rộng, in bảng, điểm và số nhiệm vụ. |
| `themNhiemVu` | Nhập, kiểm tra và lưu một nhiệm vụ. |
| `timTheoMa` | Trả vị trí tìm thấy hoặc -1, dùng chống mã trùng. |
| `main` | Tạo mảng, biến đếm và điều khiển menu. |

Thư viện: `<stdio.h>` cho `printf`, `fgets`, `sscanf`, `snprintf`, `getchar`; `<string.h>` cho `strlen`, `strcmp`, `strcspn`, `strchr`, `strcpy`.

## Kiểm tra đã thực hiện

Đã chạy 6 nhóm kiểm tra trên bản ghép: menu nhập sai và dòng dài; kết thúc đầu vào tại menu; ba trạng thái và điểm 0/chưa chấm; tên dài; kiểm tra dữ liệu thông thường khi thêm; đủ 100 nhiệm vụ và chặn mảng đầy. Chi tiết tại `docs/kiem-thu.txt`.

Các kiểm tra trên không có báo lỗi AddressSanitizer/UndefinedBehaviorSanitizer. LeakSanitizer bị tắt do môi trường chạy không hỗ trợ. Không xem đây là xác nhận mọi trường hợp đều đúng.

## Việc còn cần phối hợp với Tín

- Xử lý dòng quá dài trong phần nhập của Tín: hiện `fgets` có thể để lại phần dư, làm trôi dữ liệu sang trường tiếp theo; các hàm nhập số cũng cần xử lý dòng dài.
- Kiểm tra kết quả `fgets` ở mã, tên, người phụ trách; khi EOF/lỗi đọc giữa thao tác thêm phải hủy thêm, không lưu bản ghi dở dang. Các hàm nhập số hiện trả giá trị nhỏ nhất khi EOF, cần phân biệt lỗi đọc với giá trị nhập hợp lệ.
- Cách đọc số nguyên bằng `sscanf("%d ...")` trong phần nhập cần kiểm tra thêm trường hợp số vượt giới hạn kiểu `int`; chưa được xác nhận an toàn với đầu vào cực lớn.
- Chạy lại trên máy hai thành viên, chụp ảnh Terminal thật và thêm vào README trước khi nộp. Xác nhận repo Public, lời mời thành viên/Mentor và lịch sử commit.

## Demo từ kết quả chạy thử

Ảnh dưới đây được dựng từ đầu ra thực tế của chương trình, không phải ảnh chụp màn hình máy của thành viên. Đầu ra dạng chữ nằm trong `docs/demo-output.txt`.

![Đầu ra chạy thử](docs/demo-output.png)

Nhóm cần bổ sung ảnh chụp Terminal thật khi nghiệm thu trên máy cá nhân để đáp ứng yêu cầu Screenshot của dự án.
