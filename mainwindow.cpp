#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Deffered Copier"));
    updateDateTime();
    ui->fileRadioButton->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateRadioButton()
{
    updateNameLabel();
    QString text = bufferName;
    bufferName = ui->nameLine->text();
    ui->nameLine->setText(text);
    text = bufferFromPath;
    bufferFromPath = ui->fileLine_1->text();
    ui->fileLine_1->setText(text);
}

void MainWindow::updateDateTime()
{
    ui->dateTimeEdit->setDate(QDate::currentDate());
    ui->dateTimeEdit->setTime(QTime(0, 0));
}

void MainWindow::updateNameLabel()
{
    switch (mode) {
    case Mode::File:
        ui->nameLabel->setText(tr("New file name:"));
        break;
    case Mode::Dir:
        ui->nameLabel->setText(tr("New dir name:"));
        break;
    default:
        ui->nameLabel->setText(tr("New file name:"));
        break;
    }
}

bool MainWindow::isValidPath(QString path, int type)
{
    if (path.isEmpty()) return false;
    switch (type) {
    case Mode::File:
        {
            QFile testFile(path);
            return testFile.exists();
        }
        break;
    case Mode::Dir:
        {
            QDir testDir(path);
            return testDir.exists();
        }
        break;
    }
    return false;
}

bool MainWindow::fromLineIsValid()
{
    return isValidPath(ui->fileLine_1->text(), mode);
}

bool MainWindow::toLineIsValid()
{
    return isValidPath(ui->fileLine_2->text(), Mode::Dir);
}

bool MainWindow::nameIsValid()
{
    QString name = ui->nameLine->text();
    if (name.isEmpty()) return false;
    switch (mode) {
    case Mode::File:
        {
            if (getExtenstion(name) != fileExtension) name += "." + fileExtension;
            QFile file(ui->fileLine_2->text() + QDir::separator() + name);
            return !file.exists();
        }
        break;
    case Mode::Dir:
        {
            QDir dir(ui->fileLine_2->text() + QDir::separator() + name);
            return !dir.exists();
        }
        break;
    }
    return false;
}

bool MainWindow::dateTimeIsValid()
{
    QDateTime value = ui->dateTimeEdit->dateTime();
    return value > QDateTime::currentDateTime();
}

bool MainWindow::checkData()
{
    if (!fromLineIsValid()) {
        QMessageBox::warning(this, tr("Warning!"), tr("\"%1\" path is not existing").arg(tr("From")));
        return false;
    }
    if (!toLineIsValid()) {
        QMessageBox::warning(this, tr("Warning!"), tr("\"%1\" path is not existing").arg(tr("To")));
        return false;
    }
    if (!dateTimeIsValid()) {
        QMessageBox::warning(this, tr("Warning!"), tr("The time of copying cannot be in the past."));
        return false;
    }
    if (!nameIsValid()) {
        QMessageBox::warning(this, tr("Warning!"), tr("A similar name cannot be selected"));
        return false;
    }
    return true;
}

QString MainWindow::getExtenstion(QString fileName)
{
    int index = fileName.lastIndexOf(".");
    if (index == -1) return "";
    return fileName.mid(index + 1);
}

void MainWindow::on_dirRadioButton_clicked()
{
    mode = Mode::Dir;
    updateRadioButton();
}

void MainWindow::on_fileRadioButton_clicked()
{
    mode = Mode::File;
    updateRadioButton();
}

void MainWindow::on_selectButton_1_clicked()
{
    QString str;
    if (mode == Mode::Dir) {
        str = QFileDialog::getExistingDirectory();
    } else {
        str = QFileDialog::getOpenFileName();
    }
    if (str.isEmpty()) return;
    ui->fileLine_1->setText(str);
    str = str.mid(str.lastIndexOf(QDir::separator()) + 1);
    ui->nameLine->setText(str);
    if (mode == Mode::File) {
        fileExtension = getExtenstion(str);
    } else {
        fileExtension = "";
    }
}

void MainWindow::on_select_button_2_clicked()
{
    QString str = QFileDialog::getExistingDirectory();
    if (str.isEmpty()) return;
    ui->fileLine_2->setText(str);
}


void MainWindow::on_copyButton_clicked()
{
    if (checkData()) {

    }
}

