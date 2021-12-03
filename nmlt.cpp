#include <iostream>
using namespace std;
typedef struct {
	unsigned short ngay, thang, nam, gio, phut;
}thoi_diem;
typedef struct
{
	thoi_diem n;
	char ten_su_kien[100];
	int do_quan_trong; //Mức độ quan trọng được xét theo thang từ 1 -> 4
					   //Mức 1: không quan trọng, mức 2: có chút quan trọng
					   //Mức 3: khá quan trọng, mức 4: rất quan trọng
}su_kien;
int *SuKienQuanTrong(su_kien array[], const int& n)
{
	int j = 0;
	static int a[10];
	for (int i = 0; i < n; i++)
		if (array[i].do_quan_trong == 3 || array[i].do_quan_trong == 4)
		{
			a[j] = i;
			j++;
		}
	return a;
}
int main()
{
	thoi_diem t[5] = { {12,12,2021,23,59},{11,11,2020,21,12},{27,2,2021,7,30},{31,1,2020,4,30},{31,1,2020,4,35}};
	su_kien s[5] = { {t[1], "Quê", 4},{t[2],"Nhục",3},{t[3],"Mệt",2},{t[4],"Mỏi",1},{t[0],"Đi ngủ",4}};
	SuKienQuanTrong(s, 5);
	return 0;
}