/**
 *  \author    : zeillah
 *  \version   : 1.0
 *  \date      : 13.04.2016
 */

#include "GLWindow.h"

GLWindow::GLWindow(QWidget *parent) :
        QMainWindow(parent) {

    QGLFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QGLFormat::CoreProfile);
    glFormat.setSampleBuffers(true);
    float width  = 600;
    float height = 400;
    showTriangles = false;

    //qDebug() << "App path : " << QDir::currentPath();

    QString modelPath = "../../../Documents/FH/cg/OpenGLViewer/data/model/squirrel.obj";
    QString shaderFolder = "../../../Documents/FH/cg/OpenGLViewer/data/shader/";

    materialBox = new MaterialBox();
    viewer      = new GLViewer(glFormat, modelPath, shaderFolder, height, width, this);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QGridLayout *grid = new QGridLayout();
    centralWidget->setLayout(grid);
    grid->addWidget(viewer, 0, 0);

    setupMenubar();
}

GLWindow::~GLWindow()
{

}

void GLWindow::onFile()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Model"), "", tr("Model Files (*.obj)"));
    std::cout << "Read: " << filename.toStdString() << std::endl;

    if(filename != NULL) {
        viewer->getScene()->loadObject(filename);
        viewer->update();
    }
}

void GLWindow::onMaterial(const QString &name) {
    viewer->getScene()->updateMaterial(materialBox->getMaterial(name));
}

void GLWindow::onSmooth(int factor)
{
    viewer->getScene()->smoothModel(factor);

    viewer->update();
}

void GLWindow::onDecimate(float factor)
{
    viewer->getScene()->decimateModel(factor);

    viewer->update();
}

void GLWindow::onSubdivide(QString method, int factor)
{
    viewer->getScene()->subdivideModel(method, factor);

    viewer->update();
}

void GLWindow::onShowTriangles()
{
    showTriangles = !showTriangles;
    viewer->getScene()->showTriangles(showTriangles);
}

void GLWindow::onShowHoles()
{
    showHoles = !showHoles;
    viewer->getScene()->showHoles(showHoles);
}

void GLWindow::setupMenubar()
{
    QMenuBar *menuBar = new QMenuBar(this);
    menuBar->setNativeMenuBar(false);

    QMenu *menuWindow = menuBar->addMenu(tr("Window"));
    QAction *actionQuit = new QAction(menuWindow);
    actionQuit->setText(tr("Quit"));
    menuWindow->addAction(actionQuit);
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    QMenu *menuFile = menuBar->addMenu(tr("File"));

    QAction *actionFile = new QAction(tr("&Open Obj"), this);
    menuFile->addAction(actionFile);
    connect(actionFile, SIGNAL(triggered()), this, SLOT(onFile()));

    QMenu *menuModel = menuBar->addMenu(tr("Model"));
    QAction *actionViewType = new QAction(tr("&Show/Hide Triangles"), this);
    menuModel->addAction(actionViewType);
    connect(actionViewType, SIGNAL(triggered()), this, SLOT(onShowTriangles()));
    QAction *actionHoles = new QAction(tr("&Show/Hide Highlight for Holes of Mesh"), this);
    menuModel->addAction(actionHoles);
    connect(actionHoles, SIGNAL(triggered()), this, SLOT(onShowHoles()));

    QMenu *menuMaterial = menuModel->addMenu(tr("&Material"));

    signalMapper = new QSignalMapper(this);

    for(int i=0; i < materialBox->materials.size(); i++) {
        QAction *actionMaterial = new QAction(menuMaterial);
        signalMapper->setMapping(actionMaterial, materialBox->materials[i]->name);
        actionMaterial->setText(materialBox->materials[i]->name);
        menuMaterial->addAction(actionMaterial);
        connect(actionMaterial, SIGNAL(triggered()), signalMapper, SLOT(map()));
    }
    connect(signalMapper, SIGNAL(mapped(QString)),
            this, SLOT(onMaterial(QString)));
    setMenuBar(menuBar);

    sd = new SmoothingDialog();
    dd = new DecimationDialog();
    subd = new SubdividerDialog();

    QMenu *menuTransformation = menuBar->addMenu(tr("Transformation"));
    QAction *actionTransformation = new QAction(tr("&Smooth"), this);
    menuTransformation->addAction(actionTransformation);
    connect(actionTransformation, SIGNAL(triggered()), this, SLOT(showSmoothingDialog()));
    QAction *actionTransformation2 = new QAction(tr("&Decimate"), this);
    menuTransformation->addAction(actionTransformation2);
    connect(actionTransformation2, SIGNAL(triggered()), this, SLOT(showDecimationDialog()));
    QAction *actionTransformation3 = new QAction(tr("Subdivide"), this);
    menuTransformation->addAction(actionTransformation3);
    connect(actionTransformation3, SIGNAL(triggered()), this, SLOT(showSubdivisionDialog()));

    connect(sd, SIGNAL(smooth(int)), this, SLOT(onSmooth(int)));
    connect(dd, SIGNAL(decimate(float)), this, SLOT(onDecimate(float)));
    connect(subd, SIGNAL(subdivide(QString, int)), this, SLOT(onSubdivide(QString, int)));

}

void GLWindow::showSmoothingDialog()
{
    sd->show();
}


void GLWindow::showDecimationDialog()
{
    dd->show();
}

void GLWindow::showSubdivisionDialog()
{
    showTriangles = true;
    viewer->getScene()->showTriangles(showTriangles);
    subd->show();
}