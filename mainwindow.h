#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Student.h>
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

public slots:

    void on_AddRecord_clicked();

    void on_Show_clicked();

    void on_SavetoFiles_clicked();

    void on_ReadfromFile_clicked();

    void OnpushBtnNextClicked();

    void OnClearBtnClicked();

    //void OnNextBtnclicked();

private:
    Ui::MainWindow *ui;
    std::vector<Student>StDetails;
};
#endif // MAINWINDOW_H
