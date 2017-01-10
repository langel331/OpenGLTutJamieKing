#include <Qt/qapplication.h>
#include <Window.h>

int main(int argc, char* argv[])
{
	//QT program
	QApplication app(argc, argv);
	
	//Create and show Window
	Window window;
	window.show();

	return app.exec();
}