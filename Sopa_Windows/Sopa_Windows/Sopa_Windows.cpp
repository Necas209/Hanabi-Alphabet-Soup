// Sopa_Windows.cpp : Defines the entry point for the application.
//

#include "Game.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                DestroyAllWindows(HWND);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SOPAWINDOWS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SOPAWINDOWS));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SOPAWINDOWS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SOPAWINDOWS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and      CW_USEDEFAULT, 0
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1000, 800, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
Game game;
size_t i;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        game.Menu(hWnd);
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_BUTTON_NEWGAME:
                DestroyWindow(NewGame);
                DestroyWindow(LoadGame);
                DestroyWindow(Exit);
                game.New_Game(hWnd);
                break;
            case ID_BUTTON_LOADGAME:
                break;
            case ID_BUTTON_EXIT:
                PostQuitMessage(0);
                break;
            case ID_BUTTON_BEGINNER:
                game.Choose_Player(hWnd, ID_BUTTON_BEGINNER);
                break;
            case ID_BUTTON_EXPERT:
                game.Choose_Player(hWnd, ID_BUTTON_EXPERT);
                break;
            case ID_PLAYER_BUTTON:
                GetWindowTextA(Name_Input, p_name, 20);
                GetWindowTextA(Age_Input, p_age, 20);
                if (!isInteger(p_age))
                    ::MessageBoxA(hWnd, "Idade inválida!", "Erro" , NULL);
                else
                {
                    n_age = stoi(p_age);
                    game.Set_Player(hWnd);
                }
                break;
            case ID_BOARD_BUTTON:
                GetWindowTextA(DimX_Input, b_dimx, 20);
                GetWindowTextA(DimY_Input, b_dimy, 20);
                if (isInteger(b_dimx) and isInteger(b_dimy))
                {
                    n_dimx = stoi(b_dimx);
                    n_dimy = stoi(b_dimy);
                    game.Set_Board(hWnd);
                }
                else
                    ::MessageBoxA(hWnd, "Dimensões inválidas!", "Erro", NULL);
                break;
            case ID_FILE_NEWGAME:
                DestroyAllWindows(hWnd);
                game.New_Game(hWnd);
                break;
            case ID_FILE_SAVEGAME:
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
//
void DestroyAllWindows(HWND hWnd)
{
    DestroyWindow(NewGame);
    DestroyWindow(LoadGame);
    DestroyWindow(Exit);
    DestroyWindow(_Player);
    DestroyWindow(_Name);
    DestroyWindow(Name_Input);
    DestroyWindow(_Age);
    DestroyWindow(Age_Input);
    DestroyWindow(Player_Button);
    DestroyWindow(Board_Title);
    DestroyWindow(_DimX);
    DestroyWindow(_DimY);
    DestroyWindow(DimX_Input);
    DestroyWindow(DimY_Input);
    DestroyWindow(Board_Button);
    game.Clear_Game();
}