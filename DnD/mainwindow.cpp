#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    textEdit->setAcceptDrops(false);
    setAcceptDrops(true);

    setWindowTitle(tr("Text Editor"));
}

MainWindow::~MainWindow()
{
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list")) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) {
        return;
    }

    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty()) {
        return;
    }

    if (readFile(fileName)) {
        setWindowTitle(tr("%1 - %2").arg(fileName, tr("Drag File")));
    }
}

bool MainWindow::readFile(const QString &fileName)
{
    bool r = false;
    QFile file(fileName);
    QString content;
    if(file.open(QIODevice::ReadOnly)) {
        content = file.readAll();
        r = true;
    }
    textEdit->setText(content);
    return r;
}
