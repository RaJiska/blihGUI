#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>

class RepoSetAclWindow : public QDialog
{
	Q_OBJECT

	public:
	RepoSetAclWindow(QString &user, QString &acl, QWidget *parent);

	public slots:
	void saveOnClose(void);

	private:
	QString *user;
	QString *acl;

	QVBoxLayout layout_main;

	QHBoxLayout layout_acl;
	QLineEdit le_user;
	QCheckBox chk_r;
	QCheckBox chk_w;
	QCheckBox chk_a;

	QVBoxLayout layout_close;
	QPushButton btn_close;
};