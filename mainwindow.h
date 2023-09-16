#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QPushButton>
#include <QTableView>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>

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
    void loadButtonOnClicked();
    void insertButtonOnClicked();
    void deleteButtonOnClicked();
    void updateButtonOnClicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    QPushButton *loadButton;
    QPushButton *insertButton;
    QPushButton *deleteButton;
    QPushButton *updateButton;


    QTableView *view;

    QGroupBox *insertGroup;
    QGroupBox *deleteGroup;
    QGroupBox *updateGroup;

    QLabel *insertNameLabel;
    QLabel *insertFamilyLabel;
    QLabel *insertIdLabel;
    QLabel *deleteLabel;
    QLabel *updateNameLabel;
    QLabel *updateFamilyLabel;
    QLabel *updateIdLabel;

    QLineEdit *InsertNameEdit;
    QLineEdit *InsertFamilyEdit;
    QLineEdit *InsertIdEdit;
    QLineEdit *deleteEdit;
    QLineEdit *updateNameEdit;
    QLineEdit *updateIdEdit;
    QLineEdit *updateFamilyEdit;


    QWidget *win;

    void createDataBase();
    void createGui();
};
#endif // MAINWINDOW_H









