#include "datatablewidget.h"

DataTableWidget::DataTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    setAcceptDrops(true);
    setSelectionMode(ContiguousSelection);

    setColumnCount(3);
    setRowCount(5);
}

void DataTableWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        startPos = event->pos();
    }
    QTableWidget::mousePressEvent(event);
}

void DataTableWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance()) {
            performDrag();
        }
    }
}

void DataTableWidget::dragEnterEvent(QDragEnterEvent *event)
{
    DataTableWidget *source =
            qobject_cast<DataTableWidget *>(event->source());
    if (source && source != this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void DataTableWidget::dragMoveEvent(QDragMoveEvent *event)
{
    DataTableWidget *source =
            qobject_cast<DataTableWidget *>(event->source());
    if (source && source != this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void DataTableWidget::performDrag()
{
    QString selectedString = selectionText();
    if (selectedString.isEmpty()) {
        return;
    }

    QMimeData *mimeData = new QMimeData;
    mimeData->setHtml(toHtml(selectedString));
    mimeData->setData("text/csv", toCsv(selectedString).toUtf8());

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    if (drag->exec(Qt::CopyAction | Qt::MoveAction) == Qt::MoveAction) {
         selectionModel()->clearSelection();
    }
}

void DataTableWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("text/csv")) {
        QByteArray csvData = event->mimeData()->data("text/csv");
        QString csvText = QString::fromUtf8(csvData);
        fromCsv(csvText);
        event->acceptProposedAction();
    }
}

QString DataTableWidget::selectionText() const
{
    QString selectionString;
    QString headerString;
    QAbstractItemModel *itemModel = model();
    QTableWidgetSelectionRange selection = selectedRanges().at(0);
    for (int row = selection.topRow(), firstRow = row;
         row <= selection.bottomRow(); row++) {
        for (int col = selection.leftColumn();
             col <= selection.rightColumn(); col++) {
            if (row == firstRow) {
                headerString.append(horizontalHeaderItem(col)->text()).append("\t");
            }
            QModelIndex index = itemModel->index(row, col);
            selectionString.append(index.data().toString()).append("\t");
        }
        selectionString = selectionString.trimmed();
        selectionString.append("\n");
    }
    return headerString.trimmed() + "\n" + selectionString.trimmed();
}

QString DataTableWidget::toHtml(const QString &plainText) const
{
#if QT_VERSION >= 0x050000
    QString result = plainText.toHtmlEscaped();
#else
    QString result = Qt::escape(plainText);
#endif
    result.replace("\t", "<td>");
    result.replace("\n", "\n<tr><td>");
    result.prepend("<table>\n<tr><td>");
    result.append("\n</table>");
    return result;
}

QString DataTableWidget::toCsv(const QString &plainText) const
{
    QString result = plainText;
    result.replace("\\", "\\\\");
    result.replace("\"", "\\\"");
    result.replace("\t", "\", \"");
    result.replace("\n", "\"\n\"");
    result.prepend("\"");
    result.append("\"");
    return result;
}

void DataTableWidget::fromCsv(const QString &csvText)
{
    QStringList rows = csvText.split("\n");
    QStringList headers = rows.at(0).split(", ");
    for (int h = 0; h < headers.size(); ++h) {
        QString header = headers.at(0);
        headers.replace(h, header.replace('"', ""));
    }
    setHorizontalHeaderLabels(headers);
    for (int r = 1; r < rows.size(); ++r) {
        QStringList row = rows.at(r).split(", ");
        setItem(r - 1, 0, new QTableWidgetItem(row.at(0).trimmed().replace('"', "")));
        setItem(r - 1, 1, new QTableWidgetItem(row.at(1).trimmed().replace('"', "")));
    }
}

