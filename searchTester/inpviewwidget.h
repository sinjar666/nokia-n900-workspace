#ifndef INPVIEWWIDGET_H
#define INPVIEWWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

class InpViewWidget : public QWidget
{
    Q_OBJECT
    QHBoxLayout *layout;
    QLineEdit *key_e;
    QPushButton *searchButton;
public:
    explicit InpViewWidget(QWidget *parent = 0);
    QString getKey();

signals:
    void clicked();

public slots:
    void onSearchClicked();
};

#endif // INPVIEWWIDGET_H
