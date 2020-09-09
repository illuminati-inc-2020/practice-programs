#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

HDC hDC=NULL; // Private GDI Device 
HGLRC hRC=NULL; // Permanent Rendering 
HWND hWnd=NULL;
HINSTANCE hInstance;

int keys[256];
int active=TRUE;
int fullscreen=TRUE;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // Declaration

GLvoid ReSizeGLScene(GLsizei width, GLsizei height) // Resize And Initialize 
{
	if (height==0)
	{
		height=1; // Making Height Equal 
	}
	glViewport(0, 0, width, height); // Reset The Current
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Reset The Projection 
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW); // Select The Modelview 
	glLoadIdentity();
}
int InitGL(GLvoid) // All Setup For OpenGL 
{
	glShadeModel(GL_SMOOTH); // Enables Smooth
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective
	return TRUE;
}
int DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen 
	glLoadIdentity(); // Reset The Current 
	return TRUE;
}
GLvoid KillGLWindow(GLvoid) // Properly Kill The 
{
	if (fullscreen)
	{
		ChangeDisplaySettings(NULL,0);
		ShowCursor(TRUE); // Show Mouse Pointer
	}
	if (hRC) // Do We Have A Rendering 
	{
		if (!wglMakeCurrent(NULL,NULL))
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC)) // Are We Able To Delete 
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL; // Set RC To NULL
	}
	if (hDC && !ReleaseDC(hWnd,hDC)) // Are We Able To Release 
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL; // Set DC To NULL
	}
	if (hWnd && !DestroyWindow(hWnd)) // Are We Able To Destroy 
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;
	}
	if (!UnregisterClass("OpenGL",hInstance)) // Are We Able To Unregister 
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;
	}
}

int CreateGLWindow(char* title, int width, int height, int bits, int fullscreenflag)
{
	GLuint PixelFormat;
	static PIXELFORMATDESCRIPTOR pfd= // pfd Tells Windows 
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER, // Must Support Double PFD_TYPE_RGBA,
		16,
		0, 0, 0, 0, 0, 0, // Color Bits Ignored
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	WNDCLASS wc; // Windows Class Structure
	DWORD dwExStyle;
	DWORD dwStyle; // Window Style
	RECT WindowRect; // Grabs Rectangle Upper 
	
	WindowRect.left=(long)0; // Set Left Value To 
	WindowRect.right=(long)width;
	WindowRect.top=(long)0;
	WindowRect.bottom=(long)height;
	
	fullscreen=fullscreenflag; // Set The Global Fullscreen

	hInstance = GetModuleHandle(NULL); // Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // Redraw On Move, And 
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO); // Load The Default 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL; // No Background Required 
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "OpenGL"; // Set The Class Name

	if (!RegisterClass(&wc)) // Attempt To Register 
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	if (fullscreen)
	{
		DEVMODE dmScreenSettings; // Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings)); // Makes Sure Memory's 
		dmScreenSettings.dmSize=sizeof(dmScreenSettings); // Size Of The Devmode 
		dmScreenSettings.dmPelsWidth = width; // Selected Screen Width
		dmScreenSettings.dmPelsHeight = height; // Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
		// Try To Set Selected Mode And Get Results. NOTE: CDS_FULLSCREEN Gets Rid Of Start 
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options. Quit Or Run In A Window.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported","ERROR",MB_OK|MB_ICONEXCLAMATION))
			{
				fullscreen=FALSE; // Select Windowed Mode 
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;
			}
		}
	}
	if (fullscreen)
	{
		dwExStyle=WS_EX_APPWINDOW; // Window Extended Style
		dwStyle=WS_POPUP; // Windows Style
		ShowCursor(FALSE); // Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; // Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;
	}
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle); // Adjust Window To 
	if (!(hWnd=CreateWindowEx(	dwExStyle, // Extended Style For 
								"OpenGL", // Class Name
								title,
								WS_CLIPSIBLINGS | // Required Window Style
								WS_CLIPCHILDREN | // Required Window Style
								dwStyle, // Selected Window Style
								0, 0,
								WindowRect.right-WindowRect.left, // Calculate Adjusted 
								WindowRect.bottom-WindowRect.top, // Calculate Adjusted 
								NULL,
								NULL,
								hInstance,
								NULL)))
	{
		KillGLWindow();
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	
	if (!(hDC=GetDC(hWnd)))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	if(!SetPixelFormat(hDC,PixelFormat,&pfd)) // Are We Able To Set
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	if (!(hRC=wglCreateContext(hDC))) // Are We Able To Get
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	if(!wglMakeCurrent(hDC,hRC))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	ShowWindow(hWnd,SW_SHOW); // Show The Window
	SetForegroundWindow(hWnd); // Slightly Higher Priority
	SetFocus(hWnd);
	ReSizeGLScene(width, height);
	if (!InitGL())
	{
		KillGLWindow();
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK WndProc(	HWND hWnd, // Handle For This Window
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_ACTIVATE: // Watch For Window
		{
			if (!HIWORD(wParam))
			{
				active=TRUE;
			}
			else
			{	
				active=FALSE;
			}
			return 0; // Return To The Message 
		}
		case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0; // Prevent From Happening
			}
			break;
		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0; // Jump Back
		}
		case WM_KEYDOWN:
		{
			keys[wParam] = TRUE;
			return 0; // Jump Back
		}
		case WM_KEYUP:
		{
			keys[wParam] = FALSE;
			return 0; // Jump Back
		}
		case WM_SIZE:
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam)); // LoWord=Width, HiWord=return 0; // Jump Back
		}
	}
	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain( HINSTANCE hInstance, // Instance
					HINSTANCE hPrevInstance, // Previous Instance
					LPSTR lpCmdLine,
					int nCmdShow) // Window Show State
{
	MSG msg;
	int done=0;
	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO))
	{
		fullscreen=FALSE; // Windowed Mode
	}
	// Create Our OpenGL Window
	if (!CreateGLWindow("NeHe's OpenGL Framework",640,480,16,fullscreen))
	{
		return 0; // Quit If Window Was 
	}
	while(!done)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) // Is There A Message 
		{
			if (msg.message==WM_QUIT) // Have We Received 
			{
				done=TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// Draw The Scene. Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE]) // Updating View Only 
			{
				done=TRUE;
			}
			else
			{
				SwapBuffers(hDC); // Swap Buffers (Double 
			}
			if (keys[VK_F1]) // Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE; // If So Make Key FALSE
				KillGLWindow();
				fullscreen=!fullscreen;
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("NeHe's OpenGL Framework",640,480,16,fullscreen))
				{
					return 0; // Quit If Window Was 
				}
			}
		}
	}
	// Shutdown
	KillGLWindow();
	return (msg.wParam);
}