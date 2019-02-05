#include "sortview.h"

SortView::SortView()
{
    model = new QStringListModel(QColor::colorNames(), this);

    modelProxy = new QSortFilterProxyModel(this);
    modelProxy->setSourceModel(model);
    modelProxy->setFilterKeyColumn(0);

    view = new QListView(this);
    view->setModel(modelProxy);

    QLineEdit *filterInput = new QLineEdit;
    QLabel *filterLabel = new QLabel(tr("Filter"));
    QHBoxLayout *filterLayout = new QHBoxLayout;
    filterLayout->addWidget(filterLabel);
    filterLayout->addWidget(filterInput);

    syntaxBox = new QComboBox;
    syntaxBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    syntaxBox->addItem(tr("Regular expression"), QRegExp::RegExp);
    syntaxBox->addItem(tr("Wildcard"), QRegExp::Wildcard);
    syntaxBox->addItem(tr("Fixed string"), QRegExp::FixedString);
    QLabel *syntaxLabel = new QLabel(tr("Syntax"));
    QHBoxLayout *syntaxLayout = new QHBoxLayout;
    syntaxLayout->addWidget(syntaxLabel);
    syntaxLayout->addWidget(syntaxBox);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(view);
    layout->addLayout(filterLayout);
    layout->addLayout(syntaxLayout);

    connect(filterInput, SIGNAL(textChanged(QString)),
            this, SLOT(filterChanged(QString)));
}

void SortView::filterChanged(const QString &text)
{
    QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(
                syntaxBox->itemData(syntaxBox->currentIndex()).toInt());
    QRegExp regExp(text, Qt::CaseInsensitive, syntax);
    modelProxy->setFilterRegExp(regExp);
}

