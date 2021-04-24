#include "MyModel.hpp"

void MyModel::setText(const unsigned long long& index, const QString& string)
{
	this->item(index, 0)->setText(string);
}
