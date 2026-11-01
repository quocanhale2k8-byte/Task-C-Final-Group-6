#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

#define MAX_NV 100

struct NhiemVu {
    char ma[20];
    char ten[100];
    char nguoiPhuTrach[100];
    int trangThai;
    int daChamDiem;
    float diem;
};

int docDong(char chuoi[], int kichThuoc) {
    char *xuongDong = NULL;
    int kyTu = 0;
    int doDai = 0;

    chuoi[0] = '\0';
    fflush(stdout);
    if (fgets(chuoi, kichThuoc, stdin) == NULL) {
        return 0;
    }

    xuongDong = strchr(chuoi, '\n');
    if (xuongDong != NULL) {
        *xuongDong = '\0';
    } else {
        kyTu = getchar();
        if (kyTu != '\n' && kyTu != EOF) {
            while (kyTu != '\n' && kyTu != EOF) {
                kyTu = getchar();
            }
            chuoi[0] = '\0';
            return -1;
        }
        if (ferror(stdin)) {
            return 0;
        }
    }

    doDai = (int)strlen(chuoi);
    if (doDai > 0 && chuoi[doDai - 1] == '\r') {
        chuoi[doDai - 1] = '\0';
    }
    return 1;
}

int laRong(const char chuoi[]) {
    int i = 0;

    for (i = 0; chuoi[i] != '\0'; i++) {
        if (!isspace((unsigned char)chuoi[i])) {
            return 0;
        }
    }
    return 1;
}

int coKhoangTrang(const char chuoi[]) {
    int i = 0;

    for (i = 0; chuoi[i] != '\0'; i++) {
        if (isspace((unsigned char)chuoi[i])) {
            return 1;
        }
    }
    return 0;
}

int coKyTuDieuKhien(const char chuoi[]) {
    int i = 0;

    for (i = 0; chuoi[i] != '\0'; i++) {
        if (iscntrl((unsigned char)chuoi[i])) {
            return 1;
        }
    }
    return 0;
}

int nhapChuoi(const char *loiNhac, char chuoi[], int kichThuoc) {
    int ketQua = 0;

    while (1) {
        printf("%s", loiNhac);
        ketQua = docDong(chuoi, kichThuoc);
        if (ketQua == 0) {
            return 0;
        }
        if (ketQua == -1) {
            printf("Chi nhap toi da %d byte. Nhap lai!\n", kichThuoc - 1);
        } else if (laRong(chuoi)) {
            printf("Thong tin khong duoc de trong!\n");
        } else if (coKyTuDieuKhien(chuoi)) {
            printf("Khong nhap tab hoac ky tu dieu khien!\n");
        } else {
            return 1;
        }
    }
}

int nhapInt(const char *loiNhac, int min, int max, int *ketQua) {
    char dong[100] = "";
    char *phanDu = NULL;
    long giaTri = 0;
    int trangThaiDoc = 0;

    while (1) {
        printf("%s", loiNhac);
        trangThaiDoc = docDong(dong, sizeof(dong));
        if (trangThaiDoc == 0) {
            return 0;
        }
        if (trangThaiDoc == 1) {
            errno = 0;
            giaTri = strtol(dong, &phanDu, 10);
            if (phanDu != dong && errno == 0) {
                while (isspace((unsigned char)*phanDu)) {
                    phanDu++;
                }
                if (*phanDu == '\0' && giaTri >= min && giaTri <= max) {
                    *ketQua = (int)giaTri;
                    return 1;
                }
            }
        }
        printf("Nhap so nguyen tu %d den %d!\n", min, max);
    }
}

int nhapFloat(const char *loiNhac, float min, float max, float *ketQua) {
    char dong[100] = "";
    char *phanDu = NULL;
    float giaTri = 0.0f;
    int trangThaiDoc = 0;

    while (1) {
        printf("%s", loiNhac);
        trangThaiDoc = docDong(dong, sizeof(dong));
        if (trangThaiDoc == 0) {
            return 0;
        }
        if (trangThaiDoc == 1) {
            errno = 0;
            giaTri = strtof(dong, &phanDu);
            if (phanDu != dong && errno == 0 && isfinite(giaTri)) {
                while (isspace((unsigned char)*phanDu)) {
                    phanDu++;
                }
                if (*phanDu == '\0' && giaTri >= min && giaTri <= max) {
                    *ketQua = giaTri;
                    return 1;
                }
            }
        }
        printf("Nhap so tu %.0f den %.0f!\n", min, max);
    }
}

int timTheoMa(const struct NhiemVu danhSach[], int soNhiemVu,
             const char ma[]) {
    int i = 0;

    for (i = 0; i < soNhiemVu; i++) {
        if (strcmp(danhSach[i].ma, ma) == 0) {
            return i;
        }
    }
    return -1;
}

void themNhiemVu(struct NhiemVu danhSach[], int *soNhiemVu) {
    struct NhiemVu nv = {0};

    if (*soNhiemVu >= MAX_NV) {
        printf("Mang da day, khong them duoc nua!\n");
        return;
    }

    while (1) {
        if (!nhapChuoi("Nhap ma (vd NV001): ", nv.ma, sizeof(nv.ma))) {
            printf("\nDa huy them nhiem vu do ket thuc hoac loi nhap.\n");
            return;
        }
        if (coKhoangTrang(nv.ma)) {
            printf("Ma khong duoc co khoang trang!\n");
        } else if (timTheoMa(danhSach, *soNhiemVu, nv.ma) != -1) {
            printf("Ma da ton tai! Nhap lai.\n");
        } else {
            break;
        }
    }

    if (!nhapChuoi("Nhap ten nhiem vu: ", nv.ten, sizeof(nv.ten)) ||
        !nhapChuoi("Nhap nguoi phu trach: ", nv.nguoiPhuTrach,
                   sizeof(nv.nguoiPhuTrach)) ||
        !nhapInt("Nhap trang thai (0: chua lam, 1: dang lam, 2: hoan thanh): ",
                 0, 2, &nv.trangThai) ||
        !nhapInt("Da cham diem chua? (0: chua, 1: roi): ",
                 0, 1, &nv.daChamDiem)) {
        printf("\nDa huy them nhiem vu do ket thuc hoac loi nhap.\n");
        return;
    }

    if (nv.daChamDiem == 1 &&
        !nhapFloat("Nhap diem (0 - 10): ", 0.0f, 10.0f, &nv.diem)) {
        printf("\nDa huy them nhiem vu do ket thuc hoac loi nhap.\n");
        return;
    }

    danhSach[*soNhiemVu] = nv;
    (*soNhiemVu)++;
    printf("Da them nhiem vu %s\n", nv.ma);
}

void capNhatNhiemVu(struct NhiemVu danhSach[], int soNhiemVu) {
    char ma[20] = "";
    char chuoiMoi[100] = "";
    int viTri = 0;
    int chon = 0;
    struct NhiemVu *nv = NULL;

    if (soNhiemVu == 0) {
        printf("\nDanh sach dang rong.\n");
        return;
    }
    if (!nhapChuoi("Nhap ma nhiem vu can cap nhat: ", ma, sizeof(ma))) {
        return;
    }
    viTri = timTheoMa(danhSach, soNhiemVu, ma);
    if (viTri == -1) {
        printf("Khong tim thay nhiem vu co ma %s!\n", ma);
        return;
    }
    nv = &danhSach[viTri];

    do {
        printf("\n--- Cap nhat %s | %s ---\n", nv->ma, nv->ten);
        printf("1. Sua ten\n");
        printf("2. Sua nguoi phu trach\n");
        printf("3. Sua diem\n");
        printf("4. Doi trang thai\n");
        printf("0. Quay lai menu chinh\n");
        if (!nhapInt("Chon: ", 0, 4, &chon)) {
            return;
        }
        switch (chon) {
            case 1:
                if (!nhapChuoi("Nhap ten moi: ", chuoiMoi, sizeof(chuoiMoi))) {
                    return;
                }
                strcpy(nv->ten, chuoiMoi);
                printf("Da cap nhat ten!\n");
                break;
            case 2:
                if (!nhapChuoi("Nhap nguoi phu trach moi: ", chuoiMoi,
                               sizeof(chuoiMoi))) {
                    return;
                }
                strcpy(nv->nguoiPhuTrach, chuoiMoi);
                printf("Da cap nhat nguoi phu trach!\n");
                break;
            case 3:
                if (!nhapFloat("Nhap diem moi (0 - 10): ", 0.0f, 10.0f, &nv->diem)) {
                    return;
                }
                nv->daChamDiem = 1;
                printf("Da cap nhat diem!\n");
                break;
            case 4:
                if (!nhapInt("Nhap trang thai moi (0: chua lam, 1: dang lam, 2: hoan thanh): ",
                             0, 2, &nv->trangThai)) {
                    return;
                }
                printf("Da cap nhat trang thai!\n");
                break;
            case 0:
                break;
        }
    } while (chon != 0);
}

void xoaNhiemVu(struct NhiemVu danhSach[], int *soNhiemVu) {
    char ma[20] = "";
    char dong[10] = "";
    int viTri = 0;
    int i = 0;

    if (*soNhiemVu == 0) {
        printf("\nDanh sach dang rong.\n");
        return;
    }
    if (!nhapChuoi("Nhap ma nhiem vu can xoa: ", ma, sizeof(ma))) {
        return;
    }
    viTri = timTheoMa(danhSach, *soNhiemVu, ma);
    if (viTri == -1) {
        printf("Khong tim thay nhiem vu co ma %s!\n", ma);
        return;
    }
    printf("Tim thay: %s | %s | %s\n",
           danhSach[viTri].ma, danhSach[viTri].ten, danhSach[viTri].nguoiPhuTrach);
    printf("Xac nhan xoa? (y/n): ");
    if (docDong(dong, sizeof(dong)) != 1) {
        printf("Da huy xoa.\n");
        return;
    }
    if (strcmp(dong, "y") != 0 && strcmp(dong, "Y") != 0) {
        printf("Da huy xoa.\n");
        return;
    }
    for (i = viTri; i < *soNhiemVu - 1; i++) {
        danhSach[i] = danhSach[i + 1];
    }
    (*soNhiemVu)--;
    printf("Da xoa nhiem vu %s\n", ma);
}

void hienThiMenu(void) {
    printf("\n==========================================\n");
    printf("  QUAN LY NHIEM VU NHOM HOC LAP TRINH\n");
    printf("==========================================\n");
    printf("  1. Them nhiem vu\n");
    printf("  2. Hien thi danh sach\n");
    printf("  3. Cap nhat nhiem vu\n");
    printf("  4. Xoa nhiem vu\n");
    printf("  5. Tim kiem theo ma\n");
    printf("  6. Thong ke nhiem vu\n");
    printf("  7. Loc theo trang thai\n");
    printf("  0. Thoat\n");
    printf("------------------------------------------\n");
}

const char *tenTrangThai(int trangThai) {
    switch (trangThai) {
        case 0:
            return "Chua lam";
        case 1:
            return "Dang lam";
        case 2:
            return "Hoan thanh";
        default:
            return "Khong hop le";
    }
}

int doRongHienThi(const char chuoi[]) {
    int i = 0;
    int doRong = 0;
    unsigned char kyTu = 0;
    unsigned char keTiep = 0;

    for (i = 0; chuoi[i] != '\0'; i++) {
        kyTu = (unsigned char)chuoi[i];
        keTiep = (unsigned char)chuoi[i + 1];
        if ((kyTu & 0xC0) != 0x80) {
            if ((kyTu == 0xCC && keTiep >= 0x80 && keTiep <= 0xBF) ||
                (kyTu == 0xCD && keTiep >= 0x80 && keTiep <= 0xAF)) {
                continue;
            }
            doRong++;
        }
    }
    return doRong;
}

int doRongIn(const char chuoi[], int doRong) {
    return doRong + (int)strlen(chuoi) - doRongHienThi(chuoi);
}

void inDuongKe(int doRongMa, int doRongTen, int doRongNguoi) {
    int doRongCot[6] = {4, doRongMa, doRongTen, doRongNguoi, 12, 10};
    int i = 0;
    int j = 0;

    for (i = 0; i < 6; i++) {
        printf("+");
        for (j = 0; j < doRongCot[i] + 2; j++) {
            printf("-");
        }
    }
    printf("+\n");
}

void hienThiDanhSach(const struct NhiemVu danhSach[], int soNhiemVu) {
    int doRongMa = 8;
    int doRongTen = 24;
    int doRongNguoi = 16;
    int doDai = 0;
    int i = 0;
    char diemChuoi[20] = "";

    if (soNhiemVu == 0) {
        printf("\nDanh sach dang rong. Chon 1 de them nhiem vu.\n");
        return;
    }

    for (i = 0; i < soNhiemVu; i++) {
        doDai = doRongHienThi(danhSach[i].ma);
        if (doDai > doRongMa) {
            doRongMa = doDai;
        }
        doDai = doRongHienThi(danhSach[i].ten);
        if (doDai > doRongTen) {
            doRongTen = doDai;
        }
        doDai = doRongHienThi(danhSach[i].nguoiPhuTrach);
        if (doDai > doRongNguoi) {
            doRongNguoi = doDai;
        }
    }

    printf("\nDANH SACH NHIEM VU\n");
    inDuongKe(doRongMa, doRongTen, doRongNguoi);
    printf("| %-4s | %-*s | %-*s | %-*s | %-12s | %-10s |\n",
           "STT", doRongMa, "MA", doRongTen, "TEN NHIEM VU",
           doRongNguoi, "NGUOI PHU TRACH", "TRANG THAI", "DIEM");
    inDuongKe(doRongMa, doRongTen, doRongNguoi);

    for (i = 0; i < soNhiemVu; i++) {
        if (danhSach[i].daChamDiem == 1) {
            snprintf(diemChuoi, sizeof(diemChuoi), "%.1f", danhSach[i].diem);
        } else {
            strcpy(diemChuoi, "Chua cham");
        }
        printf("| %-4d | %-*s | %-*s | %-*s | %-12s | %-10s |\n",
               i + 1, doRongIn(danhSach[i].ma, doRongMa), danhSach[i].ma,
               doRongIn(danhSach[i].ten, doRongTen), danhSach[i].ten,
               doRongIn(danhSach[i].nguoiPhuTrach, doRongNguoi), danhSach[i].nguoiPhuTrach,
               tenTrangThai(danhSach[i].trangThai), diemChuoi);
    }

    inDuongKe(doRongMa, doRongTen, doRongNguoi);
    printf("Tong so nhiem vu: %d/%d\n", soNhiemVu, MAX_NV);
    printf("Diem hien thi lam tron 1 chu so thap phan.\n");
}

void timKiemNhiemVu(const struct NhiemVu danhSach[], int soNhiemVu) {
    char ma[20] = "";
    int viTri = -1;

    if (soNhiemVu == 0) {
        printf("\nDanh sach dang rong.\n");
        return;
    }
    if (!nhapChuoi("Nhap ma nhiem vu can tim: ", ma, sizeof(ma))) {
        return;
    }
    viTri = timTheoMa(danhSach, soNhiemVu, ma);
    if (viTri == -1) {
        printf("Khong tim thay nhiem vu co ma %s!\n", ma);
        return;
    }
    hienThiDanhSach(&danhSach[viTri], 1);
}

void thongKeNhiemVu(const struct NhiemVu danhSach[], int soNhiemVu) {
    int soChuaLam = 0;
    int soDangLam = 0;
    int soHoanThanh = 0;
    int soDaCham = 0;
    int i = 0;
    float tongDiem = 0.0f;
    float diemTrungBinh = 0.0f;

    if (soNhiemVu == 0) {
        printf("\nDanh sach dang rong.\n");
        return;
    }
    for (i = 0; i < soNhiemVu; i++) {
        switch (danhSach[i].trangThai) {
            case 0:
                soChuaLam++;
                break;
            case 1:
                soDangLam++;
                break;
            case 2:
                soHoanThanh++;
                break;
        }
        if (danhSach[i].daChamDiem == 1) {
            tongDiem += danhSach[i].diem;
            soDaCham++;
        }
    }
    printf("\nTHONG KE NHIEM VU\n");
    printf("Tong so nhiem vu: %d\n", soNhiemVu);
    printf("Chua lam: %d\n", soChuaLam);
    printf("Dang lam: %d\n", soDangLam);
    printf("Hoan thanh: %d\n", soHoanThanh);
    printf("Da cham diem: %d\n", soDaCham);
    printf("Chua cham diem: %d\n", soNhiemVu - soDaCham);
    if (soDaCham > 0) {
        diemTrungBinh = tongDiem / soDaCham;
        printf("Diem trung binh cua nhiem vu da cham: %.2f\n", diemTrungBinh);
    } else {
        printf("Chua co diem de tinh trung binh.\n");
    }
}

void locTheoTrangThai(const struct NhiemVu danhSach[], int soNhiemVu) {
    struct NhiemVu ketQua[MAX_NV] = {0};
    int trangThai = 0;
    int soKetQua = 0;
    int i = 0;

    if (soNhiemVu == 0) {
        printf("\nDanh sach dang rong.\n");
        return;
    }
    if (!nhapInt("Nhap trang thai can loc (0: chua lam, 1: dang lam, 2: hoan thanh): ",
                 0, 2, &trangThai)) {
        return;
    }
    for (i = 0; i < soNhiemVu; i++) {
        if (danhSach[i].trangThai == trangThai) {
            ketQua[soKetQua] = danhSach[i];
            soKetQua++;
        }
    }
    if (soKetQua == 0) {
        printf("Khong co nhiem vu o trang thai %s.\n", tenTrangThai(trangThai));
        return;
    }
    printf("\nKet qua loc: %s\n", tenTrangThai(trangThai));
    hienThiDanhSach(ketQua, soKetQua);
}

int main(void) {
    struct NhiemVu danhSach[MAX_NV] = {0};
    int soNhiemVu = 0;
    int chon = -1;

    do {
        hienThiMenu();
        if (!nhapInt("Chon chuc nang (0 - 7): ", 0, 7, &chon)) {
            printf("\nKet thuc nhap du lieu.\n");
            break;
        }

        switch (chon) {
            case 1:
                themNhiemVu(danhSach, &soNhiemVu);
                break;
            case 2:
                hienThiDanhSach(danhSach, soNhiemVu);
                break;
            case 3:
                capNhatNhiemVu(danhSach, soNhiemVu);
                break;
            case 4:
                xoaNhiemVu(danhSach, &soNhiemVu);
                break;
            case 5:
                timKiemNhiemVu(danhSach, soNhiemVu);
                break;
            case 6:
                thongKeNhiemVu(danhSach, soNhiemVu);
                break;
            case 7:
                locTheoTrangThai(danhSach, soNhiemVu);
                break;
            case 0:
                printf("Tam biet!\n");
                break;
        }
        if (feof(stdin) || ferror(stdin)) {
            chon = 0;
        }
    } while (chon != 0);

    return 0;
}
