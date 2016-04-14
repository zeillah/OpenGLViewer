//
// Created by Nicole Schmelzer on 27.06.15.
//

#include "SubdividerDialog.h"

SubdividerDialog::SubdividerDialog(QWidget *parent)
        : QDialog(parent) {

    label = new QLabel(tr("No of Subdivisions:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    loopSubdivision = new QRadioButton(tr("Loop Subdivision"));
    sqrt3Subdivision = new QRadioButton(tr("Sqrt3 Subdivision"));

    subdivideButton = new QPushButton(tr("Subdivide"));
    subdivideButton->setDefault(true);
    subdivideButton->setEnabled(false);

    closeButton = new QPushButton(tr("Close"));

    connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableSubdivideButton()));
    connect(loopSubdivision, SIGNAL(clicked()), this, SLOT(enableSubdivideButton()));
    connect(sqrt3Subdivision, SIGNAL(clicked()), this, SLOT(enableSubdivideButton()));
    connect(subdivideButton, SIGNAL(clicked()), this, SLOT(subdivideClicked()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *leftLayout = new QHBoxLayout;
    leftLayout->addWidget(label);
    leftLayout->addWidget(lineEdit);

    QHBoxLayout *rightLayout = new QHBoxLayout;
    rightLayout->addWidget(loopSubdivision);
    rightLayout->addWidget(sqrt3Subdivision);
    rightLayout->addWidget(subdivideButton);
    rightLayout->addWidget(closeButton);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Subdivision"));
    //setFixedHeight(sizeHint().height());
}

void SubdividerDialog::subdivideClicked()
{
    QString text = lineEdit->text();
    bool loopChecked = loopSubdivision->isChecked();
    bool sqrt3Checked = sqrt3Subdivision->isChecked();

    bool success;
    int subdivisionFactor = text.toInt(&success);

    if(success && loopChecked) {
        emit subdivide("Loop", text.toInt());
    }
    if(success && sqrt3Checked) {
       emit subdivide("Sqrt3", text.toInt());
    }

}

void SubdividerDialog::enableSubdivideButton()
{
    if((loopSubdivision->isChecked() || sqrt3Subdivision->isChecked()) && !lineEdit->text().isEmpty() ) {
        subdivideButton->setEnabled(true);
    }
    else {
        subdivideButton->setEnabled(false);
    }
}