/**
 *  \author    : Nicole Schmelzer
 *  \version   : 1.0
 *  \date      : 13.04.2016
 */

#include <QApplication>
#include "src/app/GLWindow.h"

/**
 * entry function.
 */
int main(int argc, char* argv[]) {

	//std::cout << "Current Dir " << argv[0] << std::endl;

	QApplication app(argc, argv);

    GLWindow window;
	window.show();

	return app.exec();
}
