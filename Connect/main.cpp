#include <QApplication>
#include <QPushButton>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //example 1
    /*QPushButton button("Quit");
    QObject::connect(&button, &QPushButton::clicked, &QApplication::quit);*/

    //example 2
    QPushButton button("Click");
    QObject::connect(&button, &QPushButton::clicked, [](bool) {
      qDebug() << "You clicked me!";
    });

    button.show();

    return app.exec();
}
