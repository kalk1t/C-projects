#include <windows.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <process.h>
#include <string.h>
#include <stdbool.h>

#pragma warning(disable:4996 6031)
#pragma comment(lib,"msvcrt.lib")

#define size 20

//function that registers a new account for an user.
void new_account();
//function that authorisizes an account.
void authorisize();
//function that deposits money to an account.
void deposit(char username);
//function that transfers money beetween accounts.
void transfer();
//function that withdraws the money.
void withdraw();


//struct that describes all details bank needs to know about user.
struct user {
char username[size];
char password[size];
char name[size];
char last_name[size];
int day,month, year;
char id_number[size];
char phone_number[size];



double balance;
};

int main() {
	int input;
	printf("   ***   MAIN MENU   ***   \n");
	printf("1.Registration. \n");
	printf("2.Log in. \n");
	printf("0.Exit. \n");
	scanf("%d", &input);
	switch (input) {
	case 1: {
		new_account();
	}
		  break;
	case 2: {
		authorisize();
	}
		  break;
	case 0: {
		exit(0);
	}
	}


	return 0;
}

void transfer() {
	//filename holders.
	char fname[size] = "registeredusers.txt";
	char tmp_fname[size] = "temp.txt";
	//variables to open files.
	int transfer;
	int tmp;


	
	//entering password.
	char password[size];
	printf("Re-enter the password for security reasons :   ");
	scanf("%s", password);
	//entering account id you want send to.
	char ID[size];
	printf("Enter an ID of an Account you want transfer to :   ");
	scanf("%s", ID);
	//entering amount you want to send.
	double amount;
	printf("Enter amount :   ");
	scanf("%lf", &amount);

	//opening files.
	transfer = open(fname, O_RDONLY, S_IREAD);
	tmp = open(tmp_fname, O_WRONLY | O_APPEND | O_CREAT, S_IWRITE);


	if ( transfer > 0 && tmp > 0) {
		struct user a;
		
		//reading file before program matches your account.
		while (eof(transfer) == 0) {
			memset(&a, 0, sizeof(struct user));
			read(transfer, &a, sizeof(struct user));
			if (strcmp(a.password, password) == 0) {
				//after program matches your account 
				//program will decrease your balance by amount.
				a.balance -= amount;
				printf("Current balance : %lf", a.balance);
				//write the changed information in file.
				write(tmp, &a, sizeof(struct user));
			}

		}
	}
	else {
		perror("open");
	}
	//closing files.
	close(transfer);
	close(tmp);

	//reopening files to add another information we had in file.
	//and make one more change.
	transfer = open(fname, O_RDONLY, S_IREAD);
	tmp = open(tmp_fname, O_WRONLY | O_APPEND | O_CREAT, S_IWRITE);


	if (transfer > 0 && tmp > 0) {
		struct user a;

		//reading before match ID number you are sending money to.
		while (eof(transfer) == 0) {
			memset(&a, 0, sizeof(struct user));
			read(transfer, &a, sizeof(struct user));
			if (strcmp(a.id_number, ID) == 0) {

				a.balance += amount;
				//writing changed info in the file.
				write(tmp, &a, sizeof(struct user));
			}
			else if (strcmp(a.password, password) == 0) {
				//we already changed this information above.
				continue;
			}
			else {
				//writing another info we had in file.
				write(tmp, &a, sizeof(struct user));
			}

		}
	}
	else {
		perror("open");
	}


	//closing files.
	close(transfer);
	close(tmp);



	//deleting old file.
	//giving old name to new file.
	remove("registeredusers.txt");
	rename("temp.txt", "registeredusers.txt");

}

void withdraw() {
	{

		//create filename holders.
		char fname[size] = "registeredusers.txt";
		char tmp_fname[size] = "temp.txt";

		//those variables we need to read and open files.
		int withdraw;
		int tmp;

		//recheck the password to be sure.
		char password[size];
		printf("Re-enter the password for security reasons\n");
		scanf("%s", password);

		//opening file where we have all users' information.
		withdraw = open(fname, O_RDONLY, S_IREAD);
		//opening file to change information about acc we are depositing to.
		tmp = open(tmp_fname, O_WRONLY | O_APPEND | O_CREAT, S_IWRITE);

		//check if both files open.
		if (deposit > 0 && tmp > 0) {
			struct user a;
			while (eof(deposit) == 0) {
				memset(&a, 0, sizeof(struct user));
				read(deposit, &a, sizeof(struct user));
				if (strcmp(a.password, password) == 0) {

					double amount;
					printf("Enter amount : ");
					scanf("%lf", &amount);
					a.balance -= amount;
					printf("Current Balance : %lf", a.balance);

					//writing the changed information of current user
					//in the temporary file
					write(tmp, &a, sizeof(struct user));

				}
				else {
					//we need to write in file all the user's information
					//that doesnt match the current user
					//to not to lose users.
					write(tmp, &a, sizeof(struct user));
				}
			}

		}
		else {
			perror("open");
		}


		//closing both opened files.
		close(withdraw);
		close(tmp);

		//change files to each other
		//your balance will be changed when you re-enter program.
		remove("registeredusers.txt");
		rename("temp.txt", "registeredusers.txt");

	}

}

void deposit() {

	//create filename holders.
	char fname[size] = "registeredusers.txt";
	char tmp_fname[size] = "temp.txt";

	//those variables we need to read and open files.
	int deposit;
	int tmp;

	//recheck the password to be sure.
	char password[size];
	printf("Re-enter the password for security reasons\n");
	scanf("%s", password);

	//opening file where we have all users' information.
	deposit = open(fname, O_RDONLY, S_IREAD);
	//opening file to change information about acc we are depositing to.
	tmp = open(tmp_fname, O_WRONLY | O_APPEND | O_CREAT, S_IWRITE);
	
	//check if both files open.
	if (deposit > 0 && tmp>0) {
		struct user a;
		while (eof(deposit) == 0) {
			memset(&a, 0, sizeof(struct user));
			read(deposit, &a, sizeof(struct user));
			if (strcmp(a.password,password)==0) {
				 
					double amount;
					printf("Enter amount : ");
					scanf("%lf", &amount);
					a.balance += amount;
					printf("Current Balance : %lf", a.balance);

					//writing the changed information of current user
					//in the temporary file
					write(tmp, &a, sizeof(struct user));
					
			}
			else {
				//we need to write in file all the user's information
				//that doesnt match the current user
				//to not to lose users.
				write(tmp, &a, sizeof(struct user));
			}
		}

	}
	else {
		perror("open");
	}


	//closing both opened files.
	close(deposit);
	close(tmp);

	//change files to each other
	//your balance will be changed when you re-enter program.
	remove("registeredusers.txt");
	rename("temp.txt", "registeredusers.txt");

}


void authorisize() {
	//create two variables for username and password.
	char username[size] = "";
	char password[size] = "";

	//variable to check the password
	bool psw = false;

	//the variable where we put an file name/address.
	char fname[size] = "registeredusers.txt";
	//A is a label to use if username/password is incorrect 
	//to give a user chance to try again.
	A:
	printf("Enter username : ");
	scanf("%s", username);
	printf("Enter password : ");
	scanf("%s", password);

	//variable that we need to open a file.
	int search;

	//opening file to read.
	search = open(fname, O_RDONLY, S_IREAD);
	if (search > 0) {
		//creating a struct variable to manipulate with.
		struct user a;
		while (eof(search)==0 && !psw) {
			//reading a file before end of the file
			memset(&a, 0, sizeof(struct user));
			read(search, &a, sizeof(struct user));
			
			//checking if the information matches to input.
			if(strstr(a.username,username)){


				//checking if the username and password
				//both are correct
			if ((strcmp(a.password, password) == 0) &&
				(strcmp(a.username, username) == 0)) {
				//
				psw = true;

				if (psw) {
					int inp;
					//printing some important account information.
					B:
					printf("Account owner : %s %s\n", a.name, a.last_name);
					printf("Account ID number : %s\n", a.id_number);
					printf("Account Balance : %lf\n", a.balance);
					printf("7.See more...\n");
					printf("9.Options.\n");
					scanf("%d", &inp);
					switch (inp) {
					case 7: {
							printf("Password : %s\n", password);
							printf("Birth Date :  %d:%d:%d\n", a.day, a.month, a.year);
							printf("Phone : %s\n", a.phone_number);
							
						int k;
						printf("9.Back to main page.\n");
						scanf("%d", &k);
						switch (k) {
						case 9: {
							goto B;
						}
						}

					}
						  break;
					case 9: {
						continue;
					}
					}

				}
			
			}
			else {
				printf("Username or Password you entered is incorrect!\n");
				printf("Try again!\n");
				goto A;
			}
		}
		}
	}
	else {
		perror("open");
	}

	close(search);
	//printing another operations
		//user can use with his/her account.
	if (psw) {
		int option;
		
		printf("   ***   OPTIONS   ***   \n");
		printf("1.Deposit.\n");
		printf("2.Withdraw.\n");
		printf("3.Transfer.\n");
		printf("0.Exit\n");
		scanf("%d", &option);
		switch (option) {
		case 1: {
			//function that helps us to deposit money on an acc.
			deposit();
		}
			  break;
		case 2: {
			withdraw();
		}
			  break;
		case 3: {
			transfer();
		}
			  break;
		case 0: {
			exit(0);
		}
		}
	}



}


void new_account() {

	int control= 0;
	char fname[size] = "registeredusers.txt";
	
	//variable to put an information in.
	struct user a;

	printf("     ***     CREATE NEW ACCOUNT     ***     \n\n");

	//asking user to put information to create an account.
	//and putting all these information in struct variable a.
	printf("Username : ");
	scanf("%s", a.username);
	printf("Password : ");
	scanf("%s", a.password);
	printf("Name : ");
	scanf("%s", a.name);
	printf("Last name : ");
	scanf("%s", a.last_name);
	printf("Birth Date \n");
	printf("Day : ");
	scanf("%d", &a.day);
	printf("Month : ");
	scanf("%d", &a.month);
	printf("Year : ");
	scanf("%d", &a.year);
	printf("Phone number : ");
	scanf("%s", a.phone_number);
	printf("ID Number : ");
	scanf("%s", a.id_number);

	printf("How much you'd like to deposit as your first deposit? : ");
	scanf("%lf", &a.balance);


	

	//the sign account has been created.
	printf("Congratulations,your account has been created.\n");




	//opening a file to write in.
	control = open(fname, O_WRONLY | O_APPEND | O_CREAT , S_IWRITE);
	if (control > 0) {
		//writing all the information in the file.
		write(control, &a, sizeof(struct user));
		close(control);
	}
	else {
		//in the way file didnt open,it prints a reason.
		perror("open");
	}

	//function that authorisizes you to log in in an account.
	authorisize();
}
