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

void hienThiMenu(void) {
    printf("\n==========================================\n");
    printf("  QUAN LY NHIEM VU NHOM HOC LAP TRINH\n");
    printf("==========================================\n");
    printf("  1. Them nhiem vu\n");
    printf("  2. Hien thi danh sach\n");
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
        doDai = (int)strlen(danhSach[i].ma);
        if (doDai > doRongMa) {
            doRongMa = doDai;
        }
        doDai = (int)strlen(danhSach[i].ten);
        if (doDai > doRongTen) {
            doRongTen = doDai;
        }
        doDai = (int)strlen(danhSach[i].nguoiPhuTrach);
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
               i + 1, doRongMa, danhSach[i].ma,
               doRongTen, danhSach[i].ten,
               doRongNguoi, danhSach[i].nguoiPhuTrach,
               tenTrangThai(danhSach[i].trangThai), diemChuoi);
    }

    inDuongKe(doRongMa, doRongTen, doRongNguoi);
    printf("Tong so nhiem vu: %d/%d\n", soNhiemVu, MAX_NV);
    printf("Diem hien thi lam tron 1 chu so thap phan.\n");
}

int main(void) {
    struct NhiemVu danhSach[MAX_NV] = {0};
    int soNhiemVu = 0;
    int chon = -1;

    do {
        hienThiMenu();
        if (!nhapInt("Chon chuc nang (0 - 2): ", 0, 2, &chon)) {
            printf("\nKet thuc nhap du lieu.\n");
            break;
        }

        switch (chon) {
            case 1:
                themNhiemVu(danhSach, &soNhiemVu);
                if (feof(stdin) || ferror(stdin)) {
                    chon = 0;
                }
                break;
            case 2:
                hienThiDanhSach(danhSach, soNhiemVu);
                break;
            case 0:
                printf("Tam biet!\n");
                break;
        }
    } while (chon != 0);

    return 0;
}
