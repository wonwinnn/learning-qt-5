#include "currencymodel.h"

CurrencyModel::CurrencyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int CurrencyModel::rowCount(const QModelIndex & parent) const
{
    return currencyMap.count();
}

int CurrencyModel::columnCount(const QModelIndex & parent) const
{
    return currencyMap.count();
}

QVariant CurrencyModel::headerData(int section, Qt::Orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    return currencyAt(section);
}

QString CurrencyModel::currencyAt(int offset) const
{
    return (currencyMap.begin() + offset).key();
}

void CurrencyModel::setCurrencyMap(const QMap<QString, double> &map)
{
    beginResetModel();
    currencyMap = map;
    endResetModel();
}

QVariant CurrencyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    //} else if (role == Qt::DisplayRole) {
    } else if (role == Qt::DisplayRole || role == Qt::EditRole) {
        QString rowCurrency = currencyAt(index.row());
        QString columnCurrency = currencyAt(index.column());
        if (currencyMap.value(rowCurrency) == 0.0) {
            return "####";
        }
        double amount = currencyMap.value(columnCurrency)
                            / currencyMap.value(rowCurrency);
        return QString("%1").arg(amount, 0, 'f', 4);
    }
    return QVariant();
}

Qt::ItemFlags CurrencyModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (index.row() != index.column()) {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

bool CurrencyModel::setData(const QModelIndex &index,
                            const QVariant &value, int role)
{
    if (index.isValid()
            && index.row() != index.column()
            && role == Qt::EditRole) {
        QString columnCurrency = headerData(index.column(),
                                            Qt::Horizontal, Qt::DisplayRole)
                                     .toString();
        QString rowCurrency = headerData(index.row(),
                                         Qt::Vertical, Qt::DisplayRole)
                                  .toString();
        currencyMap.insert(columnCurrency,
                           value.toDouble() * currencyMap.value(rowCurrency));
        emit dataChanged(index, index);
        return true;
    }
    return false;
}


