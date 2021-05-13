#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , tree()
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new  QGraphicsScene(this);
    scene->addRect(0, 0, 400, 400);
    scene->clear();
    ui->graphicsView->setScene(scene);
}


void MainWindow::_showBranch(BinaryTree<QString>::BinaryTreeNode* root, int x, int y)
{
    QGraphicsTextItem* text = scene->addText((QString)"key: " + QString::number(root->getKey()) + (QString)"\nText: " + root->item->getItem());
    text->setX(x);
    text->setY(y);
    if(root->left_child != nullptr) {
        scene->addLine(x + 30, y + 35, x - 65, y + 70);
        _showBranch(root->left_child, x - 100, y + 70);
    }
    if(root->right_child != nullptr) {
        scene->addLine(x + 30, y + 35, x + 100, y + 70);
        _showBranch(root->right_child, x + 100, y + 70);
    }
}
void MainWindow::displayTree()
{
    scene->clear();
    if(tree.getRoot() != nullptr)
        _showBranch(tree.getRoot(), 160, 0);
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showErrorMessage(QString str)
{
    QMessageBox box;
    box.setText(str);
    box.exec();
}

void MainWindow::on_pushButton_clicked()
{
    tree.add(ui->spinBox->value(), new QString(ui->lineEdit->text()));
    displayTree();
}

void MainWindow::on_pushButton_2_clicked()
{
    tree.balance();
    displayTree();
}

void MainWindow::on_pushButton_3_clicked()
{
    try
    {
        SmartPtr<QString>* tmp = tree.search(ui->spinBox_2->value());
        ui->label->setText(*tmp->getItem());
    }
    catch(std::out_of_range)
    {
        showErrorMessage("Не найден элемент");
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    try
    {
        SmartPtr<QString>* tmp = tree.remove(ui->spinBox_2->value());
        ui->label->setText(*tmp->getItem());
        delete tmp;
    }
    catch(std::out_of_range)
    {
        showErrorMessage("Не найден элемент");
    }
    displayTree();
}

void MainWindow::on_pushButton_4_clicked()
{
    SmartPtr<QString>** objs = tree.getInfoArr();
    QString res = "";
    for(int i = 0; i < tree.getSize(); i++)
    {
        res += objs[i]->getItem();
        res += "\n";
    }
    ui->plainTextEdit->setPlainText(res);
}

void MainWindow::on_pushButton_5_clicked()
{
    SmartPtr<QString>** objs = tree.getInfoArr(1);
    QString res = "";
    for(int i = 0; i < tree.getSize(); i++)
    {
        res += objs[i]->getItem();
        res += "\n";
    }
    ui->plainTextEdit->setPlainText(res);
}

void MainWindow::on_pushButton_6_clicked()
{
    SmartPtr<QString>** objs = tree.getInfoArr(3);
    QString res = "";
    for(int i = 0; i < tree.getSize(); i++)
    {
        res += objs[i]->getItem();
        res += "\n";
    }
    ui->plainTextEdit->setPlainText(res);
}

void MainWindow::on_pushButton_8_clicked()
{
    SmartPtr<QString>* res = tree.findMiddliest();
    if(res != nullptr)
        ui->label->setText(*res->getItem());
}
