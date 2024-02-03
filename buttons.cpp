#include "tree.h"

//建树
void tree::on_BuildTree_clicked()
{
	this->init();
	update();
}

void tree::on_Reset_clicked()
{
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
	update();
}

//先序遍历
void tree::on_PreOrder_clicked()
{
	std::function<void(LinkTree)> PreOrder = [&](LinkTree Root)->void
		{
			if (Root == nullptr)
				return;

			//qDebug() << Root->data << "->" << this->Nodes[Root->data];
			this->visit(Root);
			PreOrder(Root->lChild);
			PreOrder(Root->rChild);
		};
	PreOrder(this->root);

}

//中序遍历
void tree::on_InOrder_clicked()
{
	std::function<void(LinkTree)> InOrder = [&](LinkTree Root)->void
		{
			if (Root == nullptr)
				return;

			InOrder(Root->lChild);
			//qDebug() << Root->data << "->";
			this->visit(Root);


			InOrder(Root->rChild);
		};
	InOrder(this->root);
}

//后序遍历
void tree::on_PostOrder_clicked()
{
	std::function<void(LinkTree)> PostOrder = [&](LinkTree Root)->void
		{
			if (Root == nullptr)
				return;

			PostOrder(Root->lChild);
			PostOrder(Root->rChild);
			//qDebug() << Root->data << "->";
			this->visit(Root);


		};
	PostOrder(this->root);
}

//层次遍历
void tree::on_Bfs_clicked()
{
	std::queue<LinkTree>q;
	q.push(this->root);

	while (!q.empty())
	{
		LinkTree now = q.front();
		q.pop();
		//qDebug() << now->data << "->";
		this->visit(now);


		if (now->lChild != nullptr)
			q.push(now->lChild);
		if (now->rChild != nullptr)
			q.push(now->rChild);
	}
}


//中序遍历线索树
void tree::on_ThreadedTree_clicked()
{
	std::function<void(LinkTree, LinkTree&)>inThread = [&](LinkTree now, LinkTree& pre)->void
		{
			if (now == nullptr)
				return;

			inThread(now->lChild, pre);
			if (now->lChild == nullptr)
			{
				now->lChild = pre;
				now->lTag = true;
			}
			if (pre != nullptr && pre->rChild == nullptr)
			{
				pre->rChild = now;
				pre->rTag = true;
			}

			pre = now;
			inThread(now->rChild, pre);

		};

	std::function<void(LinkTree)>inOrder = [&](LinkTree now)->void
		{
			while (!now->lTag)
				now = now->lChild;
			while (now)
			{
				//qDebug() << now->data << "->";
				this->visit(now);

				if (!now->rTag)
				{
					now = now->rChild;
					while (now != nullptr && now->lTag == false)
						now = now->lChild;
				}
				else
					now = now->rChild;
			}
		};

	this->pre = nullptr;
	inThread(this->root, this->pre);
	inOrder(this->root);
}
