#include "Planet.h"

bool start = true;   // Начало работы
int povar;      // Повтор варианта

int CALLBACK WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR     lpCmdLine,_In_ int       nCmdShow)
{   WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    if (!RegisterClassEx(&wcex)){MessageBox(NULL,_T("Call to RegisterClassEx failed!"),_T("Windows Desktop Guided Tour"),NULL); return 1; }
    hInst = hInstance;
    HWND hWnd = CreateWindow(szWindowClass,szTitle,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,500,100,NULL,NULL,hInstance,NULL);
    if (!hWnd){MessageBox(NULL,_T("Call to CreateWindow failed!"),_T("Windows Desktop Guided Tour"),NULL); return 1; }
    ShowWindow(hWnd, SW_MAXIMIZE);
    UpdateWindow(hWnd);
    MSG msg;
   
    while(GetMessage(&msg, NULL, 0, 0)){TranslateMessage(&msg); DispatchMessage(&msg);} return msg.wParam;}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{      PAINTSTRUCT ps;   
     int dist,dx,dy;
          
     static LOGFONT font;
     font.lfHeight = 20;// Устанавливает высоту шрифта или символа
     font.lfWidth = 10;// Устанавливает среднюю ширину символов в шрифте
     font.lfEscapement = 0;// Устанавливает угол, между вектором наклона и осью X устройства
     font.lfOrientation = 0;// Устанавливает угол, между основной линией каждого символа и осью X устройства
     font.lfWeight = 900;// Устанавливает толщину шрифта в диапазоне от 0 до 1000
     font.lfItalic = 1;// Устанавливает курсивный шрифт
     font.lfUnderline = 0;// Устанавливает подчеркнутый шрифт
     font.lfStrikeOut = 0;// Устанавливает зачеркнутый шрифт
     font.lfCharSet = RUSSIAN_CHARSET;// Устанавливает набор символов
     font.lfOutPrecision = 0;// Устанавливает точность вывода
     font.lfClipPrecision = 0;// Устанавливает точность отсечения
     font.lfQuality = 0;// Устанавливает качество вывода
     font.lfPitchAndFamily = 0;// Устанавливает ширину символов и семейство шрифта
                     
     switch (message)
     {
     case WM_PAINT:
         if (start) { Planet(); var = 0; nobl = 2000; start = false;  }  // Создание моря и суши
         
         hdc = BeginPaint(hWnd, &ps);
       
         Shar(hdc);  // Рисуем полушария

         // Подсветка выбранной области на полушариях
         if (nobl < 2000) {   hBrush = CreateSolidBrush(RGB(0, 255, 0)); SelectObject(hdc, hBrush);  ExtFloodFill(hdc, centx[nobl], centy[nobl], RGB(0, 0, 0), FLOODFILLBORDER); DeleteObject(hBrush); }

         // Море - синий прямоугольник
         Rectangle(hdc, 4, 1, 794, 1011); hBrush = CreateSolidBrush(RGB(0, 72, 255)); SelectObject(hdc, hBrush); ExtFloodFill(hdc, 6, 2, RGB(0, 0, 0), FLOODFILLBORDER); DeleteObject(hBrush);

         Rissusha(); // Суша - зеленые круги
        
         // Сетка
         hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); SelectObject(hdc, hPen);
         for (int i = 13; i < 795; i += 11) Line(hdc, i - 5, 5, i - 5, 1007);
         for (int i = 10; i < 1012; i += 11) Line(hdc, 8, i - 5, 790, i - 5);
         DeleteObject(hPen);

         hfont = CreateFontIndirect(&font); SetBkColor(hdc, RGB(255, 255, 255)); SetTextColor(hdc, RGB(0, 0, 255));

         povar = var;    // На всякий случай, запоминаем номер варианта

         // Маршрут
         if (var != 1) { wsprintf(hah, _T("Задайте начальную точку. Левой клавишей мыши кликните синюю клетку."));  SelectObject(hdc, hfont);  TextOut(hdc, 850, 630, hah, lstrlen(hah)); }

         if (var == 2) { hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); SelectObject(hdc, hPen); hBrush = CreateSolidBrush(RGB(255, 255, 0));    // Задана конечная точка
                         if (nlin == 0) { for (int i = 1; i < nmarshrut; i++) { dx = marshrutx[i] * 11; dy = marshruty[i] * 11;                       // Маршрут построить невозможно
                                                                                Line(hdc, dx + 10, dy + 8, dx + 10, dy + 14); Line(hdc, dx + 17, dy + 8, dx + 17, dy + 14);
                                                                                Line(hdc, dx + 10, dy + 7, dx + 18, dy + 7); Line(hdc, dx + 10, dy + 14, dx + 18, dy + 14);
                                                                                SelectObject(hdc, hBrush); ExtFloodFill(hdc, dx + 12, dy + 11, RGB(0, 0, 0), FLOODFILLBORDER);
                                                                              }
                                          wsprintf(hah, _T("Маршрут построить невозможно")); SelectObject(hdc, hfont); TextOut(hdc, 850, 600, hah, lstrlen(hah));
                                       }
                         else for (int i = 1; i < nlin; i++) { dx = marshrutx[i] * 11; dy = marshruty[i] * 11;                                  // Рисуем маршрут
                                                               Line(hdc, dx + 10, dy + 8, dx + 10, dy + 14); Line(hdc, dx + 17, dy + 8, dx + 17, dy + 14);
                                                               Line(hdc, dx + 10, dy + 7, dx + 18, dy + 7); Line(hdc, dx + 10, dy + 14, dx + 18, dy + 14);
                                                               SelectObject(hdc, hBrush); ExtFloodFill(hdc, dx + 12, dy + 11, RGB(0, 0, 0), FLOODFILLBORDER);
                                                               wsprintf(hah, _T("Длина маршрута  %d"),  nlin); SelectObject(hdc, hfont); TextOut(hdc, 850, 600, hah, lstrlen(hah));
                                                             }
                         Risob(sinx, siny, 0, 0); Risob(finx, finy, 1, 1); var = 0;   // Рисуем А и Б
                        }
         else if (var == 1) { wsprintf(hah, _T("Задайте конечную точку. Левой клавишей мыши кликните синюю клетку.")); // Задана начальная точка
                              SelectObject(hdc, hfont); TextOut(hdc, 850, 600, hah, lstrlen(hah)); 
                              Risob(sinx, siny, 0, 0); // Рисуем А
                            }

          DeleteObject(hBrush);
          DeleteObject(hPen);
          DeleteObject(hfont); 
          EndPaint(hWnd, &ps);
          break;

     case WM_LBUTTONDOWN:    
         InvalidateRect(hWnd, NULL, TRUE); 
         curx = LOWORD(lParam); cury = HIWORD(lParam); 
         dx = 1076 - curx; dy = 280 - cury;  dx *= dx;    dy *= dy;  
         if ((dx + dy) < 77841) nobl = 3000;  // Курсор в левом полушарии
         else { dx = 1637 - curx;     dx *= dx;  nobl = 2000;     
                if (((dx + dy) < 77841) && (cury>11) && (cury < 549)) nobl = 3000;  // Курсор в правом полушарии
              }
         if (nobl == 3000) { dist = 8000000; // Поиск выбранного сектора
                             for (int i = 0; i < 1306; i++) { dx = centx[i]; dy = centy[i];   dx -= curx; dx *= dx;    dy -= cury; dy *= dy;  dx += dy; if (dx < dist) { dist = dx; nobl = i; }
                                                            }
                           }
         else  Vibvar();  // Выбор варианта продолжения дилаога
         break;

     case WM_SIZE:    // Изменение размера окна
                  InvalidateRect(hWnd, NULL, TRUE); 
                  var = povar;     // Восстанавливаем номер варианта
                  break;
     case WM_DESTROY:        PostQuitMessage(0);         break;  // Закрытие окна
    
     default:                  return DefWindowProc(hWnd, message, wParam, lParam);        break; // Остальные случаи
     }
                return 0;
}