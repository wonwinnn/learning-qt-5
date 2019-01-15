#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle(tr("Main Window"));

    openAction = new QAction(QIcon(":/images/doc-open"), tr("&Open..."), this);

    openAction->setShortcuts(QKeySequence::Open);

    openAction->setStatusTip(tr("Open an existing file"));

    connect(openAction, &QAction::triggered, this, &MainWindow::open);


    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);

    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);

    statusBar() ;
}

MainWindow::~MainWindow()
{
}


void MainWindow::open()
{
    //QMessageBox::information(this, tr("Information"), tr("Open"));

    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Question"),
                                                  tr("Are you OK?"),
                                                  QMessageBox::Yes | QMessageBox::No,
                                                  QMessageBox::Yes)) {
        QMessageBox::information(this, tr("Hmmm..."), tr("I'm glad to hear that!"));
    } else {
        QMessageBox::information(this, tr("Hmmm..."), tr("I'm sorry!"));
    }

    /*QMessageBox msgBox;
    msgBox.setText(tr("The document has been modified."));
    msgBox.setInformativeText(tr("Do you want to save your changes?"));
    msgBox.setDetailedText(tr("Differences here..."));
    msgBox.setStandardButtons(QMessageBox::Save
                              | QMessageBox::Discard
                              | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Save:
        qDebug() << "Save document!";
        break;
    case QMessageBox::Discard:
        qDebug() << "Discard changes!";
        break;
    case QMessageBox::Cancel:
        qDebug() << "Close document!";
        break;
    }*/
}

/*void MainWindow::open()
{
    //QDialog dialog;
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Hello, dialog!"));
    dialog.exec();
    qDebug() << dialog.result();
}*/

/*void MainWindow::open()
{
    QDialog *dialog = new QDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setWindowTitle(tr("Hello, dialog!"));
    dialog->show();
}*/
