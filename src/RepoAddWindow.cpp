#include "include/RepoAddWindow.hpp"
#include <QDialog>

RepoAddWindow::RepoAddWindow(QString *str, QWidget *parent) : QDialog(parent)
{
	this->lbl_reponame.setText("Repository: ");
	this->layout_input.addWidget(&this->lbl_reponame);
	this->le_reponame.setMinimumWidth(50);
	this->layout_input.addWidget(&this->le_reponame);

	this->btn_validate.setText("Add Repository");
	this->layout_validate.addWidget(&this->btn_validate);

	this->layout_main.addLayout(&this->layout_input);
	this->layout_main.addLayout(&this->layout_validate);

	this->setMaximumHeight(this->height());
	this->setLayout(&this->layout_main);

	this->name_to_return = str;
	QObject::connect(&this->btn_validate, SIGNAL(clicked()), this, SLOT(validateRepoName()));
}

void RepoAddWindow::validateRepoName(void)
{
	*(this->name_to_return) = this->le_reponame.text();
	this->close();
}