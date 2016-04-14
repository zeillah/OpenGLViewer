/**
 *  \author    : Nicole Schmelzer
 *  \version   : 1.0
 *  \date      : 27.06.15
 */

#ifndef OPENGLVIEWER_SUBDIVIDERDIALOG_H
#define OPENGLVIEWER_SUBDIVIDERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QHBoxLayout>

class SubdividerDialog : public QDialog {
    Q_OBJECT

    public:
        SubdividerDialog(QWidget *parent = 0);
        signals:
            void subdivide(QString, int);
    private:
        QLabel *label;
        QLineEdit *lineEdit;
        QPushButton *subdivideButton;
        QPushButton *closeButton;
        QRadioButton *loopSubdivision;
        QRadioButton *sqrt3Subdivision;
    private slots:
        void subdivideClicked();
        void enableSubdivideButton();
};


#endif //OPENGLVIEWER_SUBDIVIDERDIALOG_H
