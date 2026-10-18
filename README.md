# Quản lý nhiệm vụ nhóm học lập trình — Tuần 1

Ứng dụng Console bằng C, lưu tối đa 100 nhiệm vụ trong mảng struct tĩnh. Dữ liệu chỉ tồn tại trong RAM và mất khi thoát chương trình.

## Thành viên và phân công

| Thành viên | Phần phụ trách |
|---|---|
| Hà Lê Quốc An | Menu, đọc lựa chọn menu, hiển thị bảng và trạng thái bằng chữ; thiết lập repo, `.gitignore`, bổ sung README; phối hợp ghép code. |
| Tín  | Thêm nhiệm vụ; các hàm nhập và kiểm tra dữ liệu; tìm mã để chống trùng; hoàn thiện xử lý dòng dài và lỗi đọc khi thêm. |
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
