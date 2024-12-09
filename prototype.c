#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Song 
{
    char path[256];
    struct Song *prev;
    struct Song *next;
}Song;

Song* createNode(char *path) 
{
    Song *newSong = (Song *)malloc(sizeof(Song));
    strcpy(newSong->path, path);
    newSong->prev = NULL;
    newSong->next = NULL;
    return newSong;
}

Song* addSong(Song *head, char *path) 
{
    Song *newSong = createNode(path);
    if (head == NULL) 
    {
        return newSong;
    } 
    else 
    {
        Song *temp = head;
        while (temp->next != NULL) 
        {
            temp = temp->next;
        }
        temp->next = newSong;
        newSong->prev = temp;
        return head;
    }
}

void playSong(char *path) 
{
    printf("Attempting to play: %s\n", path);
    char command[512];

#ifdef _WIN32
    sprintf(command, "cmd /c start \"\" \"%s\"", path); 
#endif

    int result = system(command);
    if (result != 0) 
    {
        printf("Error: Could not play the file. Ensure the path is correct.\n");
    }
}

void playSelectedSong(Song *head, int songNumber) 
{
    if (head == NULL) 
    {
        printf("The playlist is empty!\n");
        return;
    }

    int index = 1;
    Song *temp = head;
    
    while (temp != NULL && index < songNumber) 
    {
        temp = temp->next;
        index++;
    }

    if (temp != NULL) 
    {
        playSong(temp->path);
    } 
    else 
    {
        printf("Invalid song number! Please try again.\n");
    }
}



Song* playNext(Song *current) 
{
    if (current && current->next) 
    {
        current = current->next;
        playSong(current->path);
    } 
    else 
    {
        printf("You are at the end of the playlist.\n");
    }
    return current;
}

Song* playPrevious(Song *current) 
{
    if (current && current->prev) 
    {
        current = current->prev;
        playSong(current->path);
    } 
    else 
    {
        printf("You are at the start of the playlist.\n");
    }
    return current;
}

void shufflePlay(Song *head) 
{
    if (head == NULL) 
    {
        printf("Playlist is empty!\n");
        return;
    }

    int count = 0;
    Song *temp = head;
    while (temp != NULL) 
    {
        count++;
        temp = temp->next;
    }

    srand(time(0));
    int randomIndex = rand() % count;
    temp = head;
    for (int i = 0; i < randomIndex; i++) 
    {
        temp = temp->next;
    }
    playSong(temp->path);
}

Song* loadSongsFromFile(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open the file: %s\n", filename);
        return NULL;
    }

    Song *head = NULL;
    char path[256];
    while (fgets(path, sizeof(path), file)) 
    {
        int len = strlen(path);
        if (len > 0 && path[len - 1] == '\n') 
        {
            path[len - 1] = '\0';
        }
        if (strstr(path, ".mp3") != NULL) 
        {
            head = addSong(head, path);
        } 
        else 
        {
            printf("Skipping non-mp3 file: %s\n", path);
        }
    }

    fclose(file);
    return head;
}

void displaySongs(Song *head) 
{
    printf("\nPlaylist:\n");
    Song *temp = head;
    int index = 1;
    while (temp != NULL) 
    {
        printf("%d. %s\n", index++, temp->path);
        temp = temp->next;
    }
}

Song* addSongByUser(Song *head) 
{
    char newSongPath[256];
    printf("Enter the full path of the new song (must be .mp3): ");

    while (getchar() != '\n');

    fgets(newSongPath, sizeof(newSongPath), stdin);
    
    newSongPath[strcspn(newSongPath, "\n")] = 0; 

    if (strstr(newSongPath, ".mp3") != NULL) 
    {
        head = addSong(head, newSongPath); 
        printf("Song added successfully!\n");

        FILE *file = fopen("songs.txt", "a");
        if (file == NULL) {
            printf("Error: Could not open songs.txt for appending.\n");
            return head;
        }

        fprintf(file, "%s\n", newSongPath);
        fclose(file);
    } 
    else 
    {
        printf("Invalid file format. Please add an mp3 file.\n");
    }
    return head;
}



Song* deleteSong(Song *head, int songNumber) 
{
    if (head == NULL) 
    {
        printf("The playlist is empty!\n");
        return head;
    }

    Song *temp = head;
    int index = 1;

    if (songNumber == 1) 
    {
        head = temp->next; 
        if (head != NULL)
            head->prev = NULL;
        free(temp);
        return head;
    }

    while (temp != NULL && index < songNumber) 
    {
        temp = temp->next;
        index++;
    }

    if (temp == NULL) 
    {
        printf("Invalid song number! No song found to delete.\n");
        return head;
    }

    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    free(temp);
    printf("Song deleted successfully.\n");

    return head;
}


int main() 
{
    Song *head = NULL;
    Song *current = NULL;
    int choice;
    int selectionNumber;
    const char *filename = "songs.txt";
    head = loadSongsFromFile(filename);
    current = head;
    if (head == NULL) 
    {
        printf("No valid .mp3 songs found in the playlist. Exiting...\n");
        return 0;
    }
    displaySongs(head);

    do {
        printf("\n1. Play Next\n2. Play Previous\n3. Play Selected Song\n4. Shuffle Play\n5. Display Playlist\n6. Add New Song\n7. Delete Song\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                current = playNext(current);
                break;
            case 2:
                current = playPrevious(current);
                break;
            case 3:
                printf("Enter the song number to play: ");
                scanf("%d", &selectionNumber);
                playSelectedSong(head, selectionNumber);
                break;
            case 4:
                shufflePlay(head);
                break;
            case 5:
                displaySongs(head);
                break;
            case 6:
                head = addSongByUser(head);
                break;
            case 7:
                printf("Enter the song number to delete: ");
                scanf("%d", &selectionNumber);
                head = deleteSong(head, selectionNumber);
                break;
            case 8 :
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    return 0;
}