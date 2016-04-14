//
// Created by Nicole Schmelzer on 22.06.15.
//

#include "SmoothDialog.h"

SmoothingDialog::SmoothingDialog(QWidget *parent)
     : QDialog(parent) {

    label = new QLabel(tr("Smoothing Iterations:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    smoothButton = new QPushButton(tr("Smooth"));
    smoothButton->setDefault(true);
    smoothButton->setEnabled(false);

    closeButton = new QPushButton(tr("Close"));

    connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableSmoothButton(const QString &)));
    connect(smoothButton, SIGNAL(clicked()), this, SLOT(smoothClicked()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *leftLayout = new QHBoxLayout;
    leftLayout->addWidget(label);
    leftLayout->addWidget(lineEdit);

    QHBoxLayout *rightLayout = new QHBoxLayout;
    rightLayout->addWidget(smoothButton);
    rightLayout->addWidget(closeButton);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Smooth"));
    //setFixedHeight(sizeHint().height());
}

void SmoothingDialog::smoothClicked()
{
    QString text = lineEdit->text();
    bool success;
    int smoothFactor = text.toInt(&success);
    if(success)
        emit smooth(smoothFactor);
}

void SmoothingDialog::enableSmoothButton(const QString &text)
{
     smoothButton->setEnabled(!text.isEmpty());
}