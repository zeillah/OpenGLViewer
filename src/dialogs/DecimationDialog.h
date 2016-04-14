/**
 *  \author    : zeillah
 *  \version   : 1.0
 *  \date      : 22.06.2015
 */

#ifndef OPENGLVIEWER_DECIMATIONDIALOG_H
#define OPENGLVIEWER_DECIMATIONDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class DecimationDialog : public QDialog {
    Q_OBJECT

    public:
        DecimationDialog(QWidget *parent = 0);
        signals:
            void decimate(float);
    private:
        QLabel *label;
        QLineEdit *lineEdit;
        QPushButton *decimateButton;
        QPushButton *closeButton;
    private slots:
        void decimateClicked();
        void enableDecimateButton(const QString &text);
};


#endif //OPENGLVIEWER_DECIMATIONDIALOG_H
