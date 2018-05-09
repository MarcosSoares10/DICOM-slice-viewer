#ifndef PROGRESS_H
#define PROGRESS_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class Progress;
}

class Progress : public QDialog
{
    Q_OBJECT

public:
    explicit Progress(QWidget *parent = 0);
    ~Progress();


public slots:
   Q_INVOKABLE void progressChanged(qint64 a, qint64 b);

private:
    Ui::Progress *ui;
};

#endif // PROGRESS_H
