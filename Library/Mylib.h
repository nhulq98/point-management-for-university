#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include <iostream>

#define Enter 13
#define CYAN 3
#define WHITE 15
#define BLACK 0

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13

const int dongvekhung = 20;
const int cotvekhung = 70;

const int truchoanh = 8;
const int tructung = 2;

//=====================================================KHAI BAO CAU TRUC DU LIEU============================================================================


#define MASVMAX 12


//=========================================DANH SACH SINH VIEN DANG KY============================================
struct SinhVienDK
{
	char MASV[MASVMAX];
	float DIEM;	
};
typedef struct SinhVienDK SINHVIENDK;
// KHAI BAO THEM DE XU LY TINH NANG CUOI
/*
#define SVDKMAX 5000
struct ArrayDK
{
	int n;
	SINHVIENDK *ArraySvDk;	
};
typedef struct ArrayDK ARRAYDK;
*/
struct NodeDK  
{
	SINHVIENDK DATA;
	struct NodeDK *pNext;
};
typedef struct NodeDK NODEDK;

//==============DANH SACH LIEN KET DON================
struct ListDK
{
	int n;
	//int MALOPDK;// Them vao de nhan biet day la danh sach cua then lop tin chi nao
	NODEDK *pHead, *pTail;
};
typedef struct ListDK LISTDK;

//=============================================================MON HOC==========================================================================
#define TENMHMAX 17;
struct MonHoc
{
	char MAMH[10];
	char TENMH[50];
	int STCLT;
	int STCTH;
};
typedef struct MonHoc MONHOC;
/*
struct DanhSachMon
{
	int n;
	MONHOC *mh;
};
typedef struct DanhSachMon DSMH;
*/
/*==========CAY NHI PHAN TIM KIEM==========*/
struct NodeMH
{
	MONHOC DATA;
	struct NodeMH *Left;
	struct NodeMH *Right;
};
typedef struct NodeMH NODEMH;

//==============================================================LOP TIN CHI=======================================================================
struct LopTinChi
{
	int MALOPTC;		
	//nien khoa thi vd: 2019
	int NIENKHOA;
	char MAMH[10];
	int  NHOM, SVMAX, SVMIN, HOCKY;
	LISTDK pDSDK; //tro den danh sach SV DKy Lop TC
};
typedef struct LopTinChi LOPTC;
/*==========DANH SACH TUYEN TINH==========*/
#define LOPTCMAX 5000
struct ListLopTC
{
	int n;
	LOPTC *Lop[LOPTCMAX];// tao ra cac con tro quan ly dau moi dong
};
typedef struct ListLopTC DSLOPTC;

//=================================================================SINH VIEN====================================================================

#define MASVMAX 12
#define MALOPMAX 10
#define HOMAX 30
#define TENMAX 30
//B1: khai bao cau truc du lieu
struct SinhVien
{
	char MASV[MASVMAX], MALOP[MALOPMAX];
	char HO[HOMAX], TEN[TENMAX], SODT[15];
	char PHAI[10];
	int NamHoc;
};
typedef struct SinhVien SINHVIEN;

/*==========DANH SACH LIEN KET DON==========*/
#define MAXLISTSV 10000
struct NodeSV
{
	SINHVIEN DATA;
	struct NodeSV *pNext;
};
typedef struct NodeSV NODESV;

struct ListSV
{
	int n;
	NODESV *pHead, *pTail;
};
typedef struct ListSV LISTSV;

//const int WHITE=15;
#define PASSWORD "abcdef"
using namespace std;
//const int WHITE=15;
string TIEUDEMONHOC[5]={" STT ","MAMH","TEN MON HOC"," SO CHI LY THUYET","SO CHI THUC HANH"};



char* Pwd () {
     char S[40]; int i=0;
     while ((S[i]= getch()) != Enter ) 
     { printf ("%c", '*') ; i++ ; 
     }
     S[i]='\0';
     return S;
}

int CheckPwd () {
    int dem =0; 
    for ( dem =1 ; dem <=3 ; dem++)
    { printf( "Password :"); 
      if (strcmp(Pwd(),PASSWORD) ==0)   return 1;
      else printf ( "\nPassword sai. Hay nhap lai\n")  ; 
    }
    return 0;  
}

// Hàm d?ch chuy?n con tr? d?n t?a d? x, y.
void gotoxy(int x,int y)
{    
	HANDLE hConsoleOutput;    
	COORD Cursor_an_Pos = {x-1,y-1};   
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}
// chi to mau chu cai
void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

int wherex( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}

int wherey( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
void clreol( ) {
COORD coord;
DWORD written;
CONSOLE_SCREEN_BUFFER_INFO info;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
coord.X = info.dwCursorPosition.X;
coord.Y = info.dwCursorPosition.Y;
FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
  info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
gotoxy (info.dwCursorPosition.X , info.dwCursorPosition.Y );
}


void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
// Hàm thay d?i kích c? c?a khung cmd.
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}



// Tô màu nên xung quanh chu cái
void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}



// Hàm xóa màn hình.
void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

string ChuyenSoThanhChuoi(int number)
{
	if(number == 0) return "0";
    string s = "";
	while (number!= 0)
	{
		s = char((number % 10) + 48) + s;
		number = number / 10;
	}
	return s;
}


void VeDuongVien(int x, int y, int chieudai, int maunen, int mauchu)
{
	gotoxy(x, y);
	//SetBGColor(maunen);
	SetColor(mauchu);
	for (int i = 0; i < chieudai; i++)
	{
		cout << char(196);
	}
}

void VeTuyChonDuoi(int x, int y, char *k)
{
	gotoxy(x, y);
	for(int i = 0; i < 120; i++)
	{
		cout << char(196);
	}
	gotoxy(x, y + 2);
	cout << k;
	gotoxy(1, 1);
}
void VeHinh(int x, int y, char *str, int color)
{
	gotoxy(x, y);
	textcolor(color);
	cout << str;
	textcolor(15);// tro ve binh thg
}


void VeBangDanhSach(int x, int y, int chieudai, int chieurong, int socot)
{
	// ve ------------------ 70 lan
	// tao thanh 15 dong
	int t = chieurong / socot;
	for(int i = 1; i <= chieudai; i++)
	{
		gotoxy(x, y + i);
		for(int j = 1; j <= chieurong; j++)
		{
			// dong dau
			if(i == 1)
			{
				if(j == 1)// goc dau dong
				{
					cout << char (218);// bo goc xuong duoi(goc vuong ben tay trai)
				}
				if(j == chieurong)// goc cuoi dong
				{
					cout << char(191); // ve goc bo xuong
				}
				// cac goc giua dong(5 goc)
				else if(j % t == 0)
				{
					cout << char (194);// bo goc xuong duoi(goc vuong ben tay trai)
				}// cac duong thang giua dong
				//else for (int k = 0; k < cot; k++) cout << char (196);
				else{
					//for(int k = 2; k < cot; k++)
					cout << char(196);// dau gach ngang
				}
			}
			// cuoi dong
			if(i == chieudai)
			{
				if(j == 1)// dong dau
				{
					cout << char(192);
				}
				// dong cuoi
				if(j == chieurong)
				{
					cout << char(217);
				}
				// cac goc giua dong
				else if(j % t == 0)
				{
					cout << char(193);
				}
				else{// cac dau gach ngang
					cout << char(196);
				}
			}
			// giua dong
			if(i > 1 && i < chieudai){
				if(j == 1){ // dau dong in ra cac "|" 
					cout << char (179);
				}
				if(j == chieurong)// cuoi dong "|"
					cout << char (179);
				else if(j % t == 0) {// in cac "|" cho cac moc noi
					cout << char (179);
				}
				else{
					cout << " ";
				}
	
				/*
				else if(i % 2 != 0)
				{
					cout << char(196);// in cac dau '-'
				}
				*/
			}						
			
		}
		
	}
	
}

void ThemPhanTu(char a[],int &n, int vitrithem, char phantuthem)
{
	for(int i = n - 1; i >= vitrithem; i--)
	{
		a[i + 1] = a[i];
	}
	a[vitrithem] = phantuthem;
	n++;
}

//=============================================NGUYEN MAU HAM======================================================================
void SaveFileDanhSachDangKyVaoLopTinChi(LOPTC a, char *Filename);
void NhapThongTinMonHoc(NODEMH *Root, MONHOC &mh);
void XuatMonHoc(MONHOC mh);
