#ifndef NWM_H
#define NWM_H

#include <QMainWindow>

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

private:
    Ui::NWM *ui;
};

#endif // NWM_H
