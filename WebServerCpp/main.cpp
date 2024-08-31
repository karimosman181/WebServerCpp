#include "WebServer.h"

//using namespace std;

void main()
{

	WebServer ws("0.0.0.0", 8000);

	if (ws.init() != 0) {
		return;
	}

	ws.run();

	system("pause");
}