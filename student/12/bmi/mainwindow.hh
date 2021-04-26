#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_weightLineEdit_editingFinished();

    void on_weightLineEdit_textChanged(const QString &arg1);

    void on_heightLineEdit_editingFinished();

    void on_heightLineEdit_textChanged(const QString &arg1);

    void on_countButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::MainWindow *ui;

    QString weight_;
    QString height_;
};
#endif // MAINWINDOW_HH
