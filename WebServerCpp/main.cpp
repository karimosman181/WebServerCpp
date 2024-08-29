#include "MultiClientChat.h"

//using namespace std;

void main()
{

	MultiClientChat mcc("0.0.0.0", 54000);

	if (mcc.init() != 0) {
		fprintf(stdout, "end\n");
		return;
	}

	mcc.run();

	system("pause");
}