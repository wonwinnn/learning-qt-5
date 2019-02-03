#include <QApplication>
#include <QXmlStreamWriter>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("bookindex.xml");
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Error: Cannot write file: "
                 << qPrintable(file.errorString());
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("bookindex");
    xmlWriter.writeStartElement("entry");
    xmlWriter.writeAttribute("term", "sidebearings");
    xmlWriter.writeTextElement("page", "10");
    xmlWriter.writeTextElement("page", "34-35");
    xmlWriter.writeTextElement("page", "307-308");
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("entry");
    xmlWriter.writeAttribute("term", "subtraction");
    xmlWriter.writeStartElement("entry");
    xmlWriter.writeAttribute("term", "of pictures");
    xmlWriter.writeTextElement("page", "115");
    xmlWriter.writeTextElement("page", "224");
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("entry");
    xmlWriter.writeAttribute("term", "of vectors");
    xmlWriter.writeTextElement("page", "9");
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
    if (file.error()) {
        qDebug() << "Error: Cannot write file: "
                 << qPrintable(file.errorString());
        return false;
    }


    return a.exec();
}
