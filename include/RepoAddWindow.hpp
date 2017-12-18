#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMdiArea>
#include <QTextEdit>
#include <QCheckBox>
#include <QDateEdit>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <map>
#include <thread>

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