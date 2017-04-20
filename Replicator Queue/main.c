#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "resource.h"
#include "queueDefs.h"
#include <tchar.h>

const char g_szClassName[] = "myWindowClass";
queue myQueue;
experiment myExperiment[100];
//char expName[100];
//char expFoulant[100];

char expName[100];
char expFoulant[100];

// message loop for 'create experiment' dialog box (IDD_DIALOG1)
BOOL CALLBACK AboutDlgProc1(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT1);
			HWND hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
			int a = GetWindowTextLength(hEdit);
			int b = GetWindowTextLength(hEdit2);

			

			// if all fields have not been filled
			if ((a <= 0) || (b <= 0) || (IsDlgButtonChecked(hwnd, IDC_RADIO1) == BST_UNCHECKED &&
				IsDlgButtonChecked(hwnd, IDC_RADIO2) == BST_UNCHECKED &&
				IsDlgButtonChecked(hwnd, IDC_RADIO3) == BST_UNCHECKED)) {
				MessageBox(hwnd, L"Please complete all fields", L"Error", MB_OK | MB_ICONEXCLAMATION);
				break;
			}
			// if flux step is selected
			else if (IsDlgButtonChecked(hwnd, IDC_RADIO1) == BST_CHECKED) {

				// get experiment name and foulant

				GetDlgItemTextA(hwnd, IDC_EDIT1, expName, 100);
				GetDlgItemTextA(hwnd, IDC_EDIT2, expFoulant, 100);

				// create experiment
				int free = getFreeExperiment(myQueue);
				myExperiment[free].name = expName;
				//assert(myExperiment[free].name == name);
				//assert(myExperiment[free].name =='test');
				myExperiment[free].foulant = expFoulant;
				myExperiment[free].number = free;

				

				/*const char *tempTargetFile = VIEW_QUEUE_TARGET_FILE;
				FILE *f = fopen(tempTargetFile, "w");*/
				//fprintf(f, "%s\n", myExperiment[free].name);
				/*fprintf(f, "%s\n\n", myExperiment[free].foulant);
				fprintf(f, "%d\n\n", free);
				fprintf(f, "%d\n\n", myExperiment[free].number);*/

				addExperiment(myQueue, free);
				//fprintf(f, "%s\n", myQueue->head->name);
				//link test = myQueue->head;
				//fprintf(f, "%s\n", test->name);	

				/*int ret = DialogBox(GetModuleHandle(NULL),
					MAKEINTRESOURCE(IDD_DIALOG3), hwnd, AboutDlgProc2);*/

				EndDialog(hwnd, IDOK);
			}
			break;
		}
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

// message loop for main window
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		// what happens when create experiment is pressed
		case IDC_CREATE_EXPERIMENT_BUTTON:
		{
			int ret = DialogBox(GetModuleHandle(NULL),
				MAKEINTRESOURCE(IDD_DIALOG1), hwnd, AboutDlgProc1);
			if (ret == -1) {
				MessageBox(hwnd, L"Dialog failed!", L"Error",
					MB_OK | MB_ICONINFORMATION);
			}
		}
		break;
		// what happens when view queue button is pressed
		case IDC_VIEW_QUEUE_BUTTON:
		{
			viewQueue(myQueue);
		}
		break;
		}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEXW wc;
	HWND hwnd, hwndButton, hwndButton2, hwndButton3, hwndButton4;
	MSG Msg;

	// registering the window class for the main window
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassExW(&wc))
	{
		MessageBox(NULL, L"Window Registration Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// creating the Window
	hwnd = CreateWindowExW(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		L"UTS Experimental Control Station",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	hwndButton = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"&Create Experiment",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		5,         // x position 
		180,         // y position 
		200,        // Button width
		40,        // Button height
		hwnd,     // Parent window
		(HMENU)IDC_CREATE_EXPERIMENT_BUTTON,       // No menu.
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	hwndButton2 = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"&Edit Experiment",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_FLAT,  // Styles 
		5,         // x position 
		240,         // y position 
		200,        // Button width
		40,        // Button height
		hwnd,     // Parent window
		(HMENU)IDC_EDIT_EXPERIMENT_BUTTON,       // No menu.
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	hwndButton3 = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"&View Queue",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_FLAT,  // Styles 
		5,         // x position 
		300,         // y position 
		200,        // Button width
		40,        // Button height
		hwnd,     // Parent window
		(HMENU)IDC_VIEW_QUEUE_BUTTON,       // No menu.
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	hwndButton4 = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"&Edit Queue",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_FLAT,  // Styles 
		5,         // x position 
		360,         // y position 
		200,        // Button width
		40,        // Button height
		hwnd,     // Parent window
		(HMENU)IDC_EDIT_QUEUE_BUTTON,       // No menu.
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// initializing the experiment queue
	myQueue = malloc(sizeof(struct _queue));
	if (myQueue == NULL) {
		free(myQueue);
		MessageBox(NULL, L"Queue Creation Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
	}
	else {
		myQueue->head = NULL; // change this to see if there are previous saved queues
	}

	int i = 0;
	while (i < 100) {
		myExperiment[i].next = NULL;
		i = i + 1;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}