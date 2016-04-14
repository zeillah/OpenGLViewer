/**
 *  \author    : zeillah
 *  \version   : 1.0
 *  \date      : 13.04.2016
 */

#ifndef OPENGLVIEWER_GL_WINDOW_H
#define OPENGLVIEWER_GL_WINDOW_H
#include <QMainWindow>
#include <QWidget>
#include "GLViewer.h"
#include "src/models/MaterialBox.h"
#include "src/dialogs/SmoothDialog.h"
#include "src/dialogs/SubdividerDialog.h"
#include "src/dialogs/DecimationDialog.h"

class GLWindow : public QMainWindow {
    Q_OBJECT
public:
    GLWindow(QWidget *parent = 0);
    virtual ~GLWindow();

    public slots:
	void onFile();
	void onMaterial(const QString &name);
    void showSmoothingDialog();
    void showDecimationDialog();
    void showSubdivisionDialog();

	void onSmooth(int);
	void onDecimate(float);
	void onSubdivide(QString, int);
    void onShowTriangles();
    void onShowHoles();

private:
    bool showTriangles;
    bool showHoles;
    GLViewer *viewer;
    MaterialBox *materialBox;
    QSignalMapper *signalMapper;

    SmoothingDialog *sd;
    DecimationDialog *dd;
	SubdividerDialog *subd;

    void setupMenubar();
};


#endif //OPENGLVIEWER_GL_WINDOW_H
