#include "include/MainWindow.hpp"

MainWindow::MainWindow(void)
{
	// Fusion for Linux, fixes QGroupBox Border
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
	this->layout_repolv.addWidget(&this->lv_repositories);
	this->layout_repobtns.addWidget(&this->btn_repoadd);
	this->layout_repobtns.addWidget(&this->btn_repodel);
	this->layout_repobtns.addWidget(&this->btn_reposetacl);
	this->layout_repobtns.addWidget(&this->btn_repoinfo);
	this->layout_repositories.addLayout(&this->layout_repolv);
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