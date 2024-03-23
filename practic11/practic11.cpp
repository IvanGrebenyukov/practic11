// practic11.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "practic11.h"
#include <Windows.h>
#include <CommCtrl.h>
#include <commdlg.h>

#define MAX_LOADSTRING 100
#define IDC_EDIT1 2001
#define IDC_IPADDRESS1 2002
#define IDC_SLIDER1 2003
#define IDC_LISTVIEW1 2004

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);



void PrintDialog(HWND hWnd) {
    PRINTDLG pd = { sizeof(PRINTDLG) };
    pd.Flags = PD_ALLPAGES | PD_USEDEVMODECOPIESANDCOLLATE;
    pd.hwndOwner = hWnd;
    pd.nCopies = 1;
    pd.nFromPage = 15;
    pd.nToPage = 48;
    pd.nMinPage = 1;
    pd.nMaxPage = 65535;
    if (PrintDlg(&pd) != FALSE) {

    }
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.
    
    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRACTIC11, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRACTIC11));
    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

   /* HWND hwndText = CreateWindowEx(
        0,
        CLASS_NAME,
        L"FIND Text Dialog Example"
    )*/

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRACTIC11));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PRACTIC11);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной
    

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

   CreateWindowEx(0, TEXT("Button"), TEXT("Кнопка"),
       BS_CENTER | WS_CHILD | WS_VISIBLE,
       10, 10, 100, 25,
       hWnd, (HMENU)IDC_EDIT1, hInstance, NULL);

   CreateWindowEx(0, TEXT("SysIPAddress32"),
       NULL, WS_CHILD | WS_VISIBLE,
       10, 50, 200, 25,
       hWnd, (HMENU)IDC_IPADDRESS1, hInstance, NULL);

   CreateWindowEx(0, TEXT("msctls_trackbar32"),
       NULL, WS_CHILD | WS_VISIBLE,
       10, 100, 200, 25,
       hWnd, (HMENU)IDC_SLIDER1, hInstance, NULL);

   HWND hListView = CreateWindowEx(0, WC_LISTVIEW,
       NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT,
       10, 150, 200, 200,
       hWnd, (HMENU)IDC_LISTVIEW1, hInstance, NULL);

   LV_COLUMN lvColumn1 = { };
   lvColumn1.mask = LVCF_TEXT | LVCF_WIDTH;
   lvColumn1.cx = 100;
   lvColumn1.pszText = (LPWSTR)"Column 1";

   LV_COLUMN lvColumn2 = { };
   lvColumn2.mask = LVCF_TEXT | LVCF_WIDTH;
   lvColumn2.cx = 150;
   lvColumn2.pszText = (LPWSTR)"Column 2";

   ListView_InsertColumn(hListView, 0, &lvColumn1);
   ListView_InsertColumn(hListView, 0, &lvColumn2);

   

   ShowWindow(hWnd, nCmdShow);  
   UpdateWindow(hWnd);
   
   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

TCHAR szBuffer[100] = TEXT("");
HWND hDlg = NULL;
HWND hFindDialog = NULL;

FINDREPLACE findDlg;
UINT uFindMessageString = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_PRINT: {
                PrintDialog(hWnd);
                break;
            }
            case IDM_FIND:
                if (0 == uFindMessageString) {
                    uFindMessageString = RegisterWindowMessage(FINDMSGSTRING);
                }
                if (IsWindow(hFindDialog) == FALSE) {
                    findDlg.lStructSize = sizeof(FINDREPLACE);
                    findDlg.hInstance = hInst;
                    findDlg.hwndOwner = hWnd;
                    findDlg.lpstrFindWhat = szBuffer;
                    findDlg.wFindWhatLen = _countof(szBuffer);
                    hFindDialog = FindText(&findDlg);
                }
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_CHAR:
    {
        TCHAR ch = (TCHAR)wParam;
        char str[2] = { ch , '\0' };
        MessageBox(hWnd, L"WM_CHAR", L"WM_CHAR", MB_OK | MB_ICONINFORMATION);
    }
    break;
    case WM_KEYDOWN:
    {
        MessageBox(hWnd, L"WM_KEYDOWN", L"WM_KEYDOWN", MB_OK | MB_ICONINFORMATION);
    }
    break;
    case WM_MBUTTONDBLCLK:
    {
        MessageBox(hWnd, L"WM_MBUTTONDBLCLK", L"WM_MBUTTONDBLCLK", MB_OK | MB_ICONINFORMATION);
    }
    break;
    case WM_MBUTTONDOWN:
    {
        MessageBox(hWnd, L"Received WM_MBUTTONDOWN", L"WM_MBUTTONDOWN Message", MB_OK | MB_ICONINFORMATION);
    }
    break;
    case WM_MBUTTONUP:
    {
        MessageBox(hWnd, L" WM_MBUTTONUP", L"W WM_MBUTTONUP", MB_OK | MB_ICONINFORMATION);
    }
    break;
    case WM_MOUSEMOVE:
    {
        MessageBox(hWnd, L"WM_MOUSEMOVE", L"WM_MOUSEMOVE", MB_OK | MB_ICONINFORMATION);
    }
    break;
    case WM_MOVE:
    {
        MessageBox(hWnd, L"WM_MOVE", L"WM_MOVE", MB_OK | MB_ICONINFORMATION);
    }
        break;


    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
