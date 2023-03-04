#include <stdio.h>
#include <string.h>

#define NUM_QUESTIONS 3
#define QUESTION_LENGTH 100
#define ANSWER_LENGTH 20

int main() {
    char questions[NUM_QUESTIONS][QUESTION_LENGTH] = {
        "What is the capital of France?",
        "What is the largest planet in our solar system?",
        "Who is r3dhulk?"
    };
    char answers[NUM_QUESTIONS][ANSWER_LENGTH] = {
        "Paris",
        "Jupiter",
        "Sumalya"
    };
    char userAnswer[ANSWER_LENGTH];
    int score = 0;

    printf("Welcome to the trivia game!\n");

    for (int i = 0; i < NUM_QUESTIONS; i++) {
        printf("\nQuestion %d: %s\n", i+1, questions[i]);
        printf("Enter your answer: ");
        scanf("%s", userAnswer);

        if (strcmp(userAnswer, answers[i]) == 0) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Incorrect. The correct answer is %s\n", answers[i]);
        }
    }

    printf("\nCongratulations, you finished the trivia game!\n");
    printf("Your final score is %d/%d\n", score, NUM_QUESTIONS);

    return 0;
}

