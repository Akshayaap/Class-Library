#include "App.h"


App::App():
	wnd(1366,768,L"MainWnd")
{

}


int App::Go() {
	int result;
	while (result=Window::ProcessMessages()) {
		
	}
	return result;
}