#include "WinApp.h"


WinApp* WinApp::GetInstance() 
{
	static WinApp instance;
	return &instance;
}

LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) 
{
	// ���b�Z�[�W�ɉ����ăQ�[���ŗL�̏������s��
	switch (msg)
	{
		// �E�B���h�E���j�����ꂽ
	case WM_DESTROY:
		// OS�ɑ΂��āA�A�v���I����`����
		PostQuitMessage(0);
		return 0;
	}

	// �W���̃��b�Z�[�W�������s��
	return DefWindowProc(hwnd, msg, wparam, lparam);
}



void WinApp::Initialize(int windowWidth, int windowHeight, const std::string& windowTitle)
{
	
	mWindowWidth = windowWidth;
	mWindowHeight = windowHeight;
	
	wchar_t wtitle[256] = {};
	MultiByteToWideChar(CP_ACP, 0, windowTitle.c_str(), -1, wtitle, _countof(wtitle));

	mWndClass.cbSize = sizeof(WNDCLASSEX);
	mWndClass.lpfnWndProc = (WNDPROC)WindowProc;		// �E�B���h�E�v���V�[�W����ݒ�
	mWndClass.lpszClassName = wtitle;					// �E�B���h�E�N���X��
	mWndClass.hInstance = GetModuleHandle(nullptr);		// �E�B���h�E�n���h��
	mWndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	// �J�[�\���w��


	RegisterClassEx(&mWndClass); // �E�B���h�E�N���X��OS�ɓo�^����
	RECT wrc = { 0, 0, mWindowWidth, mWindowHeight }; // �E�B���h�E�T�C�Y{ X���W, Y���W, ����, �c�� }
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false); // �����ŃT�C�Y��␳����

	// �E�B���h�E�I�u�W�F�N�g�̐���
	mHwnd = CreateWindow(
		mWndClass.lpszClassName,		// �N���X��
		wtitle,					// �^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,	// �^�C�g���o�[�Ƌ��E��������E�B���h�E
		CW_USEDEFAULT,			// �\�������W�� OS �ɂ��C��
		CW_USEDEFAULT,			// �\�������W�� OS �ɂ��C��
		wrc.right - wrc.left,	// �E�B���h�E��
		wrc.bottom - wrc.top,	// �E�B���h�E��
		nullptr,				// �e�E�B���h�E�n���h��
		nullptr,				// ���j���[�n���h��
		mWndClass.hInstance,			// �Ăяo���A�v���P�[�V�����n���h��,
		nullptr);				// �ǉ��p�����[�^�[


	// �E�B���h�E��\����Ԃɂ���
	ShowWindow(mHwnd, SW_SHOW);
}

bool WinApp::WindowQUit() 
{
	MSG msg{};

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// �A�v���P�[�V�������I���Ƃ��� message �� WM_QUIT �ɂȂ�
	return msg.message == WM_QUIT;
}

void WinApp::Finalize()
{
	UnregisterClass(mWndClass.lpszClassName, mWndClass.hInstance);
}