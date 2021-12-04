//Câu 3:  Gọi thời_điểm là một mốc ngày - tháng - năm - giờ - phút trong năm 2021 và 2022.
//Xây dựng kiểu dữ liệu biểu diễn các mốc sự kiện với mỗi mốc sự kiện cần biểu diễn 3 thông tin : 
//thời_điểm, tên sự kiện, độ quan trọng(bao gồm 4 mức : không quan trọng, có chút quan trọng, khá quan trọng, rất quan trọng).
//Hãy viết các hàm thực hiện các việc sau :
//a / Liệt kê các sự kiện khá hoặc rất quan trọng.
//b / Liệt kê các sự kiện diễn ra vào buổi sáng.
//c / Sửa độ quan trọng của 1 sự kiện(khi biết thời điểm diễn ra sự kiện đó).
//d / Xác định sự kiện rất quan trọng sau 1 thời điểm được chỉ ra.
//e / Sắp xếp danh sách theo thứ tự thời gian.
//f / Xóa các sự kiện không quan trọng ra khỏi danh sách.
#include <iostream>
using namespace std;
typedef struct {
	unsigned short ngay, thang, nam, gio, phut;
}thoi_diem;
typedef struct
{
	thoi_diem n;
	char ten_su_kien[100];
	int do_quan_trong; 
						//Mức độ quan trọng được xét theo thang từ 1 -> 4
						//Mức 1: không quan trọng, mức 2: có chút quan trọng
						//Mức 3: khá quan trọng, mức 4: rất quan trọng
}su_kien;
bool SuKienQuanTrong(su_kien x[], int i, int& dem)
{	
	//đặt điều kiện để kiểm tra xem sự kiện đó có khá quan trọng hay rất quan trọng không
	//sự kiện khá quan trọng = 3; sự kiện rất quan trọng = 4
	if (x[i].do_quan_trong == 3 || x[i].do_quan_trong == 4)
	{
		dem++; //trả về biến đếm để tính xem có sự kiện nào hay không
		return true;
	}
	return false;
}
bool SuKienBuoiSang(thoi_diem arr[], int i, int& dem)
{	
	//đặt điều kiện để kiểm tra xem sự kiện đó có diễn ra vào buổi sáng hay không
	//sự kiện diễn ra vào buổi sáng tính từ 4h00 đến 10h59
	if (arr[i].gio >= 4 && arr[i].gio <= 10)
	{
		dem++; //trả về biến đếm để tính xem có sự kiện nào hay không
		return true;
	}
	return false;
}
int KiemTraThoiDiem(thoi_diem arr[], int n) //hàm nhập vào thời điểm và kiểm tra xem nó ở vị trí nào
{
	int ngay, thang, nam, gio, phut;
	cout << "Nhập ngày, tháng, năm, giờ, phút theo thứ tự lần lượt: ";
	cin >> ngay >> thang >> nam >> gio >> phut;
	for (int i = 0; i < n; i++)
	{
		if (ngay == arr[i].ngay && thang == arr[i].thang && nam == arr[i].nam && gio == arr[i].gio && phut == arr[i].phut)
			return i; //trả về trị trí của i
	}
	return -1; //giá trị vừa nhập không phù hợp thì sẽ trả về -1
}
bool SuaDoQuanTrong(su_kien x[], thoi_diem arr[], int n, int DoQuanTrong)//sửa độ quan trọng của 1 thời điểm thành DoQuanTrong
{
	int i = KiemTraThoiDiem(arr, n);
	if (i != -1)
	{
		x[i].do_quan_trong = DoQuanTrong;
		return true;
	}
	return false;//i=-1 thì sẽ báo lỗi
}
int XacDinhThoiDiem(thoi_diem arr[], int i)
{
	//ta chuyển thời điểm thành tổng số phút và gán vào mảng thoigian có tối đa 1000 phần tử
	//Tính theo quy định 1 năm = 12 tháng, 1 tháng = 31 ngày, 1 ngày = 24 giờ, 1 giờ = 60 phút
	//Lấy cột mốc bắt đầu từ 0:00 ngày 1 tháng 1 năm 2021
	int thoigian = (arr[i].nam - 2021) * 12 * 31 * 24 * 60 + arr[i].thang * 31 * 24 * 60 + arr[i].ngay * 24 * 60 + arr[i].gio * 60 + arr[i].phut;
	return thoigian;
}
bool SKSauThoiDiem(su_kien x[], thoi_diem arr[],thoi_diem T[], int i, int& dem)//Xác định sự kiện rất quan trọng sau 1 thời điểm T được chỉ ra
{
	int thoidiem_goc = XacDinhThoiDiem(T,0);//ta mặc định struct thoi_diem T chỉ có 1 phần tử ở vị trí 0
	if (XacDinhThoiDiem(arr, i) > thoidiem_goc && x[i].do_quan_trong == 4)
	{
		dem++;
		return true;
	}
	return false;
}
void Swap(su_kien &a, su_kien &b)//chuyển đổi giá trị của 2 structure su_kien
{
	su_kien temp = a;
	a = b;
	b = temp;
}
void SwapNumber(int& a, int& b)//chuyển đổi giá trị của 2 số nguyên
{
	int temp = a;
	a = b;
	b = temp;
}
void SapXepThoiGian(su_kien x[],thoi_diem arr[], const int n)
{
	//Ta chuyển đổi thời điểm thành phút, sử dụng hàm XacDinhThoiDiem, và gán vào mảng thoigian
	int temp = 0;
	int thoigian[1000];
	for (int i = 0; i < n; i++)
	{
		thoigian[i] = XacDinhThoiDiem(arr, i);
	}
	//Nếu thời gian trước lớn hơn thời gian sau thì ta hoán đổi cả 2 vị trí của 2 mảng thoigian và mảng x của su_kien
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (thoigian[i] > thoigian[j])
			{
				Swap(x[i], x[j]);
				SwapNumber(thoigian[i], thoigian[j]);
			}
		}
	}
}
void XoaSuKien(su_kien x[], int& n)
{	
	//Xóa sự kiện không quan trọng, có mức độ quan trọng bằng 1
	for (int i = 0; i < n; i++)
	{
		if (x[i].do_quan_trong == 1)//Xét điều kiện, nếu đúng thì ta sẽ sao chép đè toàn bộ dữ liệu phía sau lên trước
		{
			for (int j = i; j < n; j++)
			{
				x[j] = x[j + 1];
			}
			n--;//trừ độ dài của dãy cho 1, tiếp tục thực hiện vòng lặp
			i--;//chặn trường hợp hoán đổi 2 vị trí đều cần phải xóa, thì lúc đó ta sẽ bỏ sót 1 vị trí
		}
		
	}
	n--;//trừ độ dài của dãy cho 1 khi kết thúc
}
void DoQuanTrong(su_kien x[], int i)
{
	//trả về mức độ quan trọng dựa trên thang đo từ 1-4
	switch (x[i].do_quan_trong)
	{
	case 1:
		cout << "		Sự kiện này không quan trọng.\n";
		break;
	case 2:
		cout << "		Sự kiện này có chút quan trọng.\n";
		break;
	case 3:
		cout << "		Sự kiện này khá quan trọng.\n";
		break;
	case 4:
		cout << "		Sự kiện này rất quan trọng.\n";
		break;
	}
}
void LietKeSKQuanTrong(su_kien x[], thoi_diem arr[], const int& n)
{	
	//Hàm liệt kê các sự kiện khá hoặc rất quan trọng (gồm ngày, tháng, năm, giờ, phút, tên sự kiện, và độ quan trọng)
	int dem = 0;
	cout << "+ Các sự kiện khá hoặc rất quan trọng: " << "\n";
	for (int i = 0; i < n; i++)
	{
		if (SuKienQuanTrong(x, i, dem))//nếu hàm trả về giá trị true
		{
			cout << "	" << arr[i].ngay << "/" << arr[i].thang << "/" << arr[i].nam << "  " << arr[i].gio << ":" << arr[i].phut;
			cout << "\n		" << x[i].ten_su_kien << "\n";
			DoQuanTrong(x, i);
		}
	}
	if (dem == 0) cout << "Không có sự kiện nào khá hoặc rất quan trọng!";
}
void LietKeSKBuoiSang(su_kien x[], thoi_diem arr[], const int& n)
{
	//Hàm liệt kê các sự kiện diễn ra vào buổi sáng (gồm ngày, tháng, năm, giờ, phút, tên sự kiện, và độ quan trọng)
	int dem = 0;
	cout << "+ Các sự kiện diễn ra vào buổi sáng: " << "\n";
	for (int i = 0; i < n; i++)
	{
		if (SuKienBuoiSang(arr, i, dem))//nếu hàm trả về giá trị true
		{
			cout << "	" << arr[i].ngay << "/" << arr[i].thang << "/" << arr[i].nam << "  " << arr[i].gio << ":" << arr[i].phut;
			cout << "\n		" << x[i].ten_su_kien << "\n";
			DoQuanTrong(x, i);
		}
	}
	if (dem == 0) cout << "Không có sự kiện nào diễn ra vào buổi sáng!";
}
void LietKeSKSauThoiDiem(su_kien x[], thoi_diem arr[], thoi_diem T[], const int& n)
{
	//Hàm liệt kê các sự kiện rất quan trọng sau 1 thời điểm cho trước (gồm ngày, tháng, năm, giờ, phút, tên sự kiện, và độ quan trọng)
	int dem = 0;
	cout << "+ Các sự kiện rất quan trọng diễn ra sau thòi điểm " << T[0].ngay << "/" << T[0].thang << "/" << T[0].nam << "  " << T[0].gio << ":" << T[0].phut << ":\n";
	for (int i = 0; i < n; i++)
	{
		if (SKSauThoiDiem(x, arr, T, i, dem))//nếu hàm trả về giá trị true
		{
			cout << "	" << arr[i].ngay << "/" << arr[i].thang << "/" << arr[i].nam << "  " << arr[i].gio << ":" << arr[i].phut;
			cout << "\n		" << x[i].ten_su_kien << "\n";
			DoQuanTrong(x, i);
		}
	}
	if (dem == 0) cout << "Không có sự kiện nào rất quan trọng diễn ra sau thời điểm trên!";
}
int main()
{
	int n = 5;
	thoi_diem t[5] = { {12,12,2022,23,59},{11,11,2021,21,12},{27,2,2022,7,30},{31,1,2021,4,30},{31,1,2021,4,35} };
	su_kien s[5] = { {t[0],"Đi ngủ",4}, {t[1], "Quê", 1},{t[2],"Nhục",3},{t[3],"Mệt",1},{t[4],"Mỏi",1} };
	thoi_diem T[1] = { 10,2,2021,12,12 };
	LietKeSKBuoiSang(s, t, n);
	LietKeSKQuanTrong(s, t, n);
	LietKeSKSauThoiDiem(s, t, T, n);
	return 0;
}