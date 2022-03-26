#include <stdio.h>

const int mainFoodListSize = 10;
char* mainFoodList[] = {
	"Pizza",
	"Hamburger",
	"Hot Dog",
	"Fries",
	"Chips",
	"Soda",
	"Candy",
	"Ice Cream",
	"Coffee",
	"Tea"
};
int choiceCount = 5;
const int threshold = 6;

void printList(char *list[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d - %s\n", i + 1, list[i]);
	}
}

int arrayHasValue(int size, int* array, int value)
{
	for(int i = 0; i < size; i++)
		if(array[i] == value)
			return 1;
	return 0;
}

void selectFood(int participantCount, int* preference, int foodListSize)
{
	int selectedCount = 0;
	while(selectedCount < choiceCount)
	{
		printf("Choose your preferred food #%d: ", selectedCount + 1);
		int choice;
		scanf("%d", &choice);
		if(choice < 1 || choice > foodListSize)
		{
			printf("Food #%d doesn't exist, ", choice);
		}
		else if(arrayHasValue(choiceCount, preference, choice - 1))
		{
			printf("Same food can't be choosen again, ");
		}
		else
		{
			preference[selectedCount] = choice - 1;
			selectedCount++;
		}
	}
}

int main()
{
	int participantCount;
	printf("Enter the number of participants: ");
	scanf("%d", &participantCount);

	int preferences[participantCount][choiceCount];
	
	for(int i = 0; i < participantCount; i++)
	{
		for(int j = 0; j < choiceCount; j++)
			preferences[i][j] = -1;

		printf("Food List:\n");
		printList(mainFoodList, mainFoodListSize);
		printf("Participant #%d:\n", i + 1);
		selectFood(participantCount, preferences[i], mainFoodListSize);
	}

	int shortListSize = 0;
	char* shortList[mainFoodListSize];
	int scores[mainFoodListSize];
	for(int i = 0; i < mainFoodListSize; i++)
		scores[i] = 0;

	for(int i = 0; i < participantCount; i++)
	{
		for(int j = 0; j < choiceCount; j++)
		{
			int choice = preferences[i][j];
			int score = choiceCount - j;
			scores[choice] += score;
			if(scores[choice] > threshold)
			{
				shortList[shortListSize] = mainFoodList[choice];
				shortListSize++;
			}
		}
	}

	if(shortListSize == 0)
	{
		printf("You are eating at home/dorm today!");
	}
	else {
		printf("Second round of elimination, choose food from the new list:\n");
		int preferencesShort[participantCount][shortListSize];
		choiceCount = shortListSize;

		for(int i = 0; i < participantCount; i++)
		{
			for(int j = 0; j < shortListSize; j++)
				preferencesShort[i][j] = -1;

			printList(shortList, shortListSize);
			printf("Participant #%d:\n", i + 1);
			selectFood(participantCount, preferencesShort[i], shortListSize);
		}

		int scoresShort[mainFoodListSize];
		for(int i = 0; i < mainFoodListSize; i++)
			scoresShort[i] = 0;

		for(int i = 0; i < participantCount; i++)
		{
			for(int j = 0; j < choiceCount; j++)
			{
				int choice = preferencesShort[i][j];
				int score = choiceCount - j;
				scoresShort[choice] += score;
			}
		}

		int maxScore = 0;
		int maxScoreIndex = 0;
		for(int i = 0; i < shortListSize; i++)
		{
			if(scoresShort[i] > maxScore)
			{
				maxScore = scoresShort[i];
				maxScoreIndex = i;
			}
		}

		printf("You are eating %s today!", shortList[maxScoreIndex]);
	}
}
