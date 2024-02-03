#include "tree.h"

tree::tree(QWidget *parent)
    : QMainWindow(parent)
{


    ui.setupUi(this);
}

tree::~tree()
{
	
}

void tree::visit(LinkTree Root)
{
	this->Nodes[Root->data] = Qt::red;
	int interval = 1000; // 0.1秒延迟
	QTimer::singleShot(interval, [&]() {
		this->Nodes[Root->data] = Qt::yellow;
		});


	QEventLoop loop;
	QTimer::singleShot(interval, &loop, &QEventLoop::quit);
	loop.exec();

	return;
}


void tree::add_edge(QString begin, QString end)
{

	//qDebug() << begin << " " << end;
	int radius = 20;
	QString EdgeName = begin + "--" + end;
	QPointF begin_pos = this->findChild<QLabel*>(begin)->pos() + QPoint(radius, radius);
	QPointF end_pos = this->findChild<QLabel*>(end)->pos() + QPoint(radius, radius);

	//qDebug() << begin_pos << " " << end_pos;
	QLineF line(begin_pos, end_pos);
	this->Edges[EdgeName] = qMakePair(line, Qt::blue);
}



void tree::init()
{
	//建树
	LinkTree& v1 = this->root = nullptr;

	v1 = new node("v1");

	LinkTree v2 = new node("v2");
	LinkTree v3 = new node("v3");
	v1->set_lChild(v2);
	v1->set_rChild(v3);
	this->add_edge("v1", "v2");
	this->add_edge("v1", "v3");


	LinkTree v4 = new node("v4");
	LinkTree v5 = new node("v5");
	v2->set_lChild(v4);
	v2->set_rChild(v5);
	this->add_edge("v2", "v4");
	this->add_edge("v2", "v5");


	LinkTree v6 = new node("v6");
	LinkTree v7 = new node("v7");
	v3->set_lChild(v6);
	v3->set_rChild(v7);
	this->add_edge("v3", "v6");
	this->add_edge("v3", "v7");


	LinkTree v8 = new node("v8");
	LinkTree v9 = new node("v9");
	v4->set_lChild(v8);
	v4->set_rChild(v9);
	this->add_edge("v4", "v8");
	this->add_edge("v4", "v9");



	LinkTree v10 = new node("v10");
	LinkTree v11 = new node("v11");
	v5->set_lChild(v10);
	v5->set_rChild(v11);
	this->add_edge("v5", "v10");
	this->add_edge("v5", "v11");
	

	LinkTree v12 = new node("v12");
	LinkTree v13 = new node("v13");
	v6->set_lChild(v12);
	v6->set_rChild(v13);
	this->add_edge("v6", "v12");
	this->add_edge("v6", "v13");


	this->Nodes["v1"] = Qt::green;
	this->Nodes["v2"] = Qt::green;
	this->Nodes["v3"] = Qt::green;
	this->Nodes["v4"] = Qt::green;
	this->Nodes["v5"] = Qt::green;
	this->Nodes["v6"] = Qt::green;
	this->Nodes["v7"] = Qt::green;
	this->Nodes["v8"] = Qt::green;
	this->Nodes["v9"] = Qt::green;
	this->Nodes["v10"] = Qt::green;
	this->Nodes["v11"] = Qt::green;
	this->Nodes["v12"] = Qt::green;
	this->Nodes["v13"] = Qt::green;
 }


void tree::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	for (const auto& [EdgeName, Edge] : this->Edges)
	{
		//qDebug() << EdgeName;
		QLineF EdgeLine = Edge.first;
		QColor EdgeColor = Edge.second;

		painter.setPen(QPen(EdgeColor, 3));
		painter.drawLine(EdgeLine);
	}

	for (const auto& node : this->findChildren<QLabel*>())
	{
		//该label不是节点就跳过
		if (this->Nodes.find(node->objectName()) == this->Nodes.end())
			continue;

		QString NodeName = node->objectName();
		QColor NodeColor = this->Nodes[NodeName];

		node->setAutoFillBackground(true);
		//QString sheet = QString("border-radius:%1px;background-color:%2").arg(20).arg(QString::);

		//qDebug() << QString::number(NodeColor, 16);
		if (NodeColor == Qt::red)
			node->setStyleSheet("border-radius:20px;background-color:red");
		else if(NodeColor == Qt::yellow)
			node->setStyleSheet("border-radius:20px;background-color:yellow");
		else
			node->setStyleSheet("border-radius:20px;background-color:green");

	}
}