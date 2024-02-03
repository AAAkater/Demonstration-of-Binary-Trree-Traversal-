#pragma once

#include <QtWidgets/QMainWindow>
#include<qvector.h>
#include<qpair.h>
#include<qpainter.h>
#include<qline.h>
#include<qtimer.h>


#include<map>
#include<queue>
#include<functional>
#include "ui_tree.h"

class node
{
public:
    QString data;
    bool lTag, rTag;
    node* lChild, * rChild;
    ~node() {}
    node(QString data)
    {
        this->data = data;
        this->lTag = this->rTag = false;
        this->lChild = this->rChild = nullptr;
    }
    void set_lChild(node* root)
    {
        this->lChild = root;
    }
    void set_rChild(node* root)
    {
        this->rChild = root;
    }
};
typedef node* LinkTree;

class tree : public QMainWindow
{
    Q_OBJECT

public:
    tree(QWidget *parent = nullptr);
    ~tree();
private:
    Ui::treeClass ui;
    LinkTree root, pre;
    std::map<QString, QPair<QLineF, QColor>>Edges;
    std::map<QString, QColor>Nodes;
    void add_edge(QString begin, QString end);
   
    void visit(LinkTree root);
    void init();
    void paintEvent(QPaintEvent* event);

private slots:

    //建树
    void on_BuildTree_clicked();
    //重置
    void on_Reset_clicked();
    //先序遍历
    void on_InOrder_clicked();
    //中序遍历
    void on_PostOrder_clicked();
    //后序遍历
    void on_PreOrder_clicked();
    //层次遍历
    void on_Bfs_clicked();
    //中序遍历线索树
    void on_ThreadedTree_clicked();
};

