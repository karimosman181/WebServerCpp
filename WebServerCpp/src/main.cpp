#include "server/WebServer.h"

//using namespace std;

int main()
{

	//TODO:
	// register all the routes in a dynamic way

	WebServer ws("0.0.0.0", 8000);

	if (ws.init() != 0) {
		return -1;
	}

	ws.run();

	system("pause");

	return 0;
}