#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "main-menu.h"
#include <stdlib.h>
//extern newGame current;

GtkWidget *diffTitle;
GtkWidget *diffList;

GtkWidget *diffPlayerTitle;
GtkWidget *diffPlayerList;

char tempName[20];
char tempPass[20];
char name[20];
char password[20];
int fd;
static int num,ready,ready2=0;
//Start Page Navigation Functions
static void goToHelp( GtkWidget *widget,
                    GtkWidget   *data )
{
     gtk_notebook_set_current_page (GTK_NOTEBOOK(data), 2);
}

static void goToStartGame( GtkWidget *widget,
                   GtkWidget   *data )
{
    gtk_notebook_set_current_page (GTK_NOTEBOOK(data), 3);
}
static void checkLogin( GtkWidget *widget,
                   GtkWidget   *data )
{
   /* if(!(strcmp(name,tempName) && strcmp(password,tempPass)))
    {    
    	gtk_notebook_set_current_page (GTK_NOTEBOOK(data), 1);
    }*/
    FILE *fp; 
    fp=fopen("Credentials.txt","r");
    
    while(fscanf(fp,"%s",tempName)==1)
  {
    fscanf(fp,"%s",tempPass);
   
    if(ready==1 && ready2==1 && (strcmp(name,tempName)==0) &&( strcmp(password,tempPass)==0))
    {
        gtk_notebook_set_current_page (GTK_NOTEBOOK(data), 1);
	num =1;
        break;
    }
  }
    if(num==0){
        g_print("Incorrect password or username\nPlease enter valid credentials\n");
    }
  
    fclose(fp);
}
static void goToCreateAccount( GtkWidget *widget,
                   GtkWidget   *data )
{
    gtk_notebook_set_current_page (GTK_NOTEBOOK(data), 4);
}


static void checkCreateAccount( GtkWidget *widget,
                   GtkWidget   *data )
{
    //create account
    fd= open("Credentials.txt",O_APPEND|O_WRONLY,0600);
    
    if(fd==-1)
    {
	printf("Failed to create and open file.\n");
    }
  if(ready==1&& ready2==1 && password!=NULL && name!=NULL){
    write(fd,name,strlen(name));
   // write(fd,strcat(password,"\n"),10);
    write(fd," ",1);
    write(fd,password,strlen(password));
    write(fd,"\n",1);
    gtk_notebook_set_current_page (GTK_NOTEBOOK(data), 1);
  }
  else{
    g_print("Invalid credentials please enter again\n");
  }
    ready=0;
    ready2=0;
    close(fd);
}


static void goToHome( GtkWidget *widget,
                   GtkWidget   *data )
{
    gtk_notebook_set_current_page (GTK_NOTEBOOK(data), 1);
}
//End Page Navigation Functions
//Login Functions
static void goToName( GtkWidget *widget,
                   GtkWidget   *data )
{
    strcpy(name,gtk_entry_get_text(GTK_ENTRY(data)));
    g_print("%s\n",gtk_entry_get_text(GTK_ENTRY(data)));
    ready=1;
    gtk_entry_set_text(GTK_ENTRY(data),"Username entered");
}
static void goToPassword( GtkWidget *widget,
                   GtkWidget   *data )
{
    strcpy(password,gtk_entry_get_text(GTK_ENTRY(data)));
    g_print("%s\n",gtk_entry_get_text(GTK_ENTRY(data)));
    
	ready2=1;
    gtk_entry_set_text(GTK_ENTRY(data),"Password  entered");

}

//Start Game Init State Functions, write game settings to state file
static void setHuman( GtkWidget *widget,
                   GtkWidget   *data )
{
    state = fopen("state.txt", "a");
    current.opponent = 0;
    fprintf(state,"opp%d",0);
    fclose(state);
}


static void setCPU( GtkWidget *widget,
                   GtkWidget   *data )
{
    gtk_widget_show(diffTitle);
    gtk_widget_show(diffList);
    state = fopen("state.txt", "a");
    current.opponent = 1;
    fprintf(state,"opp%d",1);
    fclose(state);
    //gtk_show
}
static void setPlayer( GtkWidget *widget,
                   GtkWidget   *data )
{
    gtk_widget_show(diffPlayerTitle);
    gtk_widget_show(diffPlayerList);
    state=fopen("state.txt","a");
    current.opponent = 0;
    fprintf(state,"opp%d",0);
    fclose(state);
}
static void setWhite( GtkWidget *widget,
                   GtkWidget   *data )
{
    state = fopen("state.txt", "a");
    current.set_color = 0;
    fprintf(state,"set%d",0);
    fclose(state);
}

static void setBlack( GtkWidget *widget,
                   GtkWidget   *data )
{
    state = fopen("state.txt", "a");
    current.set_color = 1;
    fprintf(state,"set%d",1);
    fclose(state);
}
//End Game Init State Functions

//This is to connect the menus to the chess game
static void startGame( GtkWidget *widget,
                   GtkWidget   *data )
{
    char *diff = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data));
    state = fopen("state.txt", "a");
    if(diff == NULL){
      fprintf(state,"diff%d",0);
    }
    else if(!strcmp(diff,"Easy")){
      fprintf(state,"diff%d",1);
    }
    else if(!strcmp(diff,"Medium")){
      fprintf(state,"diff%d",2);
    }
    else if(!strcmp(diff,"Hard")){
      fprintf(state,"diff%d",3);
    }
    fclose(state);
    system("./GUI_Chess");
}

//Exit Game
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    /* If you return FALSE in the "delete-event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs. */

    /* Change TRUE to FALSE and the main window will be destroyed with
     * a "delete-event". */

    return FALSE;
}

//Exit Game
static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}



int main( int   argc,
          char *argv[] )
{
    GtkTextBuffer *helpText;
    GtkTextIter iter;

    GtkWidget *window;              //Menu Window

    GtkWidget *gameBook;            //Layout Structure for Stacked Menus

    GtkWidget *tableLayout;         //Home Menu Table Layout
    GtkWidget *helpLayout;          //Help Menu Table Layout
    GtkWidget *newGameLayout;       //New Game Menu Table Layout
    GtkWidget *userLogin;	    //User Login Layout
    GtkWidget *createAccount;

    
    GtkWidget *title;               //Page Titles
    GtkWidget *helpTitle;
    GtkWidget *newGameTitle;
    GtkWidget *userTitle;
    GtkWidget *createAccountTitle;

    GtkWidget *newButton;           //Widgets on Home Page
    GtkWidget *helpButton;

    GtkWidget *retButton;           //Widgets on Help Page
    GtkWidget *scrollView;
    GtkWidget *helpView;

    GtkWidget *humButton;           //Widgets on New Game Page
    GtkWidget *playerButton;
    GtkWidget *cpuButton;
    GtkWidget *wButton;
    GtkWidget *bButton;
    GtkWidget *startButton;
    GtkWidget *oppTitle;
    GtkWidget *colTitle;
		                     //Widgets on userLogin
    GtkWidget *loginButton;
    GtkWidget *createAccountButton;
    GtkWidget *nameEntry;
    GtkWidget *nameButton;
    GtkWidget *hbox;
    GtkWidget *nameTitle;
    GtkWidget *passwordEntry;
    GtkWidget *passwordButton;
    GtkWidget *hbox2;
    GtkWidget *passwordTitle;
    				    //Widgets on createAccount
    GtkWidget *signUpButton;
    GtkWidget *nameSaveEntry;
    GtkWidget *nameSaveButton;
    GtkWidget *hbox3;
    GtkWidget *nameSaveTitle;
    GtkWidget *passwordSaveEntry;
    GtkWidget *passwordSaveButton;
    GtkWidget *hbox4;
    GtkWidget *passwordSaveTitle;


    gtk_init (&argc, &argv);

    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    //request for window to be size of windowWidth and windowHeight defined in the header file
    gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT) ;
    //set boarder width by window border defined in the header file
    gtk_container_set_border_width (GTK_CONTAINER(window), WINDOW_BORDER) ;
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER) ;
    gtk_window_set_title(GTK_WINDOW(window), "Welcome!") ;
    // make window size fixed
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE) ;

    /* When the window is given the "delete-event" signal (this is given
     * by the window manager, usually by the "close" option, or on the
     * titlebar), we ask it to call the delete_event () function
     * as defined above. The data passed to the callback
     * function is NULL and is ignored in the callback function. */
    g_signal_connect (window, "delete-event",
		      G_CALLBACK (delete_event), NULL);


    g_signal_connect (window, "destroy",
		      G_CALLBACK (destroy), NULL);





    //Create Menu Notebook
    gameBook = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window), gameBook);

    //Create Table Layouts
    tableLayout = gtk_table_new(10, 10, TRUE);
    helpLayout = gtk_table_new(10, 10, FALSE);
    newGameLayout = gtk_table_new(10, 10, FALSE);
    userLogin = gtk_table_new(10,10,TRUE);
    createAccount = gtk_table_new(10,10,TRUE);

    //Add Layouts to Menu Notebook
    gtk_notebook_append_page (GTK_NOTEBOOK(gameBook), userLogin, NULL);

    gtk_notebook_append_page (GTK_NOTEBOOK(gameBook), tableLayout, NULL);
    gtk_notebook_append_page (GTK_NOTEBOOK(gameBook), helpLayout, NULL);
    gtk_notebook_append_page (GTK_NOTEBOOK(gameBook), newGameLayout, NULL);
    gtk_notebook_append_page (GTK_NOTEBOOK(gameBook), createAccount, NULL);

    //Hide Clickable Tabs
    gtk_notebook_set_show_tabs (GTK_NOTEBOOK(gameBook), FALSE);
    // Set userTitle
    userTitle = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(userTitle), "<big><b><u>Kings of Chess:</u>\r   <u>User Login</u></b></big>");
    nameTitle = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(nameTitle), "<big><b><u>Name</u></b></big>");
    passwordTitle = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(passwordTitle), "<big><b><u>Password</u></b></big>");


    // set CreateAccount title
    createAccountTitle = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(createAccountTitle), "<big><b><u>Kings of Chess:</u>\r   <u>Create Account</u></b></big>");
    nameSaveTitle = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(nameSaveTitle), "<big><b><u>Name</u></b></big>");
    passwordSaveTitle = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(passwordSaveTitle), "<big><b><u>Password</u></b></big>");

    //Set Layout Titles
    title = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(title), "<big><b><u>Kings of Chess</u></b></big>");

    helpTitle = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(helpTitle), "<big><b><u>Kings of Chess:</u>\r       <u>Help</u></b></big>");

    newGameTitle = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(newGameTitle), "<big><b><u>Kings of Chess:</u>\r  <u>Game Select</u></b></big>");

    //Set Start New Game Info Titles
    oppTitle = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(oppTitle), "  <u>Select\rOpponent:</u>");

    colTitle = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(colTitle), "  <u>Select\rSet Color:</u>");
     
    
    diffTitle = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(diffTitle), "  <u>Select\rCPU Level:</u>");
    
    diffPlayerTitle = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(diffTitle), "  <u>Select\rOpponent:</u>");

    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    //Create all Widgets
    loginButton=gtk_button_new_with_label ("Login");
    createAccountButton=gtk_button_new_with_label ("Create Account");
    nameEntry=gtk_entry_new();
    nameButton=gtk_button_new_with_label ("enter");
    hbox=gtk_hbox_new(0,0);
    gtk_box_pack_start(GTK_BOX(hbox),nameEntry,0,0,0);
    gtk_box_pack_start(GTK_BOX(hbox),nameButton,0,0,0);
    passwordEntry=gtk_entry_new();
    passwordButton=gtk_button_new_with_label ("enter");
    hbox2=gtk_hbox_new(0,0);
    gtk_box_pack_start(GTK_BOX(hbox2),passwordEntry,0,0,0);
    gtk_box_pack_start(GTK_BOX(hbox2),passwordButton,0,0,0);

    signUpButton=gtk_button_new_with_label ("Sign Up");
    nameSaveEntry=gtk_entry_new();
    nameSaveButton=gtk_button_new_with_label ("enter");
    hbox3=gtk_hbox_new(0,0);
    gtk_box_pack_start(GTK_BOX(hbox3),nameSaveEntry,0,0,0);
    gtk_box_pack_start(GTK_BOX(hbox3),nameSaveButton,0,0,0);
    passwordSaveEntry=gtk_entry_new();
    passwordSaveButton=gtk_button_new_with_label ("enter");
    hbox4=gtk_hbox_new(0,0);
    gtk_box_pack_start(GTK_BOX(hbox4),passwordSaveEntry,0,0,0);
    gtk_box_pack_start(GTK_BOX(hbox4),passwordSaveButton,0,0,0);


    newButton = gtk_button_new_with_label ("New Game");
    helpButton = gtk_button_new_with_label ("Help");


    helpView = gtk_text_view_new();
    scrollView = gtk_scrolled_window_new(NULL, NULL);
    retButton = gtk_button_new_with_label ("Main Menu");
    helpText = gtk_text_view_get_buffer(GTK_TEXT_VIEW(helpView));
    gtk_text_buffer_get_iter_at_offset(helpText, &iter, 0);
    gtk_text_buffer_insert(helpText, &iter,
      "Welcome to Chess Unleashed.\nLet’s help you get started :)\n\nChess Pieces:\n\nPawn \n\t- Moves one step forward only\n\t- Can only capture pieces diagonally in front of \n\t it\n\t- Can move two steps forward if its on its \n\tstarting square\n\t- Can perform an 'En Passant' (see below)\nRook\n\t- Moves horizontally or vertically across the \n\tboard\nBishop\n\t- Moves diagonally across the board\nQueen\n\t- Moves horizontally, vertically, or diagonally \n\tacross the board\nKing\n\t- Moves one step in any direction\nKnight\n\t- Moves in an 'L' shape, 2 steps in any direction,\n\tthen one step perpendicular to the first move\n\t- Only piece that can “jump” over other pieces\n\nTerminology:\n\nRank\n\t- A row of the chessboard labeled 1-8\nFile\n\t- A column of the chessboard labeled\nCapture\n\t- To capture an opponent’s piece, you must \n\tland on that piece’s square at the end of your \n\tturn\nCheck\n\t- When a king is under threat of capture by an \n\tenemy piece. The player in check must make a \n\tmove to put himself out of check\nCheckmate\n\t- When a king is unable to get out of a check. \n\tThe game ends here and the player in \n\tcheckmate loses.\nPromotion\n\t- When a pawn reaches its 8th rank, it can be \n\treplaced by a queen/king/bishop/rook of the \n\tsame color\n\nSpecial Moves:\n\nCastling\n\t- Move where a king moves 2 spaces in the \n\tdirection of the rook on either side and the \n\trook moves to the opposite side of the king. \n\tThis can only happen if the following scenarios \n\tare true:\n\t\t1. Neither the king nor the rook have \n\t\tbeen moved before\n\t\t2. There are no pieces between the \n\t\trook and king\n\t\t3. The king is not currently in check\n\t\t4. The king does not pass through a \n\t\tsquare occupied by an enemy piece\n\t\t5. The king does not end up in check\nEn Passant\n\t- Special pawn capture that can only occur if \n\tan opposing pawn moves two spaces on its first\n\tturn and it could have been captured by your \n\tpawn if it had only moved one space.\n"
      , -1);
    //gtk_text_view_set_buffer (GTK_TEXT_VIEW(helpView), helpText);
    gtk_text_view_set_editable (GTK_TEXT_VIEW(helpView), FALSE);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(helpView), FALSE);
    gtk_container_add(GTK_CONTAINER(scrollView), helpView);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrollView), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

    humButton = gtk_button_new_with_label ("vs. Human");
    playerButton=gtk_button_new_with_label ("vs. Player Online");
    cpuButton = gtk_button_new_with_label ("vs. CPU");
    wButton = gtk_button_new_with_label ("White");
    bButton = gtk_button_new_with_label ("Black");
    startButton = gtk_button_new_with_label ("Start Game");

    diffList = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(diffList), "Easy");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(diffList), "Medium");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(diffList), "Hard");

    diffPlayerList=gtk_combo_box_text_new();
//Change to have player Names
    FILE *fp;
    fp=fopen("Credentials.txt","r");
    while(fscanf(fp,"%s",tempName)==1)
    {
	 fscanf(fp,"%s",tempPass);
         gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(diffPlayerList), tempName);
    }
    fclose(fp);
/*
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(diffPlayerList), "Easy");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(diffPlayerList), "Medium");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(diffPlayerList), "Hard");
*/
    //Assign Signals to Nav Buttons
    g_signal_connect (loginButton, "clicked",
                      G_CALLBACK (checkLogin), GTK_NOTEBOOK(gameBook));
    g_signal_connect (createAccountButton, "clicked",
                      G_CALLBACK (goToCreateAccount), GTK_NOTEBOOK(gameBook));
    g_signal_connect (nameButton, "clicked",
                      G_CALLBACK (goToName),nameEntry);
    g_signal_connect (passwordButton, "clicked",
                      G_CALLBACK (goToPassword),passwordEntry);

    g_signal_connect (signUpButton, "clicked",
                      G_CALLBACK (checkCreateAccount), GTK_NOTEBOOK(gameBook));
    g_signal_connect (nameSaveButton, "clicked",
                      G_CALLBACK (goToName),nameSaveEntry);
    g_signal_connect (passwordSaveButton, "clicked",
                      G_CALLBACK (goToPassword),passwordSaveEntry);



    g_signal_connect (newButton, "clicked",
		      G_CALLBACK (goToStartGame), GTK_NOTEBOOK(gameBook));
    g_signal_connect (helpButton, "clicked",
		      G_CALLBACK (goToHelp), GTK_NOTEBOOK(gameBook));
    g_signal_connect (retButton, "clicked",
		      G_CALLBACK (goToHome), GTK_NOTEBOOK(gameBook));

    //Assign Signals to Game Init Buttons
    g_signal_connect (humButton, "clicked",
      		G_CALLBACK (setHuman), NULL);
    g_signal_connect (cpuButton, "clicked",
      		G_CALLBACK (setCPU), NULL);
    g_signal_connect (wButton, "clicked",
          G_CALLBACK (setWhite), NULL);
    g_signal_connect (bButton, "clicked",
      		G_CALLBACK (setBlack), NULL);
    g_signal_connect (playerButton, "clicked",
                G_CALLBACK (setPlayer), NULL);

    //Starts a Chess Game in a new Window
    g_signal_connect (startButton, "clicked",
      		G_CALLBACK (startGame), GTK_COMBO_BOX_TEXT(diffList));
    g_signal_connect_swapped (startButton, "clicked",
			    G_CALLBACK (gtk_widget_destroy), window);

    //Create Visual Layout
    gtk_table_attach(GTK_TABLE(userLogin), userTitle, 1, 2, 1, 2, GTK_FILL, GTK_FILL, 0, 0) ;
    gtk_table_attach(GTK_TABLE(userLogin), loginButton, 1, 2, 8,9, GTK_FILL, GTK_FILL, 0, 0) ;
    gtk_table_attach(GTK_TABLE(userLogin), createAccountButton, 1, 2, 9, 10, GTK_FILL, GTK_FILL, 0, 0) ;
    gtk_table_attach(GTK_TABLE(userLogin), hbox, 1,3,4 , 5, GTK_FILL, GTK_FILL, 0, 0) ;
    gtk_table_attach(GTK_TABLE(userLogin), nameTitle, 1, 2, 3, 4, GTK_FILL, GTK_FILL, 0, 0) ;
    gtk_table_attach(GTK_TABLE(userLogin), hbox2, 1,3, 6, 7, GTK_FILL, GTK_FILL, 0, 0) ;
    gtk_table_attach(GTK_TABLE(userLogin), passwordTitle, 1,2, 5, 6, GTK_FILL, GTK_FILL, 0, 0) ;


    gtk_table_attach(GTK_TABLE(createAccount), createAccountTitle, 1, 2, 1, 2, GTK_FILL, GTK_FILL, 0, 0) ;
    gtk_table_attach(GTK_TABLE(createAccount), signUpButton, 1, 2, 10,11, GTK_FILL, GTK_FILL, 0, 0) ;
    gtk_table_attach(GTK_TABLE(createAccount), hbox3, 1,3,4 , 5, GTK_FILL, GTK_FILL, 0, 0) ;
    gtk_table_attach(GTK_TABLE(createAccount), nameSaveTitle, 1, 2, 3, 4, GTK_FILL, GTK_FILL, 0, 0) ;
    gtk_table_attach(GTK_TABLE(createAccount), hbox4, 1,3, 6, 7, GTK_FILL, GTK_FILL, 0, 0) ;
    gtk_table_attach(GTK_TABLE(createAccount), passwordSaveTitle, 1,2, 5, 6, GTK_FILL, GTK_FILL, 0, 0) ;

    gtk_table_attach(GTK_TABLE(tableLayout), title, 1, 2, 1, 2, GTK_FILL, GTK_FILL, 0, 0) ;
    gtk_table_attach(GTK_TABLE(tableLayout), newButton, 1, 2, 7,8, GTK_FILL|GTK_SHRINK, GTK_FILL|GTK_SHRINK, 0, 0) ;
    gtk_table_attach(GTK_TABLE(tableLayout), helpButton, 1, 2, 9, 10, GTK_FILL|GTK_SHRINK, GTK_FILL|GTK_SHRINK, 0, 0) ;

    gtk_table_attach(GTK_TABLE(helpLayout), helpTitle, 1, 2, 0, 2, GTK_FILL, GTK_FILL, 10, 10) ;
    gtk_table_attach(GTK_TABLE(helpLayout), scrollView, 0, 9, 2, 9, GTK_FILL|GTK_SHRINK, GTK_FILL|GTK_SHRINK, 10, 10) ;
    gtk_table_attach(GTK_TABLE(helpLayout), retButton, 0, 1, 9, 10, GTK_FILL|GTK_SHRINK, GTK_FILL|GTK_SHRINK, 10, 10) ;

    gtk_table_set_col_spacing(GTK_TABLE(helpLayout), 0, 20);
    gtk_table_set_col_spacing(GTK_TABLE(helpLayout), 1, 50);
    gtk_table_set_col_spacing(GTK_TABLE(helpLayout), 3, 55);
    gtk_table_set_row_spacing(GTK_TABLE(helpLayout), 3, 275);
    gtk_table_set_col_spacing(GTK_TABLE(helpLayout), 9, 20);


    gtk_table_attach(GTK_TABLE(newGameLayout), newGameTitle, 2, 3, 1, 2, GTK_FILL, GTK_FILL, 0, 10) ;
    gtk_table_attach(GTK_TABLE(newGameLayout), oppTitle, 1, 2, 3, 4, GTK_FILL|GTK_SHRINK, GTK_FILL|GTK_SHRINK, 10, 10) ;
    gtk_table_attach(GTK_TABLE(newGameLayout), humButton, 1, 2, 4, 5, GTK_FILL|GTK_SHRINK, GTK_FILL|GTK_SHRINK, 10, 10) ;
    gtk_table_attach(GTK_TABLE(newGameLayout), playerButton, 1, 2, 6, 7, GTK_FILL|GTK_SHRINK, GTK_FILL|GTK_SHRINK, 10, 10) ;
    gtk_table_attach(GTK_TABLE(newGameLayout), cpuButton, 1, 2, 5, 6, GTK_FILL|GTK_SHRINK, GTK_FILL|GTK_SHRINK, 10, 10) ;
    gtk_table_attach(GTK_TABLE(newGameLayout), colTitle, 3, 4, 3, 4, GTK_FILL|GTK_SHRINK, GTK_FILL|GTK_SHRINK, 10, 10) ;
    gtk_table_attach(GTK_TABLE(newGameLayout), wButton, 3, 4, 4, 5, GTK_FILL|GTK_SHRINK, GTK_FILL|GTK_SHRINK, 10, 10) ;
    gtk_table_attach(GTK_TABLE(newGameLayout), bButton, 3, 4, 5, 6, GTK_FILL|GTK_SHRINK, GTK_FILL|GTK_SHRINK, 10, 10) ;
    gtk_table_attach(GTK_TABLE(newGameLayout), diffTitle, 2, 3, 3, 4, GTK_FILL|GTK_SHRINK, GTK_FILL|GTK_SHRINK, 10, 10) ;
    gtk_table_attach(GTK_TABLE(newGameLayout), diffList, 2, 3, 4, 5, GTK_FILL, GTK_FILL, 10, 10) ;
    gtk_table_attach(GTK_TABLE(newGameLayout), diffPlayerTitle, 2, 3, 3, 4, GTK_FILL|GTK_SHRINK, GTK_FILL|GTK_SHRINK, 10, 10) ;
    gtk_table_attach(GTK_TABLE(newGameLayout), diffPlayerList, 2, 3, 4, 5, GTK_FILL, GTK_FILL, 10, 10) ;

    gtk_table_attach(GTK_TABLE(newGameLayout), startButton, 2, 3, 7, 8, GTK_FILL|GTK_SHRINK, GTK_FILL|GTK_SHRINK, 10, 10) ;

    gtk_table_set_col_spacing(GTK_TABLE(newGameLayout), 0, 15);
    gtk_table_set_col_spacing(GTK_TABLE(newGameLayout), 1, 20);
    gtk_table_set_col_spacing(GTK_TABLE(newGameLayout), 2, 10);
    gtk_table_set_row_spacing(GTK_TABLE(newGameLayout), 2, 50);
    gtk_table_set_row_spacing(GTK_TABLE(newGameLayout), 6, 50);

    gtk_widget_show_all(window);
    gtk_widget_hide(diffList);
    gtk_widget_hide(diffTitle);
    gtk_widget_hide(diffPlayerList);
    gtk_widget_hide(diffPlayerTitle);
    gtk_main ();

    return 0;
}
