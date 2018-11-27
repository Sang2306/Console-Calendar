#include <iostream>
#include <windows.h>
#include <cstring>
#include <ctime>
#include <conio.h>
#include <thread>
void Setcolor(WORD color);
void Setbkcolor(WORD color);
void ChangeFont(int width = 0, int height = 21);
void Moveto(short x,short y);
template<class _Tp>
void Print_at(int x, int y, _Tp data);
void ShowCursor(bool visible);
void DisableMaximizeButton();
struct Point;
void drawLine(Point start, int lenght, short direct, int symbolCode);
void drawRect(Point topLeft, Point bottomRight);
void XoaKhuNoiDung(int x = 42, int y = 4, int x1 = 97, int y1 = 20);

void ShowTime();
bool CalculateTime();
int* CalculateCols(int day, int pos_rows, int max_pos, int numbers_day_of_month);
void Print_Using_Standard(const auto& sd);
bool CheckLeapYear(const int& year);
int SoNgayCuaThang(const int& month, const int& year);
void Calendar(int day = 1, int month = 1, int year = 1900, int week_day = 1, bool reset = true);

int old_year, old_month, old_day, old_wday;
int main()
{
    DisableMaximizeButton();
    time_t tObj;
	time(&tObj);
	tm *timeStruct;
	timeStruct = localtime(&tObj);
    old_day    = timeStruct->tm_mday;
    old_wday   = timeStruct->tm_wday;
    old_month  = timeStruct->tm_mon + 1;
    old_year   = timeStruct->tm_year + 1900;
    Calendar(true);     Print_Using_Standard("Think twice code once");

    std::thread thread_1(ShowTime);
    thread_1.join();
    return 0;
}

void Setcolor(WORD color)
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
void Setbkcolor(WORD color)
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
void DisableMaximizeButton()
{
	HWND consoleWindow  = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow , GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void ChangeFont(int width, int height)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = width;                   // Width
	cfi.dwFontSize.Y = height;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
void Moveto(short x,short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = {x,y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}
template<class _Tp>
void Print_at(int x, int y, _Tp data)
{
	Moveto(x, y);
	std::cout << data;
}
void ShowCursor(bool visible)
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = visible;
   SetConsoleCursorInfo(consoleHandle, &info);
}
struct Point{
	int x,y;
	Point(int i, int j):x(i), y(j){}
};
void drawLine(Point start, int lenght, short direct, int symbolCode)
{
	if(direct==1){
		for (int i = start.x; i <= lenght; i++)
			Print_at(i, start.y, (char)symbolCode);
	}else if(direct==2){
		for (int j = start.y; j <= lenght; j++)
			Print_at(start.x, j, (char)symbolCode);
	}
}
/*
	@param start : chi dinh diem bat ky ky tren console
	@param lenght: chieu dai cua duong thang muon ve
	@param direct: huong cua duong thang (!: ngang, 2: doc)
	@param symbolcode: ma cua bieu tuong can in ra
*/
void drawRect(Point topLeft, Point bottomRight)
{
	Print_at(topLeft.x, topLeft.y, (char)218);
	Print_at(bottomRight.x, topLeft.y, (char)191);
	Print_at(bottomRight.x, bottomRight.y, (char)217);
	Print_at(topLeft.x, bottomRight.y, (char)192);
	drawLine(Point(topLeft.x+1, topLeft.y), bottomRight.x-1, 1, 196);
	drawLine(Point(topLeft.x+1, bottomRight.y), bottomRight.x-1, 1, 196);
	drawLine(Point(topLeft.x, topLeft.y+1), bottomRight.y-1, 2, 179);
	drawLine(Point(bottomRight.x, topLeft.y+1), bottomRight.y-1, 2, 179);
	Moveto(topLeft.x+1, (bottomRight.y-topLeft.y)/2 + topLeft.y);
}
/*
	@param topLeft: goc tren ben trai
	@param bottomRight: goc duoi ben phai
	1: ngang
	2: doc
*/
void XoaKhuNoiDung(int x, int y, int x1, int y1  )
{
	ShowCursor(false);
	int i = x;
	while (i <= x1){
			if(i+20 > x1){
				if(i+5 > x1){
					for (int j = y; j <= y1; j++){
						Print_at(i, j, " ");//1 khoang trong
					}
					i++;
				}else{
					for (int j = y; j <= y1; j++){
						Print_at(i, j, "     ");//5 khoang trong
					}
					i += 5;
				}
			}else{
				for (int j = y; j <= y1; j++){
					Print_at(i, j, "                    ");//20 khoang trong
				}
				i += 20;
			}

	}
}
bool CalculateTime()
{
    ShowCursor(false);
	time_t tObj;
	time(&tObj);
	tm *timeStruct;
	timeStruct = localtime(&tObj);
    std::string time_repr_hour = (timeStruct->tm_hour < 10)? '0' + std::to_string(timeStruct->tm_hour):std::to_string(timeStruct->tm_hour);
    std::string time_repr_min = (timeStruct->tm_min < 10)?('0' + std::to_string(timeStruct->tm_min)):(std::to_string(timeStruct->tm_min));
    std::string time_repr_sec =  (timeStruct->tm_sec < 10)?('0' + std::to_string(timeStruct->tm_sec)):(std::to_string(timeStruct->tm_sec));
    Print_at(20, 15, time_repr_hour + ':' + time_repr_min + ':' + time_repr_sec);
    if(timeStruct->tm_mon+1 != old_month || timeStruct->tm_mday != old_day || timeStruct->tm_year+1900 != old_year)
    {
        old_day   = timeStruct->tm_mday;
        old_wday  = timeStruct->tm_wday;
        old_month = timeStruct->tm_mon + 1;
        old_year  = timeStruct->tm_year + 1900;
        return false;
    }
    return true;
}

void ShowTime()
{
    while(true)
	{
	    ChangeFont(10,20);
	    int changeSystemDateTime = CalculateTime();
	    if(!changeSystemDateTime)
        {
            XoaKhuNoiDung(50, 5, 90, 30);
            Calendar(true);
        }
	}
}

void Print_Using_Standard(const auto& sd)
{
    Print_at(2, 2, "You are using LTS_Calendar");
    Print_at(2, 3, sd);
}
bool CheckLeapYear(const int& year)
{
	return (year%4==0 && (year%100!=0 || year%400==0));
}

short months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int SoNgayCuaThang(const int& month, const int& year)
{
	if(CheckLeapYear(year))
		return (month==2)?(months[month]+1):(months[month]);
	else
		return months[month];
}

int* CalculateCols(int day, int pos_rows, int max_pos, int numbers_day_of_month)
{
    int* cols = new int[6]{0};
    for(int i = (pos_rows < max_pos)?1:0; i < 6; i++)
    {
        if(day > numbers_day_of_month)
            break;
        cols[i] = day;
        day+=7;
    }
    return cols;
}

void Calendar(int day, int month, int year, int week_day, bool reset)
{
    int numbers_day_of_month, pivot_1, pivot_2;
	if(reset)
    {
        numbers_day_of_month = SoNgayCuaThang(old_month, old_year);
        pivot_1 = old_wday;
        pivot_2 = old_day;
        Print_at(20, 5, " " + std::to_string(old_month) + '/' + std::to_string(old_year) + " ");
    }else
    {
        numbers_day_of_month = SoNgayCuaThang(month, year);
        pivot_1 = week_day;
        pivot_2 = day;
        Print_at(20, 5, " " + std::to_string(month) + '/' + std::to_string(year) + " ");
    }
	int x =0, y = 1;
	int FLAGS[2][7];
	int DAYS[6][7];
    int max_pos = 0;
    for(int i = 0; i < 7; i++)
    {
        int d = pivot_2 + (i + 1 - pivot_1);//lay ngay cua 1 tuan dua vao ngay hien tai
        int j = 1;                          //vi tri dung theo dong tren lich
        while(d - 7 > 0)
        {
            d -= 7;
            j++;
        }
        FLAGS[0][i] = d;
        FLAGS[1][i] = j;
        max_pos = max_pos < j?j:max_pos;
    }

	for(int i = 0; i < 7; i++)
    {
        int* arr_days = CalculateCols(FLAGS[0][i], FLAGS[1][i], max_pos, numbers_day_of_month);
        for(int k = 0; k < 6; k++)
        {
            DAYS[k][i] = arr_days[k];
        }
        delete[] arr_days;
    }
    Print_at(50, 5, " Hai");Print_at(55, 5, " Ba");Print_at(60, 5, " Tu");
    Print_at(65, 5, " Nam");Print_at(70, 5, " Sau");Print_at(75, 5," Bay");
    Print_at(80, 5, " CN");
	for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            if(DAYS[i][j]<=0)
            {
                x+=5;
                continue;
            }
            drawRect(Point(50+x, 6+y), Point(53+x, 8+y));
            x+=5;
            if(DAYS[i][j] == ((reset==true)?old_day:day))
            {
                Setcolor(0);
                Setbkcolor(14);
                std::cout << DAYS[i][j];
                Setcolor(15);
                Setbkcolor(0);
            }else
                std::cout << DAYS[i][j];
        }
        x=0;
        y+=4;
    }
}
