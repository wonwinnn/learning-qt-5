#include "filesystemwidget.h"

FileSystemWidget::FileSystemWidget(QWidget *parent) :
    QWidget(parent)
{
    model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    treeView = new QTreeView(this);
    treeView->setModel(model);
    treeView->setRootIndex(model->index(QDir::currentPath()));

    QPushButton *mkdirButton = new QPushButton(tr("Make Directory..."), this);
    QPushButton *rmButton = new QPushButton(tr("Remove"), this);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(mkdirButton);
    buttonLayout->addWidget(rmButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(treeView);
    layout->addLayout(buttonLayout);

    setLayout(layout);
    setWindowTitle("File System Model");

    connect(mkdirButton, SIGNAL(clicked()),
            this, SLOT(mkdir()));
    connect(rmButton, SIGNAL(clicked()),
            this, SLOT(rm()));

    /*treeView->header()->setStretchLastSection(true);
    treeView->header()->setSortIndicator(0, Qt::AscendingOrder);
    treeView->header()->setSortIndicatorShown(true);
    #if QT_VERSION >= 0x050000
        treeView->header()->setSectionsClickable(true);
    #else
        treeView->header()->setClickable(true);
    #endif*/

    treeView->setSortingEnabled(true);

}

void FileSystemWidget::mkdir()
{
    //QModelIndex index = treeView->currentIndex().parent();
    QModelIndex index = treeView->currentIndex();
    if (!index.isValid()) {
        return;
    }
    QString dirName = QInputDialog::getText(this,
                                            tr("Create Directory"),
                                            tr("Directory name"));
    if (!dirName.isEmpty()) {
        if (!model->mkdir(index, dirName).isValid()) {
            QMessageBox::information(this,
                                     tr("Create Directory"),
                                     tr("Failed to create the directory"));
        }
    }
}

void FileSystemWidget::rm()
{
    QModelIndex index = treeView->currentIndex();
    if (!index.isValid()) {
        return;
    }
    bool ok;
    if (model->fileInfo(index).isDir()) {
        ok = model->rmdir(index);
    } else {
        ok = model->remove(index);
    }
    if (!ok) {
        QMessageBox::information(this,
                         tr("Remove"),
                         tr("Failed to remove %1").arg(model->fileName(index)));
    }
}
