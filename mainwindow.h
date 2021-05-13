#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMessageBox>
#include <QGraphicsRectItem>
#include "smartBinaryTree.cpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

template class SmartBinaryTree<QString>;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    SmartBinaryTree<QString> tree;

    QGraphicsScene* scene;

    void displayTree();
    void _showBranch(BinaryTree<QString>::BinaryTreeNode* root, int x, int y);
    void showErrorMessage(QString str);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
