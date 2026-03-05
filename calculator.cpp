#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#define ID_BTN_ADD 1
#define ID_BTN_SUB 2
#define ID_BTN_MUL 3
#define ID_BTN_DIV 4
#define ID_EDIT1 5
#define ID_EDIT2 6

HWND hEdit1, hEdit2;

/* Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/* Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("Calculator");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    wincl.hbrBackground = CreateSolidBrush(RGB(255, 165, 0));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("My Calculator"), /* Title Text */
           WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           250,                 /* The programs width */
           200,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/* This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
        CreateWindow("STATIC", "Please input two numbers",
                     WS_VISIBLE | WS_CHILD | SS_CENTER,
                     25, 20, 180, 20, hwnd, NULL, NULL, NULL);

        hEdit1 = CreateWindow("EDIT", "",
                              WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                              45, 50, 140, 20, hwnd, (HMENU)ID_EDIT1, NULL, NULL);
        hEdit2 = CreateWindow("EDIT", "",
                              WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                              45, 80, 140, 20, hwnd, (HMENU)ID_EDIT2, NULL, NULL);
        CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                     45, 110, 30, 30, hwnd, (HMENU)ID_BTN_ADD, NULL, NULL);
        CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                     80, 110, 30, 30, hwnd, (HMENU)ID_BTN_SUB, NULL, NULL);
        CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                     115, 110, 30, 30, hwnd, (HMENU)ID_BTN_MUL, NULL, NULL);
        CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                     150, 110, 30, 30, hwnd, (HMENU)ID_BTN_DIV, NULL, NULL);
        break;

    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED) {
            int wmId = LOWORD(wParam);
            char buf1[100], buf2[100];
            GetWindowText(hEdit1, buf1, 100);
            GetWindowText(hEdit2, buf2, 100);
            double num1 = atof(buf1);
            double num2 = atof(buf2);
            double result = 0;
            char t[100];

            switch (wmId) {
                case ID_BTN_ADD: result = num1 + num2; break;
                case ID_BTN_SUB: result = num1 - num2; break;
                case ID_BTN_MUL: result = num1 * num2; break;
                case ID_BTN_DIV:
                    if (num2 != 0) {
                        result = num1 / num2;
                    } else {
                        MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
                        return 0;
                    }
                    break;
                default:
                    return 0;
            }
            sprintf(t, "%f", result);
            MessageBox(hwnd, t, "Result", MB_OK);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;

    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
