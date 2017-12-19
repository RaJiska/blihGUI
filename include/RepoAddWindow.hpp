#pragma once

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class RepoAddWindow : public QDialog
{
	Q_OBJECT

	public:
	RepoAddWindow(QString *str, QWidget *parent);

	private slots:
	void validateRepoName(void);

	private:
	QString *name_to_return;

	QVBoxLayout layout_main;

	QHBoxLayout layout_input;
	QLabel lbl_reponame;
	QLineEdit le_reponame;

	QVBoxLayout layout_validate;
	QPushButton btn_validate;
};