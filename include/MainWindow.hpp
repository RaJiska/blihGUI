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

#include "include/BlihGUI.hpp"
#include "include/BlihAPI.hpp"
#include "include/Repository.hpp"

class MainWindow : public QMainWindow
{
	public:
	MainWindow(void);
	~MainWindow(void);

	void connectToBlih(void);
	void repositoryAdd(const std::string &name);
	void repositoryGetInfos(const std::string &name);

	private:
	bool handleBlihError(const json &response);
	void repositoriesList(const json &response);

	BlihAPI blih;
	std::map<std::string, Repository> repo_list;

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