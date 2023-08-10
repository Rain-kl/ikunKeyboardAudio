#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include<Mmsystem.h>

#pragma comment(lib, "winmm.lib")
using namespace std;


void playsound(const string &key) {
    if (key >= "A" && key <= "Z") {
        string path = "med/" + key + ".wav";
        PlaySound(TEXT(path.c_str()), NULL, SND_FILENAME|SND_ASYNC);
    }
}

HHOOK keyboardHook = 0;        // 钩子句柄、

LRESULT CALLBACK LowLevelKeyboardProc(
        _In_ int nCode,        // 规定钩子如何处理消息，小于 0 则直接 CallNextHookEx
        _In_ WPARAM wParam,    // 消息类型
        _In_ LPARAM lParam    // 指向某个结构体的指针，这里是 KBDLLHOOKSTRUCT（低级键盘输入事件）
) {
    KBDLLHOOKSTRUCT *ks = (KBDLLHOOKSTRUCT *) lParam;        // 包含低级键盘输入事件信息
    /*
    typedef struct tagKBDLLHOOKSTRUCT {
        DWORD     vkCode;		// 按键代号
        DWORD     scanCode;		// 硬件扫描代号，同 vkCode 也可以作为按键的代号。
        DWORD     flags;		// 事件类型，一般按键按下为 0 抬起为 128。
        DWORD     time;			// 消息时间戳
        ULONG_PTR dwExtraInfo;	// 消息附加信息，一般为 0。
    }KBDLLHOOKSTRUCT,*LPKBDLLHOOKSTRUCT,*PKBDLLHOOKSTRUCT;
    */
    if (ks->flags == 128 || ks->flags == 129) {
        // 监控键盘
        cout << char(ks->vkCode) << endl;
        playsound(string(1, char(ks->vkCode)));
    }

    // 将消息传递给钩子链中的下一个钩子
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int _tmain(int argc, _TCHAR *argv[]) {
    cout << "gh_1c376a7dea9c" << endl;
    SetConsoleOutputCP(65001);// 更改cmd编码为utf8
    // 安装钩子
    keyboardHook = SetWindowsHookEx(
            WH_KEYBOARD_LL,            // 钩子类型，WH_KEYBOARD_LL 为键盘钩子
            LowLevelKeyboardProc,    // 指向钩子函数的指针
            GetModuleHandleA(NULL),    // Dll 句柄
            NULL
    );
    if (keyboardHook == 0) {
        cout << "挂钩键盘失败" << endl;
        return -1;
    }

    //不可漏掉消息处理，不然程序会卡死
    MSG msg;
    while (1) {
        // 如果消息队列中有消息
        if (PeekMessageA(
                &msg,        // MSG 接收这个消息
                NULL,        // 检测消息的窗口句柄，NULL：检索当前线程所有窗口消息
                NULL,        // 检查消息范围中第一个消息的值，NULL：检查所有消息（必须和下面的同时为NULL）
                NULL,        // 检查消息范围中最后一个消息的值，NULL：检查所有消息（必须和上面的同时为NULL）
                PM_REMOVE    // 处理消息的方式，PM_REMOVE：处理后将消息从队列中删除
        )) {
            // 把按键消息传递给字符消息
            TranslateMessage(&msg);

            // 将消息分派给窗口程序
            DispatchMessageW(&msg);
        } else
            Sleep(0);    //避免CPU全负载运行
    }
    // 删除钩子
    UnhookWindowsHookEx(keyboardHook);

    return 0;
}


//        switch (char(ks->vkCode)) {
//            case 'A':
//                cout << "按下了a" << endl;
//                break;
//            case 'B':
//                cout << "按下了b" << endl;
//                break;
//            case 'C':
//                cout << "按下了c" << endl;
//                break;
//        }

//return 1;		// 使按键失效