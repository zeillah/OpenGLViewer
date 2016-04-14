/**
 *  \author    : Nicole Schmelzer
 *  \version   : 1.0
 *  \date      : 22.06.15
 */

#ifndef OPENGLVIEWER_SMOOTHINGDIALOG_H
#define OPENGLVIEWER_SMOOTHINGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class SmoothingDialog : public QDialog {
    Q_OBJECT

    public:
        SmoothingDialog(QWidget *parent = 0);
    private:
        QLabel *label;
        QLineEdit *lineEdit;
        QPushButton *smoothButton;
        QPushButton *closeButton;

        signals:
            void smooth(int);
    private slots:
        void smoothClicked();
        void enableSmoothButton(const QString &text);
};


#endif //OPENGLVIEWER_SMOOTHINGDIALOG_H
