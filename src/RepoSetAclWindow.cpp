#include "include/RepoSetAclWindow.hpp"

RepoSetAclWindow::RepoSetAclWindow(
	QString &user,
	QString &acl,
	QWidget *parent) : QDialog(parent)
{
	/* ACL Design */
	this->le_user.setPlaceholderText("user@epitech.eu");
	this->le_user.setMinimumWidth(200);
	this->chk_r.setText("R");
	this->chk_w.setText("W");
	this->chk_a.setText("A");
	this->layout_acl.addWidget(&this->le_user);
	this->layout_acl.addWidget(&this->chk_r);
	this->layout_acl.addWidget(&this->chk_w);
	this->layout_acl.addWidget(&this->chk_a);

	/* Close Design */
	this->btn_close.setText("Set ACL");
	this->layout_close.addWidget(&this->btn_close);

	this->layout_main.addLayout(&this->layout_acl);
	this->layout_main.addLayout(&this->layout_close);

	this->setMaximumHeight(this->height());
	this->setLayout(&this->layout_main);

	/* Misc */
	this->user = &user;
	this->acl = &acl;

	QObject::connect(&this->btn_close, SIGNAL(clicked()), this, SLOT(saveOnClose()));
}

/* --------------- PRIVATE SLOTS --------------- */

void RepoSetAclWindow::saveOnClose(void)
{
	*this->user = this->le_user.text();
	if (this->chk_r.isChecked())
		*this->acl += "r";
	if (this->chk_w.isChecked())
		*this->acl += "w";
	if (this->chk_a.isChecked())
		*this->acl += "a";
	this->close();
}