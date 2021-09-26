// LE QUANG NHU N16DCAT035 - Lop D16CQAT01_N
#include"Library/ProcessAndGraphic.h"

//==================================================================XU LY MON HOC===================================================================================

void MenuMonHoc(NODEMH *&Root, DSLOPTC dsloptc)
{
	int k, luachon;		
	do
	{
		system("cls");
		luachon = MenuTuyChinh(MonHoc, 5);
		switch(luachon)
		{
			case 1: // them mon hoc
			{
				system("cls");
				ThemMonHoc(Root);
				break;
			};
			case 2:// xoa mon hoc
			{
				system("cls");
				XoaMonHoc(Root, dsloptc);
				break;
			}
			case 3:
			{ // Cap Nhat Mon Hoc
				system("cls");
				SuaMonHoc(Root, dsloptc);					
				break;	
			};
			case 4:
			{			
				if(Root == NULL)
				{	
					BaoLoiVaNgu("Danh sach rong!", 100);	
					getch();				
					break;
				}
				system("cls");
				HienThiDanhSachMon(Root);																																			
			break;
			};
			case 5:
			{
				return;
			}								
		}	
	}while(1);				
}

//=======================================================================LOP TIN CHI================================================================================

void TaoLopTinChiMoi(DSLOPTC &dsloptc, NODEMH *Root)
{
	system("cls");
	LOPTC a;
	NhapThongTinLopTinChi(dsloptc, Root, a);
	if(MenuTuyChinh(YESNO, 2) != 1){
		BaoLoiVaNgu("Them That Bai!", 1500);
		return;
	}
	ThemLopTinChi(dsloptc, a);
	BaoLoiVaNgu("Them Thanh cong!", 1500);
	SaveFileLopTinChi(dsloptc);
}

void MenuLopTinChi(DSLOPTC &dsloptc, NODEMH *Root){
	do
	{
		//OpenFileCayMonHoc(Root);
		
		system("cls");
		int x;
		int luachon;
		luachon = MenuTuyChinh(LopTinChi, 5);
		switch(luachon)
		{
			case 98: return;

			case 1: // them lop tin chi
			{
					TaoLopTinChiMoi( dsloptc,  Root);		
	break;	};
			case 2: // Xoa lop tin chi
			{
				system("cls");
				VeTuyChonDuoi(1, 25, "ESC: Thoat ||  ENTER: Nhap tiep   **Luu y: chi sai duoc khi nhap sai ma mon");
				bool h, check = false; int chisolop, masolop;
				do{ h = true; fflush(stdin);
					// kiem tra ma lop nay co ton tai hay ko				
					//cout << "\n Nhap vao ma so can xoa: "; cin >> masolop;					
					NhapSoNguyen("\n Nhap vao ma so can xoa: ", masolop);
					chisolop = Search_MaLopTC(dsloptc, masolop); 	
					if(chisolop == -1) 
					{
						BaoLoiVaNgu("Ma lop ko ton tai!", 100);
						HamThoat(check);
						if(check == true) break;
						h = false;
						continue;
					}
					// kiem tra lop nay co sv nao dk chua
					if(dsloptc.Lop[chisolop]->pDSDK.n > 0) 
					{// da co nguoi dk
						BaoLoiVaNgu("Co sinh vien dang ky. Khong duoc xoa!", 1500);
						h = false;
					}					
				}while(h == false);	
				
				if(check == true) break;	 		
				if(MenuTuyChinh(YESNO, 2) != 1)
				{
					BaoLoiVaNgu("Xoa Loi!", 1500);
					break;
				}	
				XoaLopTC_MaSo(dsloptc, masolop);
				SaveFileLopTinChi(dsloptc);
				break;
			};
			case 3: // Sua Lop tin chi
			{
				system("cls");
				VeTuyChonDuoi(1, 25, "ESC: Thoat ||  ENTER: Nhap tiep   **Luu y: chi sai duoc khi nhap sai ma mon");
			
				bool h, check = false; int chisolop, masolop;
				do{ h = true; fflush(stdin);
					// kiem tra ma lop nay co ton tai hay ko			
					NhapSoNguyen("\n Nhap vao ma so can sua: ", masolop);
					chisolop = Search_MaLopTC(dsloptc, masolop); 	
					if(chisolop == -1) 
					{
						BaoLoiVaNgu("Ma lop khong ton tai!", 100);
						HamThoat(check);
						if(check == true) break;
						h = false;
						continue;
					}
					// kiem tra lop nay co sv nao dk chua
					if(dsloptc.Lop[chisolop]->pDSDK.n > 0) 
					{// da co nguoi dk
						BaoLoiVaNgu("Co sinh vien dang ky. Khong duoc sua!", 1500);
						h = false;
					}
				}while(h == false);				
				if(check == true) break;
				// Nhap vao thong tin can sua
				CapNhatLopTinChi(*dsloptc.Lop[chisolop]);
				if(MenuTuyChinh(YESNO, 2) != 1)
				{//ko ton tai
					BaoLoiVaNgu("Cap nhat loi!", 1500);
					break;
				} // tim thay ==> di vao sua			
				BaoLoiVaNgu("Cap nhat thanh cong!", 1500);
				SaveFileLopTinChi(dsloptc);				
			break;
			};
			case 4: // liet ke danh sach lop tin chi
			{				
				if(dsloptc.n < 1)
				{					
					BaoLoiVaNgu("Danh Sach rong!", 1500);
					getch();
					break;
				}
				system("cls");
				SetBGColor(3);
				printf("\n\t\t                      DANH SACH LOP TIN CHI                      \n\n");
				textcolor(15);
				cout << "\tSTT" << "\tMA LOP" << "\tNIEN KHOA" << "\tHOC KY" << "\tMA MON" << "\tNHOM" << "\tSVMIN" << "\tSVMAX" << "\tSVDANG KY" << endl << endl;
				XuatDanhSachLopTC(dsloptc);	
				system("pause");				
	break;	};
			case 5:
			{
				return;
			};	
		}
		
	}while(1);
}

int Search_SinhVienTrongLopTinChi(DSLOPTC dsloptc, char *MaSV)
{
	for(int i = 0; i < dsloptc.n; i++)
	{
		if(dsloptc.Lop[i]->pDSDK.n > 0)// ktra lop do co ai dk chua
		{// co roi thi di vao xet
			for(NODEDK *p = dsloptc.Lop[i]->pDSDK.pHead; p != NULL; p = p->pNext)
			{
				if(stricmp(p->DATA.MASV, MaSV) == 0)
				{// co nghia la no trung nhau
					return i;
				}
			}
			
		}
	}
	return -1;
	
}

//===================================================================XU LY SINH VIEN ==============================================================================



void MenuSinhVien(LISTSV &dssv, DSLOPTC dsloptc)
{
	do
	{		
		system("cls");
		
		int x; bool h;
		int luachon;
		luachon = MenuTuyChinh(SinhVien, 6);
		switch(luachon)
		{
			case 1: // them sinh vien
			{// Nhap Sv
				system("cls");
				SINHVIEN sv;
				NhapSinhVienVaoLop(dssv, sv);// khi mssv bi rong thi se break ra day
				if(strlen(sv.MASV) < 1){//Ktra neu Masv rong
					break;// thoat ra Menu Chinh
				}
				// dua DATA vao NODESV
				NODESV *p = TaoNodeSinhVien(sv);
				dssv.n = 0; // khoi tao so luong
				if(MenuTuyChinh(YESNO, 2) != 1){
					BaoLoiVaNgu("Them Loi!", 1500);
					break;
				}
				// them sinh vien vao danh sach co thu tu
				ThemSinhVienCoThuTu(dssv, p);
				dssv.n++; //  cap nhat so luong sv
				BaoLoiVaNgu("Them thanh cong!", 1500);
				SaveFileSinhVien(dssv);
				
			break;};
			case 2: // Xoa sinh vien
			{// Dau tien tim no 
				system("cls");
				bool check = false;
				VeTuyChonDuoi(1, 25, "ESC: Thoat ||  ENTER: Nhap tiep   **Luu y: chi sai duoc khi nhap sai ma mon");
				char *masv = new char;
				do{h = true;
					NhapChuoi("\n Nhap vao Ma sinh vien can xoa: ", masv);
					BoolKhoangTrang(h, masv);
					NODESV *p = Search_MaSV(dssv, masv);
					
					if(p == NULL)
					{
					 	h = false;
					 	BaoLoiVaNgu("khong ton tai!", 100);
					 	HamThoat(check);
						if(check == true) break;
						continue;// chay sang lan lap ms
					}
					// neu chay dc xuong day thi ms check
					int checklop = Search_SinhVienTrongLopTinChi(dsloptc, masv);
					if(checklop != -1)
					{
						h = false;
						printf("\n Sinh vien da dang ky lop co ma mon la: %s", dsloptc.Lop[checklop]->MAMH);
						BaoLoiVaNgu("Khong the xoa!", 1500);
					}		
				}while(h == false);	
				if(check == true) break;							
				if(MenuTuyChinh(YESNO, 2) != 1)
				{
					BaoLoiVaNgu("Xoa Loi!", 1500);
					break;
				}
				XoaSinhVienTheoMa(dssv, masv);
				BaoLoiVaNgu("Xoa Thanh cong!", 1500);										
			break;	
			};
			case 3:
			{
				system("cls");
				char *masv = new char; NODESV *p;
				bool check = false;
				VeTuyChonDuoi(1, 25, "ESC: Thoat ||  ENTER: Nhap tiep   **Luu y: chi sai duoc khi nhap sai ma mon");
				do{
					h = true;
					NhapChuoi("\n Nhap vao Ma sinh vien can sua: ", masv);
					BoolKhoangTrang(h, masv);
					p = Search_MaSV(dssv, masv);
					if(p == NULL){
						h = false;
						BaoLoiVaNgu("ma sinh vien khong ton tai", 100);
						HamThoat(check);
						if(check == true) break;
						continue;
					}
					
					int checklop = Search_SinhVienTrongLopTinChi(dsloptc, masv);
					if(checklop != -1)
					{
						h = false;
						printf("\n Sinh vien da dang ky lop co ma mon la: %s", dsloptc.Lop[checklop]->MAMH);
						BaoLoiVaNgu("Khong the sua!", 1500); // neu sua thi no se bi bug ngay cho nam nhap hoc. (vi neu nam nhap hoc nho hon nam mo loptc thi se ko dung)
						Sleep(2000);
					}		
					
				}while(h == false);
				
				if(check == true) break;
				NhapSinhVienKhiUpdate(p->DATA);
				if(MenuTuyChinh(YESNO, 2) != 1)
				{
					BaoLoiVaNgu("Update Loi!", 1500);
					break;
				}						
				SaveFileSinhVien(dssv);
				BaoLoiVaNgu("Update Thanh cong!", 1000);
				break;
			}
			
			case 4: 
			{		
				if(dssv.pHead == NULL){
					BaoLoiVaNgu("Danh sach rong!", 1500);
					break;
				} 
			
				system("cls");
				SetBGColor(3);
				printf("\n\t\t\t                  DANH SACH SINH VIEN                  \n\n");
				textcolor(15);
				cout << "\t\tSTT " << "\tMSSV" << "\tHO" << "\tTEN" << "\tPHAI" << "\tMA LOP" << "\tNAM HOC" << "\t   SDT" << endl << endl;				
				XuatDanhSachSinhVien(dssv);				
				system("pause");		
			break;	
			};			
			case 5:// Xem danh sach sinh vien dua vao ma lop
				{	char *malop = new char; bool h, check = false;
					system("cls");
					do{h = true;
					NhapChuoi("\nNhap vao ma lop can xem: ", malop);
					BoolKhoangTrang(h, malop);
					if(SearchMaLop(dssv, malop) == false)
					{
						BaoLoiVaNgu("Ma lop khong ton tai!", 100);
						h = false;
						printf("\nESC: Thoat || ENTER: Nhap Tiep");
						HamThoat(check);
						if(check == true) break;
					}
					}while(h == false);
					if(check == true) break;
					textcolor(63);
					printf("\n\t\t\t                      DANH SACH SINH VIEN                      \n\n");
					textcolor(15);
					cout << "\t\tSTT " << "\tMSSV" << "\tHO" << "\tTEN" << "\tPHAI" << "\tMA LOP" << "\tNAM HOC" << "\t   SDT" << endl << endl;
					XemSinhVienBangMaLop(dssv, malop);
				
					system("pause");
					break;
				};
			case 6:
				{
					return;
				};
		}
			
	}while(1);
}

//===========================================================XU LY DANH SACH DANG KY================================================================


//=============================================================================================================//

void MenuSinhVienDangKyTheoNhom(DSLOPTC dsloptc, LISTSV dssv, LOPTC &a)
{
	bool h, check = false; int luachon;
	do{system("cls");
		h = true;// xoa man hinh khi hoc ky ko hop le
		textcolor(63);
		printf("\n                      TIM THEO NHOM                      \n");
		textcolor(15);
		NhapSoNguyen("Nhap so nhom: ", a.NHOM);
		// Viet ham search ma mon trong dsloptc
		if(SearchNhomTrongLopTinChi(dsloptc, a) == -1){
			BaoLoiVaNgu("khong ton tai hoac chua ai dang ky", 100);
			h = false;
			printf("\nESC: Thoat || ENTER: Nhap Tiep");
			HamThoat(check);
			if(check == true) return;
		}
	}while(h == false);
	do{
		h = true;
		system("cls");
		textcolor(63);
		cout << "\n                      KET QUA TIM THEO NHOM                      \n";
		textcolor(15);
		char TimTheoNhom[][50] = {"1. Xem Danh Sach", "2. Thoat"};
		luachon = MenuTuyChinh(TimTheoNhom, 2);
		switch(luachon)
		{
			case 1:
				{ h = false; system("cls");
					// Goi then lietke dssv theo Nhom
					textcolor(63);
					printf("\n                      DANH SACH SINH VIEN DANG KY NHOM %d MON %s HOC KY %d NIEN KHOA %d                      \n\n", a.NHOM, a.MAMH, a.HOCKY, a.NIENKHOA);
					textcolor(15);
					cout << "\n\tSTT " << "\tMASV" << "\tHO" << "\tTEN" << "\tDIEM" << "\tMaLopTinChi" << endl; 
					z = 1;
					LietKeSinhVienTheoNhom(dsloptc, dssv, a);
					system("pause");
					break;
				};
			case 2:
				{
					return;
				}
			
		}
	}while(h == false);
	return;
}

void MenuSinhVienDangKyTheoMaMon(DSLOPTC dsloptc, LISTSV dssv, LOPTC &a)
{	
	bool h, check; int luachon;
	do{system("cls");
	//VeTuyChonDuoi(1, 25, "ESC: Thoat || ENTER: Nhap tiep   **Luu y: chi sai duoc khi nhap sai ma mon");
		h = true;// xoa man hinh khi hoc ky ko hop le
		textcolor(63);
		printf("\n                      TIM THEO MA MON                      \n");
		textcolor(15);
		NhapChuoi("Nhap ma mon: ", a.MAMH);
		// Viet ham search ma mon trong dsloptc
		if(SearchMaMonTrongLopTinChi(dsloptc, a) == -1){
			BaoLoiVaNgu("khong ton tai hoac chua co ai dang ky", 100);
			printf("\nESC: Thoat || ENTER: Nhap Tiep");
			HamThoat(check);
			if(check == true) return;
			h = false;
		}
	}while(h == false);
	do{system("cls");
		h = true;
		textcolor(63);
		cout << "\n                      KET QUA TIM THEO MA MON                      \n";
		textcolor(15);
		char TimTheoMaMon[][50] = {"1. Xem Danh Sach", "2. Tim Tiep", "3. Thoat"};
		luachon = MenuTuyChinh(TimTheoMaMon, 3);
		switch(luachon)
		{
			case 1:
				{
					h = false; system("cls");
					textcolor(63);
					printf("\n            DANH SACH SINH VIEN DANG KY MON %s HOC KY %d NIEN KHOA %d            \n\n", a.MAMH, a.HOCKY, a.NIENKHOA);
					textcolor(15);
					// Goi then lietke dssv theo Mamon
					cout << "\n\tSTT " << "\tMASV" << "\tHO" << "\tTEN" << "\tDIEM" << "\tMaLopTinChi" << endl; 
					z = 1;
					LietKeSinhVienTheoMaMon(dsloptc, dssv, a);
					getch();
					system("cls");
					break;
				};
			case 2:
				{system("cls");
					// Nhap tiep then NHOM
					MenuSinhVienDangKyTheoNhom(dsloptc, dssv, a);
					break;
				};
			case 3: {
				return;
			}
		}
		
	}while(h == false);
}

void MenuSinhVienDangKyTheoHocKy(DSLOPTC dsloptc, LISTSV dssv, LOPTC &a)
{
	bool h, check = false;	int luachon;
	do{system("cls");
		h = true;
		textcolor(63);
		printf("\n                 TIM THEO HOC KY                 \n");
		textcolor(15);
		NhapSoNguyen("\n Nhap vao hoc ky: ", a.HOCKY);
		// Viet ham search HocKy cua nien khoa nao do
		if(SearchHocKy_NienKhoa(dsloptc, a) == -1){
			BaoLoiVaNgu("khong ton tai hoac khong co ai dang ky", 100);
			h = false;
			printf("\nESC: Thoat || ENTER: Nhap Tiep");
			HamThoat(check);
			if(check == true) return;
		}
	}while(h == false);
	do{system("cls");
		h = true;
		textcolor(63);
		cout << "\n                      KET QUA TIM THEO HOC KY                      \n";
		textcolor(15);
		char TimTheoHocKy[][50] = {"1. Xem Danh Sach", "2. Tim Tiep", "3. Thoat"};
		luachon = MenuTuyChinh(TimTheoHocKy, 3);
		
		switch(luachon)
		{
			case 1:
				{ h = false;
				system("cls");
					textcolor(63);
					printf("\n                      DANH SACH SINH VIEN DANG KY HOC KY %d NIEN KHOA %d                      \n\n", a.HOCKY, a.NIENKHOA);
					textcolor(15);
					// Goi then lietke dssv theo hoc ky
					cout << "\n\tSTT " << "\tMASV" << "\tHO" << "\tTEN" << "\tDIEM" << "\tMaLopTinChi" << endl; 
					z = 1;
					LietKeSinhVienTheoHocKy(dsloptc, dssv, a);
					system("pause");
					system("cls");
					break;
				};
			case 2:
				{ system("cls");
					// Nhap tiep then ma mon
					MenuSinhVienDangKyTheoMaMon(dsloptc, dssv, a);
					break;
				};
			case 3: {
				return;
			}
		}
		
	}while(h == false);
}

void MenuSinhVienDangKyTheoNienKhoa(DSLOPTC dsloptc, LISTSV dssv)
{
	system("cls");
	int luachon, Nk;
	bool h, check =false;
	LOPTC a;
	//B1: nhap vao nien khoa
	do
	{ 
		h= true;
		fflush(stdin);
		textcolor(63);
		cout << "\n                      TIM THEO NIEN KHOA                      \n";
		textcolor(15);
		NhapSoNguyen("\nNhap vao nien khoa: ", Nk);
		a.NIENKHOA = Nk;
		if(KiemTra_NienKhoa(dsloptc, a.NIENKHOA) == -1)
		{
			h = false;
			BaoLoiVaNgu("khong ton tai hoac khong co sinh vien dang ky !", 100);
			printf("\nESC: Thoat || ENTER: Nhap Tiep");
			HamThoat(check);
			if(check == true) return;
		}
	}while(h == false);
	//char TimNienKhoa[3][50] = {"1. Xem Danh Sach", "2. Nhap Tiep", "3. Thoat"};
	do
	{
		system("cls");
		textcolor(63);
		cout << "\n                      KET QUA TIM THEO NIEN KHOA                      \n";
		textcolor(15);

		char TimTheoNienKhoa[][50] = {"1. Xem Danh Sach", "2. Tim Tiep", "3. Thoat"};
		luachon = MenuTuyChinh(TimTheoNienKhoa, 3);
		switch(luachon)
		{
			case 1:
				{h = false;
					// Goi then lietke dssv theo Nien khoa
					system("cls");
					textcolor(63);
					printf("\n                      DANH SACH SINH VIEN DANG KY NIEN KHOA %d                      \n\n", a.NIENKHOA);
					textcolor(15);
					//cout << "\tSTT " << "\tMASV" << "\tHO" << "\tTEN" << "\tDIEM" << "\tMaLopTinChi" << endl;
					z = 1;
					LietKeSinhVienTheoNienKhoa(dsloptc, dssv, a);
					system("pause");
					system("cls");
					break;
				};
			case 2:
				{system("cls");
					// Nhap tiep Hoc Ky
					MenuSinhVienDangKyTheoHocKy(dsloptc,  dssv, a);
					break;
				};
			case 3: {
				return;
			}
		}
		
	}while(h == false);
}

void XuatSinhVienDuaVaoMaSinhVien(LISTSV dssv, char *masv)
{
	dem = 1;
	for(NODESV *p = dssv.pHead; p != NULL; p = p->pNext)
	{
		if(stricmp(p->DATA.MASV, masv) == 0) // Tim sinh vien bang ma
		{// tim dc roi ne
			cout << "\t\t" << dem++ << "\t" << p->DATA.MASV << "\t" << p->DATA.HO
			<< "\t" << p->DATA.TEN << "\t" << p->DATA.PHAI << "\t" << p->DATA.MALOP
			<< "\t" << p->DATA.NamHoc << "\t   " << p->DATA.SODT << endl << endl;	
			return;					
		}
		
	}
}

void InTatCaSinhVienDaDangKyLopTinChi(DSLOPTC ds, LISTSV dssv)
{int k = 1;
	for(int i = 0; i < ds.n; i++)
	{
		if(ds.Lop[i]->pDSDK.n < 1)
		{
			continue;
		}
		int dem = 1;
		NODEDK * q = ds.Lop[i]->pDSDK.pHead;
		while(q != NULL)
		{
			// in ra all cac svdk trong lop nay ra		
			XuatSinhVienDuaVaoMaSinhVien(dssv, q->DATA.MASV);
			q = q->pNext;
		}							
	}
}

//==============================TINH NANG CUOI=======================

/*
int Search_MaSinhVienTrongDanhSachDangKy(DSLOPTC dsloptc, char *masv)
{
	// duyet dsloptc va di vao trong dsdk xem co ma sinh vien nao trung hay ko
	for(int i = 0; i < dsloptc.n; i++)
	{// di vao trong dsdk cua tung lop va ktra xem co masv nao trung vs ma check
		for(NODEDK *p = dsloptc.Lop[i]->pDSDK.pHead; p != NULL; p = p->pNext)
		{
			if(stricmp(p->DATA.MASV, masv) == 0)
			{
				return i;// lay chi so loptc 
			}
		}
	}
	return -1;
}

int Search_NienKhoaTheoMaSinhVien(DSLOPTC dsloptc, char *masv, LOPTC a)
{
	// duyet dsloptc va di vao trong dsdk xem co ma sinh vien nao trung hay ko
	for(int i = 0; i < dsloptc.n; i++)
	{// di vao trong dsdk cua tung lop va ktra
		for(NODEDK *p = dsloptc.Lop[i]->pDSDK.pHead; p != NULL; p = p->pNext)
		{// xem co nien khoa do ton tai hay ko
			if(stricmp(p->DATA.MASV, masv) == 0 && dsloptc.Lop[i]->NIENKHOA == a.NIENKHOA)
			{
				return i;
			}
		}
	}
	return -1;
}

int Search_HocKyTheoMaSinhVien(DSLOPTC dsloptc, char *masv, LOPTC a)
{
		// duyet dsloptc va di vao trong dsdk xem co ma sinh vien nao trung hay ko
	for(int i = 0; i < dsloptc.n; i++)
	{// di vao trong dsdk cua tung lop va ktra
		for(NODEDK *p = dsloptc.Lop[i]->pDSDK.pHead; p != NULL; p = p->pNext)
		{// xem co nien khoa do ton tai hay ko
			if(stricmp(p->DATA.MASV, masv) == 0 && dsloptc.Lop[i]->NIENKHOA == a.NIENKHOA && dsloptc.Lop[i]->HOCKY == a.HOCKY)
			{
				return i;
			}
		}
	}
	return -1;
}

int Search_MaMonTheoMaSinhVien(DSLOPTC dsloptc, char *masv, LOPTC a)
{
		// duyet dsloptc va di vao trong dsdk xem co ma sinh vien nao trung hay ko
	for(int i = 0; i < dsloptc.n; i++)
	{// di vao trong dsdk cua tung lop va ktra
		for(NODEDK *p = dsloptc.Lop[i]->pDSDK.pHead; p != NULL; p = p->pNext)
		{// xem co nien khoa do ton tai hay ko
			if(stricmp(p->DATA.MASV, masv) == 0 && dsloptc.Lop[i]->NIENKHOA == a.NIENKHOA && dsloptc.Lop[i]->HOCKY == a.HOCKY && stricmp(dsloptc.Lop[i]->MAMH, a.MAMH) == 0)
			{
				return i;
			}
		}
	}
	return -1;
}

int Search_NhomTheoMaSinhVien(DSLOPTC dsloptc, char *masv, LOPTC a)
{
		// duyet dsloptc va di vao trong dsdk xem co ma sinh vien nao trung hay ko
	for(int i = 0; i < dsloptc.n; i++)
	{// di vao trong dsdk cua tung lop va ktra
		for(NODEDK *p = dsloptc.Lop[i]->pDSDK.pHead; p != NULL; p = p->pNext)
		{// xem co nien khoa do ton tai hay ko
			if(stricmp(p->DATA.MASV, masv) == 0 && dsloptc.Lop[i]->NIENKHOA == a.NIENKHOA && dsloptc.Lop[i]->HOCKY == a.HOCKY && stricmp(dsloptc.Lop[i]->MAMH, a.MAMH) == 0 && dsloptc.Lop[i]->NHOM == a.NHOM)
			{
				return i;
			}
		}
	}
	return -1;
}
*/

NODEMH* LayRaMaMonBangTenMon(NODEMH *Root, char *x)
{
	while(Root != NULL  && stricmp(Root->DATA.TENMH, x) != 0)
	{
		if(stricmp(Root->DATA.TENMH, x) < 0)
		Root = Root->Right;	
		else if(stricmp(Root->DATA.TENMH, x) > 0)
		Root = Root->Left;
	}
	return Root;
}

int Search_MaMonNhapDiem(DSLOPTC dsloptc, LOPTC a)
{
	for(int i = 0; i < dsloptc.n; i++)
	{
		if(dsloptc.Lop[i]->NIENKHOA != a.NIENKHOA || dsloptc.Lop[i]->HOCKY != a.HOCKY || stricmp(dsloptc.Lop[i]->MAMH, a.MAMH) != 0)
		{
			continue; // nhay vao lop tiep theo
		}
		if(dsloptc.Lop[i]->NIENKHOA == a.NIENKHOA && dsloptc.Lop[i]->HOCKY == a.HOCKY && stricmp(dsloptc.Lop[i]->MAMH, a.MAMH) == 0)
		{// da tim dc
			return i;
		}
	}
	return -1;
}

int NhapDiemTheoTuyChon(DSLOPTC dsloptc, LISTSV dssv, NODEMH *Root, LOPTC &a, bool &check)
{
	bool h;		
	do{ h = true; fflush(stdin);	
		NhapSoNguyen("Nhap nien khoa: ", a.NIENKHOA);
		if(Search_NienKhoa(dsloptc, a.NIENKHOA) == -1)
		{
			h = false;
			BaoLoiVaNgu("Khong ton tai or chua ai dang ky", 100);
			printf("\n ENTER: Nhap lai || ESC: Thoat");
			HamThoat(check);
			if(check == true) return -1;
		}
	}while(h == false);
	
	do{ h = true;fflush(stdin);
		NhapSoNguyen("Nhap hoc ky: ", a.HOCKY);
		if(Search_HocKyNhapDiem(dsloptc, a) == -1)
		{
			h = false;
			BaoLoiVaNgu("Khong ton tai or chua ai dang ky", 100);
			printf("\n ENTER: Nhap lai || ESC: Thoat");
			HamThoat(check);
			if(check == true) return -1;
		}
	}while(h == false);
	NODEMH *p;
	do{ h = true; fflush(stdin);
		
		NhapChuoi("\nNhap ma mon: ", a.MAMH);
		if(SearchMaMonTrongLopTinChi(dsloptc, a) == -1)
		{
			h = false;
			BaoLoiVaNgu("Khong ton tai or chua ai dang ky", 100);
			printf("\n ENTER: Nhap lai || ESC: Thoat");
			HamThoat(check);
			if(check == true) return -1;
		}
		/*
		char *x = new char;
		NhapChuoi("\nNhap ten mon: ", x);
		p = LayRaMaMonBangTenMon(Root, x);
		if(p == NULL)
		{
			h = false;
			BaoLoiVaNgu("Khong ton tai or chua ai dang ky", 500);
			printf("\n ENTER: Nhap lai || ESC: Thoat");
			HamThoat(check);
			if(check == true) return -1;
			continue;			
		}
		strcpy(a.MAMH, p->DATA.MAMH);// dua vao trong loptc
		if(Search_MaMonNhapDiem(dsloptc, a) == -1){
			h = false;
			BaoLoiVaNgu("Mon Hoc nay ko ton tai", 1500);
		}
		*/
	}while(h == false);
	int chiso;
	do{ h = true; fflush(stdin);
		NhapSoNguyen("Nhap nhom: ", a.NHOM);
		chiso = SearchNhomTrongLopTinChi(dsloptc, a);
		if(chiso == -1)
		{
			h = false;
			BaoLoiVaNgu("Khong ton tai or chua ai dang ky", 100);
			printf("\nESC: Thoat || ENTER: Nhap Tiep");
			HamThoat(check);
			if(check == true) return -1;
		}
	}while(h == false);
	return chiso;
}

void HieuChinhDiem(int x, int y, LOPTC a, SINHVIEN *ArraySV, char *Filename, int n)
{
	int chiso = 0;
	int tempy = y;
	// Nhap diem vao o	
	float diem;
	/*
		Y tuong: 
		+ dich chuyen con tro den o can thay doi diem
		+ sau do lay dc ma sinh vien cua then do ra.
		+ dung ma sv cua no va di vao danh sach dang ky. cap nhat diem cua then do
		+ sau do reset lai bang danh sach
	*/
		
	while(true)
	{		
		if(kbhit())
		{
			fflush(stdin);
			char c = getch();
			// gioi han do dich chuyen con tro nam chi nam trong bang danh sach
				if(c == KEY_ESC)
				{
					return;
				}
				if(c == KEY_DOWN)
				{
					if(tempy + 1 < (y + n))// doan truoc tinh huog ko cho nhay xuong duoi
					{
						gotoxy(x, tempy += 1);
						chiso++;// vi con tro chay xuong duoi
					}
				}
				if(c == KEY_UP)
				{
					if(tempy - 1 >= y)
					{
						gotoxy(x, tempy -= 1);
						chiso--;
					}
				
				}
				if(c == KEY_ENTER)// co nghia la da lay dc chi so cua dong
				{// Dau tien ta phai xoa diem cu di	
					//gotoxy(x - 1, tempy);// nhay ve vitri dau			
					XoaTheoChieuDai(5);
					gotoxy(x, tempy);// nhay ve vitri dau				
					do{
						diem = NhapDiemTB();// chi co nhap toi da so co 4 kytu VD: 9.75, 4.9
						if(diem > 10)
						{
							BaoLoiVaXoaLoi("Diem <= 10", 80, 2);
							// xoa diem ma minh da nhap sai
							gotoxy(x, tempy);
							XoaTheoChieuDai(DemSo(diem));
							gotoxy(x, tempy);
						}
					}while(diem > 10);
						// khi trich ra dc chi so thi ta dung masv de check
						//B1: Di vao dsdk cua loptc nay va tim then co masv trung thi cap nhat diem cho no
						for(NODEDK *p = a.pDSDK.pHead; p != NULL; p = p->pNext)
						{
							if(stricmp(p->DATA.MASV, ArraySV[chiso].MASV) == 0)
							{// tim dc ma sinh vien roi UPDATE DIEM THOI
								p->DATA.DIEM = diem;// cap nhat xong roi
							}
						}
										
						// luu nhung gi vua thuc hien vao trong dsdkloptc nay
						SaveFileDanhSachDangKyVaoLopTinChi(a, Filename);
						BaoLoiVaXoaLoi("Cap nhat thanh cong", 80, 2);
						gotoxy(x, tempy);// nhay la dung vitri vua ms thay doi
						continue;					
				}
		}
	}
}
/*
void LietKeMonDangKyTheoMaSinhVien(DSLOPTC Dsloptc, LISTSV Dssv, char *masv, LOPTC a, int x, int y)
{
	int tempy = y + 2;
	int tempx= x + 3;
	
	ARRAYDK arraydk;
	
	for(int i = 0; i < Dsloptc.n; i++)
	{
		
		if(Dsloptc.Lop[i]->pDSDK.n < 1) continue;
		else
		{	
			tempx = x;// reset lai x
			// Phai thoa het cac yeu cau sau
			if(Dsloptc.Lop[i]->NIENKHOA == a.NIENKHOA && Dsloptc.Lop[i]->HOCKY == a.HOCKY && stricmp(Dsloptc.Lop[i]->MAMH, a.MAMH) == 0 && Dsloptc.Lop[i]->NHOM == a.NHOM)
			{
				// THOA ROI thi di vao dsdk cua lop tc nay
				for(NODEDK *p = Dsloptc.Lop[i]->pDSDK.pHead; p != NULL; p = p->pNext)
				{// sau do lay ma sinh vien tim trong danh sach sinh vien va IN RA
					if(stricmp(p->DATA.MASV, masv) == 0)// tim dc ma sinh vien trung khop
					{
						for(NODESV *q = Dssv.pHead; q != NULL; q = q->pNext)
						{
							if(stricmp(q->DATA.MASV, masv) == 0)
							{// tim dc sinh vien roi nhe
								// B1: cap phat bo nho DUA TREN sinh vien max cua lop tin chi nay
								arraydk.ArraySvDk = new SINHVIENDK[Dsloptc.Lop[i]->SVMAX];
								arraydk.n = 0; // khoi tao soluong 
								//B1:  dua vao mang								
								strcpy(arraydk.ArraySvDk[arraydk.n].MASV, q->DATA.MASV); // chuyen du lieu qua
								arraydk.ArraySvDk[arraydk.n].DIEM = p->DATA.DIEM;
								arraydk.n++;// cap nhat so luong
								
								//B2:  xuat mag ra
								for(int i = 0; i < arraydk.n; i++)
								{
									tempy += 2;// tang chi sodong len
									// x tang len y giu nguyen tren moi dong
									gotoxy(tempx += 7, tempy);
									cout << i + 1;
									gotoxy(tempx += 13, tempy);
									cout << arraydk.ArraySvDk[i].MASV;
									gotoxy(tempx += 13, tempy);
									cout << q->DATA.HO;
									gotoxy(tempx += 14, tempy);
									cout << q->DATA.TEN;
									gotoxy(tempx += 16, tempy);
									cout << arraydk.ArraySvDk[i].DIEM << endl; 
									//cout << " chi so dong " << i;
								}
								
								//B3: Dich chuyen con tro chay theo dong minh muon nhap diem(vi tri chuot phai co lien he voi chi so cua mang)
								gotoxy(truchoanh + 63, tructung + 4);// cho con tro nhay ve vi tri dau dong
								//B5: Nhap diem va luu vao file
								
								// Tao ra Ten file voi TEN LA : MALOPTC	
								char Filename[20];// tao vung nho de luu maloptc
								TaoTenFileTheoMaLopTinChi(Dsloptc.Lop[i]->MALOPTC, Filename);// thay doi ten file
								HieuChinhDiem(truchoanh + 63, tructung + 4, p, *Dsloptc.Lop[i], Filename);
							}
						}	
						break;// thoat ra. bvi ma sinhvien la duy nhat trong 1 loptc
					}
				
				}
			}
					
		}
		
	}
}
*/
void LietKeMonDangKyDeNhapDiem(LOPTC a, LISTSV Dssv, int x, int y)
{
	int chieurong = 70, socot = 5;
	int tempy = y + 2;
	int tempx= x + 3;
	z = 1;
	int cottb = chieurong / socot;
	SINHVIEN *ArraySV;
	int n;				
	// B1: cap phat bo nho cho mang DUA TREN sinh vien max cua lop tin chi nay
	ArraySV = new SINHVIEN[a.SVMAX];
	n = 0; // khoi tao soluong
	// THOA ROI thi di vao dsdk cua lop tc nay va lay masv ra
	for(NODEDK *p = a.pDSDK.pHead; p != NULL; p = p->pNext)
	{		// di vao lay ma sinh vien trong dsdk va so voi tung masv trong dssv De IN RA				
		for(NODESV *q = Dssv.pHead; q != NULL; q = q->pNext)
		{
			if(stricmp(p->DATA.MASV, q->DATA.MASV) == 0)
			{							
				//B1:  dua vao mang								
				strcpy(ArraySV[n].MASV, q->DATA.MASV); // chuyen du lieu tu sv vao mang							
				strcpy(ArraySV[n].HO, q->DATA.HO);
				strcpy(ArraySV[n].TEN, q->DATA.TEN);
				n++;// cap nhat so luong								
			}

		}
				
	}				
	system("cls");
	SetBGColor(3);			
	printf("\n\t\t                      BANG DIEM                      \n\n");
	textcolor(15);
				
	// Tao Thanh Nhac Lenh
	gotoxy(85, 5);
	printf("ESC : Thoat || ENTER: Nhap Diem");
	gotoxy(1, 1);
				
	// VE BANG 
	VeBangDanhSach(truchoanh, tructung, n + 3, chieurong, socot);// ve bang co 70 o, 20 dong, 5 cot
	char tieude[5][100] = {"STT", "MASV", "HO", "TEN", "DIEM"};
	InTieuDe(truchoanh, tructung, chieurong, socot, tieude, 5);
	// B2: Xuat Mang : dua vao nhung gi vua nhap va in ra				
	for(int h = 0; h < n; h++)
	{
		if(h + 1 < n + 3)
		{
			tempx = x;// reset lai x
			tempy += 1;// tang chi sodong len
			// x tang len y giu nguyen tren moi dong
			//gotoxy(tempx += 7, tempy);
			gotoxy(tempx += (cottb / 2)- (DemSo(h + 1) / 2), tempy);
			cout << h + 1;
						
			tempx = x;// reset lai x
			gotoxy(tempx += cottb + (cottb / 2)- (DemChuoi(ArraySV[h].MASV) / 2), tempy);
			cout << ArraySV[h].MASV;
						
			tempx = x;// reset lai x
			gotoxy(tempx += 2 * cottb + (cottb / 2)- (DemChuoi(ArraySV[h].HO)/ 2), tempy);
			cout << ArraySV[h].HO;
						
			tempx = x;// reset lai x
			gotoxy(tempx += 3 * cottb + (cottb / 2)- (DemChuoi(ArraySV[h].TEN)/ 2), tempy);
			cout << ArraySV[h].TEN;
						
			// dung msvien de xuat diem ra
			for(NODEDK *p = a.pDSDK.pHead; p != NULL; p = p->pNext)
			{	// di vao dsdk tim ma sinh vien htai 										
				if(stricmp(p->DATA.MASV, ArraySV[h].MASV) == 0)
				{			
					tempx = x;// reset lai x
				//	gotoxy(tempx += 4 * cottb + (cottb / 2)- (DemSo(p->DATA.DIEM)/ 2), tempy);	
					gotoxy(tempx += 4 * cottb + (cottb / 2), tempy);		
					// Xuat diem ra
					printf("%.2f", p->DATA.DIEM);
				}
			}
		}
					
	}
								
	///B3: Dich chuyen con tro chay theo dong minh muon nhap diem(vi tri chuot phai co lien he voi chi so cua mang)
	gotoxy(truchoanh + 63, tructung + 3);// cho con tro nhay ve vi tri dau dong
	//B5: Nhap diem va luu vao file
								
	// Tao ra Ten file voi TEN LA : MALOPTC	
	char Filename[20];// tao vung nho de luu maloptc
	TaoTenFileTheoMaLopTinChi(a.MALOPTC, Filename);// thay doi ten file
	HieuChinhDiem(truchoanh + 63, tructung + 3, a, ArraySV, Filename, n);
	delete ArraySV;
}

void XoaSinhVienDangKy(DSLOPTC &Dsloptc, int maLoptc, char *MaSV){
	for(int i = 0; i < Dsloptc.n; i++){
		if(Dsloptc.Lop[i]->MALOPTC == maLoptc){
		//	for(NODEDK *p = Dsloptc.Lop[i]->pDSDK.pHead; p != NULL; p = p->pNext){
				
		//	}
		}
	}
}

void MenuDangKy(DSLOPTC &Dsloptc, LISTSV Dssv, NODEMH *Root)
{
	do
	{		
		system("cls");		
		int x, luachon;
		bool check = false;
		luachon = MenuTuyChinh(DangKy, 8);
		switch(luachon)
		{
			case 1: // them sinh vien vao danh sach lop tin chi
			{// Nhap Sv
				system("cls");
				char *User = new char;
				VeTuyChonDuoi(1, 25, "ESC: Thoat || ENTER: Nhap tiep  Luu y: Chi su dung duoc khi nhap sai ma");
				//Nhap USER
				if(NhapUser(Dssv, User) == true) break;			
				LOPTC a;
				// dau tien ta loc ra cac lop tin chi dua vao nien khoa, hoc ky
				LocDanhSachLopTinChi(Dsloptc, check, a);
				if(check == true) break;
				// Nhap vao 1 trong cac ma lop tin chi trong danh sach da in ra va chuong trinh se tu dong them MaSv nay vao trong lop tc vua chon
				DangKyLopTinChiDuaVaoMaSinhVien(Dsloptc, Dssv, User, a);
		break;};
		case 2: {// Xoa sinh vien ra khoi lop tin chi			
			break;
		}
		case 3: 
		{
			system("cls");
			char *masv;	bool check = false;					
			LOPTC a;
			int chiso = NhapDiemTheoTuyChon(Dsloptc, Dssv, Root, a, check);
			if(chiso == -1) break;
			if(check == true){
				break;
			}
			if(Dsloptc.Lop[chiso]->pDSDK.n < 1)
			{
				BaoLoiVaNgu("Danh sach rong!", 1500);
				break;
			}
			LietKeMonDangKyDeNhapDiem(*Dsloptc.Lop[chiso], Dssv, truchoanh, tructung);			
			getch();
			break;	
		};
		case 4:
			{
				// In danh sach all cac sinh vien trong danh sach dk CUA LOPTINCHI theo 1 nien khoa nao do
				MenuSinhVienDangKyTheoNienKhoa(Dsloptc, Dssv);		
	break;  };
		case 5:
			{system("cls");			
				SetBGColor(3);			
				printf("\n\t\t\t===================DANH SACH SINH VIEN=====================\n\n");
				textcolor(15);
				cout << "\t\tSTT " << "\tMSSV" << "\tHO" << "\tTEN" << "\tPHAI" << "\tMA LOP" << "\tNAM HOC" << "\t   SDT" << endl << endl;
				InTatCaSinhVienDaDangKyLopTinChi(Dsloptc, Dssv);
				system("pause");				
				break;
			};
			case 6:// In bang diem mon hoc cua 1 lop tin chi
			{
				
			}
			case 8:
				{
					return;
				}
					
		
		}
	}while(1);
	
}

void Load_Database(NODEMH *&Root, DSLOPTC &dsloptc, LISTSV &dssv)
{
	OpenFileCayMonHoc(Root);
	OpenFileDanhSachLopTinChi(dsloptc);
	OpenFileDanhSachSinhVien(dssv);
	DocFileDanhSachSinhVienDangKy(dsloptc);
}

int main()
{
	//resizeConsole(1400, 700);
	//XoaManHinh();
	int chon;                  MONHOC mh; NODEMH *Root;          DSLOPTC dsloptc; LOPTC loptc;        	LISTSV dssv;  LISTDK dsdk;
	KhoiTaoCay(Root);
	KhoiTaoDanhSachSinhVien(dssv);
	
	Load_Database(Root, dsloptc, dssv);
	
	int luachon;
	do
	{
		system("cls");
    	chon = MenuTuyChinh (Menu, 5);  	
    	textcolor(15);
    	
    	switch (chon)// Menu Chinh
		{		
 			case 1: // Menu lop tin chi
			{						
				MenuMonHoc(Root, dsloptc);
            	break;
			};
			case 2:
			{
				MenuLopTinChi(dsloptc, Root);				
				break;
			};
			case 3:
			{				
				MenuSinhVien(dssv, dsloptc);
				
	break;  };
			case 4:
			{
				MenuDangKy(dsloptc, dssv, Root);
								
break;		};
			case 5:
			{	system("cls");
				luachon = MenuTuyChinh(YESNO, 2);
				if(luachon != 1)// chon No
				{
					break;
				}							
				return 0;
			};
		}
	}while(1);	
	// Giai phong all vung nho
				GiaiPhongCayMonHoc_DeQuy(Root);	
				GiaiPhongDanhSachSinhVien(dssv);
				// Giai phong danh sach lop tin chi 
				for(int i = 0; i < dsloptc.n; i++)
				{// giai phong danh sach SVDK nam trong no
					GiaiPhongDanhSachDangKy(dsloptc.Lop[i]->pDSDK); // phai xoa danh sach dk trong lop tc thu i  truoc
					delete dsloptc.Lop[i];		 // giai phong toan bo loptinchi thu i
				}
	BaoLoiVaNgu("giai phong all SUCCESS", 1500);
	return 0;
}
