#include <QApplication>
#include <QTreeWidget>
#include <QTreeWidgetItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTreeWidget treeWidget;

    QStringList headers;
    headers << "Name" << "Number";
    treeWidget.setHeaderLabels(headers);

    QStringList rootTextList;
    rootTextList << "Root" << "0";
    QTreeWidgetItem *root = new QTreeWidgetItem(&treeWidget, rootTextList);

    new QTreeWidgetItem(root, QStringList() << QString("Leaf 1") << "1");
    QTreeWidgetItem *leaf2 = new QTreeWidgetItem(root,
                                       QStringList() << QString("Leaf 2") << "2");
    leaf2->setCheckState(0, Qt::Checked);

    QList<QTreeWidgetItem *> rootList;
    rootList << root;
    treeWidget.insertTopLevelItems(0, rootList);

    treeWidget.show();


    return a.exec();
}
