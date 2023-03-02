#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <termio.h> 
#include <time.h> 
static struct termios old, new; 
void initTermios(int echo) { 
  tcgetattr(0, &old);  
  new = old;  
  new.c_lflag &= ~ICANON;  
  new.c_lflag &= echo ? ECHO : ~ECHO;  
  tcsetattr(0, TCSANOW, &new);  
} 
void resetTermios(void) { tcsetattr(0, TCSANOW, &old); } 
char getch_(int echo) { 
  initTermios(echo); 
  char ch = getchar(); 
  resetTermios(); 
  return ch; 
} 
char getch(void) { return getch_(0); } 
char getche(void) {	return getch_(1); } 
typedef struct {int wg; char ws[7];} Game; 
void display(const Game *game, const char *guess){ 
	int wg=game->wg; 
        printf("\n\t Be aware you can be hanged!!.");
         //Ascii Art
        printf("       _                                             \n");
        printf("      | |                                            \n");
        printf("      | |__   __ _ _ __   __ _ _ __ ___   __ _ _ __  \n");
        printf("      | '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\ \n");
        printf("      | | | | (_| | | | | (_| | | | | | | (_| | | | | \n");
        printf("      |_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_| \n");
        printf("                          __/ |                      \n");
        printf("                         |___/  \n");
        printf("      ");
        printf("                coded by R3DHULK ");
	printf("\n\n\t Rules : ");
	printf("\n\t - Maximum 6 mistakes are allowed.");
	printf("\n\t - All alphabet are in lower case.");
	printf("\n\t - All words are name of very popular Websites. eg. Google");
	printf("\n\t - If you enjoy continue, otherwise close it.");

	printf("\033[H\033[J ┏━━━┓\n"); 
	printf(" ┃   │\n"); 
	printf(" ┃   %c\n",   wg<1?' ':'O'); 
	printf(" ┃  %c%s%c\n",wg<3?' ':'/', wg<2?" ":"│", wg<4?' ':'\\'); 
	printf(" ┃  %c %c\n", wg<5?' ':'/',               wg<6?' ':'\\'); 
	printf(" ┃\n"); 
	printf("┏┻━━━━━━┓\n┃       ┗━┓\n┗━━━━━━━━━┛\n"); 
	printf("wrong guesses %d: %s\n", wg, game->ws); 
	printf("word: %s\n",guess); 
} 
typedef struct{ size_t word, words, *index; char *buffer; } Buffer; 
Buffer readwords(const char *fn){ 
    char buffer[512]; 
    char *bp, *wi, *wl; 
    size_t size, elements, bytes, wlen=0, ilen, len; 
    FILE *stream, *tstream; 
	FILE *fp=fopen(fn, "r"); 
	stream=open_memstream(&bp, &size); 
    do { 
        bytes = fread(buffer, sizeof(char), sizeof buffer, fp); 
        fwrite(buffer, sizeof(char), bytes, stream); 
    } while (bytes == sizeof buffer && !feof(fp)); 
    fflush(stream); fclose(stream); 
	stream=open_memstream(&wi, &ilen); 
	tstream=open_memstream(&wl, &bytes); 
	for(char *tok=strtok(bp, "\n"); tok; tok=strtok(NULL, "\n")){ 
		len=strlen(tok); 
		if(len<3 || len>50) continue; // longest word in major dict  has 45 words, rest are chemicals 
		for(char *p=tok; *p; ++p){ 
			if(isalpha(*p)) *p=tolower(*p); 
			else goto next; 
		} 
		fwrite(&wlen, sizeof wlen, 1, stream); 
		wlen+=fprintf(tstream, "%s", tok); 
		fputc(0, tstream); 
		wlen++; 
next:; 
	} 
	fflush(tstream); fclose(tstream); 
	fflush(stream);  fclose(stream); 
	free(bp); 
	return (Buffer){.words=ilen/sizeof ilen, .index=(size_t *)wi, .buffer=wl}; 
} 
int shuffle(Buffer *buf){ 
	size_t rnd, tmp; 
	for(size_t i=buf->words-1; i>0; --i){ 
		rnd=rand()%i; 
		tmp=buf->index[rnd]; 
		buf->index[rnd]=buf->index[i]; 
		buf->index[i]=tmp; 
	} 
} 
int main(void){ 
	Buffer text=readwords("/usr/share/dict/words"); 
	Game game={0,{[0 ... 6] = 0}}; 
	int ch; 
	srand(time(NULL)); 
	shuffle(&text); 
	size_t word=0; 
	char *guess=NULL; 
	do{ 
		char *unknown=text.buffer+text.index[word]; 
		size_t len=strlen(unknown); 
		guess=realloc(guess, len+1); 
		for(int i=0; i<len; ++i) guess[i]='_'; 
		guess[len]=0; 
		do{ 
			display(&game, guess); 
			ch=getch(); 
			if(strchr(unknown, ch)) 
				for(size_t i=0; i<len; ++i){ if(ch==unknown[i]) guess[i]=ch; } 
			else if(!strchr(game.ws, ch)){ game.ws[game.wg++]=ch; } 
		}while(strcmp(unknown, guess) && ch!=('d' & 0x1f) && ch!=EOF && game.wg<6); 
		display(&game, unknown); 
		if(strcmp(unknown, guess)) printf("You lost.\n"); 
		else printf("You won! With %d misses.\n",game.wg); 
		if(ch==EOF || ch==('d' & 0x1f)) break; 
		printf("Try again (Y/n)? "); 
		ch=getch(); 
		game.wg=0; 
		for(size_t i=0; i<7; ++i) game.ws[i]=0; 
		++word; 
		word %= text.words; 
	}while(tolower(ch)!='n'); 
	printf("\ncoded by R3DHULK\n"); 
} 
