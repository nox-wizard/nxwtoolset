/***************************************************************************
                          nxwtoolset.cpp  -  description
                             -------------------
    begin                : Wed Dec 25 15:37:44 CET 2002
    copyright            : (C) 2002 by Fabrizio Montesi
    email                : luxor@e-vinco.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "nxwtoolset.h"

QTextEdit *g_compEdit;

/* NoX-Wizard Toolset Main Widget */

NXWToolset::NXWToolset(QApplication *parent, const char *name) : QMainWindow(0, name)
{
        m_saveMap = new QMap<QString, bool>;
        m_funcMap = new QMap<QString, QStringList>;
        m_constMap = new QMap<QString, QString>;
        
        setCaption(APPNAME);
        
        m_application = parent;
        m_mainTab = NULL;
        m_funcList = NULL;
        m_constList = NULL;

        initBars();
        initGUI();
        loadData();
        showMaximized();
}

void NXWToolset::quitToolset()
{
        closeAllFiles();
        m_application->quit();
}

void NXWToolset::searchLists(const QString& sSearch)
{
        m_funcList->clear();
        m_constList->clear();

        QMap<QString, QStringList>::iterator it;
        for (it = m_funcMap->begin(); it != m_funcMap->end(); it++) {
		if (sSearch == NULL) {
			new QListViewItem(m_funcList, it.key());
			continue;
		}
			
		if (it.key().left(sSearch.length()) == sSearch)
			new QListViewItem(m_funcList, it.key());
	}
	
	QMap<QString, QString>::iterator it2;
	for (it2 = m_constMap->begin(); it2 != m_constMap->end(); it2++) {
		if (sSearch == NULL) {
			new QListViewItem(m_constList, it2.key());
			continue;
		}
		if (it2.key().left(sSearch.length()) == sSearch)
			new QListViewItem(m_constList, it2.key());	
	}
}

void NXWToolset::parseIncludeFile(QString sFilename, QString sFilter)
{
        /* noxwizard file processing */
        QFile file(sFilename);

        if ( !file.open( IO_ReadOnly ) ) return;
        QTextStream ts( &file );
        QString sLine, sName, sBrief, sParams, sAuthor, sSyntax, sDesc, sFirst, sJoin;
        bool bSectionFound = false;
        QStringList slLine, slParams, slFunction;
        while ((sLine = ts.readLine()) != NULL) {
                /* Functions parsing */
                if (sLine == "/*!") {
                        bSectionFound = true;
                        continue;
                }
                if (sLine == "*/" && bSectionFound == true) {
                        if (sFilter != NULL)
                                if (sName.left(sFilter.length()) != sFilter) continue;

                        sParams = slParams.join("\n - ");
                        sDesc = QString("Function: %1\nAuthor: %2\nSyntax: %3\n\nParameters\n - %4\n\nDescription: %5").arg(sName).arg(sAuthor).arg(sSyntax).arg(sParams).arg(sBrief);
                        QStringList slFunc;
                        slFunc.push_back(sDesc);
                        slFunc.push_back(sSyntax);
                        m_funcMap->insert(sName, slFunc);
                        sName = sAuthor = sSyntax = sBrief = sParams = "";
                        slParams.clear();
                        bSectionFound = false;
                        continue;
                }
                slLine = QStringList::split(" ", sLine);
                sFirst = slLine.first();
                slLine.remove(sFirst);
                sJoin = slLine.join(" ");

		if (sFirst == "\\fn") {
			sSyntax = sJoin;
			slFunction = QStringList::split("(", sJoin);
			sName = slFunction.first();
		} else if (sFirst == "\\name") sName = sJoin;
		else if (sFirst == "\\brief") sBrief = sJoin;
                else if (sFirst == "\\author") sAuthor = sJoin;
                else if (sFirst == "\\syntax") sSyntax = sJoin;
                else if (sFirst == "\\param") slParams.push_back(sJoin);
                else if (sFirst == "const" || sFirst == "#define") { /* Constants parsing */
                        if (slLine.first() == NULL) continue;
                        if (sFilter != NULL)
                                if (slLine.first().left(sFilter.length()) != sFilter) continue;
			m_constMap->insert(slLine.first(), slLine.first()); //Will contain some descriptions in the future
                }
                
        }
        file.close();
	searchLists(NULL);
}

void NXWToolset::loadData(QString sFilter)
{
	//
	// Clear all maps and lists
	//
	m_funcList->clear();
	m_constList->clear();
	m_funcMap->clear();
	m_constMap->clear();


	//
	// Get files included by override.sma
	//
	QFile file("small-scripts/override.sma");

        if ( !file.open( IO_ReadOnly ) ) return;
	QTextStream ts( &file );
	QString sLine, sLha, sRha;
	QStringList slLine;

	while ((sLine = ts.readLine()) != NULL) {
		slLine = QStringList::split(" ", sLine);
		sLha = slLine.first();
		if ( sLha != "#include" )
			continue;

		slLine.pop_front();
		sRha = slLine.first();
		sRha.remove( "\"" );

		//
		// Parse the file
		//
		parseIncludeFile( sRha, sFilter );
	}

	file.close();
}


void NXWToolset::initGUI()
{
        statusBar();

        QWidget *mainWidget = new QWidget(this, "main widget");
        setCentralWidget(mainWidget);        
        QGridLayout *mainGrid = new QGridLayout(mainWidget, 1, 2, 0, 0, "main layout");

        /* Left Part */
        m_mainTab = new QTabWidget(mainWidget);
        connect(m_mainTab, SIGNAL( currentChanged(QWidget*) ), this, SLOT( changeCaption(QWidget*) ));

        m_bottomTab = new QTabWidget(mainWidget);
        QTextEdit *compEdit = new QTextEdit(m_bottomTab);
        compEdit->setReadOnly(true);
        
        connect(compEdit, SIGNAL( cursorPositionChanged(int, int) ), this, SLOT( compCursorChanged(int, int) ));

        g_compEdit = compEdit;

        m_helpEdit = new QTextEdit(m_bottomTab);
        m_helpEdit->setReadOnly(true);
        m_bottomTab->addTab(compEdit, "Compiler");
        m_bottomTab->addTab(m_helpEdit, "Help");

        QGridLayout *leftGrid = new QGridLayout(2, 1, -1, "left layout");
        leftGrid->addWidget(m_mainTab, 0, 0);
        leftGrid->addWidget(m_bottomTab, 1, 0);
        leftGrid->setRowStretch(0, 3);
        leftGrid->setRowStretch(1, 1);
        
        /* Right Part */
        m_funcList = new QListView(mainWidget);
        m_constList = new QListView(mainWidget);
        m_constList->hide();

        QGridLayout *rightGrid = new QGridLayout(3, 1, -1, "right layout");
                
        QGridLayout *searchGrid = new QGridLayout(1, 2, -1, "search layout");
        searchGrid->addWidget(new QLabel("Search:", mainWidget), 0, 0);
        QLineEdit *searchEdit = new QLineEdit(mainWidget, "search edit");
        searchGrid->addWidget(searchEdit, 0, 1);

        connect(searchEdit, SIGNAL( textChanged(const QString&) ), this, SLOT( searchLists(const QString&) ));

        QGridLayout *listBtnGrid = new QGridLayout(1, 2, -1, "list buttons layout");
        QPushButton *btnFunctions = new QPushButton("Functions", mainWidget, "btnFunctions");
        QPushButton *btnConstants = new QPushButton("Constants", mainWidget, "btnConstants");
        listBtnGrid->addWidget(btnFunctions, 0, 0);
        listBtnGrid->addWidget(btnConstants, 0, 1);
        
        rightGrid->addLayout(searchGrid, 0, 0);
        rightGrid->addLayout(listBtnGrid, 1, 0);
        rightGrid->addWidget(m_funcList, 2, 0);
        rightGrid->addWidget(m_constList, 2, 0);

        connect(btnFunctions, SIGNAL( clicked() ), m_constList, SLOT( hide() ));
        connect(btnFunctions, SIGNAL( clicked() ), m_funcList, SLOT( show() ));

        connect(btnConstants, SIGNAL( clicked() ), m_funcList, SLOT( hide() ));
        connect(btnConstants, SIGNAL( clicked() ), m_constList, SLOT( show() ));

        m_funcList->addColumn("Functions");
        m_funcList->setColumnWidthMode(0, QListView::Maximum);
        m_constList->addColumn("Constants");
        m_constList->setColumnWidthMode(0, QListView::Maximum);

        connect(m_funcList, SIGNAL( clicked(QListViewItem*) ), this, SLOT( showFuncHelp(QListViewItem*) ));
        connect(m_funcList, SIGNAL( doubleClicked(QListViewItem*) ), this, SLOT( addSelectedFunc(QListViewItem*) ));

        connect(m_constList, SIGNAL( clicked(QListViewItem*) ), this, SLOT( showConstHelp(QListViewItem*) ));
        connect(m_constList, SIGNAL( doubleClicked(QListViewItem*) ), this, SLOT( addSelectedConst(QListViewItem*) ));
        
        /* mainGrid building */
        mainGrid->addLayout(leftGrid, 0, 0);
        mainGrid->addLayout(rightGrid, 0, 1);
        mainGrid->setColStretch(0, 4);
        mainGrid->setColStretch(1, 1);
}

void NXWToolset::initBars()
{
        /* File menu */
        QPopupMenu *mnuFile = new QPopupMenu(this);
        Q_CHECK_PTR(mnuFile);
        menuBar()->insertItem("&File", mnuFile);

        QAction *actionNew = new QAction("New", QIconSet(QPixmap("images/filenew.png")), "&New", CTRL+Key_N, this, "new");
        connect(actionNew, SIGNAL( activated() ), this, SLOT( openNewFile() ));
        actionNew->addTo(mnuFile);

        QAction *actionOpen = new QAction("Open", QIconSet(QPixmap("images/fileopen.png")), "&Open...", CTRL+Key_O, this, "open");
        connect(actionOpen, SIGNAL( activated() ), this, SLOT( openFileDialog() ));
        actionOpen->addTo(mnuFile);

        QAction *actionClose = new QAction("Close", "&Close", CTRL+Key_W, this, "close");
        connect(actionClose, SIGNAL( activated() ), this, SLOT( closeCurrFile() ));
        actionClose->addTo(mnuFile);

        QAction *actionCloseAll = new QAction("Close All", "&Close All", 0, this, "closeall");
        connect(actionCloseAll, SIGNAL( activated() ), this, SLOT( closeAllFiles() ));
        actionCloseAll->addTo(mnuFile);

        mnuFile->insertSeparator();

        QAction *actionSave = new QAction("Save", QIconSet(QPixmap("images/filesave.png")), "&Save", CTRL+Key_S, this, "save");
        connect(actionSave, SIGNAL( activated() ), this, SLOT( saveCurrFile() ));
        actionSave->addTo(mnuFile);

        QAction *actionSaveAs = new QAction("Save as", QIconSet(QPixmap("images/filesaveas.png")), "&Save as...", 0, this, "saveas");
        connect(actionSaveAs, SIGNAL( activated() ), this, SLOT( saveAsCurrFile() ));
        actionSaveAs->addTo(mnuFile);

        QAction *actionSaveAll = new QAction("Save All", "&Save All", 0, this, "saveall");
        connect(actionSaveAll, SIGNAL( activated() ), this, SLOT( saveAllFiles() ));
        actionSaveAll->addTo(mnuFile);

        mnuFile->insertSeparator();
                   
        QAction *actionQuit = new QAction("Quit", "&Quit", CTRL+Key_Q, this, "quit");
        connect(actionQuit, SIGNAL( activated() ), this, SLOT( quitToolset() ));
        actionQuit->addTo(mnuFile);

        /* Edit Menu */
        QPopupMenu *mnuEdit = new QPopupMenu(this);
        Q_CHECK_PTR(mnuEdit);
        menuBar()->insertItem("&Edit", mnuEdit);

        QAction *actionFind = new QAction("Find", "&Find...", CTRL+Key_F, this, "find");
        connect(actionFind, SIGNAL( activated() ), this, SLOT( showFindDialog() ));
        actionFind->addTo(mnuEdit);

        QAction *actionFindNext = new QAction("Find Next", "&Find Next", Key_F3, this, "find next");
        connect(actionFindNext, SIGNAL( activated() ), this, SLOT( findNext() ));
        actionFindNext->addTo(mnuEdit);

        QAction *actionFindReplace = new QAction("FindReplace", "&Find And Replace...", CTRL+Key_R, this, "find replace");
        connect(actionFindReplace, SIGNAL( activated() ), this, SLOT( showFindReplaceDialog() ));
        actionFindReplace->addTo(mnuEdit);
        
        mnuEdit->insertSeparator();
        
        QAction *actionGoToLine = new QAction("Go To Line", "&Go To Line...", CTRL+Key_G, this, "go to line");
        connect(actionGoToLine, SIGNAL( activated() ), this, SLOT( showGoToLineDialog() ));
        actionGoToLine->addTo(mnuEdit);


        
        /* SMALL Menu */
        QPopupMenu *mnuSmall = new QPopupMenu(this);
        Q_CHECK_PTR(mnuSmall);
        menuBar()->insertItem("&SMALL", mnuSmall);

        QAction *actionBuild = new QAction("Build", "&Build", Key_F8, this, "build");
        connect(actionBuild, SIGNAL( activated() ), this, SLOT( smallBuild() ));
        actionBuild->addTo(mnuSmall);

        /* Options Menu */
        QPopupMenu *mnuOptions = new QPopupMenu(this);
        Q_CHECK_PTR(mnuOptions);
        menuBar()->insertItem("&Options", mnuOptions);

        QAction *actionSettings = new QAction("Settings", "&Toolset Settings...", 0, this, "settings");
        connect(actionSettings, SIGNAL( activated() ), this, SLOT( showSettingsDialog() ));
        actionSettings->addTo(mnuOptions);


        /* Help Menu */
        QPopupMenu *mnuHelp = new QPopupMenu(this);
        Q_CHECK_PTR(mnuHelp);
        menuBar()->insertItem("&Help", mnuHelp);

        QAction *actionAbout = new QAction("About", "&About NXW Toolset", 0, this, "about");
        connect(actionAbout, SIGNAL( activated() ), this, SLOT( showAboutDialog() ));
        actionAbout->addTo(mnuHelp);

        QAction *actionAboutQt = new QAction("About", "&About QT", 0, this, "about");
        connect(actionAboutQt, SIGNAL( activated() ), this, SLOT( showAboutQtDialog() ));
        actionAboutQt->addTo(mnuHelp);

        /* File ToolBar */
        QToolBar *tbFile = new QToolBar(this, "file operations");
        
        tbFile->setLabel("File Operations");
        
        new QToolButton(QPixmap("images/filenew.png"), "New File",
                QString::null, this, SLOT(openNewFile()), tbFile, "new file");
        new QToolButton(QPixmap("images/fileopen.png"), "Open File",
                QString::null, this, SLOT(openFileDialog()), tbFile, "open file");
        new QToolButton(QPixmap("images/filesave.png"), "Save File",
                QString::null, this, SLOT(saveCurrFile()), tbFile, "save file");
        new QToolButton(QPixmap("images/fileclose.png"), "Close File",
                QString::null, this, SLOT(closeCurrFile()), tbFile, "close file");
}

void NXWToolset::showAboutQtDialog()
{
        QMessageBox::aboutQt(this);
}

void NXWToolset::showAboutDialog()
{
        NXWAboutDialog *dlgAbout = new NXWAboutDialog(this, "about dialog");

        dlgAbout->exec();
}

void NXWToolset::addSelectedFunc(QListViewItem *item)
{
        if (item == NULL) return;
        
        QString sText = item->text(0);
        if (sText == NULL) return;

        if (m_mainTab->count() < 1) return;

        QStringList slFunc = (*m_funcMap)[sText];
        
        NXWTextEdit *textEdit = reinterpret_cast<NXWTextEdit*>(m_mainTab->currentPage());
        textEdit->insert(slFunc[1]);
}

void NXWToolset::addSelectedConst(QListViewItem *item)
{
        if (item == NULL) return;

        QString sText = item->text(0);
        if (sText == NULL) return;

        if (m_mainTab->count() < 1) return;

        NXWTextEdit *textEdit = reinterpret_cast<NXWTextEdit*>(m_mainTab->currentPage());
        textEdit->insert(sText);
}

void NXWToolset::compCursorChanged(int para, int pos)
{
        QString sLink(g_compEdit->text(para));

        if (sLink.isEmpty()) return;

        QString sFilename, sRow, sFile, sSymLink;
        int nRow;
        QStringList slLink;
        slLink = QStringList::split(":", sLink);
        sFilename = slLink[0];
        sRow = slLink[1];
        nRow = sRow.toInt() - 1;
        
        
        
        QFile fLink("small-scripts");
        QFileInfo fLinkInfo(fLink);
        
        if (fLinkInfo.isSymLink()) {
                sSymLink = fLinkInfo.readLink();
                sFilename = QString("%1%2").arg(sSymLink).arg(sFilename.replace(QRegExp("small-scripts/", false), ""));
        } else sFilename = QString("%1/%2").arg(QDir::currentDirPath()).arg(sFilename);      

        QFile file(sFilename);
        if (!file.exists()) return;
        QFileInfo fileInfo(file);
        
        g_compEdit->setSelection(para, 0, para, sLink.length());

        //Let's check if the file has been already opened
        int nTab = 0;
        if (m_mainTab->count() > 0) {
                for (nTab = 0; nTab < m_mainTab->count(); nTab++) {
                        if (QString::compare(sFilename, m_mainTab->page(nTab)->name()) == 0) {
                                m_mainTab->setCurrentPage(nTab);
                                NXWTextEdit *textEdit = reinterpret_cast<NXWTextEdit*>(m_mainTab->currentPage());
                                textEdit->setCursorPosition(nRow, 0);
                                textEdit->setFocus();
                                QString sText = textEdit->text(nRow);
                                if (!sText.isEmpty())
                                        textEdit->setSelection(nRow, 0, nRow, sText.length());
                                return;
                        }
                }
        }

        (*m_saveMap)[sFilename] = false;

        NXWTextEdit *addTextEdit = new NXWTextEdit(this, file.name());
        m_mainTab->addTab(addTextEdit, fileInfo.fileName());
        if (m_mainTab->isHidden()) m_mainTab->show();
        m_mainTab->showPage(addTextEdit);
        changeCaption(addTextEdit);
        addTextEdit->setCursorPosition(nRow, 0);
        addTextEdit->setFocus();
        QString sText = addTextEdit->text(nRow);
        if (!sText.isEmpty())
                addTextEdit->setSelection(nRow, 0, nRow, sText.length());
}

void NXWToolset::showFuncHelp(QListViewItem *item)
{
        if (item == NULL) return;
        
        QString sFunc = item->text(0);
        if (sFunc == NULL) return;
        
        QStringList slFunc = (*m_funcMap)[sFunc];
        m_helpEdit->setText(slFunc.first());
        m_bottomTab->showPage(m_helpEdit);
}

void NXWToolset::showConstHelp(QListViewItem *item)
{
        if (item == NULL) return;
        
        QString sConst = item->text(0);
        if (sConst == NULL) return;

        m_helpEdit->setText(sConst);
        m_bottomTab->showPage(m_helpEdit);
}

void NXWToolset::closeCurrFile()
{
        if (m_mainTab->count() < 1) return;
        if ((*m_saveMap)[m_mainTab->currentPage()->name()] == true ||
                (QString::compare(QString(NEWFILENAME),QString(m_mainTab->currentPage()->name())) == 0 && reinterpret_cast<NXWTextEdit*>(m_mainTab->currentPage())->text() != "")
                ) {
                if ( QMessageBox::warning(this, "Question", "The file is new or it has been modified, do you want to save it?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes ) {
                        saveCurrFile();
                }
        }
        (*m_saveMap)[m_mainTab->currentPage()->name()] = false;
        m_mainTab->removePage(m_mainTab->currentPage());
        if (m_mainTab->count() < 1) {
                m_mainTab->hide();
                setCaption(APPNAME);
        }
}

void NXWToolset::saveAsCurrFile()
{
        if (m_mainTab->count() < 1) return;

        NXWTextEdit *textEdit = reinterpret_cast<NXWTextEdit*>(m_mainTab->currentPage());
        if (textEdit->text() == NULL) return;
        
        QString sFilename = QFileDialog::getSaveFileName(
                        "small-scripts",
                        "*",
                        this,
                        "save as file dialog",
                        "Choose a name for the new file" );

        if (sFilename != NULL) { //User hasn't pressed cancel
                QFile file(sFilename);
                if (file.open(IO_WriteOnly)) {
                        QTextStream ts( &file );
                        ts << textEdit->text();
                        file.flush();
                        textEdit->setModified(false);
                        QFileInfo fileInfo(file);
                        const char* sNewTabName = sFilename;
                        (*m_saveMap)[textEdit->name()] = false;
                        textEdit->setName(sNewTabName);
                        m_mainTab->setTabLabel(textEdit, fileInfo.fileName());
                        (*m_saveMap)[sFilename] = false;
                        changeCaption(m_mainTab->currentPage());
                        file.close();
                } else {
                        QMessageBox::information( this, "Error",
                        ERR_PERMISSIONS,
                        QMessageBox::Ok );
                }
        }
}

void NXWToolset::saveCurrFile()
{
        if (m_mainTab->count() < 1) return;

        QString sFilename = m_mainTab->currentPage()->name();

        if (QString::compare(sFilename, QString(NEWFILENAME)) == 0) { //It's a new file
                saveAsCurrFile();
                return;
        }

        if ((*m_saveMap)[sFilename] == false) return;

        NXWTextEdit *textEdit = reinterpret_cast<NXWTextEdit*>(m_mainTab->currentPage());
        QFile file(sFilename);
        if (file.open(IO_WriteOnly)) {
                QTextStream ts( &file );
                ts << textEdit->text();
                file.flush();
                textEdit->setModified(false);
                (*m_saveMap)[sFilename] = false;
                changeCaption(m_mainTab->currentPage());
                file.close();
        } else {
                QMessageBox::information( this, "Error",
                ERR_PERMISSIONS,
                QMessageBox::Ok );
        }

}

void NXWToolset::saveAllFiles()
{
        if (m_mainTab->count() < 1) return;
        int nTab;
        for (nTab = 0; nTab < m_mainTab->count(); nTab++) {
                m_mainTab->setCurrentPage(nTab);
                saveCurrFile();
        }
}

void NXWToolset::closeAllFiles()
{
        if (m_mainTab->count() < 1) return;
        if ((*m_saveMap)[m_mainTab->currentPage()->name()] == true ||
                (QString::compare(QString(NEWFILENAME),QString(m_mainTab->currentPage()->name())) == 0 && reinterpret_cast<NXWTextEdit*>(m_mainTab->currentPage())->text() != "")
                ) {
                if ( QMessageBox::warning(this, "Question", "The file is new or it has been modified, do you want to save it?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes ) {
                        saveCurrFile();
                }
        }
        (*m_saveMap)[m_mainTab->currentPage()->name()] = false;
        m_mainTab->removePage(m_mainTab->currentPage());

        if (m_mainTab->count() < 1) {
                m_mainTab->hide();
                setCaption(APPNAME);
        } else closeAllFiles();
}

void NXWToolset::openNewFile()
{
        if (m_mainTab == NULL) initGUI();
        NXWTextEdit *addTextEdit = new NXWTextEdit(this, NEWFILENAME);
        if (m_mainTab->isHidden()) m_mainTab->show();
        m_mainTab->addTab(addTextEdit, NEWFILENAME);
        m_mainTab->showPage(addTextEdit);
}

void NXWToolset::openFileDialog()
{
        if (m_mainTab == NULL) initGUI();

        QString sFilename = QFileDialog::getOpenFileName(
                "small-scripts",
                NULL,
                this,
                "open file dialog",
                "Choose a file to open" );

        if (sFilename == NULL) return; //User pressed cancel

        //Let's check if the file has been already opened
        int nTab = 0;
        if (m_mainTab->count() > 0) {
                for (nTab = 0; nTab < m_mainTab->count(); nTab++) {
                        if (QString::compare(sFilename, m_mainTab->page(nTab)->name()) == 0) {
                                m_mainTab->setCurrentPage(nTab);
                                return;
                        }
                }
        }

        QFile file(sFilename);
        (*m_saveMap)[sFilename] = false;

        QFileInfo fileInfo(file);

        NXWTextEdit *addTextEdit = new NXWTextEdit(this, file.name());
        m_mainTab->addTab(addTextEdit, fileInfo.fileName());
        if (m_mainTab->isHidden()) m_mainTab->show();
        m_mainTab->showPage(addTextEdit);
        

        changeCaption(addTextEdit);
}

void NXWToolset::signModified()
{
        if (m_mainTab->count() < 1) return;
        if (m_mainTab->currentPage()->name() == NEWFILENAME) return;
        if (!(reinterpret_cast<NXWTextEdit*>(m_mainTab->currentPage())->isModified())) return;
        (*m_saveMap)[m_mainTab->currentPage()->name()] = true;
        changeCaption(m_mainTab->currentPage());
}

void NXWToolset::changeCaption(QWidget* tab)
{
        QString sCaption;
        if (QString::compare(tab->name(), QString(NEWFILENAME)) == 0) { //Untitled file
                sCaption = QString("%1 - %2").arg(NEWFILENAME).arg(APPNAME);
                setCaption(sCaption);
                return;
        }

        QFile file(tab->name());
        QFileInfo fileInfo(file);

	if ((*m_saveMap)[tab->name()] == true)
		sCaption = QString("%1 [modified] - %2").arg(fileInfo.fileName()).arg(APPNAME);
        else
                sCaption = QString("%1 - %2").arg(fileInfo.fileName()).arg(APPNAME);
	
	m_mainTab->setTabToolTip(tab, fileInfo.absFilePath());

        setCaption(sCaption);
}

void NXWToolset::smallBuild()
{
        g_compEdit->clear();
        
        char *argv[5];

        argv[0] = "nxwtoolset.internal.compiler";
	argv[1] = new char[50];
	argv[2] = new char[50];
	argv[3] = new char[50];
	argv[4] = new char[50];

        strcpy(argv[1], "small-scripts/override.sma");
	strcpy(argv[2], "-osmall-scripts/override.amx");
	strcpy(argv[3], "-d1");
	strcpy(argv[4], "-i./small-scripts/include");

        int ret = compiler_main(5, (char **)argv);

        QString sResult = "\nCompiling Successful";
        if (ret > 1) sResult = "\nCompiling Unsuccessful";
        
        m_bottomTab->showPage(g_compEdit);
}

void NXWToolset::showSettingsDialog()
{
        QMessageBox::information( this, "Sorry",
        "Not implemented yet :)",
        QMessageBox::Ok );
}


void NXWToolset::statusCursorPosition(int para, int pos)
{
        statusBar()->message(QString("Row: %1  Column: %2").arg(para).arg(pos));
}

void NXWToolset::showGoToLineDialog()
{
        if (m_mainTab->count() < 1) return;
        
        bool bOk = false;
        int nRow = QInputDialog::getInteger(
                APPNAME,
                "Go to line: ", 0, 0, 2147483647, 1, &bOk, this, "go to dialog");
        if (!bOk) return;

        reinterpret_cast<NXWTextEdit*>(m_mainTab->currentPage())->setCursorPosition(nRow, 0);
}

void NXWToolset::showFindDialog()
{
        bool bOk = false;
        QString sText = QInputDialog::getText(
                    "Find Text",
                    "Find: ",
                    QLineEdit::Normal, QString::null, &bOk, this );
        if (!bOk || sText.isEmpty()) return;
        m_sFind = sText;
        findNext();
}

void NXWToolset::findNext()
{
        if (m_sFind == NULL || m_mainTab->count() < 1) return;

        NXWTextEdit *textEdit = reinterpret_cast<NXWTextEdit*>(m_mainTab->currentPage());
       
        if (textEdit->find(m_sFind, false, false, true) == true) return;

        if (QMessageBox::information(this, "Find",
                "End of page reached.\nDo you want to continue from the beginning?",
                QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) return;
        int nPara = 0, nIndex = 0;
        if (textEdit->find(m_sFind, false, false, true, &nPara, &nIndex) == true) return;
        QMessageBox::information(this, "Find", QString("Text \"%1\" not found.").arg(m_sFind), QMessageBox::Ok);
}

void NXWToolset::findNext(QString sFind)
{
        if (sFind == NULL) return;
        m_sFind = sFind;
        findNext();
}

void NXWToolset::showFindReplaceDialog()
{
        NXWFindReplaceDialog *dlgFindReplace = new NXWFindReplaceDialog(this, "find replace dialog");
        dlgFindReplace->exec();
}

void NXWToolset::replaceNext(QString sFind, QString sReplace)
{
        if (m_mainTab->count() < 1) return;

        m_sFind = sFind;
        m_sReplace = sReplace;
        NXWTextEdit *textEdit = reinterpret_cast<NXWTextEdit*>(m_mainTab->currentPage());
        if (textEdit->hasSelectedText()) {
                if (textEdit->selectedText().upper() != sFind.upper()) {
                        findNext();
                } else {
                        textEdit->insert(sReplace, false, true, true);
                        findNext();
                }
        } else findNext();
}

void NXWToolset::replaceAll(QString sFind, QString sReplace)
{
        if (m_mainTab->count() < 1) return;

        NXWTextEdit *textEdit = reinterpret_cast<NXWTextEdit*>(m_mainTab->currentPage());

        int nTimes = textEdit->text().contains(sFind, false);
        QString sText(textEdit->text().replace(QRegExp(sFind, false), sReplace));
        textEdit->setText(sText);
        (*m_saveMap)[textEdit->name()] = true;
        changeCaption(textEdit);
        QMessageBox::information(this, "Find", QString("%1 substitutions done.").arg(nTimes), QMessageBox::Ok);
}

NXWToolset::~NXWToolset()
{
}

/* END -- NoX-Wizard Toolset Main Widget */



/* NoX-Wizard file visualisation widget */

NXWTextEdit::NXWTextEdit(QWidget *parent, const char* name) : QTextEdit(parent, name)
{
        connect(this, SIGNAL( textChanged() ), parent, SLOT( signModified() ));
        connect(this, SIGNAL( cursorPositionChanged(int, int) ), parent, SLOT( statusCursorPosition(int, int) ));
        connect(this, SIGNAL( returnPressed() ), this, SLOT( indentNewLine() ));


        setFont(QFont("console"));
        if (QString::compare(QString(name), QString(NEWFILENAME)) == 0)
                return;

        QFile file(name);
        if ( file.open( IO_ReadOnly ) ) {
                QTextStream ts( &file );
                setText( ts.read() );
                file.close();
        } else {
                QMessageBox::information( this, "Error",
                ERR_PERMISSIONS,
                QMessageBox::Ok );
        }

        new NXWSyntaxHighlighter(this);
}

void NXWTextEdit::indentNewLine()
{
        int para, index, nTabPos = 0, nPos = 0;
        getCursorPosition(&para, &index);
        para--;
        if (para < 0) return;
        QString sLine = text(para);
        para++;
        for ( (nTabPos = sLine.find("\t", nPos)); (nTabPos != -1) && ((nTabPos-nPos) <= 1); (nTabPos = sLine.find("\t", ++nPos))) {
                insertAt("\t", para, index);
        }
        moveCursor(QTextEdit::MoveLineEnd, false);
}

//NoX-Wizard Toolset syntax highlighter
NXWSyntaxHighlighter::NXWSyntaxHighlighter(QTextEdit* textEdit) : QSyntaxHighlighter(textEdit)
{
}

/* Syntax Highlighter data */

#define COLOR_NONE QColor(0,0,0)
#define COLOR_COMMENT QColor(6,120,23)
#define COLOR_KEYWORD QColor(14,35,173)
#define COLOR_TYPE QColor(173,70,106)
#define COLOR_STRING QColor(222,25,7)
#define COLOR_PREPROCESSOR QColor(128,0,128)

enum eSyntax {
        SYNTAX_NONE = 0, SYNTAX_COMMENT
};

/* End -- Syntax Highlighter data */


#define MAX_KEYWORDS 11
static const QString sKeywords[MAX_KEYWORDS] = {
        "if ", "else", "switch", "case", "for", "while", "return", "const", "enum", "continue", "break"
};
                     
#define MAX_TYPES 4
static const QString sTypes[MAX_TYPES] = {
        "new", "public", "stock", "static"
};

#define MAX_PREPROCESSORS 2
static const QString sPreprocessor[MAX_PREPROCESSORS] = {
        "#define", "#include"
};
               

     
int NXWSyntaxHighlighter::highlightParagraph(const QString& sText, int nLastState)
{
        int nPos = 0, nPos2 = -1, i = 0;
        eSyntax nSyntax = SYNTAX_NONE;
        QColor cColor = COLOR_NONE;

        setFormat(0, sText.length(), COLOR_NONE);


        /* Looking for keywords */
        for (i = 0; i < MAX_KEYWORDS; i++) {
                nPos = 0;
                while ((nPos = sText.find(sKeywords[i], nPos)) != -1)
                {
                        setFormat(nPos, sKeywords[i].length(), COLOR_KEYWORD);
                        nPos += sKeywords[i].length();
                }
        }

        /* Looking for data types */
        for (i = 0; i < MAX_TYPES; i++) {
                nPos = 0;
                while ((nPos = sText.find(sTypes[i], nPos)) != -1)
                {
                        setFormat(nPos, sTypes[i].length(), COLOR_TYPE);
                        nPos += sTypes[i].length();
                }
        }

        /* Looking for preprocessors */
        for (i = 0; i < MAX_PREPROCESSORS; i++) {
                nPos = 0;
                while ((nPos = sText.find(sPreprocessor[i], nPos)) != -1)
                {
                        setFormat(nPos, sPreprocessor[i].length(), COLOR_PREPROCESSOR);
                        nPos += sPreprocessor[i].length();
                }
        }

        /* Looking for strings */
        nPos = -1;
        while ((nPos = sText.find("\"", nPos+1)) != -1)
        {
                nPos2 = sText.find("\"", nPos+1);
                if (nPos2 > nPos) {
                        nPos2 += 1;
                        setFormat(nPos, nPos2 - nPos, COLOR_STRING);
                } else {
                        setFormat(nPos, 1, COLOR_STRING);
                }
        }        

                       
        /* Looking for comments */
        nPos = sText.find("//");
        if (nPos != -1) {
                setFormat(nPos, sText.length() - nPos, COLOR_COMMENT);
                return nLastState;
        }

        nPos = -2;
        if (nLastState == SYNTAX_COMMENT) {
                nPos = sText.find("*/");
                if (nPos == -1) {
                        setFormat(0, sText.length(), COLOR_COMMENT);
                        return nLastState;
                } else {
                        nPos += 2;
                        setFormat(0, nPos, COLOR_COMMENT);
                }
        } else {
                nPos = -2;
        }

        while ((nPos = sText.find("/*", nPos+2)) != -1)
        {
                nPos2 = sText.find("*/");
                if (nPos2 > nPos) {
                        nPos2 += 2;
                        setFormat(nPos, nPos2 - nPos, COLOR_COMMENT);
                } else {
                        setFormat(nPos, sText.length() - nPos, COLOR_COMMENT);
                        return SYNTAX_COMMENT;
                }
        }

        return nSyntax;
}


/* END -- NoX-Wizard file visualisation widget */


/* NoX-Wizard settings dialog */

NXWSettingsDialog::NXWSettingsDialog(NXWToolset *parent, const char *name) : QDialog(parent, name, true)
{
	
}

/* END -- NoX-Wizard settings dialog */


/* NoX-Wizard Find And Replace dialog */

NXWFindReplaceDialog::NXWFindReplaceDialog(NXWToolset *parent, const char* name) : QDialog(parent, name, true)
{
        m_parent = parent;
        setCaption("Find and Replace");
        QGridLayout *mainGrid = new QGridLayout(this, 5, 1, 10, 5, "main layout");
        QLabel *lFind = new QLabel("Find: ", this);
        QLabel *lReplace = new QLabel("Replace with: ", this);
        m_findEdit = new QLineEdit(this, "find edit");
        m_replaceEdit = new QLineEdit(this, "replace edit");

        QGridLayout *btnGrid = new QGridLayout(1, 4, -1, "btn layout");
        QPushButton *btnSkip = new QPushButton("Skip", this, "btnSkip");
        QPushButton *btnReplaceNext = new QPushButton("Replace Next", this, "btnReplaceNext");
        QPushButton *btnReplaceAll = new QPushButton("Replace All", this, "btnReplaceAll");
        QPushButton *btnCancel = new QPushButton("Cancel", this, "btnCancel");
        btnGrid->addWidget(btnSkip, 0, 0);
        btnGrid->addWidget(btnReplaceNext, 0, 1);
        btnGrid->addWidget(btnReplaceAll, 0, 2);
        btnGrid->addWidget(btnCancel, 0, 3);

        mainGrid->addWidget(lFind, 0, 0);
        mainGrid->addWidget(m_findEdit, 1, 0);
        mainGrid->addWidget(lReplace, 2, 0);
        mainGrid->addWidget(m_replaceEdit, 3, 0);
        mainGrid->addLayout(btnGrid, 4, 0);

        connect(btnSkip, SIGNAL( clicked() ), this, SLOT( callFindNext() ));
        connect(btnCancel, SIGNAL( clicked() ), this, SLOT( close() ));
        connect(btnReplaceNext, SIGNAL( clicked() ), this, SLOT( callReplaceNext() ));
        connect(btnReplaceAll, SIGNAL( clicked() ), this, SLOT( callReplaceAll() ));
}

void NXWFindReplaceDialog::callFindNext()
{
        QString sFind;

        if (m_findEdit->text() == NULL) sFind = "";
        else sFind = m_findEdit->text();

        m_parent->findNext(sFind);
}

void NXWFindReplaceDialog::callReplaceNext()
{
        QString sFind;
        QString sReplace;

        if (m_findEdit->text() == NULL) sFind = "";
        else sFind = m_findEdit->text();
        
        if (m_replaceEdit->text() == NULL) sReplace = "";
        else sReplace = m_replaceEdit->text();
        
        m_parent->replaceNext(sFind, sReplace);
}

void NXWFindReplaceDialog::callReplaceAll()
{
        QString sFind;
        QString sReplace;

        if (m_findEdit->text() == NULL) sFind = "";
        else sFind = m_findEdit->text();

        if (m_replaceEdit->text() == NULL) sReplace = "";
        else sReplace = m_replaceEdit->text();

        m_parent->replaceAll(sFind, sReplace);

        close();
}

/* END -- NoX-Wizard Find And Replace dialog */


/* NoX-Wizard about dialog */

NXWAboutDialog::NXWAboutDialog(QWidget *parent, const char* name) : QDialog(parent, name, true)
{
        setCaption("NoX-Wizard Toolset Informations");
        resize(500,400);
        QGridLayout *mainGrid = new QGridLayout(this, 3, 1, 10, 5, "main layout");
        QTabWidget *mainTab = new QTabWidget(this);
        QLabel *lName = new QLabel(QString("\nNoX-Wizard Toolset - Version %1\n").arg(APPVERSION), this);
        lName->setFont(QFont("console"));
        QPushButton *btnClose = new QPushButton("Close", this, "btnClose");
        connect(btnClose, SIGNAL( clicked() ), this, SLOT( close() ));

        QTextEdit *readmeEdit = new QTextEdit(this);
        readmeEdit->setReadOnly(true);
        QFile fReadme("README");
        if ( fReadme.open( IO_ReadOnly ) ) {
                QTextStream ts( &fReadme );
                readmeEdit->setText( ts.read() );
                fReadme.close();
        }
        mainTab->addTab(readmeEdit, "Informations");

        QTextEdit *authorsEdit = new QTextBrowser(this);
        authorsEdit->setReadOnly(true);
        QFile fAuthors("AUTHORS");
        if ( fAuthors.open( IO_ReadOnly ) ) {
                QTextStream ts( &fAuthors );
                authorsEdit->setText( ts.read() );
                fAuthors.close();
        }
        mainTab->addTab(authorsEdit, "Authors");

        QTextEdit *todoEdit = new QTextBrowser(this);
        todoEdit->setReadOnly(true);
        QFile fTodo("TODO");
        if ( fTodo.open( IO_ReadOnly ) ) {
                QTextStream ts( &fTodo );
                todoEdit->setText( ts.read() );
                fTodo.close();
        }
        mainTab->addTab(todoEdit, "To Do List");

        QTextEdit *licenseEdit = new QTextEdit(this);
        licenseEdit->setReadOnly(true);
        QFile fLicense("COPYING");
        if ( fLicense.open( IO_ReadOnly ) ) {
                QTextStream ts( &fLicense );
                licenseEdit->setText( ts.read() );
                fLicense.close();
        }
        mainTab->addTab(licenseEdit, "License");

        QTextEdit *smallLicenseEdit = new QTextEdit(this);
        smallLicenseEdit->setReadOnly(true);
        QFile fSmallLicense("small_license.txt");
        if ( fSmallLicense.open( IO_ReadOnly ) ) {
                QTextStream ts( &fSmallLicense );
                smallLicenseEdit->setText( ts.read() );
                fSmallLicense.close();
        }
        mainTab->addTab(smallLicenseEdit, "Compiler License");

        mainGrid->addWidget(lName, 0, 0);
        mainGrid->addWidget(mainTab, 1, 0);
        mainGrid->addWidget(btnClose, 2, 0);
}

/* END -- NoX-Wizard about dialog */

void sc_printToGUI(char* buffer)
{
        g_compEdit->append(QString("%1").arg(buffer));
}
