#include"Mylib.h"

#include<string>
#include<time.h>
#include<fstream>
#include<stdlib.h>
#include<iomanip>// ho tro setw
using namespace std;

const int so_item = 5;
const int dong =5;
const int cot = 20;
const int Up = 72; // mui ten len
const int Down = 80; // mui ten xuong


//void DuyetLNR(NODEMH *Root);
void ThemNodeVaoCay_DeQuy(NODEMH *&Root, MONHOC mh);
void XuatLopTC(LOPTC lop);
int DemChuoi(char *k);
void SaveDanhSachMonHoc(NODEMH *Root);
NODEMH* LayRaMaMonBangTenMon(NODEMH *Root, char *x);
void TaoTenFileTheoMaLopTinChi(int maloptinchi, char Filename[]);

//====================================================================DO HOA==============================================================================
char Menu [][50] = {	  "1. Menu Mon Hoc           ",
			                  "2. Menu Lop Tin Chi       ",
			                  "3. Menu Sinh Vien         ",
			                  "4. Menu Danh Sach Dang Ky ",
			                  "5. Ket Thuc Chuong Trinh  "};
			                  
char MonHoc [][50] = {	"1. Them Mon hoc     ",
			                  	"2. Xoa Mon Hoc       ",
			                 	"3. Sua Mon Hoc       ",
			                  	"4. Danh Sach Mon Hoc ",
							  	"5. Thoat             "
							  };
			                  
char LopTinChi [][50] = {"1. Them Lop Tin Chi   ",
			                  "2. Xoa Lop Tin Chi      ",
			                  "3. Sua Lop Tin Chi      ",
			                  "4. Danh Sach Lop Tin Chi",	                  
			                  "5. Thoat                "};
			                  
char SinhVien [][50] = {"1. Them Sinh Vien                ",
			                  "2. Xoa Sinh Vien                  ",
			                  "3. Sua Sinh Vien                  ",
			                  "4. Xem Toan Bo Sinh Vien          ",
							  "5. Danh sach Sinh Vien Theo Ma Lop",		                  
			                  "6. Thoat                          "};
char DangKy [][50] = {		  "1. Dang Ky Vao Lop           ",
			                  "2. Xoa Sinh Vien dang ky     ",
			                  "3. Sua Diem                  ",
			                  "4. Danh sach Dang Ky Tuy Chon",	   
							  "5. Toan Bo Danh sach Dang Ky ",               
			                  "6. In Bang Diem Mon Hoc      ",
							  "7. In Diem Trung Binh        ",
							  "8. Thoat                     "};

char YESNO [][50] = {"YES","NO "};

int MenuTuyChinh(char TieuDe[][50], int sodong)
{
	
	int x = 50, y = 5;
	int tempy = y;
	// dau tien ta cho no to mau cai phan tu dau tien
	int dem = 5;
	int chiso = 0;
	// in all cac phan tu ra
	for(int i = 0; i < sodong; i++)
	{
		gotoxy(x, tempy++);
		cout << TieuDe[i];
	}
	// nhay den vitri ptu dau tien va to mau no
	gotoxy(x, dem);
	//SetBGColor(9);
	textcolor(31);
	cout << TieuDe[chiso];
	SetBGColor(0);
	//textcolor(15);
	while(true)
	{
		if(kbhit())
		{
			int c = getch();
			if(c == KEY_UP)
			{
				if(dem - 1 >= y)
				{
					XoaManHinh();
					tempy = y;// reset
					// in ra all cac ptu trong mang
					for(int i = 0; i < sodong; i++)
					{
						gotoxy(x, tempy++);
						cout << TieuDe[i];
					}
					tempy = y;
					// cho con tro chuot nhay den noi can den
					gotoxy(x, --dem);
					--chiso;
					// to mau cai cho ma no nhay den day
					//SetBGColor(9);
					textcolor(31);
					cout << TieuDe[chiso];
					SetBGColor(0);
				}
				
			}
			if(c == KEY_DOWN)
			{
				if(dem + 1 <= y + sodong - 1)
				{
					XoaManHinh();
					tempy = y;// reset
					// in ra all cac ptu trong mang
					for(int i = 0; i < sodong; i++)
					{
						gotoxy(x, tempy++);
						cout << TieuDe[i];
					}
					tempy = y;
					// cho con tro chuot nhay den noi can den
					gotoxy(x, ++dem);
					++chiso;
					// to mau cai cho ma no nhay den day
					//SetBGColor(9);
					textcolor(31);
					cout << TieuDe[chiso];
					SetBGColor(0);
				}
				
			}
			if(c == 13)
			{
				return chiso + 1;
			}
		}
		
		
	}
}

void BaoLoi(char *s){
  //int x=wherex() , y=wherey();
  //gotoxy(40, 10);
  SetBGColor(4);
  printf("\n%s", s);
  SetBGColor(1);
  textcolor(15);
}

void BaoLoiVaNgu(char *Loi, int timengu)
{
	BaoLoi(Loi);
	Sleep(timengu);
}

void InTieuDe(int x, int y, int chieurong, int socot, char tieude[][100], int sotieude)
{
	x += 1;
	y += 2;
	gotoxy(x, y);
	int cottb = chieurong / socot;
	int temp = x;
	int dem = 0;
	int k = 0;
	//char tieude[5][50]={"STT", "MASV", "HO", "TEN", "DIEM"};
	for(int i = 1; i <= chieurong; i++)
	{
		if(i % cottb == 0)
		{
			temp = x;// reset temp
			if(k == 0)
			{
				gotoxy(temp += (cottb / 2)- (DemChuoi(tieude[dem]) / 2), y);				
				k++;
			}else{
				gotoxy(temp += k * cottb + (cottb / 2) - (DemChuoi(tieude[dem]) / 2), y);
				k++;
			}						
			cout << tieude[dem++];
		}
	}	
}

// ======================================CAC TIEN XU LY=================================================================

int DemChuoi(char *k)
{ 
	int tong = 0;
	for(int i = 1; i <= strlen(k); i++)
	{
		tong++;
	}
	return tong;
}

int DemSo(int k)
{
	//DemKyTu()
	int dem;
	while(k != 0)
	{
		k /= 10;
		dem++;
	}
	return dem;
}

int NhapSo()
{
	char k[10];
	int n, slen = 0, m;
	
        do
        {
            n=getch();
            // neu n trong khoang (0->9) va do dai phai nho hon 10
            if (n >= '0' && n <= '9' && slen < 10) {
                k[slen++] = n;// tang chuoi len 1 kytu
               printf("%c", (char)n) ;// hien kytu vua nhap ra
            }
            if (n == '\b' && slen > 0) {
                k[--slen] = 0;// rut ngan chuoi
                printf("\b \b");
            }
        }
        while (n!=13);
        m=atoi(k); // chuy?n chu?i thành s? nguyên và gán cho m       
        return m;
}


void HamThoat(bool &check)
{
	while(true)
	{
		if(kbhit())
		{
			char c = getch();
			if(c == KEY_ESC)
			{// thoat ra
				check = true;
				return;
			}
			if(c == KEY_ENTER)// Nhap tiep
			{
				check = false;
				return;
			}
		}
	}
}
//Search_MaMon()
void BoolKiemTraTu(bool &h, char *k)
{
	int dem = 0;
	for(int i = 0; i < strlen(k); i++)
	{
		if(k[i] != ' ' && k[i + 1] != '/0' && k[i + 1] != ' ')
		{
			dem ++;
		}
	}
	if(dem > 1)// co 2 tu tro len
	{
		BaoLoiVaNgu("chi gom 1 tu", 1500);
		h = false;
	}
}

float TimDiemTheoMaSinhVien(LOPTC a, char *masv)
{
	for(NODEDK *p = a.pDSDK.pHead; p != NULL; p = p->pNext)
	{
		if(stricmp(p->DATA.MASV, masv) == 0)
		{
			return p->DATA.DIEM;
		}
	}
}

void XoaTheoChieuDai(int chieudai)
{
	for(int i = 1; i <= chieudai; i++){
		printf(" ");
	}
}

void NhapChuoiTimKiem(char *tieude, char S[], int x, int y) {
	printf("%s", tieude);  fflush(stdin);
    do{	
	  gets(S);
	  gotoxy(x, y);// cho no ko nhay xuong cac hang khac
    }while (strcmp(S,"")==0);	
}

//xong
void NhapSoNguyenTimKiem(char *tieude, int &so, int x, int y)
{
	printf("%s", tieude);
	do
	{		
		so = NhapSo();
		//gotoxy(x, y);
	}while(so < 1);// nho hon 1 la lap lai
}

void XoaManHinhTuyThich(int x, int y, int chieudai)
{
	gotoxy(x, y);
	XoaTheoChieuDai(chieudai);
}

void BaoLoiVaXoaLoi (char *k, int x, int y)
{
	int n = DemChuoi(k);
  	gotoxy(x, y);
  	BaoLoiVaNgu(k, 1500);
  	XoaManHinhTuyThich(x, y, n);
}

//======================================================HAM SEARCH=========================================================

int KiemTra_NienKhoa(DSLOPTC ds, int a)
{
	// duyet het danh sach de kiem tra
	for(int i = 0; i < ds.n; i++)
	{		
		if(ds.Lop[i]->NIENKHOA == a && ds.Lop[i]->pDSDK.n > 0){// ton tai
			return i;
		}
	}
	return -1; //ko ton tai
}

int Search_NienKhoa(DSLOPTC ds, int a){
	// duyet het danh sach de kiem tra
	for(int i = 0; i < ds.n; i++)
	{		
		if(ds.Lop[i]->NIENKHOA == a){// ton tai
			return i;
		}
	}
	return -1; //ko ton tai
}
int Search_HocKy(DSLOPTC ds, int a)
{
	for(int i = 0; i < ds.n; i++){
		if(ds.Lop[i]->HOCKY == a){// ton tai hoc ky
			//XuatLopTC(*ds.Lop[i]);
			//BaoLoi("Tim duoc lop co hoc ky vua nhap roi ne!");
			return i;
		}
	}
	return -1; // hoc ky ko ton tai
}

int Search_HocKyNhapDiem(DSLOPTC ds, LOPTC a)
{
	for(int i = 0; i < ds.n; i++){
		if(ds.Lop[i]->NIENKHOA == a.NIENKHOA && ds.Lop[i]->HOCKY == a.HOCKY){// ton tai hoc ky
			//XuatLopTC(*ds.Lop[i]);
			//BaoLoi("Tim duoc lop co hoc ky vua nhap roi ne!");
			return i;
		}
	}
	return -1; // hoc ky ko ton tai
}

int Search_Nhom(DSLOPTC dsloptc, LOPTC lop){
	for(int i = 0; i < dsloptc.n; i++)
	{
	// neu co 1 lop co ma mon trung nhau va nhom trung nhau  trong 1 hoc ky cua 1 nien khoa thi tra ve vitri cua no
		if(dsloptc.Lop[i]->NIENKHOA == lop.NIENKHOA && dsloptc.Lop[i]->HOCKY == lop.HOCKY && (dsloptc.Lop[i]->MAMH, lop.MAMH) == 0 && dsloptc.Lop[i]->NHOM == lop.NHOM ){// da tim thay
			return i;// tra ve vitri nam trong mang
		}
	}
	return -1;// ko tim thay
}

int Search_MaLopTC(DSLOPTC ds, int g){
	for(int i = 0; i < ds.n; i++){
		if(ds.Lop[i]->MALOPTC == g){
			return i;// trung
		}
	}
	return -1; // ko ton tai
}


// Viet ham search HocKy cua nien khoa nao do
int SearchHocKy_NienKhoa(DSLOPTC dsloptc, LOPTC a)
{
	for(int i = 0; i < dsloptc.n; i++)
	{// kiem tra co nien khoa nay ton tai hoc ky kia hay ko
		if(dsloptc.Lop[i]->NIENKHOA == a.NIENKHOA && dsloptc.Lop[i]->HOCKY == a.HOCKY)
		{// Neu co 
			return i;
		}
	}
	// ko co thi 
	return -1;
}

void SearchSinhVienDangKyCuaLopTinChi(bool &h, LOPTC lop, char *masv)
{//  di vao trong danh sach sinh vien cua lop do ma kiem tra
	for(NODEDK *p = lop.pDSDK.pHead; p != NULL; p = p->pNext)
	{
		if(stricmp(p->DATA.MASV, masv) == 0 )// sinh vien co bi trung ko
		{// da bi trung
			BaoLoiVaNgu("Da dang ky roi!", 1500);
			h = false;
			return;// ket thuc ham
		}
	}
}

int SearchMaMonTrongLopTinChi(DSLOPTC &dsloptc, LOPTC a)
{
	for(int i = 0; i < dsloptc.n; i++)
	{
		if(dsloptc.Lop[i]->NIENKHOA != a.NIENKHOA || dsloptc.Lop[i]->HOCKY != a.HOCKY || stricmp(dsloptc.Lop[i]->MAMH, a.MAMH) != 0)
		{
			continue; // nhay vao lop tiep theo
		}
		if(dsloptc.Lop[i]->NIENKHOA == a.NIENKHOA && dsloptc.Lop[i]->HOCKY == a.HOCKY && stricmp(dsloptc.Lop[i]->MAMH, a.MAMH) == 0)
		{
			return i;
		}
	}
	return -1;
}

int SearchNhomTrongLopTinChi(DSLOPTC dsloptc, LOPTC a)
{
	for(int i = 0; i < dsloptc.n; i++)
	{
		if(dsloptc.Lop[i]->NIENKHOA != a.NIENKHOA || dsloptc.Lop[i]->HOCKY != a.HOCKY || stricmp(dsloptc.Lop[i]->MAMH, a.MAMH)  != 0|| dsloptc.Lop[i]->NHOM != a.NHOM)
		{
			continue;
		}
		if(dsloptc.Lop[i]->NIENKHOA == a.NIENKHOA && dsloptc.Lop[i]->HOCKY == a.HOCKY && stricmp(dsloptc.Lop[i]->MAMH, a.MAMH)  == 0 && dsloptc.Lop[i]->NHOM == a.NHOM)
		{
			return i;
		}
	}
	return -1;
}

//Tim gia tri x xem co ton tai o node nao do trong cay ko? Neu co thi tra ve node do, neu ko thi tra ve NULL
int Search_MaMonTrongLopTinChi(DSLOPTC ds, char *x) 
{	
	for(int i = 0; i < ds.n; i++)
	{
		if(stricmp(ds.Lop[i]->MAMH, x) == 0)
		{
			return i;
		}
	}
	return -1;
}

bool SearchMaLop(LISTSV dssv, char *malop)
{
	bool h = false;
	for(NODESV *p = dssv.pHead; p != NULL; p = p->pNext)
	{
		if(stricmp(p->DATA.MALOP, malop) == 0)
		{
			h = true;
			break;// da tim thay vi ma lop la khoa chinh
		} 
	}
	return h;
}

NODESV* Search_MaSV(LISTSV dssv, char *m){
	NODESV *p;
	for(p = dssv.pHead; p != NULL; p = p->pNext){
		if(stricmp(p->DATA.MASV, m) == 0){// da tim thay
			return p;
		}
	}
	return p; // ko tim thay
}


//=========================================================== XU LY CHUOI =====================================================================//

void NoiChuoi(char *s1, char *s2)
{
	int length_s1 = strlen(s1);
	int length_s2 = strlen(s2);
	for(int i = 0; i < length_s2; i++)
	{
		s1[length_s1++] = s2[i];
	}
	s1[length_s1++] = '\0';
}

void BoolKhoangTrang(bool &h, char k[])// ham nay se thay doi bool h 	
{
	for(int i = 0; i < strlen(k); i++)
	{
		if(k[i] == ' ')
		{
			//gotoxy (60,24);
			BaoLoiVaNgu("Khong chua khoang trang!", 1500);
			h = false;
			break;
		}
	}
}

void BoolChieuDai(bool &h, char k[], int chieudaicankiemtra)
{
	if(strlen(k) - 1 > chieudaicankiemtra)
	{
		//gotoxy (60,24);
		h = false;
		SetBGColor(4);
		printf("\n Qua %d ky tu \n", chieudaicankiemtra);
	
		textcolor(15);
	}
}

void BoolKiemTraDieuKien(bool &h, int Smin, int Smax, int socankiemtra)
{
	if(socankiemtra < Smin || socankiemtra > Smax)
	{
		h = false;
		//gotoxy(60, 24);
		SetBGColor(4);
		printf("\ndieu kien thoa %d <= x <= %d \n", Smin, Smax);
		Sleep(2000);
		textcolor(15);
	}
}

bool KiemTraSoTrongChuoi(char *x)
{
	for(int i = 0; i < strlen(x); i++)
	{
		if(x[i] >= '0' && x[i] <= '9')
		{
			return true;
		}
	}
	return false;
}

int DemKyTu(string s)
{
	int dem=0;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]!=' ')
		{
			dem++;
		}
	}
	return dem;
}


//xong
void NhapSoNguyen(char *tieude, int &so)
{
	printf("\n%s", tieude);
	do
	{
		so = NhapSo();
	}while(so < 0);// nho hon 0 la lap lai
}

// xong
void NhapChuoi (char *tieude, char S[]) {
	printf("%s", tieude);  fflush(stdin);
    do{	
	  gets(S);
    }while (strcmp(S,"")==0);	
}

void XoaKyTu(char *s, int vitrixoa)
{
	int length = strlen(s);

	for(int i = vitrixoa + 1; i < length; i++)
	{
		s[i - 1] = s[i];
	}
	s[length - 1] = '\0';
}

void XoaKyTuC2(char *s, int vitrixoa)
{
	for(int i = vitrixoa + 1; i < strlen(s); i++)
	{
		s[i - 1] = s[i];
	}
	s[strlen(s) - 1] = '\0';
}

bool KiemTraKyTuTrongChuoi(char *x)
{
	for(int i = 0; i < strlen(x); i++)
	{
		if(x[i] >= 'a' && x[i] <= 'z' || x[i] >= 'A' && x[i] <= 'Z' || x[i] < '0' && x[i] > '9')
		{
			return true;
		}
	}
	return false;
}

void KiemTraSoDienThoai(bool &h, char k[])
{
	for(int i = 0; i < strlen(k); i++)
	{
		if(k[i] >= 'a' && k[i] <= 'z' || k[i] >= 'A' && k[i] <= 'Z')
		{
			BaoLoiVaNgu("Chi chua so!", 1500);
			h = false;
			break;
		}
	}
}

// Xoa het khoang trang va Viet hoa chu cai dau
void ChuanHoaMa(char *k)
{
	// xoa all cac khoang trang
	for(int i = 0; i < strlen(k); i++)
	{
		if(k[i] == ' ')
		{
			XoaKyTuC2(k, i);
			i--; // cho tro ve vitri ma no bi xoa
		}
		if(k[i] != ' ' && k[i] >= 'a' && k[i] <= 'z')// la chuthuong thi chuyen sang chu hoa
		{
			k[i] -= 32;
		}

	}

}

void ChuanHoaChuoi(char *p)
{
	int length = strlen(p);

	for(int i = 0; i < length; i++)
	{
		if(p[i] == ' ' && p[i + 1] == ' ')
		{
			XoaKyTu(p, i);
			i--;
			length--;
		}
	}

	if(p[0] == ' ')
	{
		XoaKyTu(p, 0);
		length--;
	}

	if(p[length - 1] == ' ')
	{
		XoaKyTu(p, length - 1);
		length--;
	}

	for(int i = 0; i < length; i++)
	{
		if(p[i] >= 'A' && p[i] <= 'Z')
		{
			p[i]+=32; // chuyen thanh chu thuong
		}
	}
	if(p[0] >= 'a' && p[0 ] <= 'z') p[0] -= 32; // chuyen kytu dau thanh chu hoa
	for(int i = 0;i < length - 1; i++)
	{
		if(p[i] == ' ' && p[i+1] != ' ' )// neu co khoang trang sau do la 1 cai j do khac khoang trang
		{
			if(p[i + 1] >= 'a' && p[i + 1] <= 'z') p[i + 1] -=32; // neu no la chu thuong thi -- thanh chu hoa
		}
	}

}
double NhapDiemTB()
{
	char s[4];
	int n, slen = 0;
	float diem;
        do
        {
			n=getch();
            // neu n trong khoang (0->9) va do dai phai nho hon 6
            if (n >= '0' && n <= '9' && slen < 4 || n == '.') {
            	s[slen++] = n;// tang chuoi len 1 kytu
                printf("%c", (char)n) ;// hien kytu vua nhap ra
            }
            if (n == '\b' && slen > 0) {
                s[--slen] = '\0';
                printf("\b \b");
            }
			
        }
        while (n!=13);
        diem=atof(s);

        return diem;
}

int Check_Empty_String(char *k)
{
	if(k == "")
	{
			return 1;
	}
	if(k == " ")
	{
		return 1;
	}
	return 0;// chuoi ko rong
}

//=========================================================HAM XU LY DANH SACH DANG KY===================================================================

//B2: khoi tao
void KhoiTaoDanhSachDangKy(LISTDK &dsdk){
	dsdk.pHead = NULL;
	dsdk.pTail = NULL;
}
//B3:Tao Node dang ky
NODEDK* TaoNodeDangKy(SINHVIENDK data)
{
	NODEDK *p = new NODEDK;
	if(!p){
		BaoLoiVaNgu("khong du bo nho cap phat", 1500);
		return NULL;
	}
	p->DATA = data;
	p->pNext = NULL; // khoi tao moi lien ket
	return p;
}
//B4: Them dau them cuoi
void ThemVaoDauDanhSachDangKy(LISTDK &dsdk, NODEDK *Svdk) 
{
	if(dsdk.pHead == NULL){
		dsdk.pHead = dsdk.pTail = Svdk;
	}
	else{
		Svdk->pNext = dsdk.pHead;
		dsdk.pHead = Svdk;// cap nhat thenn pHead
	}
}
void ThemVaoCuoiDanhSachDangKy(LISTDK &dsdk, NODEDK *p) 
{
	if(dsdk.pHead == NULL){
		dsdk.pHead = dsdk.pTail = p;
	}
	else{
		dsdk.pTail->pNext = p;
		dsdk.pTail = p;// cap nhat thenn pTail
	}
}

void XuatSinhVienDangKy(SINHVIENDK Svdk)
{
	printf("\n Ma sinh vien: %s", Svdk.MASV);
	printf("\n Diem sinh vien: %f", Svdk.DIEM);
}

// nhap vao ma sinh vien va kiem tra
bool NhapUser(LISTSV Dssv, char *&User)
{
	User = new char; bool h, check = false;
	do
	{ h = true;
		NhapChuoi("\nNhap vao ma sinh vien can dang ky: ", User);
		ChuanHoaMa(User);
		NODESV *p = Search_MaSV(Dssv, User);
		if(p == NULL)
		{
			SetBGColor(4);
			printf("\n User co ma %s khong ton tai!\n", User);
			SetBGColor(0);
			HamThoat(check);
			if(check == true) break;			
			h = false;
			continue;						
		}
		printf("\n User ten la: %s", p->DATA.TEN);
		Sleep(1500);
		printf("\nENTER: Tiep tuc  || ESC: Nhap lai");
		HamThoat(check);
		if(check == true)// Nhap lai
		{
			h = false; 
		}
		 
	}while(h == false);
	return check;
}

// liet ke danh sach lop tin chi dua vao nien khoa a
void LietKeLopTinChiDuaVaoNienKhoa(DSLOPTC Dsloptc, int a)
{
	cout << "\tSTT" << "\tMA LOP" << "\tNIEN KHOA" << "\tHOC KY" << "\tMA MON" << "\tNHOM" << "\tSVMIN" << "\tSVMAX" << "\tSVDANG KY" << endl << endl;
	int dem1 = 1, k = 0;
	for(int i = 0; i < Dsloptc.n; i++)
	{
		if(Dsloptc.Lop[i]->NIENKHOA == a)// liet ke ra all cac loptc co cung nien khoa
		{
			cout << "\t" << dem1++ << "\t" << Dsloptc.Lop[i]->MALOPTC << "\t" << Dsloptc.Lop[i]->NIENKHOA 
		<< "\t\t" << Dsloptc.Lop[i]->HOCKY << "\t" << Dsloptc.Lop[i]->MAMH << "\t" << Dsloptc.Lop[i]->NHOM 
		<< "\t" << Dsloptc.Lop[i]->SVMIN << "\t" << Dsloptc.Lop[i]->SVMAX << "\t";
		SetBGColor(4);
		cout << Dsloptc.Lop[i]->pDSDK.n << endl << endl;
		textcolor(15);
			
		}
	}
}

void Insert_Order_SinhVienDangKy(LISTDK &ds, NODEDK *Svdk)
{
   NODEDK *p, *t, *s;  // t la nut truoc, s la nut sau
   p = new NODEDK;
   p->DATA = Svdk->DATA;// p giu gia tri cua then ms them vao
   for(s = ds.pHead; s != NULL && stricmp(Svdk->DATA.MASV, Svdk->DATA.MASV) < 0; t=s, s = s->pNext)   ;
	if(s == ds.pHead)  // them nut vao dau danh sach lien ket
   	{
      	p->pNext = ds.pHead;
     	 ds.pHead = p;
   	}
   	else // them nut p vao truoc nut s
  	 {
      	p->pNext= s;
      	t->pNext= p;
   	}
}

void LietKeLopTinChiTheoHocKy(DSLOPTC Dsloptc, LOPTC a)
{
	textcolor(63);
	printf("\n               DANH SACH LOP TIN CHI CUA HOC KY %d NIEN KHOA %d                  \n\n", a.HOCKY, a.NIENKHOA);
	textcolor(15);
	int dem1 = 1, k = 0;
	cout << "\tSTT" << "\tMA LOP" << "\tNIEN KHOA" << "\tHOC KY" << "\tMA MON" << "\tNHOM" << "\tSVMIN" << "\tSVMAX" << "\tSVDANG KY" << endl << endl;
	for(int i = 0; i < Dsloptc.n; i++)
	{
		if(Dsloptc.Lop[i]->NIENKHOA == a.NIENKHOA && Dsloptc.Lop[i]->HOCKY == a.HOCKY)// tim hoc ky trong nien khoa
		{
			cout << "\t" << dem1++ << "\t" << Dsloptc.Lop[i]->MALOPTC << "\t" << Dsloptc.Lop[i]->NIENKHOA 
		<< "\t\t" << Dsloptc.Lop[i]->HOCKY << "\t" << Dsloptc.Lop[i]->MAMH << "\t" << Dsloptc.Lop[i]->NHOM 
		<< "\t" << Dsloptc.Lop[i]->SVMIN << "\t" << Dsloptc.Lop[i]->SVMAX << "\t";
		SetBGColor(4);
		cout << Dsloptc.Lop[i]->pDSDK.n << endl << endl;
		textcolor(15); 
		}
	}
	system("pause");
}

void LocDanhSachLopTinChi(DSLOPTC Dsloptc, bool &ktra, LOPTC &a)
{	
	system("cls");
	bool h;
	do{
		h = true; 
		textcolor(63);
		printf("\n                       TIM KIEM LOP TIN CHI                      \n");
		textcolor(15);
		fflush(stdin);
		NhapSoNguyen("\nNhap nien khoa: ", a.NIENKHOA);
		if(Search_NienKhoa(Dsloptc, a.NIENKHOA) == -1)
		{
			BaoLoiVaNgu("khong ton tai!", 1500);
			h = false;
			printf("\nESC: Thoat || ENTER: Nhap Tiep");
			HamThoat(ktra);
			if(ktra == true) break;
		}
	}while(h == false);
	int luachon;
	// in danh sach lop tin chi dua vao nien khoa(in all cac lop tin trong nam do)	
	do{
		system("cls");
		textcolor(63);
		printf("\n                       TIM KIEM LOP TIN CHI                       \n");
		textcolor(15);
		h = true;bool check = false;
		char TimtheoNienKhoa[][50] = {"1. Xem Danh Sach", "2. Tim tiep", "3. Thoat"};
		luachon = MenuTuyChinh(TimtheoNienKhoa, 3);
		switch(luachon)
		{
			case 1: {system("cls");// Xoa man hinh roi in ra
				LietKeLopTinChiDuaVaoNienKhoa(Dsloptc, a.NIENKHOA);
				system("pause");// tam dung man hinh de xem danh sach
				break;
			}
			case 2: 
			{// thoat ra 
				do
				{	
					bool check = false;
					h = true; system("cls");// xoa man hinh khi hoc ky ko hop le
					textcolor(63);
					printf("\n                       TIM KIEM LOP TIN CHI                       \n");
					textcolor(15);
					fflush(stdin);
					NhapSoNguyen("\n Nhap vao hoc ky: ", a.HOCKY);
					BoolKiemTraDieuKien(h, 1, 3, a.HOCKY);
					// Viet ham search HocKy cua nien khoa nao do
					if(SearchHocKy_NienKhoa(Dsloptc, a) == -1)
					{
						BaoLoiVaNgu("khong hop le!", 1500);
						h = false;
						printf("\nESC: Thoat || ENTER: Nhap Tiep");
						HamThoat(check);
						if(check == true) break;
					}
				}while(h == false);
				// liet ke danh sach lop tin chi dua vao hoc ky nay cua nien khoa nay
				LietKeLopTinChiTheoHocKy(Dsloptc, a);			
				return;
			}
			default:{ h = true;
				BaoLoiVaNgu("Lua chon khong hop le!", 1500);
			}
			 
		}
	}while(h != false);	

}

void ThemSinhVienDangKyCoThuTu(LISTDK &ds, NODEDK *p)
{
	if(ds.pHead == NULL) // neu danh sach rong them vao dau
	{
		ThemVaoDauDanhSachDangKy(ds, p); return;
	}
	
	Insert_Order_SinhVienDangKy(ds, p);
}

void BoolDanhSachSinhVienDayChua(bool &h, DSLOPTC dslop, int malopcankiemtra)
{
	for(int i = 0; i < dslop.n; i++)
	{
		if(dslop.Lop[i]->MALOPTC == malopcankiemtra)
		{// tim duoc lop roi ne
			// Bay gio kiem tra xem so sinh vien dang ky no da == voi so sinh vien MAX chua
			if(dslop.Lop[i]->SVMAX == dslop.Lop[i]->pDSDK.n)
			{// chay vo nay co nghia la danh sach sinh vien da day
				h = false;
				BaoLoiVaNgu("Sinh vien dang ky lop nay da Full!", 2000);
				return;// thoat ra luon vi da ra ket qua roi va Maloptc la duy nhat
			}
		}
	}
}

int LayRaNamNhapHocCuaSinhVien(LISTSV dssv, char *masv)
{
	for(NODESV *p = dssv.pHead; p != NULL; p = p->pNext)
	{
		if(stricmp(p->DATA.MASV, masv) == 0)
		{
			return p->DATA.NamHoc;// tra ve nam nhap hoc
		}
	}
}
int KiemTraMaMonDangKy(DSLOPTC dsloptc, LOPTC a, char *Masv, char *Mamon)
{
	for(int i = 0; i < dsloptc.n; i++)
	{
		if(dsloptc.Lop[i]->NIENKHOA == a.NIENKHOA && dsloptc.Lop[i]->HOCKY == a.HOCKY && stricmp(dsloptc.Lop[i]->MAMH, Mamon) == 0 )
		{
			if(dsloptc.Lop[i]->pDSDK.n > 0)
			{
				for(NODEDK *p = dsloptc.Lop[i]->pDSDK.pHead; p != NULL; p = p->pNext)
				{
					if(stricmp(p->DATA.MASV, Masv) == 0)
					{
						BaoLoiVaNgu("da tim dc", 1500);
						return i;
					}
				}
			}else break;
			
			
		}
	}
	BaoLoiVaNgu("Khong tim dc",1500);
	return -1;
}

void TimMaMonTheoMaLop(DSLOPTC dsloptc, int &MaLop, char *&Mamon)
{
	for(int i = 0; i < dsloptc.n; i++)
	{
		if(dsloptc.Lop[i]->MALOPTC == MaLop)
		{// tim dc roi
			BaoLoiVaNgu("Tim dc ma mon roi!", 1500);
			// cap nhat then mamon
			strcpy(Mamon, dsloptc.Lop[i]->MAMH);
			return;
		}
	}
}

void NhapMaLopDangKy(DSLOPTC Dsloptc, LISTSV dssv, int &check, char *Masv, bool &ktra, LOPTC a)
{
	bool h; int Malop;
	do{
		h = true; 
		NhapSoNguyen("Nhap vao ma lop can dang ky: ", Malop);
		// Ktra ma lop nay co ton tai hay ko va la cua loptc nao 
		check = Search_MaLopTC(Dsloptc, Malop); // tao bien check de luu lai vi tri cua lop ma minh tim dc
		if(check == -1)
		{	h = false;
			BaoLoiVaNgu("Ma lop khong ton tai!", 1500);
			printf("\nESC: Thoat || ENTER: Nhap Tiep");
			HamThoat(ktra);		
			if(ktra == true) return;
			continue;
		}
		// ktra dk la nam nhap hoc cua sinh vien nay phai hon hon hoac bang nam mo loptc
		if(Dsloptc.Lop[check]->NIENKHOA < LayRaNamNhapHocCuaSinhVien(dssv, Masv))
		{
			// ko dc dk bvi nam nhap hoc phai nho hon hoac bang nam mo lop
			h = false;
			BaoLoiVaNgu("Nam Nhap hoc phai <= nam mo lop", 1500);
			printf("\nESC: Thoat || ENTER: Nhap Tiep");
			HamThoat(ktra);		
			if(ktra == true) return;
			continue;
		}

		// phai kiem tra danh sach sinh vien dang ky trong nay da day hay chua
		BoolDanhSachSinhVienDayChua(h, Dsloptc, Malop);// neu day thi bat nhap lop khac
		
		char *Mamon;
		// Dung ma loptc tim ra mamon cua lop nay
		TimMaMonTheoMaLop(Dsloptc, Malop, Mamon);
		// Kiem Tra Sv (nien khoa, hoc kì, ma mom) trung nhau thi ko cho dk 
		if(KiemTraMaMonDangKy(Dsloptc, a, Masv, Mamon) != -1)
		{
			h = false;
			BaoLoiVaNgu("Sinh vien da ton tai!", 1500);
			continue;
		}
		// Kiem tra co sv nay trong lop nay chua
		SearchSinhVienDangKyCuaLopTinChi(h, *Dsloptc.Lop[check], Masv);
		//break;// check xong thi thoat ra lun. bvi maloptc la khoa chinh					
	}while(h == false);
}

void DangKyLopTinChiDuaVaoMaSinhVien(DSLOPTC &Dsloptc, LISTSV dssv, char *Masv, LOPTC a)
{
	int Malop, check; bool h, ktra = false;
	SINHVIENDK Svdk;	
	strcpy(Svdk.MASV,Masv);// nhap MASV cho then SINHVIENDK
	Svdk.DIEM = 0; // KHOI TAO DIEM cho SINH VIEN
	NODEDK *q = TaoNodeDangKy(Svdk);// dua sinh vien DK vao node
		
	NhapMaLopDangKy(Dsloptc, dssv, check, Masv, ktra, a);
	if(ktra == true) return;
		
	// Tao ra Ten file voi TEN LA : MALOPTC			
	char Filename[20];// tao vung nho de luu maloptc
	TaoTenFileTheoMaLopTinChi(Dsloptc.Lop[check]->MALOPTC, Filename);
	
	// kiem tra danh sach SVDK trong loptin chi nay co rong hay ko
	if(Dsloptc.Lop[check]->pDSDK.n < 1){// danh sach sv rong
				
		ThemVaoDauDanhSachDangKy(Dsloptc.Lop[check]->pDSDK, q);// truyen sinh vien vao dau danh sach dang ky(trong sinh vien do co MASV roi)
		BaoLoiVaNgu("Dang ky thanh cong!", 1500);
		Dsloptc.Lop[check]->pDSDK.n++; // tang bien dem len de check so luong sinh vien
		// ghi sinh vien cua lop tin chi nay vao file(Xoa het du lieu cu va them file moi)
		SaveFileDanhSachDangKyVaoLopTinChi(*Dsloptc.Lop[check], Filename);
		 	
		return;// thoat ra luon bvi moi lan chi dk dc 1 lop tc
	}// danh sachDK da co phan tu	(KHONG RONG)
	
	ThemSinhVienDangKyCoThuTu(Dsloptc.Lop[check]->pDSDK, q); 						
	Dsloptc.Lop[check]->pDSDK.n++; // cap nhat so luong dssvdk
	// dua vao luu tru database
	SaveFileDanhSachDangKyVaoLopTinChi(*Dsloptc.Lop[check], Filename);
	BaoLoiVaNgu("Dang ky thanh cong!", 1);
	BaoLoiVaNgu("Luu vao Database!", 1500);
}

int z = 1;
void XuLyInSinhVien(LOPTC loptc, LISTSV Dssv)
{	
	//Di vao DSDK cua lop tin chi va lay Masv dang ky
	for(NODEDK *p = loptc.pDSDK.pHead; p != NULL; p = p->pNext)
	{		
	// di vao trong danh sach sinh vien xem co thang nao co ma nhu nay thi IN Ra
		for(NODESV *q = Dssv.pHead; q != NULL; q = q->pNext)
		{// Kiem tra Trong DSSV co MASV nao trung voi MASV cua DSDK thi lay Ma do Doi chieu va In HET Ra									
			if(stricmp(p->DATA.MASV, q->DATA.MASV) == 0)
			{									
				//XuatSinhVien(q->DATA);
				cout << "\n\t" << z++ << "\t" << q->DATA.MASV << "\t" << q->DATA.HO
				 << "\t" << q->DATA.TEN << "\t" << p->DATA.DIEM << "\t" << loptc.MALOPTC << endl << endl; 
				//dem++;							
				break;// boi vi MASV la duy nhat => tim dc roi thi thoat ra vong for htai de nhay ra vong for ngoai de lay MASV roi vao day tiep
			}
		}
		continue;	// di kiem sinh vien khac			
	}
}

void LietKeSinhVienTheoNhom(DSLOPTC dsloptc, LISTSV dssv, LOPTC a)
{ 
	for(int i = 0; i < dsloptc.n; i++)
	{
		if(dsloptc.Lop[i]->NIENKHOA != a.NIENKHOA || dsloptc.Lop[i]->HOCKY != a.HOCKY || stricmp(dsloptc.Lop[i]->MAMH, a.MAMH) != 0 || dsloptc.Lop[i]->NHOM != a.NHOM)
		{
			continue; // nhay vao lop tiep theo
		}
		if(dsloptc.Lop[i]->NIENKHOA == a.NIENKHOA && dsloptc.Lop[i]->HOCKY == a.HOCKY && stricmp(dsloptc.Lop[i]->MAMH, a.MAMH) == 0 && dsloptc.Lop[i]->NHOM == a.NHOM)
		{// da tim dc
			XuLyInSinhVien(*dsloptc.Lop[i], dssv);
		}
	}
}

void LietKeSinhVienTheoMaMon(DSLOPTC dsloptc, LISTSV dssv, LOPTC a)
{
	
	for(int i = 0; i < dsloptc.n; i++)
	{
		if(dsloptc.Lop[i]->NIENKHOA != a.NIENKHOA || dsloptc.Lop[i]->HOCKY != a.HOCKY || stricmp(dsloptc.Lop[i]->MAMH, a.MAMH) != 0)
		{
			continue; // nhay vao lop tiep theo
		}
		if(dsloptc.Lop[i]->NIENKHOA == a.NIENKHOA && dsloptc.Lop[i]->HOCKY == a.HOCKY && stricmp(dsloptc.Lop[i]->MAMH, a.MAMH) == 0)
		{// da tim dc
			XuLyInSinhVien(*dsloptc.Lop[i], dssv);
			cout << endl;
		}
	}
}

void LietKeSinhVienTheoHocKy(DSLOPTC dsloptc, LISTSV dssv, LOPTC a)
{
	// ta di vao trong dsloptc xem co hoc ky nao nam trong nien khoa nay hay ko
	for(int i = 0; i < dsloptc.n; i++)
	{
		if(dsloptc.Lop[i]->NIENKHOA != a.NIENKHOA || dsloptc.Lop[i]->HOCKY != a.HOCKY) continue;
		if(dsloptc.Lop[i]->NIENKHOA == a.NIENKHOA && dsloptc.Lop[i]->HOCKY == a.HOCKY)
		{// kiem tra co ai dk lop nay ko
			XuLyInSinhVien(*dsloptc.Lop[i], dssv);
			cout << endl;			
		}
	}
}

void LietKeSinhVienTheoNienKhoa(DSLOPTC Dsloptc, LISTSV Dssv, LOPTC a)
{
	// B2: di vao trong dsloptc kiem tra co loptc nao co nien khoa nay thi 
	for(int i = 0; i < Dsloptc.n; i++)
	{
		if(Dsloptc.Lop[i]->NIENKHOA != a.NIENKHOA || Dsloptc.Lop[i]->pDSDK.n < 1) continue; // Nien khoa nay ko co ai dang ky het
		else// Loptc co sinh vien dang ky ne
		{
			XuLyInSinhVien(*Dsloptc.Lop[i], Dssv);
			cout << endl;
		}

	}
	return;
}

void LietKeTatCaSinhVienDangKy(DSLOPTC Dsloptc, LISTSV Dssv, int x, int y)
{
	int tempy = y + 2;
	int tempx= x + 3;
	// B2: di vao trong dsloptc va kiem tra lop nao co sv dk thi in het ra
	for(int i = 0; i < Dsloptc.n - 1; i++)
	{
		if(Dsloptc.Lop[i]->pDSDK.n < 1) continue;
		else// Loptc co sv dk ky ne
		{
		// di vao dsdk cua lop tc nay
			for(NODEDK *p = Dsloptc.Lop[i]->pDSDK.pHead; p != NULL; p = p->pNext)
			{// sau do lay ma sinh vien tim trong danh sach sinh vien va IN RA
				tempx = x;// reset lai x
				tempy += 2;// tang chi sodong len
				for(NODESV *q = Dssv.pHead; q != NULL; q = q->pNext)
				{
					if(stricmp(p->DATA.MASV, q->DATA.MASV) == 0)
					{// tim dc sinh vien roi nhe
					// x tang len y giu nguyen tren moi dong
						gotoxy(tempx += 7, tempy);
						cout << z++;
						gotoxy(tempx += 13, tempy);
						cout << q->DATA.MASV;
						gotoxy(tempx += 13, tempy);
						cout << q->DATA.HO;
						gotoxy(tempx += 14, tempy);
						cout << q->DATA.TEN;
						gotoxy(tempx += 16, tempy);
						cout << p->DATA.DIEM << endl; 
					}
				}
			}		
		}
		
	}
}
//=============================================TINH NANG CUOI CUNG==========================================//
//B1: chuyen dsdk cua lop tc qua mang dang ky
/*
void ChuyenDanhSachDangKyQuaMang(DSLOPTC Dsloptc, LISTSV Dssv, ARRAYDK array)
{
	for(int i = 0; i < Dsloptc.n - 1; i++)
	{
		
		if(Dsloptc.Lop[i]->pDSDK.n < 1) continue;
		else// Loptc co sv dk ky ne
		{	
			// di vao dsdk cua lop tc nay
			for(NODEDK *p = Dsloptc.Lop[i]->pDSDK.pHead; p != NULL; p = p->pNext)
			{// sau do lay ma sinh vien tim trong danh sach sinh vien va IN RA
				for(NODESV *q = Dssv.pHead; q != NULL; q = q->pNext)
				{
					if(stricmp(p->DATA.MASV, q->DATA.MASV) == 0)
					{// tim dc sinh vien roi nhe						
						array.ArraySvDk = new SinhVienDK;
						array.ArraySvDk->MASV = strdup(q->DATA.MASV);						
						array.ArraySvDk->DIEM = p->DATA.DIEM; 
					}
				}
			}		
		}
		
	}
}
*/

//B7: Giai phong
void GiaiPhongDanhSachDangKy(LISTDK &Dsdk)
{
	for(NODEDK *p = Dsdk.pHead; p != NULL; p = p->pNext)
	{
		NODEDK *k = p;
		Dsdk.pHead = p->pNext; // cho phead chay sang thang ben canh
		delete k; // xaa then k
	}
}

//=====================================================================HAM XU LY MON HOC================================================================================

//B2: Khoi tao
void KhoiTaoCay(NODEMH *&Root)
{
	Root = NULL;	
}

//B3: Tao Node
NODEMH* TaoNode(MONHOC x)
{
	NODEMH *p = new NODEMH; // cap phat bo nho cho NODEMH
	if(p == NULL)
		return NULL;// Không thành công do thieu vùng nho de cap phát
	// Neu chay dc xuong duoi nay tuc la node ko rong
	p->DATA = x;
	p->Left = NULL;
	p->Right = NULL;
	return p;// tra ve node p sau khi dc tao ra 
}

//B4: Thêm Môn Hoc vào cây nhi phân // DUNG MAMH lam KEY
void ThemNodeVaoCay_DeQuy(NODEMH *&Root, MONHOC mh)
{
	// neu cay ton tai phan tu
	if(Root != NULL)
	{		
		// neu ptu them vao co MAMH nho hon MAMH cua NODE goc ==> them NODE do vao trai
		if(stricmp(mh.MAMH, Root->DATA.MAMH) < 0) // neu  MAMH cua NODE them vao NHO hon MAMH nut goc 
		{
			ThemNodeVaoCay_DeQuy(Root->Left, mh); // duyet qua trai de them mh vao 
		}
		else if(stricmp( mh.MAMH, Root->DATA.MAMH) > 0 )// bvi cac node trong cay la rieng biet 
		{// neu  MAMH cua NODE chuan bi them lon hon MAMH nut goc 
			ThemNodeVaoCay_DeQuy(Root->Right, mh); // duyet qua phai de them phan tu vao
		}

	}
	else// cay rong
	{
		Root = TaoNode(mh); // node Tao ra node vao cho no la node goc
	}
}
// P la node the mang se xoa
void TimPhanTuThayThe(NODEMH *&Root, NODEMH *&p)
{
	if(Root->Right != NULL)
	{
		TimPhanTuThayThe(Root->Right, p);
	}else{// Luc nay Root->right == NULL => Root la NODE phai nhat cua cay con trai ==> do la NODE thay the
		p->DATA = Root->DATA; // lay DATA node thay the(ROOT) cap nhat cho node can xoa(p)
		p = Root; // Cho con tro p toi NOde thay the (Root) de ket thuc ham thi delete p cung chinh la delete Root
		Root = Root->Left; // Cap nhat lai moi lien ket cho 2 then trc do . boi vi day la NODE phai nhat nen la ==> moi lien ket phai tro qa trai
	}
}

NODEMH* KiemTraMaMonTrung(NODEMH *Root, char *x) // kiem tra MA MONHOC co trung cac MONHOC trong cay hay khong
{
	while(Root != NULL && stricmp(Root->DATA.MAMH, x) != 0)
	{
		if(stricmp(Root->DATA.MAMH, x) < 0)
		Root = Root->Right;	
		else if(stricmp(Root->DATA.MAMH, x) > 0)
		Root = Root->Left;
	}
	return Root;
}
void XuatMonHoc(MONHOC mh)
{	
	cout << "\nMa mon: " << mh.MAMH;
	cout << "\nTen mon: " << mh.TENMH;
	cout << "\nSo tin chi ly thuyet: " << mh.STCLT;
	cout << "\nSo tin chi thuc hanh: " << mh.STCTH << endl;
	cout << "-------------------------------------------" << endl;
}

/*
void DuyetCay_LuuVaoMang(NODEMH *Root, DSMH &ds)
{
	int i = 0;
	while(Root != NULL)
	{	
	DuyetCay_LuuVaoMang(Root->Left, ds);
	ds.mh[i] = Root->DATA;// Luu mon hoc vao trong mang DS MON HOC
	i++;
	DuyetCay_LuuVaoMang(Root->Right, ds);
	}
	ds.n = i + 1; // cap nhat so luong cua danh sach
}
*/

// DUYET CAY THEO LNR
void DuyetLNR(NODEMH *Root)
{
	if(Root != NULL)
	{	
		DuyetLNR(Root->Left);
		XuatMonHoc(Root->DATA);
		DuyetLNR(Root->Right);
	}
}

void CapNhatMonHoctrongCay(NODEMH *&Root)
{
	MONHOC mh;
	// tim mon do co trong cay hay ko
	bool h;
	do
	{ 
		h = true; 
		fflush(stdin);
		NhapChuoi("Nhap vao ten mon can thay the: ", mh.TENMH);
		ChuanHoaChuoi(mh.TENMH);
		BoolChieuDai(h, mh.TENMH, 50);
	}while(h == false);
	fflush(stdin);
	NhapSoNguyen("Nhap vao so chi ly thuyet: ", mh.STCLT);
	fflush(stdin);
	NhapSoNguyen("Nhap vao so chi thuc hanh: ", mh.STCTH);
	strcpy(Root->DATA.TENMH, mh.TENMH);
	Root->DATA.STCLT = mh.STCLT;
	Root->DATA.STCTH = mh.STCTH;
}

// Xoa Mon Hoc dua vao ma mon
void XoaMonHocTrongCay_DeQuy(NODEMH *&Root, char *x) // NODEMH chua x la NODEMH can xoa ra khoi cay
{
	if(Root == NULL)
	return; // ket thuc do ko con j de xoa
	if(stricmp(Root->DATA.MAMH, x) > 0)
	{
		XoaMonHocTrongCay_DeQuy(Root->Left, x);
	}
	else if(stricmp(Root->DATA.MAMH, x) < 0)
	{
		XoaMonHocTrongCay_DeQuy(Root->Right, x);
	}
	else{// tim thay x trong cay ==> XOA
		//TH1: Node can xoa la node la
		//TH2: Node can xoa la node co 1 con
		NODEMH *p = Root; // Gan Root da tim dc de xoa cho p va p la node bi xoa
		if(p->Left == NULL)
		{
			Root = Root->Right;
		}			
		else if(p->Right == NULL)
		{
			Root = Root->Left;
		}			
		else
		{//Th3: Node can xoa la node co du 2 con
			TimPhanTuThayThe(Root->Left, p);// ta quy uoc phan tu thay the la ptu phai nhat cua cay con trai
		}
			
		delete p;
	}
}

void NhapMonHoc(NODEMH *Root, MONHOC &mh){
	bool h, check = false;
	do
	{
		h = true;		
		fflush(stdin);
		NhapChuoi ("\nNhap vao ma mon:  ", mh.MAMH);
		BoolKhoangTrang(h, mh.MAMH);// ham nay se thay doi bool h 	
		BoolChieuDai(h, mh.MAMH, 10);// ham nay se thay doi bool h 
		ChuanHoaMa(mh.MAMH);
		if(KiemTraMaMonTrung(Root, mh.MAMH) != NULL)// ktra ma mon co bi trung
		{// tim thay p roi
			BaoLoiVaNgu ("Ma mon bi trung", 1500);
			h = false;
			printf("ESC: Thoat || ENTER: Nhap Tiep");
			HamThoat(check);
			if(check == true) break;
		}
	}while(h == false);
	do{ h = true;
		fflush(stdin);
		NhapChuoi ("\n Nhap vao ten mon: ", mh.TENMH);
		ChuanHoaChuoi(mh.TENMH);// dua ve dang VD: le   quang nHu ==> LE QUANG NHU
		BoolChieuDai(h, mh.TENMH, 16);// ham nay se thay doi bool h 
	}while(h == false);
	do{
		fflush(stdin);
		NhapSoNguyen("\n Nhap vao so chi ly thuyet: ", mh.STCLT);
		if(mh.STCLT < 1)
		{
			printf("\n STLT > 0");
		}
	}while(mh.STCLT < 1);
	
	do{
		fflush(stdin);
		NhapSoNguyen("\n Nhap vao so chi thuc hanh: ", mh.STCTH);
		if(mh.STCTH < 0)
		{
			printf("\n STTH >= 0");
		}
	}while(mh.STCTH < 0);
		
}

// Kiem tra mon hoc nay co lopTinChi nao dk chua. Neu co tra ve False ng lai TRUE
bool KiemTraMonHocKhiXoa(DSLOPTC dsloptc, char *mamon)
{
	for(int i = 0; i < dsloptc.n; i++)
	{	// kiem tra co ma mon nao trung ko
		if(stricmp(dsloptc.Lop[i]->MAMH, mamon) == 0)
		{// trung roi ne
			BaoLoiVaNgu("Da co lop dang ky", 1500);
			return false;
		}
	}
	return true;
}

int dem = 1;

void XuatDanhSachMonTheoBang(MONHOC *dsmh, int x, int y, int chieudai, int chieurong, int socot, int n)
{
	gotoxy(1, 1);
	int tempy = y + 2;
	int tempx= x + 3;
	int cottb = chieurong / socot;
	int i;
	for(i = 0; i < n; i++)
	{
		if(i < chieudai - 2)
		{
			tempx = x;	
			tempy += 1;// tang chi sodong len	
			gotoxy(tempx += (cottb / 2) - (DemSo(i + 1) / 2), tempy);		
			cout << i + 1;
			
			tempx = x;// reset lai x
			gotoxy(tempx += cottb + (cottb / 2) - (DemChuoi(dsmh[i].MAMH) / 2), tempy);
			cout << dsmh[i].MAMH;
			
			tempx = x;// reset lai x
			gotoxy(tempx += 2 * cottb + (cottb / 2) - (DemChuoi(dsmh[i].TENMH) / 2), tempy);			
			cout << dsmh[i].TENMH;
			
			tempx = x;// reset lai x
			if(DemSo(dsmh[i].STCLT) % 2 != 0)
			{
				gotoxy(tempx += 3 * cottb + (cottb / 2)- (DemSo(dsmh[i].STCLT) / 2) + 1, tempy);
			}
			else{
				gotoxy(tempx += 3 * cottb + (cottb / 2)- (DemSo(dsmh[i].STCLT) / 2) , tempy);
			}			
			cout << dsmh[i].STCLT;
			
			tempx = x;// reset lai x
			if(DemSo(dsmh[i].STCTH) % 2 != 0)
			{
				gotoxy(tempx += 4 * cottb + (cottb / 2)- (DemSo(dsmh[i].STCTH) / 2) + 1, tempy);
			}else{
				gotoxy(tempx += 4 * cottb + (cottb / 2)- (DemSo(dsmh[i].STCTH) / 2), tempy);
			}			
			cout << dsmh[i].STCTH;
		}
	}
	int tung = 5, hoanh = truchoanh + 81;
	gotoxy(hoanh, tung);// cho con tro nhay ve vi tri dau dong
	while(true)
	if(kbhit())
	{		
		char c = getch();	
		if(c == KEY_ESC)
		{
			return;
		}
	}
			
}

/*
void XuatDanhSachMonTheoBang(DSMH dsmh, int x, int y, int chieudai, int chieurong, int socot)
{
	gotoxy(1, 1);
	int tempy = y + 2;
	int tempx= x + 3;
	int cottb = chieurong / socot;
	int i;
	for(i = 0; i < dsmh.n; i++)
	{
		if(i < chieudai - 2)
		{
			tempx = x;	
			tempy += 1;// tang chi sodong len	
			gotoxy(tempx += (cottb / 2) - (DemSo(i + 1) / 2), tempy);		
			cout << i + 1;
			
			tempx = x;// reset lai x
			gotoxy(tempx += cottb + (cottb / 2) - (DemChuoi(dsmh.mh[i].MAMH) / 2), tempy);
			cout << dsmh.mh[i].MAMH;
			
			tempx = x;// reset lai x
			gotoxy(tempx += 2 * cottb + (cottb / 2) - (DemChuoi(dsmh.mh[i].TENMH) / 2), tempy);			
			cout << dsmh.mh[i].TENMH;
			
			tempx = x;// reset lai x
			if(DemSo(dsmh.mh[i].STCLT) % 2 != 0)
			{
				gotoxy(tempx += 3 * cottb + (cottb / 2)- (DemSo(dsmh.mh[i].STCLT) / 2) + 1, tempy);
			}
			else{
				gotoxy(tempx += 3 * cottb + (cottb / 2)- (DemSo(dsmh.mh[i].STCLT) / 2) , tempy);
			}			
			cout << dsmh.mh[i].STCLT;
			
			tempx = x;// reset lai x
			if(DemSo(dsmh.mh[i].STCTH) % 2 != 0)
			{
				gotoxy(tempx += 4 * cottb + (cottb / 2)- (DemSo(dsmh.mh[i].STCTH) / 2) + 1, tempy);
			}else{
				gotoxy(tempx += 4 * cottb + (cottb / 2)- (DemSo(dsmh.mh[i].STCTH) / 2), tempy);
			}			
			cout << dsmh.mh[i].STCTH;
		}
	}
	int tung = 5, hoanh = truchoanh + 81;
	gotoxy(hoanh, tung);// cho con tro nhay ve vi tri dau dong
	
	if(kbhit())
	{		
		char c = getch();	
		if(c == KEY_ESC)
		{
			return;
		}
	}
			
}
*/
int demmh = 0;

void DocMonHocVaoMang(NODEMH *Root, MONHOC *&dsmh, int &n)
{
	if(Root != NULL)
	{
		DocMonHocVaoMang(Root->Left, dsmh, n);	
		strcpy(dsmh[demmh].MAMH , Root->DATA.MAMH);
		strcpy(dsmh[demmh].TENMH , Root->DATA.TENMH);
		dsmh[demmh].STCLT = Root->DATA.STCLT;
		dsmh[demmh].STCTH = Root->DATA.STCTH;
		demmh++;
		DocMonHocVaoMang(Root->Right, dsmh, n);
	}
	n = demmh;// cap nhat so luong mon hoc
}
/*
void DocMonHocVaoMang(NODEMH *Root, DSMH &dsmh)
{
	if(Root != NULL)
	{
		DocMonHocVaoMang(Root->Left, dsmh);	
		strcpy(dsmh.mh[demmh].MAMH , Root->DATA.MAMH);
		strcpy(dsmh.mh[demmh].TENMH , Root->DATA.TENMH);
		dsmh.mh[demmh].STCLT = Root->DATA.STCLT;
		dsmh.mh[demmh].STCTH = Root->DATA.STCTH;
		demmh++;
		DocMonHocVaoMang(Root->Right, dsmh);
	}
	dsmh.n = demmh;// cap nhat so luong mon hoc
}
*/
void ThemMonHoc(NODEMH *&Root)
{					
	MONHOC mh;							
	NhapMonHoc(Root, mh);// Nhap va check Ma Mon Hoc
	if(MenuTuyChinh(YESNO, 2) != 1)
	{
		BaoLoiVaNgu("Them Loi", 2000);
		return;
	}	
	ThemNodeVaoCay_DeQuy(Root, mh);
	BaoLoiVaNgu("Them thanh cong", 2000);
	SaveDanhSachMonHoc(Root);
}

void XoaMonHoc(NODEMH *&Root, DSLOPTC dsloptc)
{
	VeTuyChonDuoi(1, 25, "ESC: Thoat ||  ENTER: Nhap tiep   **Luu y: chi sai duoc khi nhap sai ma mon");				
	char *x; x= new char; bool h, check = false;
	do
	{ 
		h = true;
		NhapChuoi("\nNhap Ma mon hoc can xoa: ", x);
		// kiem tra ma mon co ton tai
		NODEMH *p = KiemTraMaMonTrung(Root, x);
		if(p == NULL)
		{ 
			h = false;						
			BaoLoiVaNgu("Ma mon khong ton tai!", 100);																		
			HamThoat(check);
			if(check == true) return;				
			continue;
		}						
		h = KiemTraMonHocKhiXoa(dsloptc, x); // xem co lop tin chi nao dk ko
	}while(h == false);
							
	if(MenuTuyChinh(YESNO, 2) != 1)
	{// chon No
		BaoLoiVaNgu("Xoa khong thanh cong!", 2000);
		return;
	}
	// chon yes
	// thuc hien xoa
	XoaMonHocTrongCay_DeQuy(Root, x);
	BaoLoiVaNgu("Xoa thanh cong!", 2000);
	SaveDanhSachMonHoc(Root);						
}

void SuaMonHoc(NODEMH *&Root, DSLOPTC dsloptc)
{
	char x[10]; NODEMH *p;
	bool h, check = false;
	VeTuyChonDuoi(1, 25, "ESC: Thoat ||  ENTER: Nhap tiep   **Luu y: chi sai duoc khi nhap sai ma mon");
	do
	{ 
		h = true;
		NhapChuoi("\nNhap vao ma mon can sua doi: ", x);
		p = KiemTraMaMonTrung(Root, x);
		if(p == NULL)// ko tim thay mon
		{
			h = false;
			BaoLoiVaNgu("Mon hoc khong ton tai", 100);
			HamThoat(check);
			if(check == true) return;							
		}
		BoolChieuDai(h, x, 10); // Check chieu dai cua mamon
		h = KiemTraMonHocKhiXoa(dsloptc, x); // xem co lop tin chi nao dk ko									
	}while(h == false);		
	system("cls");	
	CapNhatMonHoctrongCay(p);
	
	if(MenuTuyChinh(YESNO, 2) != 1)
	{
		BaoLoiVaNgu("Cap nhat Loi!", 2000);
		return;
	}
	BaoLoiVaNgu("Cap nhat Thanh cong!", 2000);
	SaveDanhSachMonHoc(Root);				
}

void SwapMonHoc(MONHOC &a, MONHOC &b)
{
	MONHOC temp = a;
	a = b; 
	b = temp;
}
/*
void SapXepMangTangDanTheoTen(DSMH &dsmh)
{
	for(int i = 0; i < dsmh.n - 1; i++)
	{
		for(int j = i + 1; j < dsmh.n; j++)
		{
			if(stricmp(dsmh.mh[j].TENMH, dsmh.mh[i].TENMH) < 0)// ten sau nho hon ten truoc thi swap 2 MON HOC VS NHAU
			{
				SwapMonHoc(dsmh.mh[j], dsmh.mh[i]);
			}
		}
		
	}
}
*/

void SapXepMangTangDanTheoTen(MONHOC *&dsmh, int n)
{
	for(int i = 0; i < n - 1; i++)
	{
		for(int j = i + 1; j < n; j++)
		{
			if(stricmp(dsmh[j].TENMH, dsmh[i].TENMH) < 0)// ten sau nho hon ten truoc thi swap 2 MON HOC VS NHAU
			{
				SwapMonHoc(dsmh[j], dsmh[i]);
			}
		}
		
	}
}

void HienThiDanhSachMon(NODEMH *Root)
{
	//DSMH dsmh;
	//dsmh.mh = new MONHOC[1000];
	MONHOC *dsmh;
	dsmh = new MONHOC[1000];
	int n;
	demmh = 0;// reset bien dem trong Ham o duoi
	DocMonHocVaoMang(Root, dsmh, n);
	SapXepMangTangDanTheoTen(dsmh, n);
	//DocMonHocVaoMang(Root, dsmh);
	//SapXepMangTangDanTheoTen(dsmh);
	
	SetBGColor(3);
	printf("\n\t\t                            DANH SACH MON HOC                            \n\n");
	textcolor(15);	
															
	//VeTuyChonDuoi(100, 5, "ESC : Thoat.  Luu y: Bang chi duoc xem !");
	gotoxy(100, 5);
	printf("ESC : Thoat");
	gotoxy(1, 1);
	// dua vao nhung gi vua nhap va in ra
	int chieudai = 20, chieurong = 90, socot = 5; 
	//VeBangDanhSach(truchoanh, tructung, dsmh.n + 3, chieurong, socot);// ve bang co 90 o, 20 dong, 5 cot
	VeBangDanhSach(truchoanh, tructung, n + 3, chieurong, socot);// ve bang co 90 o, 20 dong, 5 cot
	char tieude[5][100] = {"STT", "MA MON", "TEN MON", "CHI LY THUYET", "CHI THUC HANH"};
	InTieuDe(truchoanh, tructung, chieurong, socot, tieude, 5);			
										
	//XuatDanhSachMonTheoBang(dsmh, truchoanh, tructung, dsmh.n + 3, chieurong, socot);
	XuatDanhSachMonTheoBang(dsmh, truchoanh, tructung, n + 3, chieurong, socot, n);
	// giai phong mang mon hoc
	delete []dsmh;			
	getch();
}

// giai phong cay
void GiaiPhongCayMonHoc_DeQuy(NODEMH *&Root)
{
	if(Root != NULL) // duyet LRN de tim dc NODE la de xoa ez nhat
	{
		GiaiPhongCayMonHoc_DeQuy(Root->Left);
		GiaiPhongCayMonHoc_DeQuy(Root->Right);
		
		delete Root;
		Root = NULL;// de khi giai phong het r. Neu co thao tac xu ly thi se ko bi loi ngang
	}
}

//=========================================================HAM XU LY LOP TIN CHI===================================================================

// ===========================KIEM TRA TRONG 1 MA MON HOC CO 2 NHOM NAO BI TRUNG KO===========================================
// nhap NHOM va CHECK xem Trong MAMON nay co NHOM nao TRUNG voi NHOM nay hay k
void Check_NhapNhom(DSLOPTC dsloptc, NODEMH *Root, LOPTC &lop)
{			
	bool h;
		// Tim then nien khoa bang cach so sanh ll tung thang trong dsloptc voi then nien khoa vua nhap o tren
		if(Search_NienKhoa(dsloptc, lop.NIENKHOA) != -1){// Tim thay nien khoa roi
		// Tim xem then hoc ky o tren minh nhap co trong Lop nay hay ko
			if(Search_HocKy(dsloptc, lop.HOCKY) != -1){// tim thay hoc ky roi
					// Tim MAMH co trong HOCKY nay hay ko(viet ham rieng)
					if(Search_MaMonTrongLopTinChi(dsloptc, lop.MAMH) != -1)
					{// Da tim thay MAMH trong HOCKY nay 
					do{
						bool check = false;
						h = true; // cap nhat lai h
						fflush(stdin);
						NhapSoNguyen("Nhap Nhom: ", lop.NHOM);
						BoolKiemTraDieuKien(h, 1, 50, lop.NHOM);
						// Kiem tra NHOM trong hoc ky nay co bi trung vs NHOM nao hay ko(1, 2, 3)
						if(Search_Nhom(dsloptc, lop) != -1){// tim thay Nhom
							// da tim thay
							BaoLoiVaNgu("Nhom da bi trung!", 1500);
							h = false;
							printf("\nESC: Thoat || ENTER: Nhap Tiep");
							HamThoat(check);
							if(check == true) break;
						}			
					}while(h == false);
						
					}
					else{// KHONG tim thay MAMH nao ne nen nhap NHOM thoai mai !
						do
						{
							h = true;
							fflush(stdin);
							NhapSoNguyen("Nhap Nhom: ", lop.NHOM);
							BoolKiemTraDieuKien(h, 1, 50, lop.NHOM);
						}while(h = false);
							
					}
				}else
				{// KHONG tim thay HOC KY nao ne nen nhap Nhom thoai mai !
					do
					{
						h = true;
						fflush(stdin);
						NhapSoNguyen("Nhap Nhom: ", lop.NHOM);
						BoolKiemTraDieuKien(h, 1, 50, lop.NHOM);							
					}while(h == false);
					
				}
	
			}else{// Khong tim thay NIEN KHOA NAO
				do{
					h = true;
					fflush(stdin);
					NhapSoNguyen(" Nhap vao Nhom: ", lop.NHOM);
					BoolKiemTraDieuKien(h, 1, 50, lop.NHOM);		
				}while(h == false);
			}
	
}

int TaoSoNgauNhien()
{// sinh so trong doan tu (1, 5000)
	srand(time(0));// reset time
	int a = 1 + rand() % 5000;
	return a;
}

void TaoMaSoLopTinChi(DSLOPTC ds, LOPTC &x)
{
	
	bool check = false;
	int h, a;
	while(check == false)
	{
		check = true;
		a = TaoSoNgauNhien(); 
		h = Search_MaLopTC(ds,a);//neu h tra ve true thi ma so moi tao da trung khoi tao lai;
		if(h != -1){
			check = false;
		}
	}
	x.MALOPTC = a; // cap nhat cho x
}
/*
void XuatLopTC(LOPTC lop)
{
	cout << "\n Ma lop tin chi: " <<  lop.MALOPTC;
	cout << "\n Nien khoa: "<< lop.NIENKHOA;
	cout << "\n Hoc ky: " << lop.HOCKY;
	cout << "\n Ma mon hoc: "<< lop.MAMH;
	cout << "\n Nhom: " << lop.NHOM;
	cout << "\n Sinh vien toi da: "<< lop.SVMAX <<" sinh vien ";
	cout << "\n Sinh vien toi thieu: "<< lop.SVMIN <<" sinh vien ";
	SetBGColor(4);
	cout << "\n Sinh vien dang ky: "<< lop.pDSDK.n <<" sinh vien " << endl;
	textcolor(15);
}
*/
// xoa lop tc dua vao ma so
void XoaLopTC_MaSo(DSLOPTC &dsloptc, int maso){
	int i = Search_MaLopTC(dsloptc, maso);// lay chi so cua lop co MALOPTC = maso;
	if(i == -1)
	{
	 BaoLoiVaNgu("ko ton tai", 1500);
	 return;	
	}else 
	{
		int check = MenuTuyChinh(YESNO, 2);
		if(check != 1)
		{// la No
			BaoLoiVaNgu("Xoa That bai!", 1500);
			return;
		}
		delete dsloptc.Lop[i];
		for(int j = i + 1; j < dsloptc.n; j++)
		{
			dsloptc.Lop[j - 1] = dsloptc.Lop[j];
		}
		dsloptc.n--;
		BaoLoiVaNgu("Xoa thanh cong", 1500);
	
				
	}
}

//NIENKHOA(trung dc) HOCKY(trung dc) MAMH(phai ton tai) nhung phai ko ton tai trong hocky nay cua nien khoa nay
void NhapThongTinLopTinChi(DSLOPTC dsloptc, NODEMH *Root, LOPTC &a)
{
	TaoMaSoLopTinChi(dsloptc, a); // tao tu dong
	bool h ;
	do{
		fflush(stdin);
		h = true;
		NhapSoNguyen("Nhap nien khoa: ", a.NIENKHOA);
		BoolKiemTraDieuKien(h, 2000, 2030, a.NIENKHOA);
	}while(h == false);
	do{	
		fflush(stdin);
		h = true;
		NhapSoNguyen("\n Nhap hoc ky: ", a.HOCKY);
		BoolKiemTraDieuKien(h, 1, 3, a.HOCKY);
	}while(h == false);
	do{	
		fflush(stdin);	
		h = true;
		NhapChuoi("\n nhap ma mon hoc: ", a.MAMH);
		ChuanHoaMa(a.MAMH);
		NODEMH *p = KiemTraMaMonTrung(Root, a.MAMH);
		if(p == NULL)
		{	bool check = false;
			h = false;
			BaoLoiVaNgu("khong ton tai!", 1500); // Nhap lai
			printf("\nESC: Thoat || ENTER: Nhap Tiep");
			HamThoat(check);
			if(check == true) return;						
		}
		
		/*
		char *x = new char;
		NhapChuoi("\nNhap ten mon: ", x);
		NODEMH *p = LayRaMaMonBangTenMon(Root, x);
		if(p == NULL)
		{	
			bool check = false;
			h = false;
			BaoLoiVaNgu("Khong ton tai", 500);
			printf("\n ENTER: Nhap lai || ESC: Thoat");
			HamThoat(check);
			if(check == true) return;
			continue;			
		}
		strcpy(a.MAMH, p->DATA.MAMH);// dua vao trong loptc		
		*/		
	}while(h == false);	
	// chay xuong nay chan chan la ma mon ton tai.
	// Bay h ta chi viec vao trong dsloptc check Nhom trong mon
	Check_NhapNhom(dsloptc, Root, a);	
	do{
		fflush(stdin);
		h = true;
		NhapSoNguyen("\n Nhap so sinh vien toi da: ", a.SVMAX);
		BoolKiemTraDieuKien(h, 5, 200, a.SVMAX);		
	}while(h == false);
	
	do{
		fflush(stdin);
		h = true;
		NhapSoNguyen("\n Nhap so sinh vien toi thieu: ", a.SVMIN);
		BoolKiemTraDieuKien(h, 1, a.SVMAX, a.SVMIN);// SVMIN phai >= 1 va SVMIN <= SVMAX			
	}while(h == false);	
	KhoiTaoDanhSachDangKy(a.pDSDK);// Khoi tao danh sach dang ky
	a.pDSDK.n = 0;// khoi tao bien dem thi ben duoi moi ++ duoc
}

void ThemLopTinChi(DSLOPTC &ds, LOPTC a)
{
	LOPTC lop;
	if (ds.n==LOPTCMAX)
	{
		BaoLoiVaNgu(" Danh sach day!", 1200); // Nhap lai
		return;
	}
	else
	{ 
		int check = MenuTuyChinh(YESNO, 2);
		if(check != 1)
		{// La NO
			BaoLoiVaNgu("Them Loi!", 1300);
			return;
		}
		else
		{
			ds.Lop[ds.n] = new LOPTC;	
			*ds.Lop[ds.n] = a;// them vao cuoi danh sách
			ds.n++;
		}
		
	}
}

void XuatDanhSachLopTC(DSLOPTC ds){
	int dem1 = 1;
	for(int i = 0 ; i < ds.n; i++){	
		cout << "\t" << dem1++ << "\t" << ds.Lop[i]->MALOPTC << "\t" << ds.Lop[i]->NIENKHOA 
		<< "\t\t" << ds.Lop[i]->HOCKY << "\t" << ds.Lop[i]->MAMH << "\t" << ds.Lop[i]->NHOM 
		<< "\t" << ds.Lop[i]->SVMIN << "\t" << ds.Lop[i]->SVMAX << "\t";
		SetBGColor(4);
		cout << ds.Lop[i]->pDSDK.n << endl << endl;
		textcolor(15);
	}
	
}

void CapNhatLopTinChi(LOPTC &a)
{
	bool h;
	do{
		system("cls");
		h = true;
		printf("\n Nhap so sinh vien toi da: ");
		a.SVMAX = NhapSo();
		BoolKiemTraDieuKien(h, 30, 200, a.SVMAX);// SVMAX >= 30 va SVMAX <=200
	}while(h == false);	
	do{
		system("cls");
		h = true;
		printf("\n Nhap so sinh vien toi thieu: ");
		a.SVMIN = NhapSo();
		BoolKiemTraDieuKien(h, 1, a.SVMAX, a.SVMIN);// SVMIN phai >= 1 va SVMIN <= SVMAX
	}while(h == false);
}

//=========================================================HAM XU LY SINH VIEN===================================================================


// B2: Khoi tao
void KhoiTaoDanhSachSinhVien(LISTSV &ds){
	ds.pHead = NULL;
	ds.pTail = NULL;
}

// B3: tao NODE
NODESV* TaoNodeSinhVien(SINHVIEN sv){
	NODESV *p = new NODESV;
	if(!p){
		BaoLoiVaNgu("Khong du bo nho", 1500);
		return NULL;
	}
	p->DATA = sv;
	p->pNext = NULL;
	return p;
}

// B4: Them vao dau cuoi.
void ThemSinhVienVaoDau(LISTSV &ds, NODESV* sv){
	if(ds.pHead == NULL)
	{// danh sach rong
		ds.pHead = ds.pTail = sv;
	}
	else{
		sv->pNext = ds.pHead;
		ds.pHead = sv; // cap nhat no chinh la node dau
	}
}
void ThemSinhVienVaoCuoi(LISTSV &ds, NODESV* sv){
	if(ds.pHead == NULL)
	{
		ds.pHead = ds.pTail = sv;
	}
	else
	{
		ds.pTail ->pNext = sv; // pTail tro next toi p
		ds.pTail = sv; // Cap nhat pTail chính là p
	}
}

void Insert_Order_SinhVien(LISTSV &dssv, NODESV *sv)
{
   NODESV *p, *t, *s;  // t la nut truoc, s la nut sau
   p = new NODESV;
   p->DATA = sv->DATA;// p giu gia tri cua then ms them vao
   // Vong for nay chay de tim then co masv lon hon then moi them vao. muc dich la de them vao sau nut do
   for(s = dssv.pHead; s != NULL && stricmp(s->DATA.MASV, sv->DATA.MASV) < 0; t=s, s = s->pNext)   ;
	if(s == dssv.pHead)  // them nut vao dau danh sach lien ket
   	{
      	p->pNext = dssv.pHead;
     	dssv.pHead = p;
   	}
   	else // them nut p vao truoc nut s
  	 {
      	p->pNext= s;
      	t->pNext= p;
   	}
}

void ThemSinhVienCoThuTu(LISTSV &dssv, NODESV *sv)
{
	if(dssv.pHead == NULL) // neu danh sach rong them vao dau
	{
		ThemSinhVienVaoDau(dssv, sv); return;
	}
	
	Insert_Order_SinhVien(dssv, sv);
}

void XuatSinhVien(SINHVIEN sv){
	
	cout << "\n Ma sinh vien: " << sv.MASV;
	cout << "\n Ma Lop: " << sv.MALOP;		
	cout << "\n Nam nhap hoc : " << sv.NamHoc;
	cout << "\n Ho : " << sv.HO;
	cout << "\n Ten : " << sv.TEN;
	cout << "\n Phai : " << sv.PHAI;
	cout << "\n So dien thoai : " << sv.SODT;
	
}

int DemTu(char *k)
{
	int	dem = 0;
 	ChuanHoaChuoi(k);// VD : Quang          NHU   ta dung de dua ve dang: Quang NHU
	for(int i = 0; i < strlen(k); i++)
	{
		if(k[i] != ' ' && k[i + 1] == ' ' && k[i + 2] != ' ')// Qua' 2 tu thi return
		{
			dem++;
		}
	}
	return dem;
}

// B5: Nhap sinh vien va CHECK MA SV 
void NhapSinhVienVaoLop(LISTSV dssv, SINHVIEN &sv)
{
	system("cls");
	bool h, check = false;
	do{
		h = true;
		NhapChuoi("\n Nhap ma lop: ", sv.MALOP);
		BoolChieuDai(h, sv.MALOP, MALOPMAX);// kiem tra MALOP ko dc lon hon MALOPMAX
		BoolKhoangTrang(h, sv.MALOP);// kiemtra MALOP ko dc chua khoang trang
	}while(h == false);
	ChuanHoaMa(sv.MALOP); // dua ve dang nguyen mau
	do{
		h = true;
		fflush(stdin);
		printf( "\nNhap ma sinh vien(rong la ket thuc): ");
		gets(sv.MASV);
		if(strlen(sv.MASV) < 1)// nhap vao rong
		{
			return;// thoat ra vi chuoi rong
		}
		BoolChieuDai(h, sv.MASV, MASVMAX);// ham nay se thay doi h == false neu lon hon MASVMAX
		BoolKhoangTrang(h, sv.MASV);  // kiemtra MASV ko dc chua khoang trang
		ChuanHoaMa(sv.MASV); // dua ve dang nguyen mau
		NODESV *p = Search_MaSV(dssv, sv.MASV);
		if(p != NULL)// ktra ma sinh vien trong danh sach
		{
		 	h = false; // da bi trung
		 	BaoLoiVaNgu("Ma bi trung", 1500);
		 	printf("\nESC: Thoat || ENTER: Nhap Tiep");
			HamThoat(check);
			if(check == true) break;
		}
	}while(h == false);	
	// Nhap nam nhap hoc.
	do{
		h = true;
		NhapSoNguyen("\n Nhap nam nhap hoc: ", sv.NamHoc);
		BoolKiemTraDieuKien(h, 2000, 2030, sv.NamHoc);// NamHoc >= 2000 va NamHoc <= 2019
	}while( h == false);

	do{
		h = true;
		NhapChuoi("\n Nhap Ho: ", sv.HO);
		if(KiemTraSoTrongChuoi(sv.HO) == true){// phat hien co SO trong chuoi
			h = false;
			BaoLoiVaNgu("Chi chua ky tu", 1500);
		}
		//them 1 khoang trang vao cuoi chuoi de de check
		int n = strlen(sv.HO);
		//ThemPhanTu(sv.HO, n, n, ' ');
	//	BoolKiemTraTu(h, sv.HO);		
		ChuanHoaChuoi(sv.HO);
		
		BoolChieuDai(h, sv.HO, HOMAX);
	}while(h == false);
	
	do{
		h = true;
		NhapChuoi("\n Nhap Ten: ", sv.TEN);
		if(KiemTraSoTrongChuoi(sv.TEN) == true){// phat hien co SO trong chuoi
			h = false;
			BaoLoiVaNgu("Chi chua ky tu", 1500);
		}
		//them 1 khoang trang vao cuoi chuoi de de check
		int n = strlen(sv.TEN);
	//	ThemPhanTu(sv.TEN, n, n, ' ');
	//	BoolKiemTraTu(h, sv.TEN);
		ChuanHoaChuoi(sv.TEN);
		BoolChieuDai(h, sv.TEN, TENMAX);// TEN phai <= 30 kytu
	}while(h == false);	
	
	do{
		h = true;
		int n;
		printf("\n Chon Phai: ");
		printf(" 1. Nam");
		printf(" || 2. Nu");
		NhapSoNguyen("\n Nhap lua chon: ", n);
		switch(n)
		{
			case 1: 
			{
				strcpy(sv.PHAI, "Nam");	break;
			};
			case 2: 
			{
				strcpy(sv.PHAI, "Nu");	    break;
			};
			default : {
				h = false; BaoLoiVaNgu("Lua chon sai!", 1500);
			}
		}
	}while(h == false);		
		
	do{			
		h = true;
		NhapChuoi("\n Nhap so dien thoai: ", sv.SODT);
		if(KiemTraKyTuTrongChuoi(sv.SODT) == true)
		{// co kytu
			BaoLoiVaNgu("Loi!. Chi Nhap So", 1500);
			h = false;
			continue;
		}
		ChuanHoaMa(sv.SODT);// loai bo all khoang trang	
		BoolChieuDai(h, sv.SODT, 15);	// SODT co do dai ko dc qua 15 kytu					
	}while(h == false);
}


/*
// VIET HAM INPUT/OUTPUT
void InPut(LISTSV &ds){
	KhoiTaoDanhSachSinhVien(ds);
	fflush(stdin);
	int m;
	//NhapSoNguyen("\n Nhap so luong sinh vien can them: ", ds.n);
	printf("\n Nhap so luong sinh vien can them: ");
	m = NhapSo();
	for(int i = 1; i <= m; i++){
		SINHVIEN sv;
		printf("\n Nhap Sinh vien thu %d", i);
		NhapSinhVien(ds, sv);
		// bo vao trong node
		NODESV *p = TaoNodeSinhVien(sv);
		ThemSinhVienVaoCuoi(ds, p);
		ds.n++;// cap nhat so luong phan tu
	}
}
*/
void XuatDanhSachSinhVien(LISTSV dssv){
	int dem = 1;	
	for(NODESV *p = dssv.pHead; p != NULL ; p = p->pNext)
	{		
		cout << "\t\t" << dem++ << "\t" << p->DATA.MASV << "\t" << p->DATA.HO
		<< "\t" << p->DATA.TEN << "\t" << p->DATA.PHAI << "\t" << p->DATA.MALOP
		<< "\t" << p->DATA.NamHoc << "\t   " << p->DATA.SODT << endl << endl;		
	}
}

//B6: Nhung xu ly can thiet

void NhapSinhVienKhiUpdate(SINHVIEN &sv)
{
	system("cls");
	bool h;		
	
	do{
		h = true;
		NhapChuoi("\n Nhap ma lop: ", sv.MALOP);
		ChuanHoaMa(sv.MALOP); // dua ve dang nguyen mau
		BoolChieuDai(h, sv.MALOP, 15);// MALOP phai <= 15 kytu
	}while(h = false);
	
	do{system("cls");
		h = true;
		NhapSoNguyen("\n Nhap nam nhap hoc: ", sv.NamHoc);
		BoolKiemTraDieuKien(h, 2000, 2030, sv.NamHoc);// NamHoc >= 2000 va NamHoc <= 2019
	}while( h == false);
	
	do{
		h = true;
		NhapChuoi("\n Nhap Ho: ", sv.HO);
		if(KiemTraSoTrongChuoi(sv.HO) == true){// phat hien co SO trong chuoi
			h = false;
			BaoLoiVaNgu("Chi chua ky tu", 1500);
		}		
		//them 1 khoang trang vao cuoi chuoi de de check
		int n = strlen(sv.HO);
		//ThemPhanTu(sv.HO, n, n, ' ');
		//BoolKiemTraTu(h, sv.HO);
		ChuanHoaChuoi(sv.HO);
		BoolChieuDai(h, sv.HO, 30);
	}while(h == false);
	
	do{
		h = true;
		NhapChuoi("\n Nhap Ten: ", sv.TEN);
		if(KiemTraSoTrongChuoi(sv.TEN) == true){// phat hien co SO trong chuoi
			h = false;
			BaoLoiVaNgu("Chi chua ky tu", 1500);
		}
		//them 1 khoang trang vao cuoi chuoi de de check
		int n = strlen(sv.TEN);
		//ThemPhanTu(sv.TEN, n, n, ' ');
		//BoolKiemTraTu(h, sv.TEN);
		ChuanHoaChuoi(sv.TEN);
		BoolChieuDai(h, sv.TEN, 30);// TEN phai <= 30 kytu
	}while(h == false);	
	
	do{
		h = true;
		int n;
		printf("\n Chon Phai: ");
		printf(" 1. Nam");
		printf(" || 2. Nu");
		NhapSoNguyen("\n Nhap lua chon: ", n);
		switch(n)
		{
			case 1: 
			{
				strcpy(sv.PHAI, "Nam");	break;
			};
			case 2: 
			{
				strcpy(sv.PHAI, "Nu");	    break;
			};
			default : {
				h = false; BaoLoiVaNgu("Lua chon sai!", 1500);
				system("cls");
			}
		}
	}while(h == false);		

	do{			
		h = true;
		NhapChuoi("\n Nhap so dien thoai: ", sv.SODT);
		ChuanHoaMa(sv.SODT);// loai bo all khoang trang	
		BoolChieuDai(h, sv.SODT, 15);	
		if(KiemTraKyTuTrongChuoi(sv.SODT) == true)
		{// co kytu
			BaoLoiVaNgu("Loi!. Chi Nhap So", 1500);
			h = false;
		}			
	}while(h == false);
}
// sua sinh vien dua vao ma sinh vien
void CapNhatSinhVien(LISTSV &ds, char *ma)
{
	for(NODESV *p = ds.pHead; p != NULL; p = p->pNext)
	{
		if(stricmp(p->DATA.MASV, ma) == 0)
		{// ma sv ton tai. vao day va sua thoi
			NhapSinhVienKhiUpdate(p->DATA);
		}
	}
}
// xoa sinh vien co ma so can tim 
void XoaSinhVienDau(LISTSV &ds)
{
	if(ds.pHead != NULL)
	{
		// LIST co 2 phan tu tro len
		NODESV *p = ds.pHead;
		ds.pHead = ds.pHead->pNext; // chay qua then phia sau de co the giai phong bo nho ma ko bi loi
		delete p;
	}	
}

void XoaSinhVienCuoi(LISTSV &ds)
{
	NODESV *truoc;
	// Tim node phia truoc node pTail
	for(NODESV *p = ds.pHead; p != NULL; p = p->pNext)
	{
		// kiem tra k co phai la pTail hay ko
		if( p->pNext == NULL)
		{// la pTai
			ds.pTail = truoc;// cho then pTail tro den Node phia sau
			truoc->pNext = NULL;
			delete p; // xoa p
			return;
		}
		truoc = p;
	}
}

void XoaSinhVienTheoMa(LISTSV &ds, char *x) // xoa sv dua theo ma sinh vien
{
	NODESV *truoc;
	// TH Dac biet ktra neu no nam o dau danh sach
	if(stricmp(ds.pHead->DATA.MASV, x) == 0){
		XoaSinhVienDau(ds);
		return;
	}
	// TH ktra neu no nam o cuoi danh sach
	if(stricmp(ds.pTail->DATA.MASV, x) == 0){
		XoaSinhVienCuoi(ds);
		return;
	}// Th2 xoa Neu sinh vien nam o giua
	for(NODESV *p = ds.pHead; p != NULL; p = p->pNext)
	{
		if(stricmp(p->DATA.MASV, x) == 0)
		{// da tim thay
			truoc->pNext = p->pNext;// quang moi lien ket cho thang phia sau
			delete p; // xoa then q
			return;
		}
		truoc = p;
	}
	
}

void XemSinhVienBangMaLop(LISTSV dssv, char *malop)
{
	int dem = 1;
	for(NODESV *p = dssv.pHead; p != NULL; p = p->pNext)
	{
		if(stricmp(p->DATA.MALOP, malop) == 0)// tim dc ma lop
		{
			cout << "\t\t" << dem++ << "\t" << p->DATA.MASV << "\t" << p->DATA.HO
		<< "\t" << p->DATA.TEN << "\t" << p->DATA.PHAI << "\t" << p->DATA.MALOP
		<< "\t" << p->DATA.NamHoc << "\t   " << p->DATA.SODT << endl << endl;
		}
	}
}

// B7: Giai phong danh sach lien ket
void GiaiPhongDanhSachSinhVien(LISTSV &ds){
	for(NODESV *p = ds.pHead; p != NULL; p = p->pNext){
		NODESV *k = p;
		ds.pHead = p->pNext;// cho then phead nhay sang node tt
		delete k;
	}
}

//======================================================================XU LY FILE===================================================================================

/*------------------------MON HOC--------------------------*/

// Doc all cac mon hoc vao trong file
void DocMonHocVaoFile(FILE *f, NODEMH *Root)
{
	if(Root != NULL) // duyet theo thu tu tang dan theo ma monhoc
	{
		DocMonHocVaoFile(f, Root->Left);
		
		DocMonHocVaoFile(f, Root->Right);
	}
	fwrite(&Root->DATA, sizeof(MONHOC), 1, f);// Luu mon hoc nay vao trong file
}

void SaveDanhSachMonHoc(NODEMH *Root)
{
	FILE * f;
 	if ((f=fopen("Data/DSMH.txt","wb"))==NULL)
 	{  
		BaoLoiVaNgu ("Loi mo file de ghi", 1500); return ;
 	}
	DocMonHocVaoFile(f, Root);
 	fclose(f);
	//BaoLoiVaNgu ("Da ghi xong danh sach vao file", 1500);
}

void OpenFileCayMonHoc(NODEMH *&Root) {
 FILE * f; MONHOC mh;
 if ((f=fopen("Data/DSMH.txt","rb"))==NULL)
 {  BaoLoiVaNgu ("Loi mo file de doc", 1500); return ;
 }
 //Root-> = 0;
 while  (!feof(f)) {
 	if(fread (&mh, sizeof (MONHOC), 1, f)!=0)
 	ThemNodeVaoCay_DeQuy(Root, mh);
 //	Root->n ++;
 }
    
 fclose(f);
}


/*------------------------LOP TIN CHI--------------------------*/

void SaveFileLopTinChi(DSLOPTC ds)
{
 	FILE * f;
 	if ((f=fopen("Data/DSLTC.txt","wb"))==NULL)
 	{  
	 	BaoLoiVaNgu ("Loi mo file de ghi", 1500); return ;
 	}
 	for (int i = 0; i < ds.n; i++)
	fwrite(ds.Lop[i], sizeof(LOPTC), 1, f);
 	fclose(f);
}

void OpenFileDanhSachLopTinChi(DSLOPTC &dsloptc) {
 FILE * f; LOPTC lop;
 if ((f=fopen("Data/DSLTC.txt","rb"))==NULL)
 {  BaoLoiVaNgu ("Loi mo file de doc", 1500); return ;
 }
 dsloptc.n = 0;
 while (fread (&lop, sizeof (LOPTC), 1, f)!=0) {
	 dsloptc.Lop[dsloptc.n] = new LOPTC;	
 	*dsloptc.Lop[dsloptc.n] = lop;
	dsloptc.n++;
	// Khoi tao danh sach dk 
	//KhoiTaoDanhSachDangKy(dsloptc.Lop[dsloptc.n]->pDSDK);
	//dsloptc.Lop[dsloptc.n]->pDSDK.n = 0;
}
 fclose(f);
}


/*------------------------SINH VIEN--------------------------*/

void SaveFileSinhVien(LISTSV ds)
{
 	FILE * f;
 	if ((f=fopen("Data/DSSV.txt","wb"))==NULL)
 	{  
	 	BaoLoiVaNgu ("Loi mo file de ghi", 1500); return ;
 	}
 //	for (int i = 0; i < ds.n; i++)
 for(NODESV *p = ds.pHead; p != NULL; p = p->pNext)
	fwrite(&p->DATA, sizeof(SINHVIEN), 1, f);
 	fclose(f);
}


void OpenFileDanhSachSinhVien(LISTSV &ds) {
 FILE * f; SINHVIEN sv;
 if ((f=fopen("Data/DSSV.txt","rb"))==NULL)
 {  BaoLoiVaNgu ("Loi mo file de doc", 1500); return ;
 }
 ds.n = 0;
 while (fread (&sv, sizeof (SINHVIEN), 1, f)!=0) {
 	NODESV * p = new NODESV;	
	 p = TaoNodeSinhVien(sv); 
	ThemSinhVienCoThuTu(ds, p);
	ds.n++;
}
 fclose(f);
}

/*------------------------SINH VIEN-------------LOPTINCHI-------------*/

// LUU DANH SACH DANG KY CUA LOP TIN CHI VAO TRONG FILE VD: loptc co maso la 3434==> luu danh sach sv dk vao file 3434.txt
void SaveFileDanhSachDangKyVaoLopTinChi(LOPTC a, char *Filename)
{
 	FILE * f;
 	if ((f=fopen(Filename,"wb"))==NULL)
 	{  
	 	BaoLoiVaNgu ("Loi mo file de ghi", 1500); return ;
 	}
 //	for (int i = 0; i < ds.n; i++)
 for (NODEDK *p = a.pDSDK.pHead; p != NULL; p = p->pNext)
 	fwrite(&p->DATA, sizeof(SINHVIENDK), 1, f);
	
 	fclose(f);
}
// DOc danh sach sinh vien dang ky vao trong lop tin chi vd: loptc co maso la 3434==> doc danh sach sv dk vao file 3434.txt
void OpenFileDanhSachDangKyTrongLopTinChi(LOPTC &a, char *Filename) {
 FILE * f; SINHVIENDK svdk;
 if ((f=fopen(Filename,"rb"))==NULL)
 {  //BaoLoiVaNgu ("Loi mo file de doc");
  	return ;
 }
 	a.pDSDK.n = 0;// khoi tao so luong svdk
 	// Khoi tao danh sach dk cua lop
 	KhoiTaoDanhSachDangKy(a.pDSDK);
 	// dua cac phan tu vao trong danh sach nay
 while (fread (&svdk, sizeof (SINHVIENDK), 1, f)!=0) {
 	// tao node cho data sinhviendk vua moi dc chuyen vao
	NODEDK *p = TaoNodeDangKy(svdk);
	ThemVaoCuoiDanhSachDangKy(a.pDSDK, p);
	a.pDSDK.n++;
}
 fclose(f);
}

void TaoTenFileTheoMaLopTinChi(int maloptinchi, char Filename[])
{
	// Tao ra Ten file voi TEN  == "MALOPTINCHI"		
	itoa(maloptinchi, Filename, 10); // chuyen maloptc tu so sang chuoi va luu vao Filename
	// Noi duoi .txt vao sau Filename
	char duoifile[] = ".txt";
	// them duoi .txt vao sau filename
	NoiChuoi(Filename, duoifile);
}
void DocFileDanhSachSinhVienDangKy(DSLOPTC &dsloptc)
{
	// doc toan bo file danh sach sv dk cua tung lop tin chi
	for(int i = 0; i < dsloptc.n; i++)
	{
		// kiem tra lop nay co ai dk chua
		if(dsloptc.Lop[i]->pDSDK.n < 1) continue;
		
		// co roi thi moi doc file
			char Filename[20];
			// Tao ra Ten file voi TEN LA : MALOPTC			
			TaoTenFileTheoMaLopTinChi(dsloptc.Lop[i]->MALOPTC, Filename);
			// phai doc file danh sach svdk cua lop tin chi thu I
			OpenFileDanhSachDangKyTrongLopTinChi(*dsloptc.Lop[i], Filename);
		
		
	}	
}
// AUTHOR: LE QUANG NHU PTIT
