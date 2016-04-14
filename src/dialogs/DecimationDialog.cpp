//
// Created by Nicole Schmelzer on 22.06.15.
//

#include "DecimationDialog.h"

DecimationDialog::DecimationDialog(QWidget *parent)
        : QDialog(parent) {

    label = new QLabel(tr("Decimation in %:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    decimateButton = new QPushButton(tr("Decimate"));
    decimateButton->setDefault(true);
    decimateButton->setEnabled(false);

    closeButton = new QPushButton(tr("Close"));

    connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableDecimateButton(const QString &)));
    connect(decimateButton, SIGNAL(clicked()), this, SLOT(decimateClicked()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *leftLayout = new QHBoxLayout;
    leftLayout->addWidget(label);
    leftLayout->addWidget(lineEdit);

    QHBoxLayout *rightLayout = new QHBoxLayout;
    rightLayout->addWidget(decimateButton);
    rightLayout->addWidget(closeButton);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Decimate"));
    //setFixedHeight(sizeHint().height());
}

void DecimationDialog::decimateClicked()
{
    QString text = lineEdit->text();

    bool success;
    float decimationFactor = text.toFloat(&success);
    if(success)
        emit decimate(decimationFactor);
}

void DecimationDialog::enableDecimateButton(const QString &text)
{
    decimateButton->setEnabled(!text.isEmpty());
}