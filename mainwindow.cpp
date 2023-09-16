#include "mainwindow.h"
#include "qobjectdefs.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QPushButton>
#include <QTableView>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlTableModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    win = new QWidget;
    win->setWindowTitle("DataBase");
    setCentralWidget(win);

    createDataBase();
    createGui();

    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadButtonOnClicked);

    connect(insertButton, &QPushButton::clicked, this, &MainWindow::insertButtonOnClicked);
    connect(insertButton, &QPushButton::clicked, this, &MainWindow::loadButtonOnClicked);

    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteButtonOnClicked);   
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::loadButtonOnClicked);

    connect(updateButton, &QPushButton::clicked, this, &MainWindow::updateButtonOnClicked);
    connect(updateButton, &QPushButton::clicked, this, &MainWindow::loadButtonOnClicked);



}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();

}

void MainWindow::createDataBase()
{
    db.setDatabaseName("/home/ali/Desktop/list.db");
    if(!db.open())
    {
        qDebug() << "Error";
        return;
    }

    QSqlQuery q;
    q.exec("CREATE TABLE list (id INTEGER PRIMARY KEY, name TEXT, family TEXT)");


}

void MainWindow::createGui()
{


    QVBoxLayout *vl = new QVBoxLayout;
    loadButton = new QPushButton("Load");
    view = new QTableView;

    vl->addWidget(view);
    vl->addWidget(loadButton);

    /////////

    insertGroup = new QGroupBox("Insert");
    insertNameLabel = new QLabel("Name");
    insertFamilyLabel = new QLabel("Family");
    insertIdLabel = new QLabel("Id");
    InsertNameEdit = new QLineEdit;
    InsertFamilyEdit = new QLineEdit;
    InsertIdEdit = new QLineEdit;
    insertButton = new QPushButton("Insert");

    QGridLayout *glInsert = new QGridLayout;
    glInsert->addWidget(insertNameLabel, 0, 0);
    glInsert->addWidget(InsertNameEdit, 0, 1);
    glInsert->addWidget(insertFamilyLabel, 1, 0);
    glInsert->addWidget(InsertFamilyEdit, 1, 1);
    glInsert->addWidget(insertIdLabel, 2, 0);
    glInsert->addWidget(InsertIdEdit, 2, 1);
    glInsert->addWidget(insertButton, 3, 0, 1, 2);
    insertGroup->setLayout(glInsert);

    /////////

    deleteGroup = new QGroupBox("Delete");
    deleteButton = new QPushButton("Delete");
    deleteLabel = new QLabel("Id");
    deleteEdit = new QLineEdit;

    QGridLayout *glDelete = new QGridLayout;
    glDelete->addWidget(deleteLabel, 0, 0);
    glDelete->addWidget(deleteEdit, 0, 1);
    glDelete->addWidget(deleteButton, 1, 0, 1 ,2);
    deleteGroup->setLayout(glDelete);

    /////////

    updateGroup = new QGroupBox("Update");
    updateButton = new QPushButton("Update");
    updateIdLabel = new QLabel("Id");
    updateNameLabel = new QLabel("Name");
    updateFamilyLabel = new QLabel("Family");
    updateNameEdit = new QLineEdit;
    updateFamilyEdit = new QLineEdit;
    updateIdEdit = new QLineEdit;

    QGridLayout *glUpdate = new QGridLayout;
    glUpdate->addWidget(updateNameLabel, 0, 0);
    glUpdate->addWidget(updateNameEdit, 0, 1);
    glUpdate->addWidget(updateFamilyLabel, 1, 0);
    glUpdate->addWidget(updateFamilyEdit, 1, 1);
    glUpdate->addWidget(updateIdLabel, 2, 0);
    glUpdate->addWidget(updateIdEdit, 2, 1);
    glUpdate->addWidget(updateButton, 3, 0, 1, 2);
    updateGroup->setLayout(glUpdate);

    /////////

    QHBoxLayout *hlAll = new QHBoxLayout;
    hlAll->addWidget(insertGroup);
    hlAll->addWidget(deleteGroup);
    hlAll->addWidget(updateGroup);


    QVBoxLayout *vlAll = new QVBoxLayout(win);
    vlAll->addLayout(vl);
    vlAll->addLayout(hlAll);
    win->setLayout(vlAll);
}

void MainWindow::loadButtonOnClicked()
{
    QSqlQuery q;
    q.exec("SELECT * FROM list");
    QSqlTableModel *m = new QSqlTableModel;
    m->setQuery(q);
    view->setModel(m);

}

void MainWindow::insertButtonOnClicked()
{
    QString name = InsertNameEdit->text();
    QString family = InsertFamilyEdit->text();
    int id = InsertIdEdit->text().toInt();

    QSqlQuery q;
    q.prepare("INSERT INTO list (id, name, family) VALUES ( :id, :name, :family)");
    q.bindValue(":id", id);
    q.bindValue(":name", name);
    q.bindValue(":family", family);

    if(!q.exec())
        qDebug() << "Error";

    InsertNameEdit->setText("");
    InsertFamilyEdit->setText("");
    InsertIdEdit->setText("");
}

void MainWindow::deleteButtonOnClicked()
{
    int i = deleteEdit->text().toInt();

    QSqlQuery q;

    q.prepare("DELETE FROM list WHERE id = :id ");
    q.bindValue(":id", i);

    if(!q.exec())
        qDebug() << "Error";

    deleteEdit->setText("");

}

void MainWindow::updateButtonOnClicked()
{
    QString name = updateNameEdit->text();
    QString family = updateFamilyEdit->text();
    int id = updateIdEdit->text().toInt();


    QSqlQuery q;
    q.prepare("UPDATE list SET name = :name, family = :family WHERE id = :id");
    q.bindValue(":id", id);
    q.bindValue(":name", name);
    q.bindValue(":family", family);

    if(!q.exec())
        qDebug() << "Error";

    updateNameEdit->setText("");
    updateFamilyEdit->setText("");
    updateIdEdit->setText("");
}




