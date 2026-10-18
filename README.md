# Quan ly nhiem vu (C) — Tuan 1

Bai tap nhom ap dung: `struct`, `string.h` (`strcmp`, `strcspn`, `fgets`),
tach nhieu ham (`themNhiemVu`, `hienThiDanhSach`, `nhapInt`, ...),
do-while + switch-case lam menu.

Quy uoc chung (da thong nhat):
- Toi da 100 nhiem vu (`danhSach`, `soNhiemVu`)
- Ma: vd NV001, khong rong, khong khoang trang, khong trung
- Ten / nguoi phu trach: khong rong, cho phep dau cach
- Trang thai: 0 (chua lam), 1 (dang lam), 2 (hoan thanh)
- Diem 0–10; `daChamDiem` 0/1 de phan biet "chua cham" voi "duoc 0 diem"
- Ten bien/ham dung camelCase

## Cach bien dich

```bash
gcc main.c -o nhiemvu
```

## Cach chay

```bash
./nhiemvu        # Linux / macOS
nhiemvu.exe      # Windows
```

## Demo

```
Chon: 1
Nhap ma (vd NV001): NV01
Nhap ten nhiem vu: Hoc C
Nhap nguoi phu trach: Kuro
Nhap trang thai (0: chua lam, 1: dang lam, 2: hoan thanh): 1
Da cham diem chua? (0: chua, 1: roi): 1
Nhap diem (0 - 10): 8.5
Da them nhiem vu NV01

Chon: 1
Nhap ma (vd NV001): NV01
Ma da ton tai! Nhap lai.
Nhap ma (vd NV001): NV02
...

Chon: 2
MA       | TEN        | NGUOI PHU TRACH | TRANG THAI | DIEM
NV01     | Hoc C      | Kuro            | 1          | 8.5
NV02     | Hoc struct | An              | 0          | chua cham
```

Cac truong hop bi chan va bat nhap lai: ma trung, ma co khoang trang,
ten/nguoi rong, trang thai ngoai 0–2, diem ngoai 0–10, mang day.
Nhap chu thay so o menu khong lam ket chuong trinh.
