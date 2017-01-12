#include "nwm.h"
#include "ui_nwm.h"

NWM::NWM(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NWM)
{
    ui->setupUi(this);
    this->setFixedSize(400, 130);
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

void NWM::on_btnFile_clicked()
{
    mod_s0beit = QFileDialog::getOpenFileName(this, tr("Select mod_s0beit"),
                                              "" , tr("d3d9.dll"));
    ui->btnPatch->setEnabled(true);
    ui->txtPath->setText(mod_s0beit);
}

void NWM::on_btnPatch_clicked()
{
    file = new QFile(mod_s0beit);
    file->open(QIODevice::ReadWrite);
    d3d9_data = file->readAll();

    bool easy = false;
    bool full = false;
    for(int i = 0; i < d3d9_data.size(); ++i){

        if ((ui->rbEeasy->isChecked() || ui->rbFull->isChecked())
                && i + 4 < d3d9_data.size()){
            if (d3d9_data[i + 0] == (char)0x83 &&
                d3d9_data[i + 1] == (char)0xEC &&
                d3d9_data[i + 2] == (char)0x28 &&
                d3d9_data[i + 3] == (char)0x68){

                easy = true;
                d3d9_data.replace(i, 1, "\xC3");
            }
        }
        if (ui->rbFull->isChecked() && i + 12 < d3d9_data.size()){
            if (d3d9_data[i + 0] == (char)0x53 &&
                d3d9_data[i + 1] == (char)0x56 &&
                d3d9_data[i + 2] == (char)0x57 &&
                d3d9_data[i + 3] == (char)0x8B &&
                d3d9_data[i + 4] == (char)0x7D &&
                d3d9_data[i + 5] == (char)0x1C &&
                d3d9_data[i + 6] == (char)0x33 &&
                d3d9_data[i + 7] == (char)0xDB &&
                d3d9_data[i + 8] == (char)0x8B &&
                d3d9_data[i + 9] == (char)0x47 &&
                d3d9_data[i + 10] == (char)0x30 &&
                d3d9_data[i + 11] == (char)0xA3){

                full = true;
                d3d9_data.replace(i + 6, 2, "\x90\x90");
            }
        }
        if (ui->rbRestore->isChecked()){

            if (i + 4 < d3d9_data.size()){
                if (d3d9_data[i + 0] == (char)0xC3 &&
                    d3d9_data[i + 1] == (char)0xEC &&
                    d3d9_data[i + 2] == (char)0x28 &&
                    d3d9_data[i + 3] == (char)0x68){

                    easy = true;
                    d3d9_data.replace(i, 1, "\x83");
                }
            }
            if (i + 12 < d3d9_data.size()){
                if (d3d9_data[i + 0] == (char)0x53 &&
                    d3d9_data[i + 1] == (char)0x56 &&
                    d3d9_data[i + 2] == (char)0x57 &&
                    d3d9_data[i + 3] == (char)0x8B &&
                    d3d9_data[i + 4] == (char)0x7D &&
                    d3d9_data[i + 5] == (char)0x1C &&
                    d3d9_data[i + 6] == (char)0x90 &&
                    d3d9_data[i + 7] == (char)0x90 &&
                    d3d9_data[i + 8] == (char)0x8B &&
                    d3d9_data[i + 9] == (char)0x47 &&
                    d3d9_data[i + 10] == (char)0x30 &&
                    d3d9_data[i + 11] == (char)0xA3){

                    full = true;
                    d3d9_data.replace(i + 6, 2, "\x33\xDB");
                }
            }
        }
        if ((ui->rbEeasy->isChecked() && easy) ||
            (ui->rbFull->isChecked() && easy && full))
            break;
    }

    if (!easy && !full){
        QMessageBox msgBox;
        msgBox.setText("NWM patching is failed");
        msgBox.exec();
    } else {
        file->remove();
        file->open(QIODevice::WriteOnly);
        file->reset();
        file->write(d3d9_data);
        QMessageBox msgBox;
        msgBox.setText("NWM patching is successfully");
        msgBox.exec();
    }
    file->close();
    delete file;
}
