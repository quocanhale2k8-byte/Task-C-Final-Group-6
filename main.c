#include <stdio.h>
#include <string.h>

#define MAX_NV 100

struct NhiemVu {
    char ma[20];         // vd NV001: khong rong, khong khoang trang, khong trung
    char ten[100];       // khong rong, cho phep dau cach
    char nguoiPhuTrach[100]; // khong rong, cho phep dau cach
    int trangThai;       // 0: chua lam, 1: dang lam, 2: hoan thanh
    int daChamDiem;      // 0: chua cham, 1: da cham
    float diem;          // 0 - 10 (chi nhap khi daChamDiem = 1)
};

// ---------- ham phu tro ----------

void xoaXuongDong(char s[]) {
    s[strcspn(s, "\n")] = '\0';
}

// Rong neu khong co ky tu nao, hoac chi toan khoang trang
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

// Nhap so nguyen trong [min, max]; nhap chu hoac sai pham vi thi bat nhap lai
int nhapInt(const char *loiNhac, int min, int max) {
    char dong[100];
    int giaTri;
    char thua;
    while (1) {
        printf("%s", loiNhac);
        if (!fgets(dong, sizeof(dong), stdin))
            return min;
        // %c phia sau de loai truong hop "12abc"
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
        if (!fgets(dong, sizeof(dong), stdin))
            return min;
        if (sscanf(dong, "%f %c", &giaTri, &thua) == 1 &&
            giaTri >= min && giaTri <= max)
            return giaTri;
        printf("Nhap so tu %.0f den %.0f!\n", min, max);
    }
}

// ---------- PHAN CUA KURO: them nhiem vu + kiem tra du lieu ----------

void themNhiemVu(struct NhiemVu danhSach[], int *soNhiemVu) {
    // 1. Chan mang day
    if (*soNhiemVu >= MAX_NV) {
        printf("Mang da day, khong them duoc nua!\n");
        return;
    }

    struct NhiemVu nv;

    // 2. Ma: khong rong, khong khoang trang, khong trung -> sai thi nhap lai
    while (1) {
        printf("Nhap ma (vd NV001): ");
        fgets(nv.ma, sizeof(nv.ma), stdin);
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

    // 3. Ten: khong rong, cho phep dau cach
    while (1) {
        printf("Nhap ten nhiem vu: ");
        fgets(nv.ten, sizeof(nv.ten), stdin);
        xoaXuongDong(nv.ten);
        if (laRong(nv.ten)) {
            printf("Ten khong duoc de trong! Nhap lai.\n");
            continue;
        }
        break;
    }

    // 4. Nguoi phu trach: khong rong
    while (1) {
        printf("Nhap nguoi phu trach: ");
        fgets(nv.nguoiPhuTrach, sizeof(nv.nguoiPhuTrach), stdin);
        xoaXuongDong(nv.nguoiPhuTrach);
        if (laRong(nv.nguoiPhuTrach)) {
            printf("Nguoi phu trach khong duoc de trong! Nhap lai.\n");
            continue;
        }
        break;
    }

    // 5. Trang thai: 0 - 2
    nv.trangThai = nhapInt("Nhap trang thai (0: chua lam, 1: dang lam, 2: hoan thanh): ", 0, 2);

    // 6. Diem: hoi da cham chua, roi moi nhap diem 0 - 10
    nv.daChamDiem = nhapInt("Da cham diem chua? (0: chua, 1: roi): ", 0, 1);
    if (nv.daChamDiem == 1)
        nv.diem = nhapFloat("Nhap diem (0 - 10): ", 0, 10);
    else
        nv.diem = 0;

    // Tat ca hop le -> luu vao mang, tang bien dem goc
    danhSach[*soNhiemVu] = nv;
    (*soNhiemVu)++;
    printf("Da them nhiem vu %s\n", nv.ma);
}

// ---------- menu + hien thi (de chay demo; ghep voi ban cua ban kia sau) ----------

void hienThiMenu(void) {
    printf("\n===== MENU =====\n");
    printf("1. Them nhiem vu\n");
    printf("2. Hien thi danh sach\n");
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
        // Doc ca dong roi moi tach so: nhap chu khong lam ket chuong trinh
        if (!fgets(dong, sizeof(dong), stdin))
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
            case 0:
                printf("Tam biet!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (chon != 0);

    return 0;
}
