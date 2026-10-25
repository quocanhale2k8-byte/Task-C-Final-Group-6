#include <stdio.h>
#include <string.h>

#define MAX_NV 100

struct NhiemVu {
    char ma[20];
    char ten[100];
    char nguoiPhuTrach[100];
    int trangThai;
    int daChamDiem;
    float diem;
};

void xoaXuongDong(char s[]) {
    s[strcspn(s, "\n")] = '\0';
}

int laRong(char s[]) {
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] != ' ' && s[i] != '\t')
            return 0;
    return 1;
}

int coKhoangTrang(char s[]) {
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] == ' ' || s[i] == '\t')
            return 1;
    return 0;
}

int timTheoMa(struct NhiemVu danhSach[], int soNhiemVu, char ma[]) {
    for (int i = 0; i < soNhiemVu; i++)
        if (strcmp(danhSach[i].ma, ma) == 0)
            return i;
    return -1;
}

int docDong(char *dong, int kichThuoc) {
    if (!fgets(dong, kichThuoc, stdin))
        return -1;
    if (strchr(dong, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 1;
    }
    return 0;
}

void nhapChuoiKhongRong(const char *loiNhac, char *dich, int kichThuoc) {
    while (1) {
        printf("%s", loiNhac);
        if (docDong(dich, kichThuoc) == 1) {
            printf("Nhap qua dai! Nhap lai.\n");
            continue;
        }
        xoaXuongDong(dich);
        if (laRong(dich)) {
            printf("Khong duoc de trong! Nhap lai.\n");
            continue;
        }
        break;
    }
}

int nhapInt(const char *loiNhac, int min, int max) {
    char dong[100];
    int giaTri;
    char thua;
    while (1) {
        printf("%s", loiNhac);
        if (docDong(dong, sizeof(dong)) == -1)
            return min;

        if (sscanf(dong, "%d %c", &giaTri, &thua) == 1 &&
            giaTri >= min && giaTri <= max)
            return giaTri;
        printf("Nhap so nguyen tu %d den %d!\n", min, max);
    }
}

float nhapFloat(const char *loiNhac, float min, float max) {
    char dong[100];
    float giaTri;
    char thua;
    while (1) {
        printf("%s", loiNhac);
        if (docDong(dong, sizeof(dong)) == -1)
            return min;
        if (sscanf(dong, "%f %c", &giaTri, &thua) == 1 &&
            giaTri >= min && giaTri <= max)
            return giaTri;
        printf("Nhap so tu %.0f den %.0f!\n", min, max);
    }
}

void themNhiemVu(struct NhiemVu danhSach[], int *soNhiemVu) {

    if (*soNhiemVu >= MAX_NV) {
        printf("Mang da day, khong them duoc nua!\n");
        return;
    }

    struct NhiemVu nv;

    while (1) {
        printf("Nhap ma (vd NV001): ");
        if (docDong(nv.ma, sizeof(nv.ma)) == 1) {
            printf("Ma qua dai! Nhap lai.\n");
            continue;
        }
        xoaXuongDong(nv.ma);
        if (laRong(nv.ma)) {
            printf("Ma khong duoc de trong! Nhap lai.\n");
            continue;
        }
        if (coKhoangTrang(nv.ma)) {
            printf("Ma khong duoc co khoang trang! Nhap lai.\n");
            continue;
        }
        if (timTheoMa(danhSach, *soNhiemVu, nv.ma) != -1) {
            printf("Ma da ton tai! Nhap lai.\n");
            continue;
        }
        break;
    }

    nhapChuoiKhongRong("Nhap ten nhiem vu: ", nv.ten, sizeof(nv.ten));

    nhapChuoiKhongRong("Nhap nguoi phu trach: ", nv.nguoiPhuTrach, sizeof(nv.nguoiPhuTrach));

    nv.trangThai = nhapInt("Nhap trang thai (0: chua lam, 1: dang lam, 2: hoan thanh): ", 0, 2);

    nv.daChamDiem = nhapInt("Da cham diem chua? (0: chua, 1: roi): ", 0, 1);
    if (nv.daChamDiem == 1)
        nv.diem = nhapFloat("Nhap diem (0 - 10): ", 0, 10);
    else
        nv.diem = 0;

    danhSach[*soNhiemVu] = nv;
    (*soNhiemVu)++;
    printf("Da them nhiem vu %s\n", nv.ma);
}

void capNhatNhiemVu(struct NhiemVu danhSach[], int soNhiemVu) {
    char ma[20];
    printf("Nhap ma nhiem vu can cap nhat: ");
    docDong(ma, sizeof(ma));
    xoaXuongDong(ma);

    int viTri = timTheoMa(danhSach, soNhiemVu, ma);
    if (viTri == -1) {
        printf("Khong tim thay nhiem vu co ma %s!\n", ma);
        return;
    }

    struct NhiemVu *nv = &danhSach[viTri];
    int chon;
    do {
        printf("\n--- Cap nhat %s | %s ---\n", nv->ma, nv->ten);
        printf("1. Sua ten\n");
        printf("2. Sua nguoi phu trach\n");
        printf("3. Sua diem\n");
        printf("4. Doi trang thai\n");
        printf("0. Quay lai menu chinh\n");
        chon = nhapInt("Chon: ", 0, 4);
        switch (chon) {
            case 1:
                nhapChuoiKhongRong("Nhap ten moi: ", nv->ten, sizeof(nv->ten));
                printf("Da cap nhat ten!\n");
                break;
            case 2:
                nhapChuoiKhongRong("Nhap nguoi phu trach moi: ", nv->nguoiPhuTrach, sizeof(nv->nguoiPhuTrach));
                printf("Da cap nhat nguoi phu trach!\n");
                break;
            case 3:
                nv->diem = nhapFloat("Nhap diem moi (0 - 10): ", 0, 10);
                nv->daChamDiem = 1;
                printf("Da cap nhat diem!\n");
                break;
            case 4:
                nv->trangThai = nhapInt("Nhap trang thai moi (0: chua lam, 1: dang lam, 2: hoan thanh): ", 0, 2);
                printf("Da cap nhat trang thai!\n");
                break;
            case 0:
                break;
        }
    } while (chon != 0);
}

void xoaNhiemVu(struct NhiemVu danhSach[], int *soNhiemVu) {
    if (*soNhiemVu == 0) {
        printf("Chua co nhiem vu nao.\n");
        return;
    }

    char ma[20];
    printf("Nhap ma nhiem vu can xoa: ");
    docDong(ma, sizeof(ma));
    xoaXuongDong(ma);

    int viTri = timTheoMa(danhSach, *soNhiemVu, ma);
    if (viTri == -1) {
        printf("Khong tim thay nhiem vu co ma %s!\n", ma);
        return;
    }

    printf("Tim thay: %s | %s | %s\n",
           danhSach[viTri].ma, danhSach[viTri].ten, danhSach[viTri].nguoiPhuTrach);
    char dong[10];
    printf("Xac nhan xoa? (y/n): ");
    if (docDong(dong, sizeof(dong)) == -1) {
        printf("Da huy xoa.\n");
        return;
    }
    if (dong[0] != 'y' && dong[0] != 'Y') {
        printf("Da huy xoa.\n");
        return;
    }

    for (int i = viTri; i < *soNhiemVu - 1; i++)
        danhSach[i] = danhSach[i + 1];
    (*soNhiemVu)--;
    printf("Da xoa nhiem vu %s\n", ma);
}

void hienThiMenu(void) {
    printf("\n===== MENU =====\n");
    printf("1. Them nhiem vu\n");
    printf("2. Hien thi danh sach\n");
    printf("3. Cap nhat nhiem vu\n");
    printf("4. Xoa nhiem vu\n");
    printf("0. Thoat\n");
    printf("Chon: ");
}

void hienThiDanhSach(const struct NhiemVu danhSach[], int soNhiemVu) {
    if (soNhiemVu == 0) {
        printf("Chua co nhiem vu nao.\n");
        return;
    }
    printf("\n%-8s | %-20s | %-15s | %-10s | %s\n",
           "MA", "TEN", "NGUOI PHU TRACH", "TRANG THAI", "DIEM");
    for (int i = 0; i < soNhiemVu; i++) {
        if (danhSach[i].daChamDiem == 1)
            printf("%-8s | %-20s | %-15s | %-10d | %.1f\n",
                   danhSach[i].ma, danhSach[i].ten,
                   danhSach[i].nguoiPhuTrach, danhSach[i].trangThai,
                   danhSach[i].diem);
        else
            printf("%-8s | %-20s | %-15s | %-10d | %s\n",
                   danhSach[i].ma, danhSach[i].ten,
                   danhSach[i].nguoiPhuTrach, danhSach[i].trangThai,
                   "chua cham");
    }
}

int main(void) {
    struct NhiemVu danhSach[MAX_NV];
    int soNhiemVu = 0;
    int chon;
    char dong[100];
    char thua;

    do {
        hienThiMenu();

        if (docDong(dong, sizeof(dong)) == -1)
            break;
        if (sscanf(dong, "%d %c", &chon, &thua) != 1) {
            printf("Lua chon khong hop le!\n");
            continue;
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
            case 0:
                printf("Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (chon != 0);

    return 0;
}
