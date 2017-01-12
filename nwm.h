#ifndef NWM_H
#define NWM_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

namespace Ui {
class NWM;
}

class NWM : public QMainWindow
{
    Q_OBJECT

public:
    explicit NWM(QWidget *parent = 0);
    ~NWM();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_btnFile_clicked();

    void on_btnPatch_clicked();

private:
    Ui::NWM *ui;
    QString mod_s0beit;
    QByteArray d3d9_data;
    QFile *file;
};

#endif // NWM_H
