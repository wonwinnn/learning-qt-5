#ifndef SORTVIEW_H
#define SORTVIEW_H
#include <QListView>
#include <QStringListModel>
#include <QSortFilterProxyModel>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>


class SortView : public QWidget
{
    Q_OBJECT
public:
    SortView();

private:
    QListView *view;
    QStringListModel *model;
    QSortFilterProxyModel *modelProxy;
    QComboBox *syntaxBox;

private slots:
    void filterChanged(const QString &text);
};

#endif // SORTVIEW_H
