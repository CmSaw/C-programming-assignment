#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>

struct donation
{
	char supplyname[30];
	char supplycode[3];
	char donator[15];
	int shipment;
	float quantity;
};
struct dist
{
	char supplycode[30];
	float amount;
	char receiver[30];
};
struct donation D[5];
struct dist d[100];
int Dlength = 0, dlength = 0;
char stringcheck[100];

void main()
{
	void function1(), function2(), function3(), function4(), function5(), function6();
	FILE* Dfile;
	FILE* dfile;

	fopen_s(&Dfile, "donation", "r");
	if (Dfile != NULL)
	{
		while (fread(&D[Dlength], sizeof(struct donation), 1, Dfile)) //read donation file
		{
			Dlength++;
		}
		fclose(Dfile);
	}
	else printf("\ndonation file Not Found");
	fopen_s(&dfile, "dist", "r");
	if (dfile != NULL)
	{
		while (fread(&d[dlength], sizeof(struct dist), 1, dfile)) //read distribute file
		{
			dlength++;
		}
		fclose(dfile);
	}
	else printf("\ndistribute file Not Found"); _getch();

	int choice;
	do
	{
		choice = 0;
		system("cls");
		printf("\nCOVID-19 DONATION MANAGEMENT SYSTEM\n");
		printf("\n\t1.Create Inventory");
		printf("\n\t2.Update donation quantities");
		printf("\n\t3.Search donation");
		printf("\n\t4.List All Distribute Record");
		printf("\n\t5.List Inventory");
		printf("\n\t6.Save and Exit program");
		printf("\n\nEnter your choice:");
		scanf_s("%d", &choice); while (getchar() != '\n');

		if (choice == 1)
			function1();
		else if (choice == 2)
			function2();
		else if (choice == 3)
			function3();
		else if (choice == 4)
			function4();
		else if (choice == 5)
			function5();
		else if (choice == 6)
			function6();
		else
			printf("INVALID INPUT!"); _getch();
	} while (choice != 6);
}

void function1()
{
	char loop = 'y';
	do
	{
		if (Dlength >= 5)
		{
			printf("Inventory Full!");
			return;
		}
		printf("...................................");
		printf("\n Create Inventory\n");
		printf("Enter Name of Supply:");
		gets_s(stringcheck); while (getchar() != '\n');
		if (strlen(stringcheck) > 30)
		{
			printf("Too long!");
			return;
		}
		else strcpy_s(D[Dlength].supplyname, stringcheck);
		printf("Enter Supply Code:");
		gets_s(stringcheck); while (getchar() != '\n');
		if (strlen(stringcheck) > 3)
		{
			printf("Too long!");
			return;
		}
		else strcpy_s(D[Dlength].supplycode, stringcheck);
		printf("Enter Donator:");
		gets_s(stringcheck); while (getchar() != '\n');
		if (strlen(stringcheck) > 15)
		{
			printf("Too long!");
			return;
		}
		else strcpy_s(D[Dlength].donator, stringcheck);
		printf("Enter No. of Shipment:");
		int check = scanf_s(" %d", &D[Dlength].shipment); while (getchar() != '\n');
		if (check != 1 || D[Dlength].shipment <= 0)
		{
			printf("Please Enter Valid Number!");
			return;
		}
		printf("\nEnter Received Quantity (In million):");
		int check2 = scanf_s(" %f", &D[Dlength].quantity); while (getchar() != '\n');
		if (check2 != 1 || D[Dlength].quantity <= 0)
		{
			printf("Please Enter Valid Number!");
			return;
		}
		Dlength++;
		printf("\nRecord Updated!");
		printf("\nContinue? (y/n):");
		scanf_s(" %c", &loop); while (getchar() != '\n');
	} while (loop == 'y' || loop == 'Y');
}

void function2()
{
	int choice2, choice3;
	char code[3], receiver[30];
	float amount;
	printf("...................................");
	printf("\n Update donation quantities\n");
	printf("\n1.Receive Donation");
	printf("\n2.Distribute Donation");
	printf("\n3.Undo previous distribution");
	printf("\nEnter choice:");
	scanf_s("%d", &choice2); while (getchar() != '\n');


	if (choice2 == 1)
	{
		printf("Enter Supply Code:");
		gets_s(stringcheck); while (getchar() != '\n');
		if (strlen(stringcheck) > 3)
		{
			printf("Too long!");
			return;
		}
		else strcpy_s(code, stringcheck);
		printf("Enter Receive Amount (In million):");
		int check = scanf_s("%f", &amount); while (getchar() != '\n');
		if (check != 1 || amount <= 0)
		{
			printf("Please Enter Valid Number!");
			return;
		}
	}
	else if (choice2 == 2)
	{
		printf("Enter Supply Code:");
		gets_s(stringcheck); while (getchar() != '\n');
		if (strlen(stringcheck) > 3)
		{
			printf("Too long!");
			return;
		}
		else strcpy_s(code, stringcheck);
		printf("Enter Distribute Amount (In million):");
		int check = scanf_s("%f", &amount); while (getchar() != '\n');
		if (check != 1 || amount <= 0)
		{
			printf("Please Enter Valid Number!");
			return;
		}
		printf("\nEnter Receiver:");
		gets_s(stringcheck); while (getchar() != '\n');
		if (strlen(stringcheck) > 30)
		{
			printf("Too long!");
			return;
		}
		else strcpy_s(receiver, stringcheck);
		amount = -1 * amount;	//change amount to negative value for following subtraction
	}
	else if (choice2 == 3)
	{
		char confirmation;
		if (dlength == 0)
		{
			printf("There is no previous distribution");
			return;
		}
		for (int i = 0; i < dlength; i++)
		{
			printf("\n%d.  \tSupply Code:%s\tAmount:%.2fM\tReceiver:%s", i + 1, d[i].supplycode, d[i].amount, d[i].receiver);
		}
		printf("\n\nPlease Enter which record you want to delete:");
		int delchoice = scanf_s("%d", &choice3); while (getchar() != '\n');
		if (delchoice != 1 || delchoice <= 0 || choice3 > dlength)
		{
			printf("Please Enter Valid Number!");
			return;
		}
		choice3--;

		printf("Delete This Record? :");
		printf("\n\tSupply Code:%s\tAmount:%.2fM\tReceiver:%s", d[choice3].supplycode, d[choice3].amount, d[choice3].receiver);
		printf("\nYes(Y)/No(N):");
		scanf_s(" %c", &confirmation); while (getchar() != '\n');

		if (confirmation == 'y' || confirmation == 'Y')
		{
			for (int i = 0; i < Dlength; i++)
			{
				if (strcmp(d[choice3].supplycode, D[i].supplycode) == 0) //add back the distributed amount to inventory
				{
					D[i].quantity += d[choice3].amount;
				}
			}

			for (int i = choice3; i < dlength; i++) //use the next element in array to overwrite the current element
			{
				d[i] = d[i + 1];
			}
			dlength--;
			printf("\nRecord Updated!"); _getch();
		}
		return;

	}
	else
	{
		printf("INVALID INPUT!"); _getch();
		return;
	}

	int counter = 0;
	while (counter < Dlength)
	{
		if (strcmp(code, D[counter].supplycode) == 0)
		{
			if (D[counter].quantity + amount < 0)
			{
				printf("Out of Stock!");
				printf("\nStock left: %.2fM", D[counter].quantity); _getch();
				return;
			}
			else
			{
				D[counter].quantity += amount;
				if (choice2 == 2)
				{
					amount = -1 * amount;	//change back to positive value
					strcpy_s(d[dlength].supplycode, code);
					d[dlength].amount = amount;
					strcpy_s(d[dlength].receiver, receiver);
					dlength++;
				}
				printf("Record Updated!"); _getch();
				return;
			}
		}
		counter++;
	}
	printf("Supply Code Not Found"); _getch();
}

void function3()
{
	char search[3];
	int counter = 0;
	printf("...................................");
	printf("\n Search Donation\n");

	printf("Enter the supply code:");
	gets_s(stringcheck); while (getchar() != '\n');
	if (strlen(stringcheck) > 3)
	{
		printf("Too long!");
		return;
	}
	else strcpy_s(search, stringcheck);
	while (counter < Dlength)
	{
		if (strcmp(search, D[counter].supplycode) == 0) //find the same supplycode
		{
			printf("Supply Name:%s\tSupply Code:%s\tDonator:%s\tNo. of Shipment:%d\tQuantity:%.2fM", D[counter].supplyname, D[counter].supplycode, D[counter].donator, D[counter].shipment, D[counter].quantity);
			_getch();
			return;
		}
		counter++;
	}
	printf("Supply Code Not Found"); _getch();
}

void function4()
{
	struct dist swap; //declare dummy variable
	float CT = 0, HS = 0, FM = 0, SM = 0, OM = 0;
	printf("...................................");
	printf("\n List Distribute\n");

	for (int i = 0; i < dlength; i++)
	{
		for (int j = i; j < dlength; j++)
		{
			if (d[i].amount < d[j].amount)
			{
				swap.amount = d[i].amount;					//move smaller data to dummy
				strcpy_s(swap.supplycode, d[i].supplycode);
				strcpy_s(swap.receiver, d[i].receiver);
				d[i].amount = d[j].amount;					//move bigger data to smaller data
				strcpy_s(d[i].supplycode, d[j].supplycode);
				strcpy_s(d[i].receiver, d[j].receiver);
				d[j].amount = swap.amount;					//move dummy to bigger data
				strcpy_s(d[j].supplycode, swap.supplycode);
				strcpy_s(d[j].receiver, swap.receiver);
			}
		}
	}
	for (int i = 0; i < dlength; i++)
	{
		printf("\nSupply Code:%s\tAmount:%.2fM\tReceiver:%s", d[i].supplycode, d[i].amount, d[i].receiver);
		if (!strcmp(d[i].supplycode, "CT"))
		{
			CT += d[i].amount;
		}
		else if (!strcmp(d[i].supplycode, "HS"))
		{
			HS += d[i].amount;
		}
		else if (!strcmp(d[i].supplycode, "FM"))
		{
			FM += d[i].amount;
		}
		else if (!strcmp(d[i].supplycode, "SM"))
		{
			SM += d[i].amount;
		}
		else if (!strcmp(d[i].supplycode, "OM"))
		{
			OM += d[i].amount;
		}
	}
	printf("\n\nTotal Distributed:");
	printf("\n  Contactless Thermometer: %.2f millions", CT);
	printf("\n  Hand Sanitizers: %.2f millions", HS);
	printf("\n  Face Mask: %.2f millions", FM);
	printf("\n  Surgical Mask: %.2f millions", SM);
	printf("\n  Oxygen Mask: %.2f millions", OM);

	_getch();
}

void function5()
{
	printf("...................................");
	printf("\n List Donation\n");
	for (int i = 0; i < Dlength; i++)
	{
		printf("\nSupply Name:%s\tSupply Code:%s\tDonator:%s\tNo. of Shipment:%d\tQuantity:%.2fM", D[i].supplyname, D[i].supplycode, D[i].donator, D[i].shipment, D[i].quantity);
	}
}
void function6()
{
	FILE* Dfile2;
	FILE* dfile2;
	fopen_s(&Dfile2, "donation", "w");
	for (int i = 0; i < Dlength; i++) //save donation file
	{
		fwrite(&D[i], sizeof(struct donation), 1, Dfile2);
	}
	fclose(Dfile2);
	fopen_s(&dfile2, "dist", "w");
	for (int i = 0; i < dlength; i++) //save distribute file
	{
		fwrite(&d[i], sizeof(struct dist), 1, dfile2);
	}
	fclose(dfile2);
	if (fwrite != 0)
	{
		printf("files saved!"); _getch();
		exit;
	}
	else
	{
		printf("Error saving file!"); _getch();
		return;
	}
}