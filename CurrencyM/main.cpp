#include "currencymodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMap<QString, double> data;
    data["USD"] = 1.0000;
    data["CNY"] = 0.1628;
    data["GBP"] = 1.5361;
    data["EUR"] = 1.2992;
    data["HKD"] = 0.1289;

    QTableView view;
    CurrencyModel *model = new CurrencyModel(&view);
    model->setCurrencyMap(data);
    view.setModel(model);
    view.resize(400, 300);
    view.show();

    return a.exec();
}
