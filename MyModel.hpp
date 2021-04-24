#ifndef MYMODEL_HPP
#define MYMODEL_HPP

#include <QStandardItemModel>

class MyModel : public QStandardItemModel
{
	Q_OBJECT
public:
	MyModel() = default;

private slots:
	void setText(const unsigned long long& index, const QString& string);
};

#endif // MYMODEL_HPP
