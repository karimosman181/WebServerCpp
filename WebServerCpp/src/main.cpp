#include "server/WebServer.h"

//using namespace std;

void main()
{

	//TODO:
	// register all the routes in a dynamic way

	WebServer ws("0.0.0.0", 8000);

	if (ws.init() != 0) {
		return;
	}

	ws.run();

	system("pause");
}