/*
Course: COMP 150
Last Name: Sherrell
First Name: Justin

File:  Project02Fall22_SherrellJ.cpp
Summary: My program is a simulation of an archery tournament, 
where you can change stats of players and weather to manipulate the game.
*/
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <windows.h> // windows time function 
#include <fstream>
#include <iomanip> // setw()
#include <sstream>  // stringstream. Let's me convert int's to a string
#include <limits>
#include <istream>
using namespace std;
fstream myFile;
const int team_size = 4; // 3 players and one team name

bool autoplay,skip,predict;

float wait = 100,multi = 15;

struct PlayerInfo
{
    string player;
    int skill;
    int focus;
    int power;
    float shots_had;
    float points;
    float avg_points;
};

void initialize(PlayerInfo *s, string names[team_size]);
int stat_check(PlayerInfo *s, int i);
int compete(PlayerInfo *Team_1,PlayerInfo *Team_2);
void See_Stats(PlayerInfo *s,string names[team_size]);
void ChangeStats(PlayerInfo *s,string names[team_size]);
void print(int x);
void autoplaymenu();
int who_won(PlayerInfo *Team);
void After_Game_Stats(PlayerInfo *s,string names[team_size]);

int main()
{
	myFile.open("Archery_Turnement.txt",ios::out); // create / overwrite file
	myFile.close();
	
	srand (time(NULL));
	string Justin_names[team_size] = {"Justin","  KJ  "," Noah ","Team Canada"};
	string Bob_names[team_size] = {"Oliver"," Emma "," Liam ","Team USA"};
	string Danny_names[team_size] = {"Asahi","Chiyo","Emiko","Team Japan"};
	string Johney_names[team_size] = {"Louis","Elise"," Maxime ","Team France"};
	
	PlayerInfo Justin_team[team_size];
	PlayerInfo Bob_team[team_size];
	PlayerInfo Danny_team[team_size];
	PlayerInfo Johney_team[team_size];
	
	bool playAgain;
	do{
		playAgain = false;
		predict = false;
	    initialize(Justin_team , Justin_names);
	    initialize(Bob_team , Bob_names);
	    initialize(Danny_team , Danny_names);
	    initialize(Johney_team , Johney_names);
    	
    	string predictGuess;
	    int input;
	    do{
		    cout<<"\n\t\t\t\t\tMain Menu \n [1] Play Game [2] Show Team's stats [3] Change Player stats  [4] Random Stats [5] Guess winner ";
		    cin>>input;
		    
		    while(input > 5 || input < 1|| cin.fail()){
		    	cout<<"Invalid Choice Pick Again: ";
		    	cin.clear(); // clear the error state
  				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any invalid 
		    	cin >> input;
			}
		    
		    switch(input) {
			  	case 1:
			    break;
			  	case 2:
				  	See_Stats(Justin_team,Justin_names);
				    See_Stats(Bob_team,Bob_names);
				    See_Stats(Danny_team,Danny_names);
				    See_Stats(Johney_team,Johney_names);
				    break;
				case 3:
					int ChangeStatsInput;
					cout<<"\nWhat team? [1] Canada [2] USA [3] Japan [4] France  ";
			    	cin>>ChangeStatsInput;
					switch(ChangeStatsInput) {
			  			case 1:
			  				ChangeStats(Justin_team,Justin_names);
			    		break;
			    		case 2:
			  				ChangeStats(Bob_team,Bob_names);
			    		break;
			    		case 3:
			  				ChangeStats(Danny_team,Danny_names);
			    		break;
			    		case 4:
			  				ChangeStats(Johney_team,Johney_names);
			    		break;
			    		default:
			    			cout<<"\nInvalid Input returning to main menu . . .";
			    		
					}
					break;
				case 4:
					initialize(Justin_team , Justin_names);
			    	initialize(Bob_team , Bob_names);
			    	initialize(Danny_team , Danny_names);
			    	initialize(Johney_team , Johney_names);
			    	cout<<"\n------------------------\nPlayer Stats Randomised\n------------------------\n";
			    	break;
			    case 5:
			    	int what_team;
			    	cout<<"What Team do you think will win? [1] Canada [2] USA [3] Japan [4] France ";
			    	cin>>what_team;
			    	switch(what_team){
			    		case 1:
			  				predict = true;
			  				predictGuess = Justin_names[3];
			  				cout <<"\nPrediction Saved\n";
			    		break;
			    		case 2:
			    			predict = true;
			  				predictGuess = Bob_names[3];
			  				cout <<"\nPrediction Saved\n";
			    		break;
			    		case 3:
			    			predict = true;
			  				predictGuess = Danny_names[3];
			  				cout <<"\nPrediction Saved\n";
			    		break;
			    		case 4:
			    			predict = true;
			  				predictGuess = Johney_names[3];
			  				cout <<"\nPrediction Saved\n";
			    		break;
			    		default:
			    			cout<<"\nInvalid Input returning to main menu . . .";
					}
			}
		
	}while(input !=1);
	
	
		autoplaymenu();
	
		int team1picker,team2picker;
		bool checked = false;
	
		int semifinal[4]={0,0,0,0};
		int wins[4]={0,0,0,0};
		do{
			team1picker = rand() % 4;
			team2picker = rand() % 4;
			
			if(team1picker == team2picker){
				continue;
			}
			else{
				checked = true;
				semifinal[team1picker]=1;
				semifinal[team2picker]=1;
			}
			
		}while(!checked);
		
		// pointers to stuctures
		PlayerInfo *team1;
		PlayerInfo *team2; 
		
		
		switch(team1picker) {
	  	case 0:{team1 = Justin_team; break;}
	    case 1:{team1 = Bob_team; break;}
	    case 2:{team1 = Danny_team; break;}
	    case 3:{team1 = Johney_team; break;}
		}
		
		
		switch(team2picker) {
	  	case 0:{team2 = Justin_team; break;}
	  	case 1:{team2 = Bob_team; break;}
	  	case 2:{team2 = Danny_team; break;}
	    case 3:{team2 = Johney_team; break;}
		}
		
	    myFile.open("Archery_Turnement.txt",ios::app);
	    if(myFile.is_open()){
			myFile<< setw(25) << "Game 1" <<endl;
			myFile<<"----------------------------------------------"<<"\n\n";
			myFile.close();}
				
	 	Sleep(wait); cout<<"\n\n \t\t GAME 1! " <<endl;
		Sleep(wait);	cout<<"----------------------------------------------"<<"\n\n";
		
		// GAME 1
		int game1 = compete(team1,team2);
		 
		wins[game1] = 1; // update team who won in array

		if(!autoplay)system("pause");else Sleep(wait*multi * 2);
		 
		// picking team that hasn't fought yet
		for(int x =0; x<4;x++){ 
			if(semifinal[x] == 0){
				team1picker = x;
				semifinal[x] = 1;
				break;}}
				
		// picking team that hasn't fought yet
		for(int x =0; x<4;x++){
			if(semifinal[x] == 0){
				team2picker = x;
				semifinal[x] = 1;}}
		
		switch(team1picker) {
	  	case 0:{team1 = Justin_team; break;}
	  	case 1:{ team1 = Bob_team; break;}
	    case 2:{team1 = Danny_team; break;}	
	    case 3:{team1 = Johney_team; break;}
		}
		
		switch(team2picker) {
	  	case 0:{team2 = Justin_team; break;}
	  	case 1:{team2 = Bob_team; break;}
		case 2:{team2 = Danny_team; break;}
		case 3:{team2 = Johney_team; break;}
		}
				
		
		 
	 	
	 	myFile.open("Archery_Turnement.txt",ios::app);
	    if(myFile.is_open()){
		myFile<< setw(25) << "Game 2" <<endl;
		myFile<<"----------------------------------------------"<<"\n\n";
		myFile.close();}
		
		Sleep(wait); cout<<"\n\n \t\t GAME 2! " <<"\n----------------------------------------------"<<"\n\n";
		if(!autoplay) system("pause"); else Sleep(wait*multi);
		cout<<"\n\n";
		
		// game 2
		int game2 = compete(team1,team2);
		
		wins[game2] = 2; // update team who won in array
		
		
		cout<<"\n\n \t\t GRAND FINALS! " <<"\n----------------------------------------------"<<"\n\n";
		if(!autoplay) system("pause"); else Sleep(wait*multi);
		cout<<"\n\n";
		
		myFile.open("Archery_Turnement.txt",ios::app);
	    if(myFile.is_open()){
		myFile<< setw(25) << "GRAND FINALS!" <<endl;
		myFile<<"----------------------------------------------"<<"\n\n";
		myFile.close();}
		
		// find team that won game 1
		for(int x =0; x<4;x++){
			if(wins[x] == 1){
				team1picker = x;}}
				
				
		// find team that won game 2
		for(int x =0; x<4;x++){
			if(wins[x] == 2){
				team2picker = x;
				wins[x] = 1;}}  
				
		switch(team1picker) {
	  	case 0:{team1 = Justin_team; break;}
	  	case 1:{team1 = Bob_team; break;}
		case 2:{team1 = Danny_team; break;}
		case 3:{team1 = Johney_team; break;}
		}
		switch(team2picker) {
	  	case 0:{team2 = Justin_team; break;}
	  	case 1:{team2 = Bob_team; break;}
		case 2:{team2 = Danny_team; break;}
		case 3:{team2 = Johney_team; break;}
		}
		
		// GAME 3
		int Game3 = compete(team1,team2);
		wins[Game3] = 2; // update who won the finals 
		
		int first,second,third1,third2;
		string first_place,second_place,third1_place,third2_place;
		
		bool firstthird = false;
		
		// Team's Placements
		for(int i=0;i<4;i++){
			if(wins[i] == 2){
				first = i;
			}
			else if(wins[i] == 1){
				second = i;
			}
			else if (wins[i] == 0 && !firstthird){
				third1 = i;
				wins[i] = 1;
				firstthird = true;
			}
			else {
				third2 = i;
				wins[i] = 1;
			}
		}
			
		PlayerInfo *Winning_Team;
		
		switch(first) {
	  	case 0:{first_place = Justin_team[3].player; Winning_Team = Justin_team; break;}
	  	case 1:{first_place = Bob_team[3].player; Winning_Team = Bob_team; break;}
		case 2:{first_place = Danny_team[3].player; Winning_Team = Danny_team; break;}
		case 3:{first_place = Johney_team[3].player; Winning_Team = Johney_team; break;}
		}
		// Calculating avg points for the team
		for(int i = 0; i<3; i++){
		Winning_Team[i].avg_points = Winning_Team[i].points / Winning_Team[i].shots_had;
		}
		
		float highest_avg = Winning_Team[0].avg_points;
		int mvp_loc = 0;
		// finding mvp player based off avg_points and setting the location of were the mvp is in the array.
		for(int i = 1; i<3; i++){
			
			if(highest_avg < Winning_Team[i].avg_points){
				highest_avg = Winning_Team[i].avg_points;
				mvp_loc = i;
			}
		}
		
		PlayerInfo *second_place_team;
		switch(second) {
	  	case 0:{second_place = Justin_team[3].player; second_place_team = Justin_team; break;}
	  	case 1:{second_place = Bob_team[3].player; second_place_team = Bob_team; break;}
		case 2:{second_place = Danny_team[3].player; second_place_team = Danny_team; break;}
		case 3:{second_place = Johney_team[3].player; second_place_team = Johney_team; break;}
		}
		// Calculating avg points for the team
		for(int i = 0; i<3; i++){
		second_place_team[i].avg_points = second_place_team[i].points / second_place_team[i].shots_had;
		}
		
		
		PlayerInfo *third1_place_team;
		switch(third1) {
	  	case 0:{third1_place = Justin_team[3].player; third1_place_team = Justin_team; break;}
	  	case 1:{third1_place = Bob_team[3].player; third1_place_team = Bob_team; break;}
		case 2:{third1_place = Danny_team[3].player; third1_place_team = Danny_team; break;}
		case 3:{third1_place = Johney_team[3].player; third1_place_team = Johney_team; break;}
		}
		// Calculating avg points for the team
		for(int i = 0; i<3; i++){
		third1_place_team[i].avg_points = third1_place_team[i].points / third1_place_team[i].shots_had;
		}
		
		PlayerInfo *third2_place_team;
		switch(third2) {
	  	case 0:{third2_place = Justin_team[3].player; third2_place_team = Justin_team; break;}
	  	case 1:{third2_place = Bob_team[3].player; third2_place_team = Bob_team; break;}
		case 2:{third2_place = Danny_team[3].player; third2_place_team = Danny_team; break;}
		case 3:{third2_place = Johney_team[3].player; third2_place_team = Johney_team; break;}
		}
		// Calculating avg points for the team
		for(int i = 0; i<3; i++){
		third2_place_team[i].avg_points = third2_place_team[i].points / third2_place_team[i].shots_had;
		}
		
		if(!autoplay) system("pause"); else Sleep(wait*multi);
		
		Sleep(wait); cout<<"\n--------------------------------------------------------\n\n";
		Sleep(wait); cout<<"\tGRAND CHAMPIONS: "<<first_place<<"!!!!!!!"<<endl;
		Sleep(wait); cout<<"\n    Winning Team MVP\n    "<< Winning_Team[mvp_loc].player<<"   Points: "<<Winning_Team[mvp_loc].points<<"   Shots: "<<Winning_Team[mvp_loc].shots_had<<fixed<<setprecision(2)<<"   Avg Points: "<<Winning_Team[mvp_loc].avg_points;
		
		myFile.open("Archery_Turnement.txt",ios::app);
	    if(myFile.is_open()){
	    myFile<<"\n--------------------------------------------------------\n\n";
		myFile<<"\tGRAND CHAMPIONS: "<<first_place<<"!!!!!!!"<<endl;
		myFile<<"\n  MVP : "<< Winning_Team[mvp_loc].player<<"   Points: "<<Winning_Team[mvp_loc].points<<"   Shots: "<<Winning_Team[mvp_loc].shots_had<<fixed<<setprecision(2)<<"   Avg Points: "<<Winning_Team[mvp_loc].avg_points;
		myFile<<"\n\n--------------------------------------------------------\n";
		myFile.close();}
		
		if(predict){
			if(predictGuess == first_place)
				cout<<"\n\n\tYour Prediction Was Correct!";
				else
				cout<<"\n\n\tSorry Your Prediction Was Incorrect";
		}
		
		
		Sleep(wait); cout<<"\n\n--------------------------------------------------------\n\n";
		Sleep(wait); cout<<"\t   Second Place: "<<second_place<<endl;
		myFile.open("Archery_Turnement.txt",ios::app);
		if(myFile.is_open()){
	    myFile<<"\n\n--------------------------------------------------------\n\n";
		myFile<<"\t   Second Place: "<<second_place<<endl;
		myFile.close();}
		
		
		
		Sleep(wait); cout<<"\n--------------------------------------------------------\n";
		Sleep(wait); cout<<"\n\t    Third Place: "<<third1_place<<endl;
		myFile.open("Archery_Turnement.txt",ios::app);
		if(myFile.is_open()){
	    myFile<<"\n--------------------------------------------------------\n";
		myFile<<"\n\t    Third Place: "<<third1_place<<endl;
		myFile.close();}
		
		
		Sleep(wait); cout<<"\n--------------------------------------------------------\n";
		Sleep(wait); cout<<"\n\t    Third Place: "<<third2_place<<endl;
		myFile.open("Archery_Turnement.txt",ios::app);
		if(myFile.is_open()){
	    myFile<<"\n--------------------------------------------------------\n";
		myFile<<"\n\t    Third Place: "<<third2_place<<endl;
		myFile<<"\n--------------------------------------------------------\n\n\n\n";
		myFile.close();}
		
		cout<<"\n--------------------------------------------------------\n\n\n\n";
		
		if(!autoplay) system("pause"); else Sleep(wait*multi);
		
		cout<<"See End Game Stats? [1] Yes [2] No  ";
		cin>>input;
		while(input > 2 || input < 1|| cin.fail()){
		    	cout<<"Invalid Choice Pick Again: ";
		    	cin.clear(); // clear the error state
  				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any invalid 
		    	cin >> input;
			}
		
		if(input == 1){
			After_Game_Stats(Justin_team,Justin_names);
			After_Game_Stats(Bob_team,Bob_names);
			After_Game_Stats(Danny_team,Danny_names);
			After_Game_Stats(Johney_team,Johney_names);
		}
		
		
		Sleep(wait); cout<<"\n\nPlay again?  [1] Yes  [2] No ";
		cin>>input;
		while(input > 2 || input < 1|| cin.fail()){
		    	cout<<"Invalid Choice Pick Again: ";
		    	cin.clear(); // clear the error state
  				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any invalid 
		    	cin >> input;
			}
			
		if(input == 1){
			myFile.open("Archery_Turnement.txt",ios::app);
	    	if(myFile.is_open()){
	    	myFile<< "\n ______________________________________________________\n"<<endl;
	    	myFile<< setw(25) << " NEW GAME ";
			myFile<< "\n ______________________________________________________\n"<<endl;
			myFile.close();
		}
			playAgain = true;
			
		}

}while(playAgain);

    return 0;	
}

void After_Game_Stats(PlayerInfo *s,string names[team_size]){
	
	cout<<endl<< setw(25) <<names[3]<<endl;
	
	cout<<"Names:    ";
	for(int i=0; i<3; i++) {
        cout<< setw(9) << s[i].player << "   ";
    }
	cout<<"\nshots:    ";
	for(int i=0; i<3; i++) {
        cout<<fixed<<setprecision(0)<< setw(9) << s[i].shots_had<<"  ";
    }
    cout<<endl<<"points:    ";
    for(int i=0; i<3; i++) {
    	cout<< setw(8)<< s[i].points << "   ";
	}
	cout<<endl<<"avg points:";
	for(int i=0; i<3; i++) {
    	cout<<fixed<<setprecision(2)<< setw(8)<< s[i].avg_points << "   ";
	}
	
	cout<<"\n\n"<<"--------------------------------------------\n";
};

void autoplaymenu(){
	
		autoplay = false; skip = false; float playspeed; // defualt
		int input;
		cout<<"AutoPlay? [1] Yes  [2] No  ";
		cin>>input;
		
		if(input == 1)
		autoplay = true;
		
		if(autoplay){
			cout<<"AutoPlay speed? [1] Default [2] Slower [3] Fast [4] Super Fast [5] Skip to end \n";
			cin>>playspeed;
		while(playspeed > 5 || playspeed < 1 || cin.fail()){
				cin.clear(); // clear the error state
  				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any invalid 
		    	cout<<"Invalid Choice Pick Again: ";
		    	cin >> playspeed;
			}
		
				
			if(playspeed == 2)
				playspeed = .8; // so wait get's longer
				
			else if(playspeed == 3)
				playspeed = 10;
		
			else if(playspeed == 5){
				playspeed = 50000; // skip to end speed
				skip = true; // bypass the weather checks
			}
			wait = wait / playspeed;
		}
	
}
// Showing stats
void See_Stats(PlayerInfo *s,string names[team_size]){
	
	cout<< setw(25) <<names[3]<<endl;
	cout<<"Names:";
	for(int i=0; i<3; i++) {
        cout<< setw(9) << s[i].player << "   ";
    }
    cout<<endl<<"Skill:";
    for(int i=0; i<3; i++) {
    	cout<< setw(8)<< s[i].skill << "   ";
	}
	cout<<endl<<"Focus:";
	for(int i=0; i<3; i++) {
    	cout<< setw(8)<< s[i].focus << "   ";
	}
	cout<<endl<<"Power:";
	for(int i=0; i<3; i++) {
    	cout << setw(8) << s[i].power<< "   ";
	}
    cout<<"\n-----------------------------------------\n";
};
// Printing out txt files for shooting arrows.
void print(int x)
{							  // 0                       1                        2                   3                      4
	string txt_Files[15]={"art/2_bot_shot.txt","art/2_botbot_shot.txt","art/2_top_shot.txt","art/2_toptop_shot.txt","art/5_bot_shot.txt",
	//       5                         6                   7                   8 				9
	"art/5_top_shot.txt","art/10_bot_shot.txt","art/10_top_shot.txt","art/20_shot.txt","art/miss_shot.txt"};

	myFile.open(txt_Files[x].c_str()); // The c_str() makes it posible for myfile.open to read the file name.
	if(myFile.is_open()) // checks if file is open
	{
		string line; 
		while (getline(myFile,line)) // line will fail at end of txt file
		{
			Sleep(wait *.75); // sleeps the program 
			cout<<line<<endl; // output current line
		}
		myFile.close(); // closes file
	}
}
// Changing stats on players 
void ChangeStats(PlayerInfo *s,string names[team_size]){
	int choice;
	int pickAgain;
	do{
	cout<<endl<< setw(35) <<" Pick A player"<<endl<<"------------------------------------------------------------\n";
	for(int i=0; i<3; i++) {
        cout<< setw(9) <<"[" << i+1 <<"] " << s[i].player << "   ";
    }
    cout<<endl;
    cin >> choice;
    while(choice > 3 || choice < 1){
    	cout<<"Invalid Choice Pick Again: ";
    	cin >> choice;
	}
		cout<<"Pick between 1 - 10 for a fair game"<<endl<<"-----------------------------\n";
		cout<<"Current skill: "<< s[choice - 1].skill <<endl;
		cout<<"Input new skill: ";
		cin>>s[choice - 1].skill;
        
        cout<<"Current focus: "<<s[choice - 1].focus<<endl;
		cout<<"Input new focus: ";
		cin>>s[choice - 1].focus;
        
        cout<<"Current power: "<<s[choice - 1].power<<endl;
		cout<<"Input new power: ";
		cin>>s[choice - 1].power;
        
        cout<<"Change another player? [1] Yes [2] No ";
        cin>>pickAgain;
        
    }while(pickAgain == 1);
}
// Setting all players stats to a random number beten 1 - 10
// And giving players names.
void initialize(PlayerInfo *s, string names[team_size])
{
		
    for(int i=0; i<4; i++) 
	{
        s[i].player = names[i];
        s[i].skill = rand() % 10 + 1; // 
        s[i].focus = rand() % 10 + 1; // 
        s[i].power = rand() % 10 + 1; // 
        s[i].avg_points = 0;
        s[i].points = 0;
        s[i].shots_had = 0;
    }
}
// computing what points they get base of there stats and random numbers.
int stat_check(PlayerInfo *s, int i, int weather)
{
	int distraction = rand() % 10 + 1; 
	int inspiration = rand() % 10 + 1;
	int nervousness = rand() % 10 + 1;
        															// Weather could be good or bad
    int shot =  s[i].skill + s[i].focus + s[i].power + 2 * inspiration + weather - distraction - nervousness;
    
    int random;
    int points;
    if(shot >= 30){ // 20 points
    	print(8); // printing out picture that lines up with a 20 point shot.
    	return 20;
	}
	else if(shot >= 20){ // 6 or 7  10 points
    	print(rand() % 2 + 6); // top or bottom of target.
    	return 10;
	}
	else if(shot >= 10){ // 5 or 4  5 points
    	print(rand() % 2 + 4);
    	return 5;
	}
	else if(shot >= 5){ // 0 1 2 3   2 points
    	print(rand() % 4);
    	return 2;
	}
	else { 
    	print(9); // missed shot
    	return 0;
	}
	
}

// Teams compete here.
int compete(PlayerInfo *Team_1,PlayerInfo *Team_2){
	int x=0;	
	myFile.open("Archery_Turnement.txt",ios::app);
    if(myFile.is_open()){
		myFile<< setw(16) <<Team_1[3].player << " vs " <<Team_2[3].player<<"\n\n";
		myFile.close();
	}
	
	Sleep(wait); cout <<"\n--------------------------------------------\n" << setw(16) <<Team_1[3].player << " vs " <<Team_2[3].player<<"\n--------------------------------------------\n";
	Sleep(wait); cout <<"\t\tBest Of [3] \n--------------------------------------------\n";
	
	int weather = rand() % 11 - 5; // -5 to 5
	int input=0;
	
	if(!skip){
		cout<<"Set weather? [1] Yes [2] No ";
		cin>>input;
		if(input == 1){ 
			cout<<"Pick from -5 to 5.  [-5] Being awful weather ----- [5] Perfect weather\n";
			cin>>weather;
			while(weather > 5 || weather < -5 || cin.fail()) {
					cin.clear(); // clear the error state
  					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore any invalid 
			    	cout<<"Invalid Choice Pick Again: ";
			    	cin >> weather;
				}
		cout<<"Weather Set.";
		}
	}
	
	Sleep(wait);
	if(weather >= 3)
	cout<<"\nIt's Amazing Weather Today.\n";
	else if(weather >= 0)
	cout<<"\nIt's a okay weather Today.\n";
	else if(weather >= -1)
	cout<<"\nIt's a light rain Today.\n";
	else if(weather >= -3)
	cout<<"\nIt's Raining And Its Windy Today.\n";
	else
	cout<<"\nThe Weather Is Awful.\n";
	
	int Team1_Total=0,Team2_Total=0;
	bool win = false;
	
	do{
		bool tie = false;
		Sleep(wait); cout<<endl;
		
	myFile.open("Archery_Turnement.txt",ios::app);
    if(myFile.is_open()){
    	myFile<<"Match "<<(x+1)<<endl;
		myFile<< setw(16) <<Team_1[x].player << " vs " <<Team_2[x].player<<endl;
		myFile.close();
	}
	
	
	Sleep(wait); cout << "\t  Match " << (x+1) << "\n----------------------------------\n";
	Sleep(wait); cout << "\t" << Team_1[x].player << " vs " << Team_2[x].player << "\n----------------------------------\n";
	
	if(!autoplay) system("pause"); else Sleep(wait*multi *2);
	
	int Score_1=0,Score_2=0;
	
	int team1_round1_p=0,team1_round2_p=0,team1_round3_p=0;
	int team2_round1_p=0,team2_round2_p=0,team2_round3_p=0;
	
	stringstream ss;
	string team1_shot1,team1_shot2,team1_shot3,S_Score_1;
	string team2_shot1,team2_shot2 ="00",team2_shot3="00",S_Score_2;
	
	Sleep(wait); cout <<"\n\t\t\t "<<Team_1[3].player<<" Shooting\n\n";
	
	if(!autoplay) system("pause"); else Sleep(wait*multi);
	
	for(int i = 0;i<3;i++)
	{
		Sleep(wait); cout<<Team_1[3].player<<endl;
		Sleep(wait); cout<<"Shooter: "<<Team_1[x].player<<"\t\t Shot "<<i+1 <<" of 3"<<"\n\n";
		int points = stat_check(Team_1,x,weather);
		ss.clear(); // clearing string stream
		Team_1[x].shots_had += 1;  // keeping track of shot had for player
		Team_1[x].points += points; // keeping track of points for player
		switch(i){
			// Converting int's to strings and adding a 0 if the number is less then 10 so it lines up nice in the stats.
			case 0: team1_round1_p = points; if(points < 10){ss<<"0"<<team1_round1_p;} else ss<<team1_round1_p; ss >> team1_shot1;  break;
			case 1: team1_round2_p = points; if(points < 10){ss<<"0"<<team1_round2_p;} else ss<<team1_round2_p; ss >> team1_shot2;  break;
			case 2: team1_round3_p = points; if(points < 10){ss<<"0"<<team1_round3_p;} else ss<<team1_round3_p; ss >> team1_shot3;  break;
		}
		Score_1 += points;
		Sleep(wait); cout << endl << "Points Scored: " << points <<"\t\tPoints so far: "<<Score_1<<"\n\n";
		if(!autoplay) system("pause"); else Sleep(wait*multi);
	}
	
  	ss.clear();
	if(Score_1 < 10){ss<<"0"<<Score_1;} else ss<<Score_1; ss >> S_Score_1;

	Sleep(wait); cout<<"\n\n\n";
	Sleep(wait); cout<<"\t\t"<< Team_1[x].player << "   vs \t" << Team_2[x].player <<endl;
	Sleep(wait); cout<<"            ____________________________"<<endl;
	Sleep(wait); cout<<"Shot 1 --> |     "<<team1_shot1<<"       |             |"<<endl;
	Sleep(wait); cout<<"Shot 2 --> |     "<<team1_shot2<<"       |             |"<<endl;
	Sleep(wait); cout<<"Shot 3 --> |     "<<team1_shot3<<"       |             |"<<endl;
	Sleep(wait); cout<<"Total ---> |     "<<S_Score_1       <<"       |             |"<<"\n\n";
	
	if(!autoplay) system("pause"); else Sleep(wait*multi);
	
	Sleep(wait); cout <<"\n\t\t\t "<<Team_2[3].player<<" Shooting\n\n";
	
	if(!autoplay) system("pause"); else Sleep(wait*multi);
	
	for(int i = 0;i<3;i++)
	{
		Sleep(wait); cout<<Team_2[3].player<<endl;
		Sleep(wait); cout<<"Shooter: "<<Team_2[x].player<<"\t\t Shot "<<i+1 <<" of 3"<<"\n\n";
		int points = stat_check(Team_2,x,weather);
		Team_2[x].shots_had += 1; // keeping track of shot had for player
		Team_2[x].points += points; // keeping track of points for player
		ss.clear(); // clearing string stream
		switch(i){
			case 0: team2_round1_p = points; if(points < 10){ss<<"0"<<team2_round1_p;} else ss<<team2_round1_p; ss >> team2_shot1;  break;
			case 1: team2_shot2=""; team2_round2_p = points; if(points < 10){ss<<"0"<<team2_round2_p;} else ss<<team2_round2_p; ss >> team2_shot2;  break;
			case 2: team2_shot3=""; team2_round3_p = points; if(points < 10){ss<<"0"<<team2_round3_p;} else ss<<team2_round3_p; ss >> team2_shot3;  break;
		}
		Score_2 += points;
		Sleep(wait); cout << endl << "Points Scored: " << points <<"\t\tPoints so far: "<<Score_2<<"\n\n";
		Sleep(wait); cout<<Team_1[x].player<<"'s"<<" Total Points: "<<Score_1 <<"\n\n";
		if(!autoplay) system("pause"); else Sleep(wait*multi);
		if(Score_2 > Score_1)
		break;
	}
	ss.clear();
	if(Score_2 < 10){ss<<"0"<<Score_2;} else ss<<Score_2; ss >> S_Score_2;

	
	Sleep(wait); cout<<"\n\n\n";
	Sleep(wait); cout<<"\t\t"<< Team_1[x].player << "   vs \t" << Team_2[x].player <<endl;
	Sleep(wait); cout<<"            ___________________________"<<endl;
	Sleep(wait); cout<<"Shot 1 --> |     "<<team1_shot1<<"      |      "<<team2_shot1<<"     |"<<endl;
	Sleep(wait); cout<<"Shot 2 --> |     "<<team1_shot2<<"      |      "<<team2_shot2<<"     |"<<endl;
	Sleep(wait); cout<<"Shot 3 --> |     "<<team1_shot3<<"      |      "<<team2_shot3<<"     |"<<endl;
	Sleep(wait); cout<<"Total ---> |     "<<S_Score_1       <<"      |      "<<S_Score_2<<"     |"<<"\n\n";
	
	
	if(!autoplay) system("pause"); else Sleep(wait*multi);
	
	myFile.open("Archery_Turnement.txt",ios::app);
    if(myFile.is_open()){	
		myFile<<Team_1[x].player << " Score: "<< Score_1 <<"     "<<Team_2[x].player<< " Score: "<<Score_2<<endl;
		myFile.close();}
		
	if(Score_1 == Score_2){
		tie = true;
		Sleep(wait); cout<<"\n-----------------------------\nIt's A TIE! Rematch\n-----------------------------\n";
		myFile.open("Archery_Turnement.txt",ios::app);
		if(myFile.is_open()){
		myFile <<"\nIt's A TIE! Rematch \n\n";
		myFile.close();}
	}
	else if(Score_1>Score_2){
		Sleep(wait); cout<<"\n------------------------------------------------\n\t"<<Team_1[x].player<<" Scored 1 point for "<<Team_1[3].player<<"\n------------------------------------------------\n";
		
		myFile.open("Archery_Turnement.txt",ios::app);
    	if(myFile.is_open()){	
		myFile<<Team_1[x].player<<" Scored 1 point for "<<Team_1[3].player<<"\n\n";
		myFile.close();}
		
		Team1_Total++;
		if(Team1_Total == 2){
			win = true;
			myFile.open("Archery_Turnement.txt",ios::app);
			if(myFile.is_open()){
			myFile<<Team_1[3].player<<" WON! "<<"\n\n";
			myFile.close();}
		}
	}
	else{
		Sleep(wait); cout<<"\n------------------------------------------------\n\t"<<Team_2[x].player<<" Scored 1 point for "<<Team_2[3].player<<"\n------------------------------------------------\n";
		
		myFile.open("Archery_Turnement.txt",ios::app);
		if(myFile.is_open()){
		myFile<<Team_2[x].player<<" Scored 1 point for "<<Team_2[3].player<<"\n\n";
		myFile.close();}
		
		Team2_Total++;
		if(Team2_Total == 2){
			win = true;
			myFile.open("Archery_Turnement.txt",ios::app);
			if(myFile.is_open()){
			myFile<<Team_2[3].player<<" WON! "<<"\n\n";
			myFile.close();}
		}
	}
	
	myFile.open("Archery_Turnement.txt",ios::app);
			if(myFile.is_open()){
			myFile<<"\t"<<Team_1[3].player<<": "<<Team1_Total<<"\t\t"<<Team_2[3].player<<": "<<Team2_Total<<"\n------------------------------------------------\n";
			myFile.close();}
	
	Sleep(wait); cout<<"\t"<<Team_1[3].player<<": "<<Team1_Total<<"\t\t"<<Team_2[3].player<<": "<<Team2_Total<<"\n------------------------------------------------\n";

	if(!tie){
		x++;
	}
	
	}while(!win);
	
	if(Team1_Total>Team2_Total){
		Sleep(wait); cout<<"\n\n------------------------------------------------\n\t\t"<<Team_1[3].player<<" Won!!"<<"\n------------------------------------------------\n\n";
		return who_won(Team_1); // Figure out what team won
	}
	else if(Team1_Total<Team2_Total){
		Sleep(wait); cout<<"\n\n------------------------------------------------\n\t\t"<<Team_2[3].player<<" Won!!"<<"\n------------------------------------------------\n\n";

		return who_won(Team_2); // Figure out what team won
	}
	
	if(!autoplay) system("pause"); else Sleep(wait*multi * 2);
}
// send back a number that correlates to an array to figure out a winner
who_won(PlayerInfo *Team){
	if(Team[3].player == "Team Canada")
	return 0;
	if(Team[3].player == "Team USA")
	return 1;
	if(Team[3].player == "Team Japan")
	return 2;
	if(Team[3].player == "Team France")
	return 3;
}
