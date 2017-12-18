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

#include "include/BlihGUI.hpp"
#include "include/BlihAPI.hpp"
#include "include/Repository.hpp"
#include "include/RepoAddWindow.hpp"

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
	MainWindow(void);
	~MainWindow(void);

	public slots:
	void loginChanged(QString str);
	void connectToBlih(void);
	void repositoryItemSelected(void);
	void repositoryAdd(void);
	void repositoryDelete(void);
	void repositoryGetInfos(const std::string &name);

	private:
	void cachedCredentialsAreValid(void);
	bool handleBlihError(const json &response);
	void actionRepositoryAdd(const QString &name);
	void actionRepositoryList(const json &response);
	void actionRepositoryDelete(const QString &name);

	BlihAPI blih;
	std::map<std::string, Repository> repo_list;
	QString cached_login;

	/* Design */
	QWidget widget_central;
	QVBoxLayout layout_main;

	/* Connection */
	QGroupBox gbox_connection;
	QHBoxLayout layout_connection;
	QLabel lbl_conlogin;
	QLabel lbl_conpassword;
	QLineEdit le_conlogin;
	QLineEdit le_conpassword;
	QCheckBox chk_conremember;
	QPushButton btn_conconnection;

	/* Repositories */
	QGroupBox gbox_repositories;
	QVBoxLayout layout_repositories;
	QVBoxLayout layout_repolw;
	QListWidget lw_repositories;
	QHBoxLayout layout_repobtns;
	QPushButton btn_repoadd;
	QPushButton btn_repodel;
	QPushButton btn_reposetacl;
	QPushButton btn_repoinfo;
};