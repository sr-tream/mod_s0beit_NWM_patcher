#include "nwm.h"
#include "ui_nwm.h"

NWM::NWM(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NWM)
{
    ui->setupUi(this);
}

NWM::~NWM()
{
    delete ui;
}

void NWM::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
