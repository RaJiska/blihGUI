#include "include/MainWindow.hpp"

MainWindow::MainWindow(void)
{
	/* Fusion for Linux, fixes QGroupBox Border */
	QApplication::setStyle("Fusion");

	/* Login */
	this->gbox_connection.setTitle("Connection");
	this->lbl_conlogin.setText("Login: ");
	this->lbl_conpassword.setText("Password: ");
	this->btn_conconnection.setText("Connection");
	this->chk_conremember.setText("Remember");
	this->le_conpassword.setEchoMode(QLineEdit::Password);
	this->layout_connection.addWidget(&this->lbl_conlogin);
	this->layout_connection.addWidget(&this->le_conlogin);
	this->layout_connection.addWidget(&this->lbl_conpassword);
	this->layout_connection.addWidget(&this->le_conpassword);
	this->layout_connection.addWidget(&this->chk_conremember);
	this->layout_connection.addWidget(&this->btn_conconnection);
	this->gbox_connection.setLayout(&this->layout_connection);
	
	/* Repositories list */
	this->gbox_repositories.setTitle("Repositories");
	this->btn_repoadd.setText("Add");
	this->btn_repodel.setText("Delete");
	this->btn_reposetacl.setText("Set ACLs");
	this->btn_repoinfo.setText("Infos");
	this->btn_repoadd.setDisabled(true);
	this->btn_repodel.setDisabled(true);
	this->btn_reposetacl.setDisabled(true);
	this->btn_repoinfo.setDisabled(true);
	this->layout_repolw.addWidget(&this->lw_repositories);
	this->layout_repobtns.addWidget(&this->btn_repoadd);
	this->layout_repobtns.addWidget(&this->btn_repodel);
	this->layout_repobtns.addWidget(&this->btn_reposetacl);
	this->layout_repobtns.addWidget(&this->btn_repoinfo);
	this->layout_repositories.addLayout(&this->layout_repolw);
	this->layout_repositories.addLayout(&this->layout_repobtns);
	this->gbox_repositories.setLayout(&this->layout_repositories);

	layout_main.addWidget(&this->gbox_connection);
	layout_main.addWidget(&this->gbox_repositories);

	this->widget_central.setLayout(&layout_main);
	this->setCentralWidget(&this->widget_central);
}

MainWindow::~MainWindow(void)
{

}

/* --------------- PUBLIC --------------- */

void MainWindow::connectToBlih(void)
{
	json response;

	this->le_conlogin.setDisabled(true);
	this->le_conpassword.setDisabled(true);
	this->chk_conremember.setDisabled(true);
	this->btn_conconnection.setDisabled(true);
	response = blih.repositoryList();
	if (!this->handleBlihError(response))
	{
		this->repositoriesList(response);
		this->btn_repoadd.setDisabled(false);
		this->btn_repoadd.setDisabled(true);
		this->btn_repodel.setDisabled(true);
		this->btn_reposetacl.setDisabled(true);
		this->btn_repoinfo.setDisabled(true);
	}
	this->le_conlogin.setDisabled(false);
	this->le_conpassword.setDisabled(false);
	this->chk_conremember.setDisabled(false);
	this->btn_conconnection.setDisabled(false);
}

void MainWindow::repositoryAdd(const std::string &name)
{
	json response;

	this->btn_repoadd.setDisabled(true);
	response = this->blih.repositoryCreate(name);
	if (!this->handleBlihError(response))
	{
		Repository repo;
		this->repo_list[name] = repo;
		this->lw_repositories.addItem(QString::fromStdString(name));
	}
	this->btn_repoadd.setDisabled(false);
}

void MainWindow::repositoryGetInfos(const std::string &name)
{
	json response;

	this->btn_repoinfo.setDisabled(true);
	response = this->blih.repositoryInfo(name);
	if (!this->handleBlihError(response))
	{
		this->repo_list[name].creation = response["message"]["creation_time"].get<long>();
		this->repo_list[name].description = response["message"]["description"];
		this->repo_list[name].is_public = response["message"]["public"];
		this->repo_list[name].url = response["message"]["url"];
		this->repo_list[name].uuid = response["message"]["uuid"];
		/* TODO: Display new window here */
	}
	this->btn_repoinfo.setDisabled(false);
}

/* --------------- PRIVATE --------------- */

bool MainWindow::handleBlihError(const json &response)
{
	QString str;

	if (response == nullptr)
		str = "Internal error :(\nPlease report at https://github.com/RaJiska/blihGUI/issues.";
	else if (response["_STATUS_CODE"] != "200")
	{
		str = "Error Code: " + QString::fromStdString(response["_STATUS_CODE"]) +
			"\nMessage: " + QString::fromStdString(response["message"]);
	}
	else
		return false;
	QMessageBox::critical(this, "BLIH Error", str);
	return true;
}

void MainWindow::repositoriesList(const json &response)
{
	this->lw_repositories.clear();
	this->repo_list.clear();
	for (auto &it : json::iterator_wrapper(response["repositories"]))
	{
		Repository repo;
		this->repo_list[it.key()] = repo;
		this->lw_repositories.addItem(QString::fromStdString(it.key()));
	}
}