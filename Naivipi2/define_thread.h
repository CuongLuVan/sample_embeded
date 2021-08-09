#ifndef DEFINE_THREAD_H
#define DEFINE_THREAD_H

#endif // DEFINE_THREAD_H
#define  WM_APP 1
#define MAIN_THEAD WM_APP+1

#define PROCESS_TO_MAIN_THEAD WM_APP+10
#define AUDIO_TO_MAIN_THEAD WM_APP+11
#define SCREEN_TO_MAIN_THEAD WM_APP+12
#define COMMUNICATE_TO_MAIN_THEAD WM_APP+13

#define FROM_PROCESS_TASK WM_APP+2
#define FROM_AUDIO_TASK WM_APP+3
#define FROM_SCREEN_TASK WM_APP+4
#define FROM_COMMUNICATE_TASK WM_APP+5
#define FROM_SENSOR            001
#define FROM_BLDC              002
#define FROM_JOYSTICK          003
#define FROM_JOYSTICK_MECHANIC 004
#define far
#define TIMEOUT_20MS 100
typedef unsigned long DWORD;
typedef void far *LPVOID;

/*typedef struct tagMSG{
    HWND hwnd;
    UNIT message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD time;
    POINT pt;
#ifdef _MAC
    DWORD lPrivate;
#endif
}MSG, *PMSG, NEAR *NPMSG, FAR *LPMSG;
*/





