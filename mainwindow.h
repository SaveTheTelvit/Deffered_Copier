#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QDebug>

enum Mode {
    File = 0,
    Dir = 1
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dirRadioButton_clicked();
    void on_fileRadioButton_clicked();
    void on_selectButton_1_clicked();
    void on_select_button_2_clicked();
    void on_copyButton_clicked();

private:
    Ui::MainWindow *ui;
    int mode = Mode::File;
    QString fileExtension = "";
    QString bufferFromPath = "";
    QString bufferName = "";
    void updateRadioButton();
    void updateDateTime();
    void updateNameLabel();
    bool checkData();
    bool dateTimeIsValid();
    bool fromLineIsValid();
    bool toLineIsValid();
    bool nameIsValid();
    bool isValidPath(QString path, int type);
    QString getExtenstion(QString fileName);
};
#endif // MAINWINDOW_H
